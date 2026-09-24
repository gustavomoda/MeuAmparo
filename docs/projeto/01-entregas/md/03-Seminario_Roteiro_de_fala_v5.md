# MeuAmparo — roteiro de fala

## 1. MeuAmparo

Abertura: o projeto pretende identificar possíveis quedas, permitir pedidos de ajuda e avisar cuidadores com a localização. Hoje apresentamos o planejamento. A instituição ainda está em prospecção.

## 2. Todas as fases, com evidências

Vamos ouvir a instituição, definir requisitos, projetar e desenvolver a solução, testar e avaliar. Estudos técnicos podem avançar durante a prospecção. As atividades com o público dependem do aceite. Cada fase gera evidências: registros, requisitos, código, testes e avaliação.

## 3. Marcos até novembro

Calendário atualizado da Aula 04: planejamento em 23/09, seminário de desenvolvimento em 28/10 e entrega final com seminário de avaliação em 25/11. Proposta de sequência: requisitos e validação, implementação e testes, avaliação e relatos.

## 4. C com ESP-IDF e uma pequena PoC

Usaremos C com ESP-IDF. ESP-IDF é o framework oficial da Espressif: reúne ferramentas, drivers e bibliotecas para programar a família ESP32. Ele aceita C e C++. C++ oferece classes e outros recursos úteis para organizar interfaces e componentes, mas não torna o detector automaticamente mais preciso ou mais rápido. C já atende ao cálculo e mantém continuidade com a PoC atual. Podemos avaliar C++ se a complexidade da interface touch justificar; ainda não é uma mudança definida. Fonte: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/cplusplus.html . Core contém a lógica independente de hardware; firmware executa no ESP32; simulator reúne circuitos e cenários; test executa a lógica no computador. A pequena PoC já reúne magnitude da aceleração com teste de host e LED no ESP32-S3 simulado. Ela não implementa o detector completo nem o painel. Captura da estrutura fornecida pelo grupo.

## 5. Quem pensamos em envolver

Pessoas idosas são as beneficiárias. Cuidadores e familiares são destinatários dos alertas. A coordenação da instituição ajuda a definir a rotina e a viabilizar a participação. Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano são candidatas, não parceiras confirmadas.

## 6. Como vamos iniciar o contato

Estratégia proposta: telefonar à coordenação, apresentar o projeto de extensão e pedir uma conversa. Levar a carta de apresentação e um resumo visual. Ouvir necessidades antes de fechar requisitos. Se houver interesse, combinar a participação e registrar o aceite. Durante o desenvolvimento, validar fluxo e interface. Ao final, demonstrar a simulação e recolher feedback, com registros autorizados. Não provocar quedas em pessoas.

## 7. Frentes de trabalho

Proposta de distribuição ainda a confirmar: Gustavo na implementação técnica; Isa na organização de requisitos, registros e preparação da avaliação. Ambos participam do contato, testes e revisão. A distribuição será registrada e ajustada à disponibilidade e ao aprendizado. Não apresentar essas frentes como atividades individuais já realizadas.

## 8. GitHub Projects e Kanban

Vamos organizar as tarefas no GitHub Projects: https://github.com/users/gustavomoda/projects/2/views/4 . O repositório reúne código, documentos e histórico. O quadro já existe. Propomos quatro estados e cada tarefa com responsável, prazo e critério de conclusão. O exemplo no slide ilustra o fluxo, não representa o status real das tarefas. Confirmar a ferramenta com o professor. Exemplo de pronto: acionamento do botão gera o evento esperado e há registro do teste.

## 9. O cálculo acontece no dispositivo

Para explicar: o sensor mede aceleração em três direções perpendiculares, chamadas X, Y e Z. ax é a aceleração no eixo X; ay, no Y; az, no Z. Esses eixos acompanham a posição do sensor, não são direções fixas do ambiente. Elevamos cada leitura ao quadrado, somamos e tiramos a raiz. A é a magnitude: um único valor que resume a aceleração medida, incluindo a gravidade. Exemplo: ax=0, ay=0 e az=1 g resultam em A=1 g. É uma extensão do teorema de Pitágoras para três dimensões. O MPU6050 fornece aceleração nos três eixos em g. O ESP32 calcula a magnitude. Em repouso ela fica próxima de 1 g. Uma fase de queda livre pode se aproximar de zero; um impacto pode produzir um pico. A magnitude independe da orientação dos eixos, mas posição e fixação no corpo afetam a medição. O cálculo já está implementado; as regras de detecção ainda serão desenvolvidas. A decisão será local, enquanto o backend recebe e exibe o evento.

## 10. Redução de falsos positivos

Um pico isolado pode ocorrer ao sentar rapidamente, deitar ou bater o dispositivo. Estratégia a validar: considerar janela de tempo, impacto, orientação e movimento posterior. Limites e tempos serão ajustados com dados de teste. Não exigir queda livre ou imobilidade como condição universal: há quedas que não apresentam esses sinais. Comparar falsos alarmes e quedas não detectadas. Incluir queda do aparelho solto como limitação a investigar. Referências: https://www.mdpi.com/1424-8220/17/1/198 e https://pmc.ncbi.nlm.nih.gov/articles/PMC3353905/

## 11. Como vamos medir

Testar o algoritmo no computador com dados gravados, depois a integração no Wokwi. SisFall e FallAllD são candidatos sujeitos à conferência de licença e formato. Separar dados de ajuste e avaliação. Contar quedas detectadas, não detectadas e falsos alarmes. Detecção = detectadas / total de quedas testadas. Registrar duração ou atividades para contextualizar falsos alarmes. Ensaios curtos não comprovam menos de um alarme falso por dia. A configuração em menos de 15 minutos pode ser avaliada na demonstração, conforme aceite. Autonomia de 8 horas depende de hardware futuro. Todos os números são metas.

## 12. Hardware pensado para o dispositivo

Referência definida: Waveshare ESP32-S3-SIM7670G-4G. ESP32-S3 executa a lógica, GNSS fornece localização e modem envia alertas na proposta física. MPU6050 fornece aceleração e rotação. Visor touch de 1,69 polegada, botão manual, LED e buzzer, bateria 18650 e case completam a proposta. A integração do visor e seu custo ainda precisam ser validados. Sem compra neste semestre. A imagem é conceitual e medidas não foram validadas na placa física.

## 13. O desafio da placa e do case

O desafio foi chegar a uma placa e a um case que funcionem juntos e sejam adequados à proposta de uso. O modelo existe, mas as medidas e os encaixes ainda dependem da placa física. Precisaremos testar conforto, peso, estabilidade, leitura e uso da tela, acesso ao botão e pressão ao deitar, especialmente durante o sono. Essa avaliação física é futura, já que neste semestre não haverá montagem. A instituição poderá opinar sobre a proposta visual, mas isso não comprova conforto.

## 14. Por que o Wokwi

O Wokwi simula ESP32-S3, MPU6050, botão, LED e buzzer e executa firmware compilado com ESP-IDF. Permite repetir cenários sem aguardar hardware. Não simula a placa Waveshare completa. Planejamos localização por dados simulados e transporte pelo Wi-Fi virtual; GNSS e modem celular reais ficam sem validação. Confirmar Wokwi com professor: roteiro cita software livre. Fontes: https://docs.wokwi.com/guides/esp32 ; https://docs.wokwi.com/parts/wokwi-mpu6050 ; https://docs.wokwi.com/guides/esp32-wifi

## 15. Orçamento e alternativa comercial

MeuAmparo: estimativa documentada em setembro de 2026 para futura montagem, sem compra neste semestre. Placa R$459,99, frete R$8,90, MPU6050 R$28,10, bateria R$45 a R$70, botão/buzzer/LED R$15, pinos e fios R$10, PETG R$15, cinta/clip R$15. Total exato R$596,99 a R$621,99, arredondado no planejamento. Não inclui visor touch, trabalho de desenvolvimento, plano de dados ou hospedagem. A proposta com visor touch de 1,69 polegada foi confirmada pelo grupo; o custo da tela será cotado e o total revisado. Apple Watch SE 3: a partir de R$3.299 na loja oficial consultada em 16/09/2026; preço inicial não representa necessariamente a versão celular. Possui detecção de queda e SOS; comunicação depende de conectividade e configuração compatíveis. É um produto comercial, enquanto MeuAmparo é um projeto ainda em simulação, com personalização e código aberto como proposta. Não presumir desempenho, conforto ou confiabilidade equivalentes. Fontes: docs/projeto/01-entregas/md/Roteiro_2-Planejamento.md; https://www.apple.com/br/shop/buy-watch/apple-watch-se ; https://support.apple.com/pt-br/108896

## 16. Projeto aberto: GNU GPL v3

Escolhemos GNU GPL versão 3. Ela permite usar, estudar, modificar e compartilhar o código. Na distribuição de versões derivadas abrangidas pela GPL, a mesma licença e o acesso ao código-fonte correspondente preservam essas liberdades. Isso facilita continuidade e colaboração no projeto. Materiais e dependências de terceiros mantêm suas licenças. Fonte: LICENSE do repositório e https://www.gnu.org/licenses/gpl-3.0.html . Encerrar com os próximos passos: contato com instituição, confirmação do Wokwi e Kanban, e desenvolvimento dos cenários do detector.
