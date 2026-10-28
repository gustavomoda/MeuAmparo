#include "mpu6050.h"

#include "esp_check.h"
#include "esp_log.h"
#include "i2c_bus.h"

#define MPU_ADDR          0x68
#define REG_PWR_MGMT_1    0x6B
#define REG_ACCEL_CONFIG  0x1C
#define REG_GYRO_CONFIG   0x1B
#define REG_ACCEL_XOUT_H  0x3B
#define REG_WHO_AM_I      0x75

/* Faixa de ±8 g: o impacto de uma queda passa fácil de 4 g, e a faixa padrão de ±2 g
 * cortaria justo o pico que o detector procura. */
#define ACCEL_FS_8G       0x10
#define ACCEL_LSB_PER_G   4096.0f

/* ±500 °/s cobre giro de corpo caindo sem saturar. */
#define GYRO_FS_500       0x08
#define GYRO_LSB_PER_DPS  65.5f

static const char *TAG = "mpu6050";

/* Falha de I2C na inicialização sai com a chamada que falhou no log, para o erro
 * apontar a linha e não só um código numérico. */
#define TRY(x) ESP_RETURN_ON_ERROR((x), TAG, "%s", #x)

static i2c_master_dev_handle_t dev;

static esp_err_t write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    return i2c_master_transmit(dev, buf, sizeof buf, 100);
}

static esp_err_t read_regs(uint8_t reg, uint8_t *out, size_t len)
{
    return i2c_master_transmit_receive(dev, &reg, 1, out, len, 100);
}

esp_err_t ma_mpu6050_init(void)
{
    i2c_master_bus_handle_t bus;
    TRY(ma_i2c_bus_get(&bus));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU_ADDR,
        .scl_speed_hz = 400000,
    };
    TRY(i2c_master_bus_add_device(bus, &dev_cfg, &dev));

    uint8_t who = 0;
    TRY(read_regs(REG_WHO_AM_I, &who, 1));
    if (who != MPU_ADDR) {
        ESP_LOGE(TAG, "WHO_AM_I=0x%02x, esperado 0x%02x", who, MPU_ADDR);
        return ESP_ERR_NOT_FOUND;
    }

    /* O MPU6050 liga dormindo; zerar PWR_MGMT_1 acorda com o oscilador interno. */
    TRY(write_reg(REG_PWR_MGMT_1, 0x00));
    TRY(write_reg(REG_ACCEL_CONFIG, ACCEL_FS_8G));
    TRY(write_reg(REG_GYRO_CONFIG, GYRO_FS_500));

    ESP_LOGI(TAG, "pronto: ±8 g, ±500 °/s");
    return ESP_OK;
}

static int16_t be16(const uint8_t *p)
{
    return (int16_t)((p[0] << 8) | p[1]);
}

esp_err_t ma_mpu6050_read(ma_imu_sample_t *out)
{
    /* Leitura em rajada dos 14 bytes: acelerômetro, temperatura e giroscópio saem do
     * mesmo instante, em vez de três leituras com o sensor atualizando no meio. */
    uint8_t raw[14];
    esp_err_t err = read_regs(REG_ACCEL_XOUT_H, raw, sizeof raw);
    if (err != ESP_OK) {
        return err;
    }
    out->ax = be16(&raw[0]) / ACCEL_LSB_PER_G;
    out->ay = be16(&raw[2]) / ACCEL_LSB_PER_G;
    out->az = be16(&raw[4]) / ACCEL_LSB_PER_G;
    out->gx = be16(&raw[8]) / GYRO_LSB_PER_DPS;
    out->gy = be16(&raw[10]) / GYRO_LSB_PER_DPS;
    out->gz = be16(&raw[12]) / GYRO_LSB_PER_DPS;
    return ESP_OK;
}
