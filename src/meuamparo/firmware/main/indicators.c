#include "indicators.h"

#include "board.h"
#include "driver/ledc.h"
#include "esp_check.h"

/* Buzzer passivo precisa de onda quadrada, não de nível alto. 2 kHz fica na faixa em que
 * o ouvido humano é mais sensível, o que importa para quem já ouve pouco. */
#define BUZZER_FREQ_HZ 2000
#define BUZZER_DUTY_ON (1 << 9)  /* 50% em resolução de 10 bits */

static const char *TAG = "indicators";

esp_err_t ma_indicators_init(void)
{
    gpio_config_t led = {
        .pin_bit_mask = 1ULL << MA_PIN_LED,
        .mode = GPIO_MODE_OUTPUT,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&led), TAG, "led");

    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = BUZZER_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_RETURN_ON_ERROR(ledc_timer_config(&timer), TAG, "ledc timer");

    ledc_channel_config_t ch = {
        .gpio_num = MA_PIN_BUZZER,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ESP_RETURN_ON_ERROR(ledc_channel_config(&ch), TAG, "ledc channel");

    ma_indicators_set(false, false);
    return ESP_OK;
}

void ma_indicators_set(bool led, bool buzzer)
{
    static bool last_buzzer = true;  /* força a primeira escrita */

    gpio_set_level(MA_PIN_LED, led);

    /* Só mexe no LEDC quando o estado muda: chamado a 50 Hz, reescrever o duty toda vez
     * reiniciaria o ciclo do PWM e deixaria o som picotado. */
    if (buzzer != last_buzzer) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, buzzer ? BUZZER_DUTY_ON : 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        last_buzzer = buzzer;
    }
}
