# Documentos do projeto

Esta pasta guarda o que o grupo produz: as entregas da disciplina, o levantamento da instituição, o
projeto do case e a identidade visual. O material recebido da Estácio fica separado, em
[`docs/material-disciplina/`](../material-disciplina).

Quem quiser entender o projeto antes dos documentos, comece pelo [README da raiz](../../README.md).

## Entregas

A entrega na SAVA é em PDF, uma por grupo. O `.docx` serve para editar, o `.md` é a fonte de onde o
texto sai.

| Entrega | Onde está | Prazo | Pontos |
|---|---|---|---|
| Diagnóstico e teorização, seções 1.1 a 1.5 | `01-entregas/*/Roteiro_1-Diagnostico-e-Teorizacao_v1.*` | 09/09 | 2,0 |
| Planejamento, seções 2.1 a 2.5 | `01-entregas/*/Roteiro_2-Planejamento.*` | 23/09 | 1,0 |
| Canvas do projeto, 11 blocos | `01-entregas/docx/Canvas-Projeto.docx` | apresentado nos seminários | — |
| Canvas de apresentação | `01-entregas/*/Canvas_Apresentacao_v1.*` | apresentado nos seminários | — |

Faltam gerar os PDFs do Roteiro 2 e do Canvas-Projeto.

## Calendário

| Data | O que acontece | Pontos |
|---|---|---|
| 09/set | Entrega: diagnóstico e teorização | 2,0 |
| 16/set | Seminário de planejamento | — |
| 21/set | Prazo de submissão do III EPEI | — |
| 23/set | Entrega: planejamento do projeto | 1,0 |
| 28/out | Seminário de desenvolvimento | — |
| 25/nov | Entrega final e seminário de avaliação | 7,0 |

Aprovação exige grau igual ou superior a 6,0 e frequência de pelo menos 75%. Essas datas vêm dos
roteiros; o Canvas registra algumas diferentes. Confira o calendário oficial antes de contar com
qualquer uma delas.

## As pastas

```
01-entregas/            o que vai para a SAVA
  docx/                 versão editável
  md/                   fonte do texto
  pdf/                  o arquivo que se posta
  figuras/              imagens usadas nas entregas
02-parte-interessada/   19 instituições de Ribeirão Preto, roteiro da ligação e perguntas da visita
03-hardware/            cotação, projeto do case e posicionamento no corpo
  case/                 modelo em OpenSCAD, STL da base e da tampa
  renders/              imagens conceituais do case e das formas de fixação
04-identidade-visual/   marca e ícone, em PNG de 512 a 6000 px e em SVG
```

Nas pastas 02 e 03, o `.docx` e o `.md` do mesmo documento ficam lado a lado. Editou um, confira o
outro: eles não sincronizam sozinhos.

Os renders de `03-hardware/renders/` mostram um display touch de 1,69" que não consta na arquitetura
nem na cotação. São estudos visuais, não a configuração decidida.

## O que ainda está em aberto

A instituição parceira. Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano são as candidatas do
levantamento, mas nenhuma parceria foi firmada e nenhuma visita de escuta aconteceu. Sem isso, a
seção 2.2 do planejamento fica sem as evidências que o roteiro exige.

A placa e o orçamento, que estão documentados em duas versões que ninguém conciliou. O Word de
compras registra a Waveshare ESP32-S3-SIM7670G-4G comprada no mercado nacional, entre R$ 597 e
R$ 622. O Canvas e o Markdown de compras ainda dizem LilyGO T-A7670G R2 importada, R$ 419. Os dois
valores são estimativas de setembro de 2026.

As medidas da placa. O case foi desenhado a partir de dados de catálogo da Waveshare, então encaixes
e furação precisam ser conferidos com a placa em mãos antes de mandar imprimir.

A divisão das frentes de trabalho: o cronograma da seção 2.3 identifica frentes, não pessoas.

Nada foi montado nem medido em placa física até agora. Os números que aparecem nos documentos são
metas e estimativas.
