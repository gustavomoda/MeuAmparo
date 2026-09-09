# 2. Planejamento e desenvolvimento do projeto

## 2.1 Plano de trabalho

O planejamento organiza o desenvolvimento do MeuAmparo até novembro de 2026. A parceria ainda está em prospecção. As atividades de campo dependem do acordo com a instituição; os períodos abaixo são previsões de trabalho.

A sequência proposta começa pela escuta, passa pela definição dos requisitos e pela validação da solução e só então chega à implementação destinada ao uso na instituição. Estudos de sensores e ensaios de bancada podem ocorrer antes. A aquisição depende da escolha da placa e do orçamento.

Tabela 1 – Marcos acadêmicos da disciplina

| Entrega ou seminário | Data |
|---|---|
| Diagnóstico e teorização, seções 1.1 a 1.5 | 09/09 |
| Seminário de planejamento | 16/09 |
| Planejamento, seções 2.1 a 2.5 | 23/09 |
| Seminário de desenvolvimento | 28/10 |
| Detalhamento técnico, encerramento e seminário final | 25/11 |

Fonte: calendário atualizado da disciplina (2026).

Tabela 2 – Atividades previstas e formas de acompanhamento

| Período previsto | Ação e dependência | Frente de trabalho | Recurso e evidência esperada |
|---|---|---|---|
| 09 a 23/09 | Contato e formalização da parceria | Relação com a instituição | Carta de apresentação; registro do aceite |
| 16 a 30/09 | Escuta da coordenação e cuidadores | Relação com a instituição e documentação | Visita; resumo conferido pelos participantes |
| 23/09 a 07/10 | Requisitos e comparação de microcontroladores | Hardware | Computador; requisitos e comparação técnica |
| 30/09 a 14/10 | Arquitetura e fluxo de funcionamento | Hardware e firmware | Ferramentas de diagramação; diagramas |
| 14 a 21/10 | Validação da proposta, antes da implementação para uso | Relação com a instituição | Reunião; decisões e ajustes registrados |
| Até 21/10, após decisão de compra | Aquisição dos componentes | Hardware | Recursos do grupo; comprovantes e recebimento |
| 07 a 21/10 | Estudo do algoritmo e ensaios de bancada | Firmware | ESP-IDF e dados de referência; registros dos ensaios |
| Após validação, até 11/11 | Implementação e integração de detecção, localização e alertas | Firmware e painel | Hardware e computador; versões do código e testes |
| 21/10 a 04/11 | Ajuste e fabricação do case, após conferir a placa | Hardware | OpenSCAD e impressão 3D; medidas e encaixes |
| 28/10 a 18/11 | Montagem e testes individuais e de integração | Hardware e firmware | Protótipo; registros de acertos, falhas e tempos |
| 11 a 18/11, após testes de integração | Oficina de montagem e configuração | Relação com a instituição e documentação | Kit e manual; tempo e dificuldades observadas |
| 18 a 25/11 | Avaliação de reação | Relação com a instituição | Formulário; respostas e comentários |
| 11 a 25/11 | Relato coletivo, relatos individuais e entrega | Documentação e ambos os discentes | Evidências das atividades; texto e PDF para SAVA |

Fonte: planejamento dos autores (2026). A atribuição individual das frentes está na seção 2.3.

Os prazos após a validação ficam condicionados ao aceite da instituição e ao recebimento dos componentes. Se essas etapas atrasarem, o escopo e a agenda precisarão ser acordados com o orientador.

## 2.2 Forma de envolvimento do público participante

Na primeira visita, pretendemos ouvir a coordenação e os cuidadores sobre a rotina, as ocorrências que exigem ajuda e a comunicação entre os responsáveis. Essa conversa deve orientar a prioridade das funções. O grupo apresentará a proposta com base no que for registrado e levará de volta os requisitos para conferência, antes da implementação destinada ao uso local.

Durante o desenvolvimento, a equipe será convidada a discutir os destinatários dos alertas e o procedimento após um aviso. A avaliação do formato de uso considera peso, conforto e acesso ao botão. Cintura, peito e braço são posições propostas para estudo. O cordão, se utilizado, terá engate de segurança.

Os testes de detecção serão realizados por adultos saudáveis em ambiente controlado. Pessoas idosas não participarão de quedas simuladas. A equipe da instituição poderá avaliar a interface e a configuração, sem precisar executar os ensaios de queda.

Na oficina, um participante tentará configurar o dispositivo com o material de apoio e sem intervenção do grupo. Registraremos o tempo, os erros e a ajuda solicitada. Depois, coordenação e cuidadores poderão responder ao formulário de reação. Depoimentos em vídeo serão opcionais e dependerão de autorização.

Os encontros serão combinados conforme a disponibilidade da instituição. Após cada reunião, o grupo organizará um resumo para conferência dos participantes. Atas, formulários e registros autorizados serão identificados por data e atividade e anexados conforme os encontros ocorrerem.

## 2.3 Grupo de trabalho

O grupo tem dois integrantes: Luis Gustavo Moda, matrícula 202402520751, e Isabelly Vitoria, matrícula 202608616779. A distribuição individual das atividades técnicas e do contato com a instituição ainda não foi registrada; por isso, o cronograma identifica frentes de trabalho, não pessoas.

Tabela 3 – Integrantes e situação da divisão de atividades

| Discente | Matrícula | Responsabilidade individual |
|---|---|---|
| Luis Gustavo Moda | 202402520751 | Relato individual e participação nos seminários; divisão das frentes pendente |
| Isabelly Vitoria | 202608616779 | Relato individual e participação nos seminários; divisão das frentes pendente |

Fonte: registro do grupo (2026).

As frentes abrangem contato e formalização, hardware e case, firmware em C, backend e painel, além de documentação. A definição nominal completa esta seção. As revisões em dupla previstas no planejamento apoiam o aprendizado das partes técnicas por ambos.

## 2.4 Metas, critérios ou indicadores de avaliação do projeto

As metas abaixo são resultados pretendidos, ainda sem medições do protótipo. Os registros dos testes devem identificar a versão do firmware, a posição de uso e as condições do ensaio, para permitir a comparação entre ajustes.

### Objetivo 1 – Desenvolver e avaliar o protótipo

O desenvolvimento começa pelos requisitos e pela comparação entre microcontroladores. A escolha considera consumo, custo, memória, dimensões e periféricos, com a comparação prevista de pelo menos quatro famílias. Depois da validação, a implementação será verificada por função e no conjunto completo.

Tabela 4 – Metas técnicas e medição prevista

| Aspecto | Meta | Como medir |
|---|---|---|
| Detecção de queda | Pelo menos 90% das quedas simuladas | Dividir quedas detectadas pelo total de quedas simuladas e multiplicar por 100; registrar também as falhas |
| Alarmes falsos | Menos de 1 por dia por dispositivo | Contar avisos indevidos no período de uso e registrar as horas observadas; ensaios curtos não comprovam a meta diária |
| Saída da área segura | Alerta em até 2 minutos | Comparar o instante de cruzamento do limite com o recebimento do alerta pelo cuidador |
| Autonomia | Pelo menos 8 horas por carga | Medir o tempo de funcionamento contínuo, registrando frequência de localização e transmissão |
| Configuração do alerta | Botão manual e localização disponível no aviso | Acionar o botão e verificar o recebimento; testar GNSS em local aberto e registrar indisponibilidade de sinal |
| Custo | Teto inicial de R$ 500 na alternativa LilyGO | Somar os gastos efetivos; o teto não comporta a estimativa Waveshare de R$ 597 a R$ 622 |

Fonte: metas do projeto e procedimentos propostos pelos autores (2026).

Os alarmes falsos por atividade, usados no protocolo do case, serão registrados separadamente da taxa diária. A localização em ambiente fechado e a identificação por rede conhecida são possibilidades de estudo, sem desempenho demonstrado. A função de localização não deve apresentar uma posição antiga como se fosse atual.

### Objetivo 2 – Publicar documentação de projeto aberto

O material previsto inclui esquema elétrico, lista de materiais com fornecedores, modelo do case e código-fonte sob licença MIT. A verificação terá duas partes: conferir a presença desses arquivos e observar uma pessoa de fora do grupo seguindo o roteiro de montagem. Serão anotados os passos concluídos, as dúvidas e as intervenções necessárias. A documentação será ajustada a partir dessas dificuldades.

### Objetivo 3 – Capacitar a equipe da instituição

A oficina abordará montagem, configuração e operação. A meta de configuração é que um membro da equipe conclua o procedimento em menos de 15 minutos, sem intervenção do grupo. O registro inclui tempo e ajuda solicitada, mesmo quando a meta não for atingida.

A avaliação de reação tem meta mínima de 4 em 5. O formulário deve permitir comentário sobre as dificuldades, e o relatório apresentará as respostas e a quantidade de participantes. Como critério proposto de consolidação, será usada a média das notas de avaliação geral. O vídeo, quando autorizado, complementa o formulário e não é obrigatório.

## 2.5 Recursos previstos

O grupo considera duas alternativas de aquisição, ainda sem escolha de placa ou compra confirmada. Os valores foram registrados em setembro de 2026.

Tabela 5 – Alternativas de orçamento para uma unidade

| Alternativa | Estimativa registrada | Fonte prevista |
|---|---|---|
| LilyGO T-A7670G R2 importada | R$ 419; teto inicial de R$ 500 | Grupo |
| Waveshare ESP32-S3-SIM7670G-4G no mercado nacional | R$ 597 a R$ 622 | Grupo |
| Plano de dados e hospedagem | Valores ainda não definidos | Sem financiamento acordado |

Fonte: MeuAmparo_Cotacao-e-Compras.md, MeuAmparo_Cotacao-e-Compras.docx e 00-LEIA-ME.docx, registros de setembro de 2026. Valores estimados, não preços atuais.

A visão de menor custo inicial favorece a LilyGO na estimativa: R$ 178 a R$ 203 abaixo da Waveshare. Depende, porém, do prazo e do custo da importação, além da revisão do case existente.

A visão de aquisição nacional favorece o aproveitamento do desenho do case para a Waveshare, com conferência física dos encaixes antes da fabricação. Essa alternativa supera o teto inicial em R$ 97 a R$ 122. Ambas dependem de cotação atual; a decisão continua aberta.

A composição LilyGO é: placa, R$ 169; MPU6050, R$ 28; bateria, R$ 55; interface e conexões, R$ 25; case e cordão, R$ 30; placa portadora, R$ 12/unidade; frete e encargos, R$ 100. A portadora pressupõe lote de cinco, cujo desembolso precisa entrar na compra. A caixa comercial de R$ 25 é outra possibilidade do levantamento.

Estão previstos ESP-IDF para firmware em C, OpenSCAD para o case e Git para versionamento. O roteiro da disciplina prevê simulação em software livre e admite montagem física conforme os recursos. A aplicação dessa alternativa ao MeuAmparo depende da compatibilidade do simulador com ESP32 e os periféricos e da orientação do professor.

Laboratório e impressora 3D da Estácio dependem de disponibilidade. Participam os dois discentes, o Prof. Omar Sacilotto Donaires como orientador e a equipe da instituição, conforme acordo. Não há financiamento da IES ou da parceira confirmado.
