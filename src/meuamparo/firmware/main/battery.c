#include "battery.h"

#include "board.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_check.h"

static const char *TAG = "battery";
static adc_oneshot_unit_handle_t adc;

esp_err_t ma_battery_init(void)
{
    adc_oneshot_unit_init_cfg_t unit = {.unit_id = ADC_UNIT_1};
    ESP_RETURN_ON_ERROR(adc_oneshot_new_unit(&unit, &adc), TAG, "unidade ADC");

    /* 12 dB de atenuação cobre até ~3,1 V no pino, a faixa toda do divisor. */
    adc_oneshot_chan_cfg_t chan = {.atten = ADC_ATTEN_DB_12, .bitwidth = ADC_BITWIDTH_12};
    return adc_oneshot_config_channel(adc, MA_ADC_BATTERY, &chan);
}

int ma_battery_percent(void)
{
    int raw = 0;
    if (adc == NULL || adc_oneshot_read(adc, MA_ADC_BATTERY, &raw) != ESP_OK) {
        return -1;
    }
    return raw * 100 / 4095;
}
