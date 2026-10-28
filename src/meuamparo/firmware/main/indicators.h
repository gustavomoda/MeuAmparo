#ifndef MEUAMPARO_INDICATORS_H
#define MEUAMPARO_INDICATORS_H

#include <stdbool.h>

#include "esp_err.h"

/* LED e buzzer. Quem decide quando ligar é a máquina de estados do core. */

esp_err_t ma_indicators_init(void);

void ma_indicators_set(bool led, bool buzzer);

#endif /* MEUAMPARO_INDICATORS_H */
