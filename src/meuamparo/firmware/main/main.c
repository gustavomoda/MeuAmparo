// Demo mínima: pisca o LED de status. Serve para provar a cadeia inteira antes de
// existir sensor ou alerta — ESP-IDF compila, binário sobe no Wokwi, pino responde.
// Quando o detector de queda entrar, este LED vira o indicador de alerta.

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// GPIO2 no devkit ESP32-S3 e no diagrama do Wokwi. A placa definitiva ainda está
// em aberto na documentação, então o pino vive aqui e não espalhado pelo código.
#define MA_LED_GPIO GPIO_NUM_2

// Meio segundo aceso, meio apagado: rápido o bastante para ver na apresentação,
// lento o bastante para contar no vídeo.
#define MA_BLINK_PERIOD_MS 500

static const char *TAG = "meuamparo";

void app_main(void)
{
    gpio_config_t led = {
        .pin_bit_mask = 1ULL << MA_LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&led));

    ESP_LOGI(TAG, "demo do LED iniciada no GPIO%d", MA_LED_GPIO);

    int level = 0;
    while (1) {
        level = !level;
        gpio_set_level(MA_LED_GPIO, level);
        ESP_LOGI(TAG, "led=%d", level);
        vTaskDelay(pdMS_TO_TICKS(MA_BLINK_PERIOD_MS));
    }
}
