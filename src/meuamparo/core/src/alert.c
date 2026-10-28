#include "meuamparo/alert.h"

#include <stdio.h>

int ma_alert_format(char *buf, size_t size, const ma_alert_t *a)
{
    return snprintf(buf, size,
                    "{\"device\":\"%s\",\"kind\":\"%s\",\"t_ms\":%lu,\"lat\":%.6f,\"lon\":%.6f}",
                    a->device_id, ma_alert_kind_name(a->kind), (unsigned long)a->t_ms,
                    a->pos.lat, a->pos.lon);
}
