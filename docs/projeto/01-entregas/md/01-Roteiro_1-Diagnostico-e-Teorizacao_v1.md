SOCIEDADE DE ENSINO SUPERIOR ESTÁCIO DE RIBEIRÃO PRETO

Campus Ribeirão Preto

Bacharelado em Ciência da Computação

Programação de Microcontroladores (ARA4710)

# MEU AMPARO

Dispositivo vestível de detecção de queda e localização para pessoas idosas

Diagnóstico e teorização

Luis Gustavo Moda – Matrícula 202402520751

Isabelly Vitoria – Matrícula 202608616779

Orientador: Prof. Omar Sacilotto Donaires

2026

Ribeirão Preto / SP

---

# 1. Diagnóstico e teorização

## 1.1 Identificação das partes interessadas e parceiros

O MeuAmparo é uma proposta de dispositivo vestível para pessoas idosas, desenvolvida por Luis Gustavo Moda e Isabelly Vitoria na disciplina Programação de Microcontroladores, da Estácio Ribeirão Preto. Pretendemos trabalhar com uma instituição sem fins lucrativos do município e sua equipe de cuidadores. Em 9 de setembro de 2026, a parceria ainda está em prospecção, sem acordo formalizado ou visita de escuta registrada.

Casa do Vovô, Lar Padre Euclides e Lar do Vovô Albano estão entre as candidatas do levantamento do grupo. A escolha depende da demanda apresentada pela entidade e da disponibilidade para os encontros.

O público pretendido é de pessoas com 60 anos ou mais, especialmente aquelas que precisam de acompanhamento por histórico de quedas ou episódios de desorientação. A faixa inicial de 15 a 40 pessoas é uma estimativa de planejamento. Ainda não dispomos de informações locais sobre escolaridade, renda, gênero ou necessidades de apoio. A caracterização dos participantes depende da instituição escolhida.

Cuidadores e coordenação participarão da definição do fluxo de atendimento aos alertas; familiares de referência poderão ser envolvidos conforme a rotina do local. A formalização da parceria e as autorizações de participação e de imagem antecedem as atividades que delas dependem.

## 1.2 Problemática e/ou problemas identificados

Uma queda sem testemunhas pode deixar a pessoa sem condições de pedir ajuda. Partimos desse problema para estudar um dispositivo que identifique movimentos compatíveis com uma queda e avise um cuidador. O botão de pânico atende a outra situação: quando a pessoa consegue pedir ajuda por conta própria. A proposta também inclui localização e aviso de saída de uma área segura, cuja utilidade precisa ser discutida com a instituição.

As projeções do IBGE divulgadas em 2024 mostram que a população com 60 anos ou mais passou de 8,7% em 2000 para 15,6% em 2023, cerca de 33 milhões de pessoas. Para 2070, a projeção é de 37,8%. Esses dados dimensionam o envelhecimento no país, mas não descrevem o público de uma instituição específica.

Novaes et al. (2023) analisaram internações e custos relacionados às quedas entre 2000 e 2020. No estado de São Paulo, encontraram crescimento médio anual de 4,3% nas internações e de 8,5% nos custos totais. O estudo projetou cerca de 150 mil internações e R$ 260 milhões em custos para o SUS em 2025.

Nesta etapa, o diagnóstico é documental; a escuta da instituição vai confirmar ou ajustar a demanda. A pergunta que levaremos é: como avisar os cuidadores sobre uma possível queda ou afastamento, com localização disponível e custo de manutenção compatível com sua rotina? A escuta deve esclarecer quais ocorrências preocupam a equipe, como o atendimento funciona hoje e se as funções propostas são úteis.

## 1.3 Justificativa

Escolhemos uma aplicação de microcontroladores ligada ao cuidado de pessoas idosas. O desenvolvimento permite aplicar programação em C, leitura de sensores e comunicação entre periféricos a uma necessidade que será discutida fora da sala de aula. A seleção do hardware exige comparar consumo, dimensões e custo com os recursos necessários ao dispositivo.

A proposta usa ESP32, sensor MPU6050, localização por GNSS e comunicação 4G. O alerta deve chegar a um backend e aparecer em um painel web, cuja tecnologia ainda não foi definida. Para os cuidadores, o benefício esperado é receber o aviso e a localização disponível; o atendimento continua dependendo da equipe. Não temos medições que comprovem redução no tempo de socorro.

Construir o protótipo permite estudar o algoritmo e adaptar o modo de alerta. Isso, por si só, não demonstra vantagem sobre um produto pronto. A comparação com botões de emergência, relógios com localização e serviços de teleassistência precisa considerar custo total, suporte e facilidade de operação. As faixas de preço do levantamento inicial não têm identificação suficiente de modelos e fornecedores para sustentar uma comparação conclusiva.

Pretendemos publicar o código e a documentação sob licença GNU GPL v3. A oficina permitirá observar se uma pessoa de fora do grupo consegue seguir as instruções e em quais etapas precisa de ajuda. A necessidade de apoio técnico será um dos resultados dessa avaliação.

## 1.4 Objetivos/resultados/efeitos a serem alcançados

1. Desenvolver e avaliar um protótipo vestível de baixo custo para detectar possíveis quedas, receber pedidos manuais de ajuda e avisar cuidadores sobre a saída de uma área segura, informando a localização disponível.

2. Publicar o hardware e o firmware como projeto aberto, sob licença GNU GPL v3, com lista de materiais e instruções de montagem e configuração, avaliando sua compreensão por uma pessoa de fora do grupo.

3. Capacitar a equipe da instituição para montar, configurar e operar o dispositivo em uma oficina prática, registrando as dificuldades e o nível de apoio necessário.

A avaliação combina ensaios técnicos com a participação da equipe. Quedas simuladas serão feitas somente por adultos saudáveis em ambiente controlado, nunca por pessoas idosas. Os cuidadores poderão avaliar a operação dos alertas, realizar o exercício de configuração e responder ao formulário de reação. As metas e os métodos de medição estão na seção 2.4 do planejamento.

## 1.5 Referencial teórico

O IBGE (2024) fornece a base demográfica do diagnóstico. O aumento da participação de pessoas idosas na população situa o tema; os requisitos do MeuAmparo dependem de informações sobre a instituição.

Novaes et al. (2023) mostram a evolução das internações e dos gastos relacionados a quedas. O estudo fundamenta a relevância do problema, não a eficácia de uma solução vestível, que o protótipo ainda precisa demonstrar.

Sucerquia, López e Vargas-Bonilla (2017) apresentam o SisFall, conjunto de registros de quedas e movimentos cotidianos obtidos por sensores inerciais. Essa referência orienta o estudo da diferença entre uma queda e ações que também produzem acelerações bruscas. No projeto, a sequência de movimento, impacto e orientação será investigada no firmware. Os dados de referência complementam, e não substituem, os testes com a placa, o sensor e a posição de uso escolhidos.

O roteiro da disciplina relaciona a escolha do microcontrolador aos requisitos da aplicação e prevê desenvolvimento em C, integração de periféricos e testes. Seguiremos essa relação entre requisito, implementação e verificação: cada função proposta precisa de um ensaio que permita observar seu funcionamento. O planejamento de extensão também exige participação da parte interessada na validação e na avaliação, o que vincula o desenvolvimento técnico à rotina de quem utilizará a solução.

O tratamento de localização e dos registros dos participantes exige definir finalidade, acesso, armazenamento e descarte. A hospedagem no Brasil é uma proposta do projeto e não comprova, isoladamente, conformidade com a LGPD. As condições de participação e registro serão acordadas antes das atividades com a instituição.

## Referências

ESTÁCIO. Programação de Microcontroladores ARA4710: roteiro de extensão. Material da disciplina disponibilizado pelo Prof. Omar Sacilotto Donaires. Ribeirão Preto, 2026.2.

IBGE. População do país vai parar de crescer em 2041. Agência de Notícias, 22 ago. 2024. Disponível em: https://agenciadenoticias.ibge.gov.br/agencia-noticias/2012-agencia-de-noticias/noticias/41056-populacao-do-pais-vai-parar-de-crescer-em-2041. Acesso em: 9 set. 2026.

NOVAES, Areta Dames Cachapuz et al. Acidentes por quedas na população idosa: análise de tendência temporal de 2000 a 2020 e o impacto econômico estimado no sistema de saúde brasileiro em 2025. Ciência & Saúde Coletiva, v. 28, n. 11, p. 3101–3110, 2023. DOI: https://doi.org/10.1590/1413-812320232811.15722022.

SUCERQUIA, Angela; LÓPEZ, José David; VARGAS-BONILLA, Jesús Francisco. SisFall: a fall and movement dataset. Sensors, v. 17, n. 1, art. 198, 2017. DOI: https://doi.org/10.3390/s17010198.
