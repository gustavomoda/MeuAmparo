#include "ma_test.h"
#include "meuamparo/geofence.h"

/* Centro de referência em Ribeirão Preto. Coordenada ilustrativa, não é endereço de
 * nenhuma pessoa nem da instituição parceira. */
static const ma_geo_point_t CENTER = {-21.1775, -47.8103};

/* Desloca para o norte: 1 grau de latitude tem ~111,2 km em qualquer ponto. */
static ma_geo_point_t north(double meters)
{
    ma_geo_point_t p = {CENTER.lat + meters / 111195.0, CENTER.lon};
    return p;
}

static void test_distance(void)
{
    MA_CHECK_NEAR(ma_geo_distance_m(&CENTER, &CENTER), 0.0, 1e-6);

    ma_geo_point_t p = north(100.0);
    MA_CHECK_NEAR(ma_geo_distance_m(&CENTER, &p), 100.0, 0.5);

    /* Ribeirão Preto até a Praça da Sé: 290,3 km em linha reta, conferido com a mesma
     * fórmula calculada à parte em Python. A tolerância cobre só arredondamento. */
    ma_geo_point_t sp = {-23.5505, -46.6333};
    MA_CHECK_NEAR(ma_geo_distance_m(&CENTER, &sp), 290294.0, 5.0);
}

static void test_exit_fires_once(void)
{
    ma_geofence_t g;
    ma_geofence_init(&g, CENTER, 200.0, 20.0);

    int alerts = 0;
    for (double m = 0; m <= 400; m += 10) {
        ma_geo_point_t p = north(m);
        alerts += ma_geofence_update(&g, &p);
    }
    MA_CHECK(alerts == 1);
    MA_CHECK(g.outside);
}

static void test_border_jitter_does_not_repeat(void)
{
    ma_geofence_t g;
    ma_geofence_init(&g, CENTER, 200.0, 20.0);

    /* GNSS oscilando ±8 m em volta da borda: um alerta só. */
    int alerts = 0;
    for (int i = 0; i < 100; i++) {
        ma_geo_point_t p = north(200.0 + (i % 2 ? 8.0 : -8.0));
        alerts += ma_geofence_update(&g, &p);
    }
    MA_CHECK(alerts == 1);
}

static void test_rearms_after_return(void)
{
    ma_geofence_t g;
    ma_geofence_init(&g, CENTER, 200.0, 20.0);

    ma_geo_point_t out = north(300.0), back = north(100.0);
    MA_CHECK(ma_geofence_update(&g, &out));
    MA_CHECK(!ma_geofence_update(&g, &back));
    MA_CHECK(!g.outside);
    MA_CHECK(ma_geofence_update(&g, &out));
}

int main(void)
{
    test_distance();
    test_exit_fires_once();
    test_border_jitter_does_not_repeat();
    test_rearms_after_return();
    MA_REPORT();
}
