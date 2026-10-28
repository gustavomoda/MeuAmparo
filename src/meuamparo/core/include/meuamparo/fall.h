#ifndef MEUAMPARO_FALL_H
#define MEUAMPARO_FALL_H

#include <stdbool.h>
#include <stdint.h>

#include "meuamparo/types.h"

/*
 * Detector de queda por limiar, em três fases sobre a magnitude da aceleração:
 *
 *   1. queda livre: magnitude abaixo de freefall_g por pelo menos min_freefall_ms;
 *   2. impacto: pico acima de impact_g em até impact_window_ms depois da queda livre;
 *   3. imobilidade: passado settle_ms do impacto, a magnitude fica perto de 1 g por
 *      stillness_ms seguidos.
 *
 * A terceira fase é o que separa queda de pulo ou de sentar com força. Quem pula também
 * passa por queda livre e impacto, mas logo volta a se mexer. Quem cai e não consegue
 * levantar fica parado, e é essa pessoa que precisa do alerta.
 *
 * Os limiares são de partida, tirados da literatura de detecção por limiar. Só viram
 * números defendidos depois de medidos contra um dataset público de quedas.
 */

typedef struct {
    float freefall_g;           /* abaixo disso conta como queda livre */
    uint32_t min_freefall_ms;   /* descarta vale de um único ruído */
    float impact_g;             /* acima disso conta como impacto */
    uint32_t impact_window_ms;  /* tempo máximo entre o fim da queda livre e o impacto */
    uint32_t settle_ms;         /* ignora o rebote logo depois do impacto */
    uint32_t stillness_ms;      /* quanto tempo parado confirma a queda */
    float stillness_tol_g;      /* distância máxima de 1 g que ainda conta como parado */
} ma_fall_config_t;

typedef enum {
    MA_FALL_IDLE,
    MA_FALL_FREEFALL,
    MA_FALL_AWAIT_IMPACT,
    MA_FALL_SETTLE,
    MA_FALL_STILLNESS,
} ma_fall_phase_t;

typedef struct {
    ma_fall_config_t cfg;
    ma_fall_phase_t phase;
    uint32_t t_phase;  /* instante em que a fase atual começou */
} ma_fall_detector_t;

ma_fall_config_t ma_fall_default_config(void);

void ma_fall_init(ma_fall_detector_t *d, const ma_fall_config_t *cfg);

/*
 * Alimenta uma amostra. Devolve true uma única vez, na amostra que confirma a queda;
 * em seguida o detector volta a IDLE e já está pronto para a próxima.
 */
bool ma_fall_update(ma_fall_detector_t *d, const ma_imu_sample_t *s);

const char *ma_fall_phase_name(ma_fall_phase_t p);

#endif /* MEUAMPARO_FALL_H */
