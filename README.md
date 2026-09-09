<img src="docs/Logomarca/Logos/MeuAmparo_01_Marca_vetorial.svg" alt="MeuAmparo" width="320">

# MeuAmparo

Dispositivo vestível de baixo custo para pessoas idosas: detecta queda, aceita pedido manual de
ajuda pelo botão e avisa o cuidador com a localização, inclusive quando a pessoa sai de uma área
segura.

Projeto de extensão da disciplina Programação de Microcontroladores (ARA4710), Estácio Ribeirão
Preto, semestre 2026.2.

## Estado atual

Início do desenvolvimento. O que existe hoje:

| Parte | Estado |
|---|---|
| Documentação da disciplina | roteiros 1 e 2, canvas, cotação, prospecção de instituições |
| Hardware | case paramétrico em OpenSCAD, com STL de base e tampa |
| Identidade visual | marca e ícone em PNG e SVG |
| `core/` | só a magnitude de aceleração, com teste de host passando |
| `firmware/` | vazio |
| `simulator/` | vazio |
| Backend e painel | não iniciados |

Nada foi montado nem medido em placa física. Os números que aparecem na documentação são metas e
estimativas, não resultados.

## Estrutura

```
docs/     material da disciplina, entregas, identidade visual e figuras
src/      código: core, firmware, simulador e testes
.agents/  instruções para agentes de IA que trabalham no repositório
```

O código fica em `src/meuamparo/`, separado em quatro pastas com uma fronteira rígida:

```
core/       algoritmos em C puro. Não sabe que ESP32 existe
firmware/   ESP-IDF. Só o que roda na placa
simulator/  Wokwi, custom chips e traces. Nada daqui vai para a placa
test/       testes de host, rodam sem ESP-IDF instalado
```

O motivo da separação está em [`src/meuamparo/README.md`](src/meuamparo/README.md). Resumindo: a meta
de detectar 90% das quedas só se mede rodando o algoritmo contra centenas de traces, e isso precisa
compilar em segundos no notebook, sem placa.

## Rodando os testes

Precisa de um compilador C11 e nada além disso. Sem ESP-IDF, sem placa.

```sh
cd src/meuamparo
make help    # lista os alvos
make test    # compila e roda os testes do core
```

## Arquitetura prevista

ESP32-S3, sensor inercial MPU6050, GNSS, conectividade 4G, bateria 18650, botão de pânico, buzzer e
LED. Firmware em C com ESP-IDF. Backend e painel web de alertas e histórico ainda sem stack definida.

## Metas

Detectar pelo menos 90% das quedas simuladas, menos de um alarme falso por dia, alerta de saída da
área segura em até dois minutos, autonomia mínima de oito horas, configuração independente em menos
de 15 minutos e avaliação da instituição parceira de pelo menos 4/5.

São critérios de aceitação definidos no planejamento. Nenhum foi medido ainda.

## Pendências

- **Placa**: a documentação tem duas versões. Índice e Word de compras dizem Waveshare
  ESP32-S3-SIM7670G-4G, R$ 597 a R$ 622; canvas e Markdown de compras ainda dizem LilyGO T-A7670G R2,
  R$ 419. Não consolidado.
- **Display**: o render do protótipo mostra tela touch de 1,69", que não consta na arquitetura
  documentada nem na cotação.
- **Instituição parceira**: em prospecção. Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano são
  as candidatas. Nenhuma parceria firmada.
- **Dataset de queda**: SisFall e FallAllD são os candidatos, licença e formato a conferir.

## Grupo

- Luis Gustavo Moda — 202402520751
- Isabelly Vitoria — 202608616779

Orientação: Prof. Omar Sacilotto Donaires.

## Licença

O planejamento prevê publicação sob licença MIT. O arquivo `LICENSE` ainda não foi adicionado, então
até lá o código não está formalmente licenciado.
