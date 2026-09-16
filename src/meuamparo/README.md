# MeuAmparo — firmware e simulador

Dispositivo vestível de baixo custo para pessoas idosas: detecta queda, aceita pedido manual de
ajuda pelo botão e avisa o cuidador com a localização, inclusive quando a pessoa sai de uma área
segura.

Disciplina Programação de Microcontroladores (ARA4710), Estácio Ribeirão Preto, 2026.2.
Grupo: Luis Gustavo Moda e Isabelly Vitoria. Orientação: Prof. Omar Sacilotto Donaires.

## Estrutura

```
core/         algoritmos em C puro. Não sabe que ESP32 existe.
firmware/     ESP-IDF. Só entra aqui o que roda na placa física.
simulator/    Wokwi, custom chips, traces e ferramentas. Nada daqui vai para a placa.
test/         testes de host do core, rodam no Mac sem ESP-IDF instalado.
```

A fronteira entre as três pastas é a regra mais importante do repositório. `core/` não inclui
nenhum header do ESP-IDF. `firmware/` não contém trace, mock nem cenário. `simulator/` pode
depender de qualquer coisa, porque não vai para produção.

## Como rodar

```
make setup      instala ESP-IDF e wokwi-cli, pulando o que já existe
make test       compila e roda os testes de host do core
make firmware   compila o firmware ESP-IDF
make sim        roda a demo no Wokwi headless sobre o binário compilado
make clean      apaga build/ e firmware/build/
```

`make test` não depende de nada disso. Precisa de um compilador C11 e mais nada, que é o motivo
de ele rodar igual no Mac, no Windows do laboratório e num CI sem toolchain de embarcado.

Os outros alvos precisam do ESP-IDF. `make setup` clona a v5.5.5 em `~/esp/esp-idf`, instala a
toolchain do esp32s3 em `~/.espressif` e o `wokwi-cli` pelo npm. Cada etapa confere antes de
baixar, então repetir o comando custa segundos em vez de vários GB. Serve para conferir uma
máquina nova sem medo de refazer download.

Feito o setup, falta carregar o ambiente na shell uma vez por sessão:

```
. ~/esp/esp-idf/export.sh
export WOKWI_CLI_TOKEN=...   # token de CI, em https://wokwi.com/dashboard/ci
```

`make sim` compila antes de rodar e falha se a linha `led=1` não aparecer no serial em 10
segundos. O LED piscando no navegador é o que se vê na apresentação; o critério de verificação
é essa linha no log.

## A demo do LED

`firmware/main/main.c` pisca o GPIO2 a cada meio segundo e imprime o estado. Não lê sensor, não
chama o `core/` e não envia alerta nenhum. Existe para fechar a cadeia do passo 4 antes de haver
lógica dentro dela: o ESP-IDF compila, o binário sobe no Wokwi, o pino responde. Quando o detector
de queda entrar, esse LED vira o indicador de alerta.

O circuito fica em `simulator/wokwi/diagram.json`: devkit ESP32-S3, LED e resistor de 330 Ω.

## Por que separar assim

A meta documentada é detectar pelo menos 90% das quedas simuladas com menos de um alarme falso
por dia. Isso não se mede apertando botão no simulador: mede-se rodando o algoritmo contra
centenas de traces de acelerômetro e contando acertos. Para isso o algoritmo precisa compilar no
Mac, em segundos, sem placa e sem toolchain de embarcado. Daí o `core/`.

O firmware fica fino de propósito: lê o MPU6050, lê o GNSS, chama o core, obedece ao que o core
decidir. Se a lógica de queda vivesse dentro de uma task do FreeRTOS, cada ajuste de limiar
custaria um ciclo de compilar, gravar e derrubar o protótipo de novo.

## Decisões, e por quê

### PICSimLab ficou de fora

PICSimLab simula PIC16/18, AVR e STM32. Não simula ESP32, então não roda uma linha do firmware
deste projeto. Também não tem peça para MPU6050, GNSS ou modem: sensor de queda e GPS virariam
texto digitado num terminal virtual.

Ele aparece na Aula 04 como leitura do Módulo 2 do conteúdo digital, junto com MPLAB e CCS C. É
bibliografia da disciplina, não exigência do projeto. A Aula 03 lista o ESP32 entre as famílias
de microcontrolador estudadas, ao lado de PIC, AVR e ARM.

### Wokwi como bancada visual

O Wokwi roda o binário do ESP-IDF de verdade, não uma reimplementação. Tem ESP32-S3, MPU6050,
botão, LED e buzzer como peças prontas. Roda no navegador, o que resolve Mac, Windows e a máquina
do laboratório com a mesma URL e nenhuma instalação. A extensão do VS Code roda local nos dois
sistemas, mas pede chave de licença.

### O modem 4G não é simulado. O transporte é trocado

Nenhum simulador tem modelo de SIM7670 ou A7670. Em vez de escrever um chip falso que responde
comandos AT, o firmware conversa com uma interface de transporte que tem duas implementações: no
Wokwi sai pelo Wi-Fi virtual, que dá internet real ao ESP32 simulado; na placa sai pelo modem.
O backend recebe a mesma requisição nos dois casos e não precisa saber a diferença.

Isso troca um custom chip complicado por uma interface de três funções. O preço é honesto: o
caminho do modem continua sem cobertura de teste até a placa chegar.

### GNSS precisa de custom chip

Aqui não tem atalho. O Wokwi não tem GPS na biblioteca, então o jeito é escrever um custom chip
que cospe sentenças NMEA de uma rota gravada. É o que permite a demo rodar sozinha: a pessoa
caminha, sai da área segura, o alerta dispara sem ninguém arrastar slider.

### O que simulador nenhum prova

Autonomia de oito horas só sai medindo a placa com a bateria real. Conforto e fixação dependem
das pessoas da instituição parceira. Alarme falso em uso cotidiano depende de rotina real, não de
trace de laboratório. O simulador cobre lógica e demonstração, e é isso.

## Plano

Cada passo tem um critério de verificação. Passo sem critério verificável não conta como pronto.

1. Esqueleto e `core/` compilando isolado. Verifica: `make test` passa no Mac, sem ESP-IDF.
2. Detector de queda e replayer de trace. Verifica: taxa de detecção e falsos positivos impressos
   como número, medidos contra dataset público.
3. Geofence e máquina de estados. Verifica: teste dispara alerta ao cruzar o raio, e uma vez só.
4. Firmware ESP-IDF com transporte Wi-Fi. Verifica: compila, sobe no Wokwi, alerta sai no log.
5. Custom chips do simulador (GNSS e replay do MPU). Verifica: cenário roda do play até o alerta
   sem interação, com LED e buzzer disparando.
6. Backend mínimo e painel com mapa. Verifica: alerta saído do Wokwi aparece no painel.
7. Seeder de dados sintéticos. Verifica: painel com histórico e vários dispositivos.
8. Documentos da disciplina. Verifica: coerência entre Word, Markdown e Canvas.

## Pendências

- A placa é a Waveshare ESP32-S3-SIM7670G. O Wokwi não tem peça para o modem 4G nem para o GNSS,
  então essas partes precisam ser representadas de outro jeito na simulação.
- Dataset de queda: SisFall e FallAllD são os candidatos. Conferir licença e formato antes de usar.
- Licença do Wokwi para a extensão do VS Code. A versão web resolve a apresentação.
