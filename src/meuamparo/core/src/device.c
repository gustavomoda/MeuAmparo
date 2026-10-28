#include "meuamparo/device.h"

ma_device_config_t ma_device_default_config(void)
{
    ma_device_config_t c = {
        .cancel_window_ms = 10000,
        .alarm_ms = 5000,
        .blink_ms = 250,
    };
    return c;
}

void ma_device_init(ma_device_t *d, const ma_device_config_t *cfg)
{
    d->cfg = *cfg;
    d->state = MA_DEV_MONITORING;
    d->t_state = 0;
    d->buzzer_in_alarm = false;
}

static void raise_alarm(ma_device_t *d, uint32_t t, ma_device_output_t *out, ma_alert_kind_t kind,
                        bool buzzer)
{
    d->state = MA_DEV_ALARM;
    d->t_state = t;
    d->buzzer_in_alarm = buzzer;
    out->send = true;
    out->kind = kind;
}

ma_device_output_t ma_device_step(ma_device_t *d, uint32_t t, ma_device_input_t in)
{
    ma_device_output_t out = {0};
    const uint32_t elapsed = t - d->t_state;

    switch (d->state) {
    case MA_DEV_MONITORING:
        /* Botão tem prioridade: se os dois chegam juntos, a pessoa pediu ajuda e está
         * consciente, então não faz sentido abrir janela de cancelamento. */
        if (in.button) {
            raise_alarm(d, t, &out, MA_ALERT_PANIC, true);
        } else if (in.fall) {
            if (d->cfg.cancel_window_ms == 0) {
                raise_alarm(d, t, &out, MA_ALERT_FALL, true);
            } else {
                d->state = MA_DEV_FALL_PENDING;
                d->t_state = t;
            }
        } else if (in.geofence_exit) {
            raise_alarm(d, t, &out, MA_ALERT_GEOFENCE, false);
        }
        break;

    case MA_DEV_FALL_PENDING:
        if (in.button) {
            d->state = MA_DEV_MONITORING;
            d->t_state = t;
            out.cancelled = true;
        } else if (elapsed >= d->cfg.cancel_window_ms) {
            raise_alarm(d, t, &out, MA_ALERT_FALL, true);
        }
        break;

    case MA_DEV_ALARM:
        /* Durante o aviso, um novo aperto vira novo pedido: quem aperta de novo quer
         * ajuda, e o cuidador precisa ver que a pessoa insistiu. */
        if (in.button) {
            raise_alarm(d, t, &out, MA_ALERT_PANIC, true);
        } else if (elapsed >= d->cfg.alarm_ms) {
            d->state = MA_DEV_MONITORING;
            d->t_state = t;
        }
        break;
    }

    /* A saída física deriva do estado depois da transição, para que a amostra do envio
     * já acenda o LED. */
    const uint32_t since = t - d->t_state;
    switch (d->state) {
    case MA_DEV_MONITORING:
        break;
    case MA_DEV_FALL_PENDING: {
        const bool on = ((since / d->cfg.blink_ms) % 2) == 0;
        out.led = on;
        out.buzzer = on;
        break;
    }
    case MA_DEV_ALARM:
        out.led = true;
        out.buzzer = d->buzzer_in_alarm;
        break;
    }
    return out;
}

const char *ma_alert_kind_name(ma_alert_kind_t k)
{
    switch (k) {
    case MA_ALERT_FALL: return "fall";
    case MA_ALERT_PANIC: return "panic";
    case MA_ALERT_GEOFENCE: return "geofence";
    }
    return "?";
}
