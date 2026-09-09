# Estrutura do repositório

Duas metades com propósitos diferentes: `docs/` guarda o que é entregue para a faculdade,
`src/` guarda o que roda. Não misture. Documento não entra em `src/`, código não
entra em `docs/`.

```
.agents/workflow/   estas instruções. AGENTS.md e CLAUDE.md são só ponteiros para o index.md
docs/               material da disciplina, entregas, identidade visual, figuras
src/meuamparo/      código: core, firmware, simulador e testes
```

## docs/

```
docs/material estácio/   PDFs e modelos da disciplina. Material recebido, não editar
docs/projeto/            entregas do grupo e fontes de trabalho
docs/Logomarca/          identidade visual em PNG e SVG
docs/Marketing/          vazia hoje
```

`material estácio/` tem as aulas 01 a 05, o roteiro de extensão, a carta de apresentação, o Canvas
oficial em docx e pdf, e o edital do III EPEI. É a fonte para modelo, formatação e calendário.
Consulte antes de redigir qualquer entrega, e não presuma a regra de formatação.

`projeto/` mantém a organização numerada que veio do 00-LEIA-ME.docx:

```
00-LEIA-ME.docx        índice das entregas
01-entregas/           roteiros 1 e 2, Canvas de apresentação, Canvas-Projeto
02-parte-interessada/  levantamento de instituições de Ribeirão Preto
03-hardware/           case (scad, dois stl, render), cotação, posicionamento
04-figuras/            imagens usadas nos documentos e nos slides
05-fontes-markdown/    versão Markdown dos documentos que também existem em Word
```

O par Word/Markdown de `05-fontes-markdown/` não sincroniza sozinho. Editou um, confira o outro
antes de dizer que está pronto.

Arquivos que começam com `~$` são lock temporário do Word. Ignore, não versione, não trate como
conteúdo.

`Logomarca/` tem `Logos/` (marca com nome) e `icones/` (só o símbolo), cada um em 512, 1024, 2048,
uma versão de 6000px e o vetorial em SVG. Prefira o SVG quando o destino aceitar.

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
