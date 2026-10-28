#include "position.h"

/* Ponto ilustrativo no centro de Ribeirão Preto. Não é endereço de ninguém. */
static const ma_geo_point_t HOME = {-21.177500, -47.810300};

bool ma_position_get(ma_geo_point_t *out)
{
    *out = HOME;
    return true;
}

ma_geo_point_t ma_position_home(void)
{
    return HOME;
}
