#include "ma_test.h"
#include "meuamparo/imu.h"

int main(void)
{
    /* Dispositivo parado: só a gravidade, qualquer que seja o eixo apontado para baixo. */
    ma_imu_sample_t rest = {0, 0.0f, 0.0f, 1.0f, 0, 0, 0};
    MA_CHECK_NEAR(ma_accel_magnitude(&rest), 1.0, 1e-6);

    ma_imu_sample_t rest_tilted = {0, 0.6f, 0.0f, 0.8f, 0, 0, 0};
    MA_CHECK_NEAR(ma_accel_magnitude(&rest_tilted), 1.0, 1e-6);

    /* Queda livre: os três eixos vão para perto de zero. */
    ma_imu_sample_t free_fall = {0, 0.02f, -0.01f, 0.03f, 0, 0, 0};
    MA_CHECK(ma_accel_magnitude(&free_fall) < 0.1f);

    /* Impacto: pico bem acima de 1 g. */
    ma_imu_sample_t impact = {0, 3.0f, 4.0f, 0.0f, 0, 0, 0};
    MA_CHECK_NEAR(ma_accel_magnitude(&impact), 5.0, 1e-6);

    MA_REPORT();
}
