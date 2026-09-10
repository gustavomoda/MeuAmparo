#ifndef MEUAMPARO_IMU_H
#define MEUAMPARO_IMU_H

#include "meuamparo/types.h"

/*
 * Magnitude do vetor de aceleração, em g.
 *
 * É a base da detecção de queda: em repouso o valor fica perto de 1 g (só a gravidade),
 * durante a queda livre cai para perto de 0, e no impacto contra o chão dispara para um
 * pico bem acima de 1. O algoritmo do passo 2 procura exatamente essa sequência.
 *
 * Usar a magnitude em vez dos eixos separados também resolve a orientação: não importa
 * como o dispositivo está preso na cintura ou no peito, o módulo do vetor é o mesmo.
 */
float ma_accel_magnitude(const ma_imu_sample_t *s);

#endif /* MEUAMPARO_IMU_H */
