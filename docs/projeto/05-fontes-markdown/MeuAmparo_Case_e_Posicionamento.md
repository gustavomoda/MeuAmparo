# MeuAmparo — Case do dispositivo e posicionamento no corpo

Projeto do invólucro para impressão terceirizada e protocolo de teste de posicionamento
Setembro de 2026

---

## 1. Dimensões do case

O modelo foi construído a partir da placa **Waveshare ESP32-S3-SIM7670G-4G**, cujo datasheet informa **110 × 30,44 mm**.

| | Medida |
|---|---|
| Placa | 110,00 × 30,44 × 1,60 mm |
| Suporte da bateria 18650 sobre a placa | 19,50 mm *(a medir)* |
| Componentes sob a placa | 3,00 mm *(a medir)* |
| Folga interna | 1,50 mm por lado |
| Espessura de parede | 2,20 mm |
| **Case fechado** | **117,4 × 37,8 × 30,0 mm** |
| Peso estimado do conjunto | 100 a 115 g |

Para comparação: um cartão de crédito tem 85,6 × 54 mm. O dispositivo é mais comprido e bem mais estreito — o formato lembra um crachá de congresso ou um controle de portão grande.

O case é dividido em **base** (bandeja que abriga a placa, com o recorte do USB e os furos do buzzer) e **tampa** (com o botão, os LEDs e a janela da antena), unidas por quatro parafusos M2 auto-atarraxantes nos cantos e por um lábio de encaixe que alinha as duas peças.

---

## 2. Onde fica cada coisa

Todas as posições são medidas **a partir da borda esquerda da placa**, no sentido do comprimento. Cada uma é um parâmetro no arquivo `.scad` e muda numa linha.

### Face superior (tampa)

| Elemento | Diâmetro / tamanho | Posição | Função |
|---|---|---|---|
| **Botão de pânico** | Ø 12 mm | 30 mm | Acionamento manual e cancelamento do alarme falso. Grande e saliente de propósito: mão com artrose não acha botão pequeno, e no escuro tem que dar para achar pelo tato |
| **LED RGB do projeto** | Ø 5,2 mm | 15 mm | Estado do dispositivo, visível para o cuidador. Verde ligado, âmbar sem rede, vermelho piscando em alerta |
| **Janela dos LEDs da placa** | 22 × 7 mm, parede de 0,8 mm | 22 mm *(a medir)* | Deixa ver os LEDs de fábrica sem furar. Impressa em 0,8 mm o PETG fica translúcido |
| **Janela da antena GNSS** | 26 × 26 mm, parede de 1,2 mm | 92 mm *(a medir)* | **Crítico.** A antena cerâmica precisa "ver" o céu. Parede fina, nada de metal por cima, e essa face sempre voltada para fora do corpo |

Os LEDs de fábrica da placa, segundo a documentação da Waveshare, são: **azul** para energia, **verde** para carregamento solar, **vermelho piscando** para status da rede e **amarelo** para advertência de bateria invertida. Nenhum deles é informação para o idoso — são para quem monta e diagnostica. Por isso ficam atrás de uma janela translúcida, e não de um furo.

### Face inferior (base)

| Elemento | Detalhe | Posição |
|---|---|---|
| **Furos do buzzer** | Matriz 3 × 3 de Ø 2,2 mm, espaçados 4,5 mm | 62 mm, centralizado na largura |
| **Rebaixo do clipe de cinto** | 30 × 18 × 1,2 mm, com dois furos M3 a 18 mm um do outro | centro |

Os furos do buzzer ficam voltados para baixo para não acumular água, e o som ainda atravessa a roupa.

### Lateral esquerda

| Elemento | Detalhe |
|---|---|
| **Recorte do USB-C** | 9,5 × 4,2 mm, centralizado na largura, alinhado ao conector |

A carga é diária, então o conector precisa ser acessível sem abrir o case.

### Topo (lateral direita)

Dois ilhoses de Ø 4,5 mm, afastados 14 mm um do outro, para o cordão de pescoço. O cordão deve ser **largo e macio**: com 100 g pendurados, fio fino de 3 mm serra o pescoço.

**Segurança:** o cordão precisa ser do tipo *breakaway*, que se solta sob tração. É requisito de segurança, não conforto — cordão fixo em pescoço de idoso é risco de estrangulamento.

---

## 3. O que medir quando a placa chegar

O modelo é paramétrico. Ao receber a placa, meça estes sete valores com paquímetro e altere as linhas correspondentes no arquivo `.scad`. Nada mais precisa mudar.

| Parâmetro no arquivo | O que medir |
|---|---|
| `alt_sup_18650` | Altura do suporte da bateria, do topo da placa até o ponto mais alto |
| `alt_inferior` | Altura dos componentes soldados na face de baixo da placa |
| `pos_usb` | Distância da borda esquerda até o centro do conector USB-C |
| `pos_leds_placa` | Distância da borda esquerda até o centro do grupo de LEDs |
| `pos_antena_gnss` | Distância da borda esquerda até o centro da antena cerâmica |
| `usb_larg` e `usb_alt` | Largura e altura do corpo do conector USB-C |
| `pcb_comp` e `pcb_larg` | Confirmar os 110 × 30,44 mm do datasheet |

Só depois dessa conferência os arquivos devem ir para a impressão. Imprimir antes de medir é jogar dinheiro fora.

---

## 4. Especificação de impressão

| Parâmetro | Valor | Por quê |
|---|---|---|
| Material | **PETG** | O PLA amolece a 60 °C e deforma no painel do carro ou ao sol. O PETG aguenta e é menos quebradiço. Custa quase o mesmo |
| Cor | Clara, ou natural translúcido | Absorve menos calor e deixa as janelas de LED funcionarem |
| Altura de camada | 0,20 mm | Suficiente; 0,12 mm só deixa mais lento |
| Perímetros | 3 | Define a resistência real da parede de 2,2 mm |
| Preenchimento | 25%, giroide | Rigidez suficiente sem peso extra |
| Suportes | Não | O modelo foi desenhado sem balanços que exijam suporte |
| Orientação | Ambas as peças com a face aberta para cima | Melhor acabamento nas faces visíveis |

**Custo do serviço terceirizado:** de R$ 40 a R$ 60 por conjunto de duas peças. Você envia os arquivos `meuamparo_case_base.stl` e `meuamparo_case_tampa.stl`, e recebe pronto. Não é preciso ter a máquina.

**Ferragens a comprar à parte:** 4 parafusos M2 × 8 mm auto-atarraxantes (tampa), 2 parafusos M3 × 6 mm (clipe de cinto), 1 clipe de cinto metálico, 1 cordão breakaway.

---

## 5. Alternativa sem impressão

A placa Waveshare **já vem com estojo acrílico transparente e parafusos** no pacote. Ele protege a eletrônica, mas não prende no corpo.

Para vestir sem fabricar nada: **porta-celular de neoprene com passador de cinto e ilhó para cordão**, de R$ 20 a R$ 35 em qualquer marketplace. Um modelo para celular grande engole os 117 × 38 mm com folga, e a dupla fixação resolve as duas posições — cinto de dia, pescoço à noite.

**Isso deve constar da documentação do kit como opção padrão.** Uma ONG também não tem impressora 3D, e exigir uma peça impressa cria uma barreira de replicação que o projeto não precisa ter. O case impresso entra como melhoria opcional, não como requisito.

---

## 6. Posicionamento no corpo — as opções a testar

O pulso está descartado por um motivo simples: com 117 mm de comprimento, o dispositivo não cabe. Restam três posições viáveis, e a decisão entre elas deve sair de teste, não de opinião.

| Posição | Qualidade esperada do sinal | Conforto | Cobertura 24h | Como fixar |
|---|---|---|---|---|
| **A — Cintura, no cinto** | **Melhor.** Fica sobre o centro de massa, que é onde os conjuntos de dados de referência posicionam o sensor | Boa, discreta sob a roupa | Falha à noite: de pijama não há cinto | Clipe de cinto ou porta-celular com passador |
| **B — Peito, no cordão** | Muito boa | Sente-se o peso; exige cordão largo | Funciona sempre, inclusive dormindo | Cordão breakaway, curto o bastante para o aparelho encostar no corpo |
| **C — Braço, na braçadeira** | Média. O braço tem aceleração própria e gera mais alarme falso | Razoável de dia | Incômodo para dormir | Braçadeira de corrida para celular, R$ 25 a R$ 40 |

**Detalhe que quase todo projeto erra:** na posição B, o cordão precisa ser curto o suficiente para o dispositivo **encostar no peito**. Solto, ele balança, e o acelerômetro lê o balanço como movimento — o algoritmo enche de falso positivo. Regule para o aparelho ficar cerca de 15 cm abaixo do queixo.

---

## 7. Protocolo de teste de posicionamento

Executar assim que o firmware detectar queda, antes de qualquer teste com a instituição.

### Regras de segurança

Os testes de queda são feitos por **voluntários adultos e saudáveis do próprio grupo**, sobre colchonete, nunca por pessoas idosas. Nenhuma queda é simulada por participante do projeto de extensão.

### Sequência, repetida nas três posições

**Bloco 1 — Quedas que devem ser detectadas** (5 repetições de cada):

1. Queda para a frente, com apoio dos braços
2. Queda para a frente, sem apoio
3. Queda lateral, para a direita
4. Queda lateral, para a esquerda
5. Queda para trás, sentando e caindo
6. Escorregão com queda lenta, deslizando pela parede

**Bloco 2 — Atividades que NÃO podem disparar alarme** (5 repetições de cada):

1. Sentar-se bruscamente numa cadeira
2. Deitar-se rapidamente na cama
3. Levantar-se da cadeira
4. Caminhar 20 passos
5. Subir e descer cinco degraus
6. Agachar para pegar um objeto no chão
7. Tirar o dispositivo e apoiá-lo na mesa

### O que registrar

| Métrica | Como calcular | Meta |
|---|---|---|
| **Sensibilidade** | quedas detectadas ÷ 30 quedas do bloco 1 | ≥ 90% |
| **Alarmes falsos** | disparos no bloco 2 ÷ 35 atividades | ≤ 5% |
| **Tempo até o alerta** | do impacto ao envio, em segundos | ≤ 45 s, contando a janela de cancelamento |
| **Conforto** | nota de 1 a 5 dada pelo voluntário após 2 h de uso | ≥ 4 |

Registrar em planilha, uma linha por tentativa, com posição, tipo de movimento, se detectou e observação. Filmar ao menos uma repetição de cada tipo: além de servir de evidência obrigatória para o roteiro de extensão, o vídeo ajuda a entender por que uma detecção falhou.

### Decisão

A posição escolhida é a que atinge as metas de sensibilidade e alarme falso com a maior nota de conforto. Se duas posições empatarem no sinal, **vence a de melhor conforto** — porque dispositivo que incomoda não é usado, e dispositivo na gaveta tem sensibilidade zero.

Se a cintura vencer no sinal mas perder na cobertura noturna, a resposta não é escolher uma: é entregar o dispositivo com as duas fixações e orientar o uso no cinto durante o dia e no pescoço à noite.

---

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `meuamparo_case.scad` | Modelo paramétrico em OpenSCAD, com todos os parâmetros comentados |
| `meuamparo_case_base.stl` | Base, pronta para impressão |
| `meuamparo_case_tampa.stl` | Tampa, pronta para impressão |
| `case_conjunto.png` | Vista das duas peças |
| `case_tampa.png` | Vista da tampa |

O OpenSCAD é software livre e o modelo é código-fonte, o que permite versioná-lo no mesmo repositório do firmware. Para gerar os STL depois de ajustar as medidas:

```
openscad -o meuamparo_case_base.stl  -D peca=1 meuamparo_case.scad
openscad -o meuamparo_case_tampa.stl -D peca=2 meuamparo_case.scad
```
