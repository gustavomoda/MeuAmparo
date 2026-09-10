#ifndef MEUAMPARO_TYPES_H
#define MEUAMPARO_TYPES_H

#include <stdint.h>

/*
 * Tipos compartilhados entre o firmware e os testes de host.
 *
 * O core recebe amostras já convertidas para unidade física. Quem lê o registrador
 * bruto do MPU6050 e aplica a escala é o driver, não o algoritmo: assim o mesmo
 * código de detecção roda com dados da placa e com dados de um trace gravado.
 */

typedef struct {
    uint32_t t_ms;      /* instante da amostra, em ms desde o boot ou desde o início do trace */
    float ax, ay, az;   /* aceleração em g */
    float gx, gy, gz;   /* velocidade angular em graus/s */
} ma_imu_sample_t;

#endif /* MEUAMPARO_TYPES_H */
