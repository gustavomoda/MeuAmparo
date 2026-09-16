# Documentos do MeuAmparo

Aqui fica tudo o que o grupo escreveu para a disciplina e para o projeto. O material que veio da
Estácio, como aulas, modelos e edital, está em [`docs/material-disciplina/`](../material-disciplina).
Se você ainda não sabe o que é o MeuAmparo, leia antes o [README principal](../../README.md).

## Se você só precisa da entrega

Os PDFs que vão para a SAVA ficam direto em `01-entregas/`, para quem só quer ler. A disciplina
aceita só PDF, um por grupo.

O texto dos roteiros é escrito em Markdown, em `md/`, e é dele que saem o Word e o PDF. A geração
automática ainda está sendo montada; até ela ficar pronta, quem mexer no Markdown precisa levar a
mudança para o `.docx` em `docx/`. Os Canvas são a exceção: eles seguem o modelo do professor e
continuam sendo editados direto no Word.

- Roteiro 1, diagnóstico e teorização: prazo em 09/09, PDF gerado.
- Roteiro 2, planejamento: prazo em 23/09, ainda em rascunho e sem PDF.
- Canvas do projeto e Canvas de apresentação: usados nos seminários. Só o de apresentação tem PDF.

## Datas que importam

| Data | O que acontece | Pontos |
| --- | --- | --- |
| 09/set | Entrega do diagnóstico e teorização | 2,0 |
| 16/set | Seminário de planejamento | — |
| 21/set | Prazo de submissão do III EPEI | — |
| 23/set | Entrega do planejamento | 1,0 |
| 28/out | Seminário de desenvolvimento | — |
| 25/nov | Entrega final e seminário de avaliação | 7,0 |

Para passar, a nota precisa ser 6,0 ou mais, com pelo menos 75% de frequência. Essas datas são as
do calendário atualizado na Aula 04. O Canvas ainda mostra as da Aula 01, que foram adiadas: o
diagnóstico era 02/09 e o seminário de desenvolvimento, 21/10.

## Onde está cada coisa

```text
01-entregas/            os PDFs entregues na SAVA
  md/                   texto dos roteiros, a fonte de onde sai o resto
  docx/                 versão em Word
  figuras/              imagens usadas nas entregas, como o Gantt
02-parte-interessada/   14 instituições de Ribeirão Preto e o Conselho do Idoso, com roteiro de ligação
03-hardware/            cotação, projeto do case e onde usar o dispositivo no corpo
  case/                 modelo em OpenSCAD e os STL da base e da tampa
  renders/              imagens conceituais do case e das formas de prender
04-identidade-visual/   marca e ícone, em PNG e SVG
```

Nas pastas 02 e 03, o `.docx` e o `.md` de um mesmo documento ainda ficam lado a lado e não se
atualizam sozinhos. Quem mexer em um precisa levar a mudança para o outro, senão os dois começam a
contar histórias diferentes, o que já aconteceu neste projeto.

As imagens de `03-hardware/renders/` são estudos de aparência. Algumas mostram uma tela touch que
não faz parte da arquitetura nem da cotação.

## O que ainda não está resolvido

A instituição parceira ainda não existe. Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano são
as candidatas mais fortes, mas até agora nenhuma foi visitada e nenhum acordo foi fechado. O
planejamento depende dessa conversa: sem ela, não há como dizer como a equipe da instituição vai
participar.

A placa de referência é a Waveshare ESP32-S3-SIM7670G. Ela usa o mesmo chip, o ESP32-S3, que o
código e o simulador já usam, e o case foi desenhado para ela. Só que ela não vai ser comprada neste
semestre: não dá tempo de receber, montar e testar até novembro. Uma unidade completa custaria entre
R$ 597 e R$ 622, pela estimativa de setembro de 2026. O case partiu das medidas do catálogo e nunca
foi conferido com a placa. Parte dos documentos ainda cita a LilyGO T-A7670G R2, a opção anterior.

Pelo roteiro da disciplina, o sistema é desenvolvido e testado em simulação, e a montagem física só
entra se houver recursos. Aqui ela não vai entrar: todo o desenvolvimento e os testes são no Wokwi. Só que o roteiro pede software livre, e
o Wokwi não é; essa escolha ainda precisa ser justificada ou combinada com o professor.

O cronograma divide o trabalho por frente (instituição, hardware, firmware e documentação), mas
ainda não diz quem cuida de cada uma.

E vale lembrar que nada foi montado nem medido até agora. Números como os 90% de detecção de queda
são metas, não resultados.
