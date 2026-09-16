<img src="docs/projeto/04-identidade-visual/logos/marca_vetorial.svg" alt="MeuAmparo" width="320">

# MeuAmparo

Dispositivo vestível de baixo custo para pessoas idosas: detecta queda, aceita pedido manual de
ajuda pelo botão e avisa o cuidador com a localização, inclusive quando a pessoa sai de uma área
segura.

Projeto de extensão da disciplina Programação de Microcontroladores (ARA4710), Estácio Ribeirão
Preto, semestre 2026.2. O desenvolvimento e os testes acontecem em simulação, no Wokwi, como o
roteiro da disciplina prevê; não haverá montagem física neste semestre.

O acompanhamento das tarefas fica no [quadro do projeto no GitHub](https://github.com/users/gustavomoda/projects/2):
cada entrega da disciplina é um marco, cada tarefa tem prazo, responsável e critério de pronto.

## Estado atual

Início do desenvolvimento, em 16/09/2026. O que existe hoje:

| Parte | Estado |
| --- | --- |
| Documentação da disciplina | Roteiro 1 entregue; Roteiro 2 em rascunho para 23/09; canvas apresentado |
| Instituição parceira | levantamento de 14 entidades; nenhuma contatada ainda |
| Hardware | case paramétrico em OpenSCAD, com STL de base e tampa, nunca conferido com a placa |
| Identidade visual | marca e ícone em PNG e SVG |
| `core/` | só a magnitude de aceleração, com teste de host passando |
| `firmware/` | projeto ESP-IDF mínimo, que pisca um LED |
| `simulator/` | diagrama Wokwi com ESP32-S3 e LED, rodando o firmware mínimo |
| Backend e painel | não iniciados |

Nada foi montado nem medido em placa física, e não vai ser neste semestre. Os números que aparecem
na documentação são metas e estimativas, não resultados.

## Estrutura

```text
docs/material-disciplina/   material recebido da Estácio, não editar
docs/projeto/               entregas, instituições, hardware e identidade visual (tem um README)
src/meuamparo/              código: core, firmware, simulador e testes
.agents/                    instruções para agentes de IA que trabalham no repositório
```

O código fica em `src/meuamparo/`, separado em quatro pastas com uma fronteira rígida:

```text
core/       algoritmos em C puro. Não sabe que ESP32 existe
firmware/   ESP-IDF. Só o que roda na placa
simulator/  Wokwi, custom chips e traces. Nada daqui vai para a placa
test/       testes de host, rodam sem ESP-IDF instalado
```

O motivo da separação está em [`src/meuamparo/README.md`](src/meuamparo/README.md). Resumindo: a meta
de detectar 90% das quedas só se mede rodando o algoritmo contra centenas de traces, e isso precisa
compilar em segundos no notebook, sem placa.

## Rodando

Os testes do core precisam só de um compilador C11. Firmware e simulação precisam do ESP-IDF e do
`wokwi-cli`, que o `make setup` instala.

```sh
cd src/meuamparo
make help      # lista os alvos
make test      # compila e roda os testes do core, sem ESP-IDF
make setup     # instala ESP-IDF e wokwi-cli, pulando o que já existe
make firmware  # compila o firmware (com o export.sh do ESP-IDF carregado)
make sim       # roda o firmware no Wokwi
```

## Arquitetura

A placa de referência é a Waveshare ESP32-S3-SIM7670G-4G, que junta o ESP32-S3, o modem 4G e o GNSS.
Em volta dela: sensor inercial MPU6050, bateria 18650, botão de pânico, buzzer e LED. Firmware em C
com ESP-IDF. Backend e painel web de alertas ainda sem stack definida.

A simulação no Wokwi cobre o ESP32-S3, o MPU6050, o botão, o buzzer e o LED. O 4G e o GNSS não
existem no simulador e serão representados de outra forma, por exemplo pelo Wi-Fi simulado.

## Metas

Detectar pelo menos 90% das quedas simuladas, menos de um alarme falso por dia, alerta de saída da
área segura em até dois minutos, autonomia mínima de oito horas, configuração independente em menos
de 15 minutos e avaliação da instituição parceira de pelo menos 4/5.

São critérios definidos no planejamento. Nenhum foi medido, e alguns (autonomia, alarmes falsos por
dia, configuração pela equipe) dependem de hardware que não vai existir neste semestre; a forma de
avaliá-los em simulação ainda está sendo decidida.

## Pendências

- **Simulador**: o Wokwi não é software livre, que é o que o roteiro da disciplina cita. Falta
  confirmar com o professor.
- **Documentos antigos**: o canvas e o Markdown de compras ainda citam a LilyGO T-A7670G R2, opção
  anterior à Waveshare, e as imagens conceituais em `docs/projeto/03-hardware/renders/` mostram uma
  tela touch que não faz parte do projeto.
- **Divisão do trabalho**: as frentes (instituição, firmware, backend, documentação) ainda não têm
  responsável nominal.
- **Instituição parceira**: em prospecção. Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano são
  as candidatas. Nenhuma parceria firmada.
- **Dataset de queda**: SisFall e FallAllD são os candidatos, licença e formato a conferir.

## Grupo

- Luis Gustavo Moda
- Isabelly Vitoria

Orientação: Prof. Omar Sacilotto Donaires.

## Licença

O código e os materiais autorais do MeuAmparo são disponibilizados sob a
[GNU General Public License, versão 3](LICENSE) (`GPL-3.0-only`).

Materiais da disciplina, dependências e outros conteúdos de terceiros mantêm suas próprias licenças.
