#include "transport.h"

#include <stdio.h>

bool ma_transport_send(const char *json)
{
    /* Prefixo fixo para quem lê o log separar o alerta do resto da saída, inclusive o
     * cenário automático do Wokwi, que espera por essa linha. */
    printf("MA_ALERT %s\n", json);
    fflush(stdout);
    return true;
}
