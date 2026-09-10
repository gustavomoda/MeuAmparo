#include "meuamparo/imu.h"

#include <math.h>

float ma_accel_magnitude(const ma_imu_sample_t *s)
{
    return sqrtf(s->ax * s->ax + s->ay * s->ay + s->az * s->az);
}
