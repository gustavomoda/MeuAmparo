#ifndef MEUAMPARO_TRANSPORT_H
#define MEUAMPARO_TRANSPORT_H

#include <stdbool.h>

/*
 * Saída do alerta já formatado pelo core. O resto do firmware só conhece esta função.
 *
 * A implementação atual (transport_serial.c) escreve a mensagem no serial, que é o que
 * a simulação consegue mostrar. Na placa, uma transport_modem.c com o mesmo contrato
 * mandaria a mesma linha pelo SIM7670G. Trocar uma pela outra é mudar um arquivo no
 * CMakeLists, sem tocar no main.
 */

bool ma_transport_send(const char *json);

#endif /* MEUAMPARO_TRANSPORT_H */
