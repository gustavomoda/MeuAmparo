#ifndef MEUAMPARO_I2C_BUS_H
#define MEUAMPARO_I2C_BUS_H

#include "driver/i2c_master.h"
#include "esp_err.h"

/*
 * Barramento I2C único do dispositivo. O MPU6050 e o visor dividem os mesmos dois
 * pinos, cada um no seu endereço, então quem criar o barramento primeiro cria para
 * todos. Os dois drivers pedem o handle aqui em vez de cada um abrir o seu.
 */
esp_err_t ma_i2c_bus_get(i2c_master_bus_handle_t *out);

#endif /* MEUAMPARO_I2C_BUS_H */
