#ifndef MEUAMPARO_MPU6050_H
#define MEUAMPARO_MPU6050_H

#include "esp_err.h"
#include "meuamparo/types.h"

/*
 * Driver mínimo do MPU6050 por I2C. Entrega a amostra já em g e graus/s, que é o que o
 * core espera: a conversão de registrador bruto para unidade física acaba aqui.
 */

esp_err_t ma_mpu6050_init(void);

/* Preenche tudo menos t_ms, que é responsabilidade de quem chama. */
esp_err_t ma_mpu6050_read(ma_imu_sample_t *out);

#endif /* MEUAMPARO_MPU6050_H */
