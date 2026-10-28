#ifndef MEUAMPARO_BOARD_H
#define MEUAMPARO_BOARD_H

#include "driver/gpio.h"
#include "hal/adc_types.h"

/*
 * Pinagem do protótipo, igual à do simulator/wokwi/diagram.json. Mudou aqui, muda lá.
 *
 * Os pinos são do devkit ESP32-S3 do Wokwi. Na Waveshare ESP32-S3-SIM7670G parte deles
 * já está ocupada pelo modem e pelo GNSS, então a pinagem precisa ser revista com o
 * esquemático da placa antes de qualquer montagem física.
 */
#define MA_PIN_LED      GPIO_NUM_2
#define MA_PIN_BUTTON   GPIO_NUM_4
#define MA_PIN_BUZZER   GPIO_NUM_5
#define MA_PIN_I2C_SDA  GPIO_NUM_8
#define MA_PIN_I2C_SCL  GPIO_NUM_9

/* GPIO1 é o canal 0 do ADC1 no ESP32-S3. No Wokwi, ligado a um potenciômetro que faz
 * o papel da tensão da bateria. */
#define MA_PIN_BATTERY  GPIO_NUM_1
#define MA_ADC_BATTERY  ADC_CHANNEL_0

#endif /* MEUAMPARO_BOARD_H */
