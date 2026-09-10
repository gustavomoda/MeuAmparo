# core

C puro. Nenhum header do ESP-IDF, nenhuma chamada ao FreeRTOS, nenhum acesso direto a hardware.

Contém a detecção de queda, o geofence, a máquina de estados do dispositivo e a declaração da
interface de transporte. Recebe dados prontos e devolve decisões.

A razão de existir: o algoritmo precisa rodar em segundos no Mac contra centenas de traces para
que a meta de 90% de detecção seja medida, e não estimada. Se depender do ESP-IDF, cada ajuste de
limiar vira um ciclo de gravar e testar na placa.

Quem implementa as bordas é `../firmware/` na placa e `../test/` no host.
