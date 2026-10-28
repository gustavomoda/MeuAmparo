// Laço principal do MeuAmparo. Fino de propósito: lê sensor, botão e posição, entrega
// ao core e obedece ao que ele decidir. Nenhuma regra de queda ou de alerta mora aqui.

#include "board.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "indicators.h"
#include "meuamparo/alert.h"
#include "meuamparo/device.h"
#include "meuamparo/fall.h"
#include "meuamparo/geofence.h"
#include "meuamparo/imu.h"
#include "mpu6050.h"
#include "position.h"
#include "transport.h"

// 50 Hz é a taxa dos datasets públicos de queda (SisFall grava a 200 Hz e é comum
// reamostrar para 50). Mais rápido gasta bateria sem ganhar detecção.
#define MA_SAMPLE_PERIOD_MS 20

// Raio da área segura. 200 m cobre casa e quarteirão; o valor real vem do cuidador.
#define MA_GEOFENCE_RADIUS_M 200.0
#define MA_GEOFENCE_HYST_M   20.0

#define MA_DEVICE_ID "ma-01"

// Linha de telemetria no serial a cada tanto, para a apresentação mostrar o sensor vivo
// sem afogar o log a 50 linhas por segundo.
#define MA_TELEMETRY_EVERY_MS 2000

static const char *TAG = "meuamparo";

static uint32_t now_ms(void)
{
    return (uint32_t)(esp_timer_get_time() / 1000);
}

static void button_init(void)
{
    gpio_config_t btn = {
        .pin_bit_mask = 1ULL << MA_PIN_BUTTON,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&btn));
}

// Devolve true só na amostra em que o botão passa de solto para apertado. Ler a 50 Hz
// já filtra o repique mecânico, que dura poucos milissegundos.
static bool button_pressed_edge(void)
{
    static bool was_down = false;
    const bool down = gpio_get_level(MA_PIN_BUTTON) == 0;  // pull-up: apertado é nível 0
    const bool edge = down && !was_down;
    was_down = down;
    return edge;
}

static void send_alert(ma_alert_kind_t kind, uint32_t t)
{
    ma_alert_t a = {.device_id = MA_DEVICE_ID, .kind = kind, .t_ms = t};
    ma_position_get(&a.pos);

    char json[160];
    const int n = ma_alert_format(json, sizeof json, &a);
    if (n < 0 || (size_t)n >= sizeof json) {
        ESP_LOGE(TAG, "alerta não coube no buffer (%d bytes)", n);
        return;
    }
    ma_transport_send(json);
}

void app_main(void)
{
    ESP_ERROR_CHECK(ma_indicators_init());
    button_init();
    ESP_ERROR_CHECK(ma_mpu6050_init());

    ma_fall_detector_t fall;
    const ma_fall_config_t fall_cfg = ma_fall_default_config();
    ma_fall_init(&fall, &fall_cfg);

    ma_device_t dev;
    const ma_device_config_t dev_cfg = ma_device_default_config();
    ma_device_init(&dev, &dev_cfg);

    ma_geofence_t fence;
    ma_geofence_init(&fence, ma_position_home(), MA_GEOFENCE_RADIUS_M, MA_GEOFENCE_HYST_M);

    ESP_LOGI(TAG, "monitorando a %d Hz, janela de cancelamento de %lu ms",
             1000 / MA_SAMPLE_PERIOD_MS, (unsigned long)dev_cfg.cancel_window_ms);

    ma_fall_phase_t last_phase = fall.phase;
    ma_dev_state_t last_state = dev.state;
    uint32_t next_telemetry = 0;
    TickType_t wake = xTaskGetTickCount();

    while (1) {
        const uint32_t t = now_ms();

        ma_imu_sample_t s = {.t_ms = t};
        if (ma_mpu6050_read(&s) != ESP_OK) {
            ESP_LOGW(TAG, "falha na leitura do MPU6050");
            vTaskDelayUntil(&wake, pdMS_TO_TICKS(MA_SAMPLE_PERIOD_MS));
            continue;
        }

        ma_device_input_t in = {
            .fall = ma_fall_update(&fall, &s),
            .button = button_pressed_edge(),
        };
        ma_geo_point_t pos;
        if (ma_position_get(&pos)) {
            in.geofence_exit = ma_geofence_update(&fence, &pos);
        }

        const ma_device_output_t out = ma_device_step(&dev, t, in);
        ma_indicators_set(out.led, out.buzzer);

        if (fall.phase != last_phase) {
            ESP_LOGI(TAG, "queda: %s -> %s (|a|=%.2f g)", ma_fall_phase_name(last_phase),
                     ma_fall_phase_name(fall.phase), ma_accel_magnitude(&s));
            last_phase = fall.phase;
        }
        if (in.fall) {
            ESP_LOGW(TAG, "queda confirmada: aperte o botão em até %lu s para cancelar",
                     (unsigned long)(dev_cfg.cancel_window_ms / 1000));
        }
        if (out.cancelled) {
            ESP_LOGI(TAG, "alerta de queda cancelado pela pessoa");
        }
        if (out.send) {
            send_alert(out.kind, t);
        }
        if (dev.state != last_state) {
            static const char *names[] = {"monitorando", "queda pendente", "alarme"};
            ESP_LOGI(TAG, "estado: %s", names[dev.state]);
            last_state = dev.state;
        }
        if (t >= next_telemetry) {
            ESP_LOGI(TAG, "a=(%.2f, %.2f, %.2f) |a|=%.2f g", s.ax, s.ay, s.az,
                     ma_accel_magnitude(&s));
            next_telemetry = t + MA_TELEMETRY_EVERY_MS;
        }

        vTaskDelayUntil(&wake, pdMS_TO_TICKS(MA_SAMPLE_PERIOD_MS));
    }
}
