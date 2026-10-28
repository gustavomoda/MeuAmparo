// Laço principal do MeuAmparo. Fino de propósito: lê sensor, botão e posição, entrega
// ao core e obedece ao que ele decidir. Nenhuma regra de queda ou de alerta mora aqui.

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "battery.h"
#include "board.h"
#include "display.h"
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

// Atualização do visor: rápida o bastante para o |a| parecer ao vivo, lenta o bastante
// para não disputar o I2C com o sensor.
#define MA_SCREEN_EVERY_MS 200

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

// Hora mostrada no visor. Na placa ela viria do GNSS ou da rede 4G; na simulação não há
// nenhum dos dois, então parte da hora em que o firmware foi compilado e soma o tempo
// desde o boot. Serve para a tela, nunca para o alerta, que usa t_ms.
static void clock_text(char *out, size_t size, uint32_t t_ms)
{
    const int built = ((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0')) * 60 +
                      (__TIME__[3] - '0') * 10 + (__TIME__[4] - '0');
    const int minutes = (built + (int)(t_ms / 60000)) % (24 * 60);
    snprintf(out, size, "%02d:%02d", minutes / 60, minutes % 60);
}

// O que o visor mostra agora. Os textos ficam em buffers para comparar com o último
// quadro desenhado: só se manda 1 KB pelo I2C quando algo mudou, porque o barramento é
// o mesmo da leitura do sensor.
typedef struct {
    char clock[12];
    int battery;
    char title[12];
    char line1[24];
    char line2[24];
    bool smile;
    bool alert;
} screen_t;

static void compose(screen_t *sc, const ma_device_t *dev, const ma_device_config_t *cfg,
                    uint32_t t, bool cancelled, ma_alert_kind_t kind)
{
    static const char *sent[] = {"Enviado: queda", "Enviado: ajuda", "Enviado: area segura"};

    memset(sc, 0, sizeof *sc);
    clock_text(sc->clock, sizeof sc->clock, t);
    sc->battery = ma_battery_percent();

    if (cancelled) {
        snprintf(sc->title, sizeof sc->title, "Cancelado");
        snprintf(sc->line1, sizeof sc->line1, "Alerta de queda");
        snprintf(sc->line2, sizeof sc->line2, "cancelado pela pessoa");
    } else if (dev->state == MA_DEV_FALL_PENDING) {
        const uint32_t left = cfg->cancel_window_ms - (t - dev->t_state);
        sc->alert = true;
        snprintf(sc->title, sizeof sc->title, "QUEDA?");
        snprintf(sc->line1, sizeof sc->line1, "Aperte o botao");
        // A janela é de segundos; o int limita o texto a "para cancelar: 10 s".
        snprintf(sc->line2, sizeof sc->line2, "para cancelar: %d s", (int)((left + 999) / 1000) % 100);
    } else if (dev->state == MA_DEV_ALARM) {
        sc->alert = true;
        snprintf(sc->title, sizeof sc->title, "ALERTA");
        snprintf(sc->line1, sizeof sc->line1, "%s", sent[kind]);
        snprintf(sc->line2, sizeof sc->line2, "com a posicao");
    } else {
        sc->smile = true;
    }
}

// Faixa no serial para quem assiste à demonstração: o log técnico continua igual, e o
// que importa salta aos olhos no meio dele.
static void banner(const char *title, const char *detail)
{
    printf("\n==========  %s  ==========\n", title);
    if (detail != NULL) {
        printf("%s\n", detail);
    }
    printf("\n");
    fflush(stdout);
}

// Narra cada fase do detector em português, para a plateia acompanhar a queda.
static void narrate_phase(ma_fall_phase_t from, ma_fall_phase_t to, float mag)
{
    char detail[80];
    if (to == MA_FALL_FREEFALL) {
        snprintf(detail, sizeof detail, "|a| = %.2f g: o sensor quase nao sente a gravidade", mag);
        banner("FASE 1 DE 3: QUEDA LIVRE", detail);
    } else if (to == MA_FALL_SETTLE) {
        snprintf(detail, sizeof detail, "pico de %.2f g contra o chao", mag);
        banner("FASE 2 DE 3: IMPACTO", detail);
    } else if (to == MA_FALL_STILLNESS) {
        banner("FASE 3 DE 3: PESSOA PARADA, DEITADA", "conferindo se continua parada por 1,5 s");
    } else if (to == MA_FALL_IDLE && from == MA_FALL_FREEFALL) {
        banner("NAO E QUEDA", "queda livre curta demais (menos de 60 ms): tratada como ruido");
    } else if (to == MA_FALL_IDLE && from == MA_FALL_AWAIT_IMPACT) {
        banner("NAO E QUEDA", "nenhum impacto de 2,5 g em ate 1 s depois da queda livre");
    } else if (to == MA_FALL_IDLE && from == MA_FALL_STILLNESS && fabsf(mag - 1.0f) > 0.3f) {
        banner("NAO E QUEDA", "a pessoa voltou a se mexer: sem alerta");
    }
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
    // Sem visor o dispositivo continua protegendo: LED, buzzer e alerta não dependem
    // dele. Por isso a falha vira aviso no log, e não parada.
    if (ma_display_init() != ESP_OK) {
        ESP_LOGW(TAG, "visor não respondeu, seguindo sem ele");
    }
    if (ma_battery_init() != ESP_OK) {
        ESP_LOGW(TAG, "leitura da bateria indisponível");
    }

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
    screen_t shown;
    memset(&shown, 0xFF, sizeof shown);  // força o primeiro desenho
    uint32_t next_screen = 0;
    uint32_t cancelled_until = 0;
    ma_alert_kind_t last_kind = MA_ALERT_FALL;
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
            narrate_phase(last_phase, fall.phase, ma_accel_magnitude(&s));
            ESP_LOGI(TAG, "queda: %s -> %s (|a|=%.2f g)", ma_fall_phase_name(last_phase),
                     ma_fall_phase_name(fall.phase), ma_accel_magnitude(&s));
            last_phase = fall.phase;
        }
        if (in.fall) {
            banner("QUEDA DETECTADA", "LED e buzzer piscando: a pessoa tem 10 s para cancelar no botao");
            ESP_LOGW(TAG, "queda confirmada: aperte o botão em até %lu s para cancelar",
                     (unsigned long)(dev_cfg.cancel_window_ms / 1000));
        }
        if (out.cancelled) {
            ESP_LOGI(TAG, "alerta de queda cancelado pela pessoa");
        }
        if (out.cancelled) {
            banner("ALERTA CANCELADO", "a pessoa apertou o botao: esta bem");
            cancelled_until = t + 2000;  // tempo para a pessoa ler que deu certo
        }
        if (out.send) {
            last_kind = out.kind;
        }

        // Redesenha no máximo 5 vezes por segundo, e só se o quadro mudou.
        if (t >= next_screen) {
            screen_t sc;
            compose(&sc, &dev, &dev_cfg, t, t < cancelled_until, last_kind);
            if (memcmp(&sc, &shown, sizeof sc) != 0) {
                const ma_display_frame_t frame = {
                    .clock = sc.clock, .battery_pct = sc.battery, .title = sc.title,
                    .line1 = sc.line1, .line2 = sc.line2, .smile = sc.smile, .alert = sc.alert,
                };
                ma_display_draw(&frame);
                shown = sc;
            }
            next_screen = t + MA_SCREEN_EVERY_MS;
        }

        if (out.send) {
            static const char *what[] = {"ALERTA ENVIADO: QUEDA", "ALERTA ENVIADO: PEDIDO DE AJUDA",
                                         "ALERTA ENVIADO: SAIU DA AREA SEGURA"};
            banner(what[out.kind], "mensagem com tipo, hora e posicao:");
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
