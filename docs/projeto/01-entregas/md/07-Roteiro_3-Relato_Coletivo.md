<!--
MODELO PARA PREENCHER. Seções 3.1 e 3.2 do Roteiro 3 (roteiro de extensão).

Como usar:
- Os comentários como este não aparecem no PDF, mas precisam ser apagados antes da
  entrega. Os campos entre {chaves} também.
- O que já está escrito fora de comentário são fatos tirados do repositório. Confiram
  antes de manter.
- Escrevam na primeira pessoa do plural. É a voz do grupo.
- O professor tem o Roteiro 1 e o Roteiro 2. Tudo que mudou desde então precisa estar
  explicado aqui, não escondido.

O que o roteiro pede no 3.1: "considerações do grupo sobre o atingimento dos objetivos
sociocomunitários estabelecidos para o projeto". Não é diário de bordo. É responder,
objetivo por objetivo, se o projeto chegou aonde prometeu e o que mostra isso.
-->

# 3. Encerramento do projeto

## 3.1 Relato coletivo

<!--
Abertura em um parágrafo: o que é o MeuAmparo, para quem foi pensado e em que período o
trabalho aconteceu (agosto a novembro de 2026). Sem repetir o diagnóstico inteiro.
-->

{parágrafo de abertura}

### Objetivo 1: desenvolver e avaliar o protótipo

<!--
Texto do Roteiro 1, seção 1.4: "Desenvolver e avaliar um protótipo vestível de baixo
custo para detectar possíveis quedas, receber pedidos manuais de ajuda e avisar
cuidadores sobre a saída de uma área segura, informando a localização disponível."

Digam se foi atingido, atingido em parte ou não atingido, e por quê.
-->

Situação: {atingido / atingido em parte / não atingido}

O que foi feito, conforme o repositório:

- Detector de queda em C, em três fases (queda livre, impacto, imobilidade), com testes de
  host que rodam com `make test`.
- Botão de pedido de ajuda, LED e buzzer no firmware ESP-IDF.
- Área segura (geofence) implementada e testada no core. No firmware a posição é fixa,
  porque o Wokwi não tem GNSS, então a saída da área não dispara na simulação.
- Circuito no Wokwi com ESP32-S3, MPU6050, botão, buzzer e LED, e cenários automáticos de
  queda, queda cancelada, pulo e botão.

<!--
Comparem com as metas da Tabela 4 do Roteiro 2. Para cada uma: medida ou não medida.
- Detecção de 90%: os testes usam traces sintéticos escritos pelo grupo, não registros
  de pessoas. Não é a medição da meta. Se até a entrega usarem o SisFall, troquem aqui.
- Alarme falso menor que 1 por dia: só se mede em uso real. Digam isso.
- Botão gera alerta com posição: {resultado do cenário botao.yaml}
- Alerta de área segura em até 2 minutos: não medido na simulação (posição fixa).
- Autonomia de 8 horas: não medida, não houve hardware.
-->

{metas: o que foi medido, o que não foi e por quê}

<!--
Mudanças em relação ao Roteiro 2 que precisam ser explicadas:
- O backend e o painel de alertas saíram do escopo. Digam por quê, com as palavras de
  vocês: prazo, prioridade para o código embarcado, etc.
- O alerta sai pelo serial da simulação, e não pelo Wi-Fi simulado como dizia o
  Roteiro 2.
-->

{mudanças de escopo e motivo}

### Objetivo 2: publicar o projeto aberto

<!--
Roteiro 1: "Publicar o hardware e o firmware como projeto aberto, sob licença GNU GPL v3,
com lista de materiais e instruções de montagem e configuração, avaliando sua
compreensão por uma pessoa de fora do grupo."

Critério do Roteiro 2: alguém de fora do grupo roda a simulação só com as instruções; o
grupo anota tempo, dúvidas e ajudas pedidas. Se isso foi feito, coloquem quem foi (sem
dado pessoal sensível), o tempo e as dúvidas. Se não foi, digam.
-->

Situação: {atingido / atingido em parte / não atingido}

{repositório publicado? licença GPL v3 aplicada, lista de materiais, instruções de
simulação, teste com pessoa de fora do grupo}

### Objetivo 3: orientar a equipe da instituição

<!--
Roteiro 1: "Capacitar a equipe da instituição para montar, configurar e operar o
dispositivo em uma oficina prática, registrando as dificuldades e o nível de apoio
necessário."

Roteiro 2 trocou a oficina de montagem por um encontro de demonstração da simulação,
com dois critérios: configurar quem recebe os alertas em menos de 15 minutos sem ajuda,
e média de reação de pelo menos 4 em 5.

Atenção: sem backend, não existe tela para "configurar quem recebe os alertas". Esse
critério precisa ser revisto ou declarado não avaliado.

Se nenhuma instituição aceitou, este é o lugar da justificativa (decisão do grupo em
28/10/2026). Ela precisa ter fatos: quais instituições foram procuradas (Casa do Vovô,
Lar Padre Euclides, Lar do Vovô Albano), quando, por qual meio, e qual resposta veio.
Contato que não aconteceu não entra.
-->

Situação: {atingido / atingido em parte / não atingido}

{encontro com a instituição ou justificativa com datas e contatos}

### Considerações do grupo

<!--
Um ou dois parágrafos. O que o grupo aprendeu sobre fazer extensão: a distância entre o
plano e o que foi possível, o efeito de não ter hardware, o que fariam diferente.
Evitem final motivacional. Terminem com um fato ou com o próximo passo concreto.
-->

{considerações}

## 3.2 Avaliação de reação da parte interessada

<!--
O roteiro pede "formulário, entrevista gravada em áudio/vídeo, depoimento em áudio/vídeo
etc., para que o efetivo atingimento dos objetivos sociocomunitários propostos fique
evidente".

Se houve avaliação:
- quem participou (função, não nome, se não houver autorização), quantas pessoas e a data;
- o instrumento usado (anexar o formulário);
- as respostas, em tabela, com a média de cada pergunta;
- se a meta de 4 em 5 foi atingida.

Se não houve: digam isso claramente e remetam à justificativa do Objetivo 3. Não
preencham com estimativa.

O roteiro exige evidência em foto ou vídeo de todo o processo. Listem aqui o que há.
-->

{avaliação de reação ou justificativa}

Evidências:

- {foto, vídeo, print ou formulário, com data}
