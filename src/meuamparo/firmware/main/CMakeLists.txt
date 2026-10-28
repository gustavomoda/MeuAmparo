# transport_serial.c é o transporte da simulação. Na placa, troca-se por um
# transport_modem.c com o mesmo contrato de transport.h.
idf_component_register(SRCS "main.c" "i2c_bus.c" "mpu6050.c" "display.c" "battery.c" "indicators.c"
                            "position.c" "transport_serial.c"
                       INCLUDE_DIRS "."
                       REQUIRES meuamparo_core esp_driver_gpio esp_driver_i2c
                                esp_driver_ledc esp_lcd esp_adc esp_timer)
