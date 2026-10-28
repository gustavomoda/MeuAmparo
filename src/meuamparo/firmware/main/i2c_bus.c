#include "i2c_bus.h"

#include "board.h"

static i2c_master_bus_handle_t bus;

esp_err_t ma_i2c_bus_get(i2c_master_bus_handle_t *out)
{
    if (bus == NULL) {
        i2c_master_bus_config_t cfg = {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = MA_PIN_I2C_SDA,
            .scl_io_num = MA_PIN_I2C_SCL,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .flags.enable_internal_pullup = true,
        };
        esp_err_t err = i2c_new_master_bus(&cfg, &bus);
        if (err != ESP_OK) {
            return err;
        }
    }
    *out = bus;
    return ESP_OK;
}
