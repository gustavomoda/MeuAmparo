#ifndef MEUAMPARO_POSITION_H
#define MEUAMPARO_POSITION_H

#include <stdbool.h>

#include "meuamparo/geofence.h"

/*
 * Fonte de posição do dispositivo. Na Waveshare, quem responde é o GNSS do SIM7670G,
 * pela UART do modem. Esse driver ainda não existe: sem a placa não há como testá-lo, e
 * o Wokwi não tem peça de GNSS.
 *
 * Até lá a função devolve uma coordenada fixa, a mesma que define o centro da área
 * segura. Consequência direta: no protótipo a saída da área segura nunca dispara. A
 * lógica do geofence está pronta e testada no core (test/test_geofence.c), mas não é
 * exercitada pelo firmware.
 */

bool ma_position_get(ma_geo_point_t *out);

/* Centro da área segura configurado para este dispositivo. */
ma_geo_point_t ma_position_home(void);

#endif /* MEUAMPARO_POSITION_H */
