#ifndef MEUAMPARO_BATTERY_H
#define MEUAMPARO_BATTERY_H

#include "esp_err.h"

/*
 * Carga da bateria em porcentagem, lida por ADC. Na placa, a tensão da 18650 chega ao
 * pino por um divisor resistivo e a faixa útil vai de 3,0 V (vazia) a 4,2 V (cheia).
 * Na simulação não existe bateria: um potenciômetro no mesmo pino faz o papel da
 * tensão, e a conversão abaixo trata a faixa inteira do ADC como 0 a 100%. A curva
 * real da 18650 não é linear e precisa ser calibrada com a placa.
 */

esp_err_t ma_battery_init(void);

/* Devolve -1 se a leitura falhar, para o visor esconder o indicador. */
int ma_battery_percent(void);

#endif /* MEUAMPARO_BATTERY_H */
