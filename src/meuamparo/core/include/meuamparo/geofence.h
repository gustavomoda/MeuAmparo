#ifndef MEUAMPARO_GEOFENCE_H
#define MEUAMPARO_GEOFENCE_H

#include <stdbool.h>

/*
 * Área segura circular: um centro e um raio em metros, configurados pelo cuidador.
 *
 * Círculo em vez de polígono porque é o que dá para configurar em menos de 15 minutos,
 * que é uma das metas: o cuidador marca a casa no mapa e escolhe o raio.
 */

typedef struct {
    double lat, lon;  /* graus decimais, WGS84, como o GNSS entrega */
} ma_geo_point_t;

typedef struct {
    ma_geo_point_t center;
    double radius_m;
    double hysteresis_m;  /* margem para voltar a contar como dentro */
    bool outside;
} ma_geofence_t;

/* Distância em metros pela fórmula de haversine. O erro de tratar a Terra como esfera
 * fica abaixo de 0,5%, desprezível perto do erro de um GNSS de pulso. */
double ma_geo_distance_m(const ma_geo_point_t *a, const ma_geo_point_t *b);

void ma_geofence_init(ma_geofence_t *g, ma_geo_point_t center, double radius_m,
                      double hysteresis_m);

/*
 * Devolve true só na posição que cruza de dentro para fora. Ficar fora não repete o
 * alerta. Para rearmar, a pessoa precisa voltar para dentro do raio menos a histerese:
 * sem essa margem, o ruído do GNSS na borda geraria um alerta a cada poucos segundos.
 */
bool ma_geofence_update(ma_geofence_t *g, const ma_geo_point_t *p);

#endif /* MEUAMPARO_GEOFENCE_H */
