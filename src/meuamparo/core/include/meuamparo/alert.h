#ifndef MEUAMPARO_ALERT_H
#define MEUAMPARO_ALERT_H

#include <stddef.h>
#include <stdint.h>

#include "meuamparo/device.h"
#include "meuamparo/geofence.h"

/*
 * Mensagem de alerta em JSON de uma linha. O formato mora no core, e não no firmware,
 * para ser o mesmo qualquer que seja o transporte: hoje a linha sai no serial da
 * simulação, na placa sairia pelo modem 4G. Quem recebe não precisa saber a diferença.
 *
 * Exemplo:
 *   {"device":"ma-01","kind":"fall","t_ms":12840,"lat":-21.199300,"lon":-47.792300}
 *
 * Seis casas decimais de grau dão cerca de 11 cm, bem abaixo da precisão do GNSS.
 */

typedef struct {
    const char *device_id;
    ma_alert_kind_t kind;
    uint32_t t_ms;
    ma_geo_point_t pos;
} ma_alert_t;

/* Mesmo contrato do snprintf: devolve o tamanho que a mensagem teria. Se for maior ou
 * igual a size, a mensagem foi cortada e não deve ser enviada. */
int ma_alert_format(char *buf, size_t size, const ma_alert_t *a);

#endif /* MEUAMPARO_ALERT_H */
