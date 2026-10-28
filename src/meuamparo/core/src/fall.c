#include "meuamparo/fall.h"

#include <math.h>

#include "meuamparo/imu.h"

ma_fall_config_t ma_fall_default_config(void)
{
    ma_fall_config_t c = {
        .freefall_g = 0.5f,
        .min_freefall_ms = 60,
        .impact_g = 2.5f,
        .impact_window_ms = 1000,
        .settle_ms = 500,
        .stillness_ms = 1500,
        .stillness_tol_g = 0.3f,
    };
    return c;
}

void ma_fall_init(ma_fall_detector_t *d, const ma_fall_config_t *cfg)
{
    d->cfg = *cfg;
    d->phase = MA_FALL_IDLE;
    d->t_phase = 0;
}

static void enter(ma_fall_detector_t *d, ma_fall_phase_t p, uint32_t t)
{
    d->phase = p;
    d->t_phase = t;
}

bool ma_fall_update(ma_fall_detector_t *d, const ma_imu_sample_t *s)
{
    const ma_fall_config_t *c = &d->cfg;
    const float mag = ma_accel_magnitude(s);
    const uint32_t t = s->t_ms;
    const uint32_t elapsed = t - d->t_phase;

    switch (d->phase) {
    case MA_FALL_IDLE:
        if (mag < c->freefall_g) {
            enter(d, MA_FALL_FREEFALL, t);
        }
        return false;

    case MA_FALL_FREEFALL:
        if (mag < c->freefall_g) {
            return false;
        }
        if (elapsed < c->min_freefall_ms) {
            enter(d, MA_FALL_IDLE, t);
            return false;
        }
        /* A amostra que encerra a queda livre pode já ser o impacto: numa queda curta,
         * a 50 Hz, não há garantia de amostra intermediária entre o vale e o pico. */
        if (mag >= c->impact_g) {
            enter(d, MA_FALL_SETTLE, t);
        } else {
            enter(d, MA_FALL_AWAIT_IMPACT, t);
        }
        return false;

    case MA_FALL_AWAIT_IMPACT:
        if (mag >= c->impact_g) {
            enter(d, MA_FALL_SETTLE, t);
        } else if (elapsed > c->impact_window_ms) {
            enter(d, MA_FALL_IDLE, t);
        }
        return false;

    case MA_FALL_SETTLE:
        if (elapsed >= c->settle_ms) {
            enter(d, MA_FALL_STILLNESS, t);
        }
        return false;

    case MA_FALL_STILLNESS:
        /* Qualquer movimento cancela: a pessoa levantou ou nunca caiu de fato. */
        if (fabsf(mag - 1.0f) > c->stillness_tol_g) {
            enter(d, MA_FALL_IDLE, t);
            return false;
        }
        if (elapsed >= c->stillness_ms) {
            enter(d, MA_FALL_IDLE, t);
            return true;
        }
        return false;
    }
    return false;
}

const char *ma_fall_phase_name(ma_fall_phase_t p)
{
    switch (p) {
    case MA_FALL_IDLE: return "idle";
    case MA_FALL_FREEFALL: return "freefall";
    case MA_FALL_AWAIT_IMPACT: return "await_impact";
    case MA_FALL_SETTLE: return "settle";
    case MA_FALL_STILLNESS: return "stillness";
    }
    return "?";
}
