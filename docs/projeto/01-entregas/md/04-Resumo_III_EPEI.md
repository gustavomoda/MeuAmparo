# Resumo para o III EPEI

Texto puro para o formulário de submissão do III Encontro de Pesquisa, Extensão e Internacionalização (edital em `docs/material-disciplina/Edital_III_EPEI.pdf`). Sem tabela, figura, autoria ou referência bibliográfica, conforme os itens 3.2 e 3.6 do edital. Os dados de identificação (curso, área, autores, e-mails, orientador, responsável, modalidade) vão nos campos próprios do formulário, não neste texto.

---

Título: MeuAmparo: dispositivo vestível de baixo custo para detecção de queda e localização de pessoas idosas

Tema e problema de pesquisa

O trabalho trata de um dispositivo vestível de baixo custo para pessoas idosas, capaz de reconhecer movimento compatível com queda, aceitar pedido manual de ajuda e avisar o cuidador com a localização, inclusive quando a pessoa sai de uma área definida como segura. O problema de partida é a queda sem testemunha: a pessoa cai, não consegue pedir socorro e o atendimento depende de alguém perceber. A população brasileira com 60 anos ou mais passou de 8,7% em 2000 para 15,6% em 2023 (IBGE, 2024). No estado de São Paulo, as internações por queda nessa faixa etária cresceram em média 4,3% ao ano entre 2000 e 2020, com custo projetado de cerca de R$ 260 milhões para o SUS em 2025 (NOVAES et al., 2023). A pergunta é como avisar cuidadores sobre uma possível queda ou afastamento, com localização, a um custo compatível com a rotina de uma instituição sem fins lucrativos. É um projeto de extensão em andamento, com parceria prevista com uma instituição de atendimento a idosos de Ribeirão Preto.

Objetivos

Desenvolver e avaliar um protótipo vestível que detecte possíveis quedas, receba pedido manual de ajuda e avise o cuidador sobre a saída de uma área segura, informando a localização. Publicar hardware, firmware e documentação como projeto aberto sob licença GNU GPL v3, com lista de materiais e roteiro de montagem. Capacitar a equipe da instituição parceira, em oficina prática, a montar, configurar e operar o dispositivo.

Referencial teórico

O dimensionamento do problema vem das projeções demográficas (IBGE, 2024) e do estudo de tendência das internações e dos custos de quedas em idosos entre 2000 e 2020 (NOVAES et al., 2023). Para a detecção, a base é o conjunto SisFall (SUCERQUIA; LÓPEZ; VARGAS-BONILLA, 2017), com registros de quedas e de atividades cotidianas obtidos por sensores inerciais, que orienta a distinção entre queda e movimentos bruscos do dia a dia. A abordagem adotada procura a sequência característica da queda na magnitude do vetor de aceleração: valor próximo de 1 g em repouso, aproximação de zero na queda livre e pico no impacto. Usar a magnitude em vez dos eixos separados torna o cálculo independente da orientação em que o dispositivo está preso ao corpo. O roteiro de extensão da disciplina relaciona a escolha do microcontrolador aos requisitos, prevê implementação em C com verificação por ensaios e exige a participação da parte interessada na validação. O tratamento dos dados de localização segue as exigências da LGPD quanto a finalidade, acesso, armazenamento e descarte; hospedagem no Brasil é proposta, não prova de conformidade.

Metodologia

O projeto segue o roteiro da disciplina: diagnóstico documental, planejamento, desenvolvimento e avaliação com a parte interessada. A arquitetura prevista usa o microcontrolador ESP32-S3, o sensor inercial MPU6050, receptor GNSS, modem 4G, bateria 18650, botão de pânico, buzzer e LED, com firmware em C sobre o ESP-IDF e um painel web de alertas. O código é organizado em quatro camadas: núcleo em C puro com os algoritmos, sem dependência de hardware; firmware da placa; simulador; e testes de host, que rodam no computador. A separação permite executar o detector contra centenas de registros de referência em segundos e medir a taxa de detecção antes de qualquer ensaio com placa. Neste semestre o desenvolvimento e os testes são só em simulação, no Wokwi, que reproduz o ESP32-S3, o MPU6050, botão, buzzer e LED. GNSS e modem não têm peça no simulador e serão representados por dados simulados e transporte via Wi-Fi virtual. As metas definidas são detectar pelo menos 90% das quedas simuladas, menos de um alarme falso por dia, alerta de saída da área segura em até dois minutos, autonomia mínima de oito horas, configuração por um cuidador em menos de 15 minutos e avaliação de reação de pelo menos 4 em 5. Quedas simuladas são realizadas apenas por adultos saudáveis em ambiente controlado, nunca por pessoas idosas. A escuta da instituição orienta requisitos e avaliação.

Resultados parciais

O diagnóstico e o planejamento foram concluídos e entregues à disciplina. Três instituições de Ribeirão Preto foram levantadas como candidatas à parceria (Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano); o acordo ainda não foi firmado. A plataforma de referência foi definida em 16 de setembro de 2026: a placa Waveshare ESP32-S3-SIM7670G-4G, que reúne microcontrolador, modem 4G e GNSS numa peça só, preferida a uma alternativa importada mais barata por ter venda nacional com nota fiscal e prazo menor. A lista de materiais estimada em setembro de 2026 fica entre R$ 597 e R$ 622 por unidade, sem plano de dados nem hospedagem; um relógio comercial com detecção de queda parte de R$ 3.299 na loja oficial consultada na mesma data. O case foi modelado de forma paramétrica em OpenSCAD, com STL da base e da tampa gerados, com três posições de uso propostas para avaliação com a instituição. O código está sob GNU GPL v3, com a estrutura de camadas implantada e uma prova de conceito que calcula a magnitude da aceleração, com teste de host passando, e aciona o LED no ESP32-S3 simulado. O detector completo, o painel e as medições das metas ainda não existem.

Conclusões

Até esta etapa, o projeto tem problema dimensionado, metas verificáveis, plataforma escolhida, custo estimado, case modelado e base de código com teste automatizado. Duas condições limitam o restante do semestre: a parceria ainda em prospecção e a restrição à simulação, que deixa GNSS, modem e autonomia sem validação física. A próxima etapa é implementar o detector no núcleo, medir a taxa de detecção e de alarmes falsos contra os registros de referência e integrar a simulação no Wokwi, para o seminário de desenvolvimento de 28 de outubro e a entrega final de 25 de novembro de 2026. Todos os números de desempenho citados são metas, não resultados obtidos.

Palavras-chave: detecção de queda; dispositivo vestível; pessoa idosa; ESP32; extensão universitária.
