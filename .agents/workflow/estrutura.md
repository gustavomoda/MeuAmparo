# Estrutura do repositório

Duas metades com propósitos diferentes: `docs/` guarda o que é entregue para a faculdade,
`src/` guarda o que roda. Não misture. Documento não entra em `src/`, código não
entra em `docs/`.

```
.agents/workflow/   estas instruções. AGENTS.md e CLAUDE.md são só ponteiros para o index.md
docs/               material da disciplina e documentos do projeto
src/meuamparo/      código: core, firmware, simulador e testes
```

## docs/

```
docs/material-disciplina/   PDFs e modelos da disciplina. Material recebido, não editar
docs/projeto/               tudo que o grupo produz
```

`material-disciplina/` tem as aulas 01 a 05, o roteiro de extensão, a carta de apresentação, o
Canvas oficial em docx e pdf, e o edital do III EPEI. É a fonte para modelo, formatação e
calendário. Consulte antes de redigir qualquer entrega, e não presuma a regra de formatação.

`projeto/` tem um `README.md` que serve de índice e mantém a organização numerada:

```
01-entregas/            o que vai para a SAVA
  docx/                 versão editável de cada entrega
  md/                   fonte do texto
  pdf/                  o arquivo que se posta
  figuras/              imagens usadas nas entregas, como o Gantt do cronograma
02-parte-interessada/   levantamento de instituições de Ribeirão Preto
03-hardware/            cotação, case e posicionamento
  case/                 scad e os dois stl
  renders/              imagens conceituais do case e das fixações
04-identidade-visual/   logos/ e icones/, em PNG de 512 a 6000 px e em SVG
```

Nas pastas 02 e 03 o `.docx` e o `.md` do mesmo documento ficam lado a lado; em `01-entregas` eles
estão separados por formato. Nenhum par sincroniza sozinho: editou um, confira o outro antes de
dizer que está pronto.

Prefira o SVG da identidade visual quando o destino aceitar.

Arquivos que começam com `~$` são lock temporário do Word. Ignore, não versione, não trate como
conteúdo.

## src/meuamparo/

```
core/        algoritmos em C puro. Não sabe que ESP32 existe
firmware/    ESP-IDF. Só o que roda na placa física
simulator/   Wokwi, custom chips, traces e ferramentas. Nada daqui vai para a placa
test/        testes de host do core, rodam no Mac sem ESP-IDF instalado
build/       saída do make, fora do git
Makefile     alvos help, test e clean
```

Hoje só `core/` e `test/` têm conteúdo: um `imu.c` de oito linhas e um teste que passa.
`firmware/main`, `firmware/components` e as quatro pastas de `simulator/` estão vazias. Os README
de cada pasta descrevem o destino, não o estado atual — não leia como se já existisse.

O detalhe de cada camada, e o motivo da separação, está em `src/meuamparo/README.md` e nos README de
`core/`, `firmware/` e `simulator/`. Esses arquivos são a fonte; não duplique o conteúdo deles aqui.
