#include "meuamparo/geofence.h"

#include <math.h>

#define MA_EARTH_RADIUS_M 6371000.0
#define MA_PI 3.14159265358979323846

static double rad(double deg)
{
    return deg * MA_PI / 180.0;
}

double ma_geo_distance_m(const ma_geo_point_t *a, const ma_geo_point_t *b)
{
    const double dlat = rad(b->lat - a->lat);
    const double dlon = rad(b->lon - a->lon);
    const double h = sin(dlat / 2) * sin(dlat / 2) +
                     cos(rad(a->lat)) * cos(rad(b->lat)) * sin(dlon / 2) * sin(dlon / 2);
    return 2.0 * MA_EARTH_RADIUS_M * asin(sqrt(h));
}

void ma_geofence_init(ma_geofence_t *g, ma_geo_point_t center, double radius_m,
                      double hysteresis_m)
{
    g->center = center;
    g->radius_m = radius_m;
    g->hysteresis_m = hysteresis_m;
    g->outside = false;
}

bool ma_geofence_update(ma_geofence_t *g, const ma_geo_point_t *p)
{
    const double d = ma_geo_distance_m(&g->center, p);

    if (!g->outside && d > g->radius_m) {
        g->outside = true;
        return true;
    }
    if (g->outside && d < g->radius_m - g->hysteresis_m) {
        g->outside = false;
    }
    return false;
}
