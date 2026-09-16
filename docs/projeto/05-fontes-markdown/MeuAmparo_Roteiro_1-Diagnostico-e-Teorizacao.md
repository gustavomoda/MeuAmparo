# MeuAmparo

**Dispositivo aberto de detecção de queda e localização para pessoas idosas**

Sociedade de Ensino Superior Estácio de Ribeirão Preto
Bacharelado em Ciência da Computação
Disciplina: Programação de Microcontroladores (ARA4710) — 2026.2
Docente orientador: Prof. Omar Sacilotto Donaires
Discentes: a definir
Ribeirão Preto / SP — setembro de 2026

---

# 1. Diagnóstico e teorização

## 1.1 Identificação das partes interessadas e parceiros

### Situação atual da parceria

A instituição parceira está **a definir**. O grupo iniciou a prospecção em setembro de 2026, partindo da relação oficial de organizações cadastradas no Conselho Municipal do Idoso de Ribeirão Preto, cujos registros são válidos até 31 de março de 2028. A escolha por essa fonte não é acidental: entidades ali inscritas já passaram pelo crivo do conselho municipal, o que dispensa verificação adicional de idoneidade e assegura que atuam formalmente com a população idosa do município.

### Perfil do público participante pretendido

Independentemente de qual instituição venha a firmar a parceria, o público participante direto é composto por pessoas com 60 anos ou mais, de ambos os sexos, atendidas por entidade sem fins lucrativos de Ribeirão Preto. O perfil socioeconômico predominante nessas organizações é de baixa renda, com sustento vindo de aposentadoria ou benefício assistencial, e escolaridade concentrada no ensino fundamental incompleto. Estima-se de 15 a 40 participantes, número a ser confirmado com a instituição.

Dentro desse público, dois subgrupos concentram o risco que o projeto pretende endereçar. O primeiro reúne pessoas com mobilidade reduzida, que fazem uso de bengala ou andador e apresentam histórico de queda. O segundo é formado por pessoas com quadro demencial, sujeitas à desorientação espacial e ao afastamento não percebido do local onde vivem.

O público indireto é composto pelos cuidadores formais, responsáveis pelo acompanhamento diário e pelo primeiro socorro; pelos familiares de referência, que hoje só tomam conhecimento de uma ocorrência quando a instituição consegue telefonar; e pela coordenação técnica, a quem cabe decidir sobre a adoção de qualquer tecnologia no ambiente.

### Instituições em prospecção

O grupo organizou as candidatas em quatro perfis, conforme a natureza do atendimento e a aderência ao problema:

**Instituições de longa permanência de caráter filantrópico.** É o perfil de maior aderência, porque os residentes vivem no local, existe equipe de cuidadores e a queda noturna sem testemunha é o cenário concreto.

| Instituição | Registro CMI | Aderência observada |
|---|---|---|
| Sociedade Espírita Cinco de Setembro (Casa do Vovô) | 004 | Mantém os projetos "Conexão Digital 60+" e "Rede de Proteção 60+", o que indica abertura declarada a soluções tecnológicas |
| Lar Padre Euclides | 006 | Desenvolve o projeto "Viver em Movimento — Reabilitação Funcional e Qualidade de Vida da Pessoa Idosa", diretamente ligado ao risco de queda |
| Associação Assistencial Maria de Nazaré (Lar do Vovô Albano) | 005 | Cinco projetos ativos voltados ao público 60+, incluindo "Bem Viver 60+: Cuidado Integral e Proteção à Pessoa Idosa" |
| Lar dos Velhos da Igreja Presbiteriana (Lar Presbiteriano Lili Ribeiro) | 002 | Abrigo institucional com o projeto "Viver Ativo" |
| Associação de Caridade Santa Rita de Cássia | 003 | Modalidade casa-lar, com grupo reduzido, o que facilita a implantação e o acompanhamento |
| Comunidade Missionária Divina Misericórdia (Casa Santa Dulce dos Pobres) | 034 | Acolhimento institucional |

**Centros-dia.** A pessoa idosa vai e volta diariamente, o que torna relevante o alerta de afastamento da área segura: Cantinho do Céu (registro 031), Instituto Limite, com o Centro Dia do Idoso Viver (028), e o Centro Dia do Idoso da APAE de Ribeirão Preto (015).

**Serviços de atendimento domiciliar.** Aqui a pessoa mora sozinha, e é onde a localização por satélite mais faz diferença, já que não há ninguém por perto quando a queda acontece: Instituto de Desenvolvimento Social Caminhando com Amor, que opera o Serviço de Atendimento Domiciliar (017), ABRACCIA (013), Associação S.O.S. Vidas (020) e Centro de Referência Popular (035).

**Parceria de caráter acadêmico.** A Fundação de Apoio ao Ensino, Pesquisa e Assistência, FAEPA (021), mantém o projeto "60+ Ninguém fica para trás". Traria peso institucional ao trabalho, em contrapartida a um processo de aprovação previsivelmente mais longo.

### Critérios de escolha

A definição da parceira observará quatro critérios, nesta ordem: existência de demanda real declarada pela própria instituição durante a visita de escuta; disponibilidade da equipe para participar do desenvolvimento e dos testes; autorização para registro fotográfico e em vídeo, exigência do roteiro de extensão; e proximidade geográfica, que viabiliza os encontros presenciais dentro do semestre.

### Formalização prevista

Definida a instituição, a parceria será formalizada pela Carta de Apresentação emitida pela Estácio, pela Carta de Autorização assinada pela entidade e por termo de acordo de cooperação. Esses documentos, somados ao termo de autorização de uso de imagem, serão anexados a este roteiro como evidência, conforme exigido.

---

## 1.2 Problemática e problemas identificados

### O país envelhece, e depressa

Segundo as Projeções da População do IBGE (2024), a parcela de brasileiros com 60 anos ou mais saltou de 8,7% em 2000 para 15,6% em 2023, o equivalente a 33 milhões de pessoas, e deve alcançar 37,8% da população em 2070. A idade média do país subiu de 28,3 para 35,5 anos no mesmo intervalo. Não se trata de uma demanda passageira, mas de uma pressão crescente e previsível sobre a rede de cuidado.

### A queda deixou de ser acidente isolado

Silva et al. (2023), analisando os dados do Sistema de Informações Hospitalares do SUS entre 2000 e 2020, encontraram crescimento sustentado tanto das internações quanto dos gastos por quedas na população idosa. No estado de São Paulo, a variação percentual anual média foi de 4,3% nas internações e 8,5% nos custos totais. Os autores projetam que, em 2025, as internações por quedas no Brasil ficariam **próximas de 150 mil, gerando cerca de R$ 260 milhões em custos para o SUS**.

A dimensão do problema aparece também em outros indicadores citados no mesmo estudo. O Estudo Longitudinal da Saúde dos Idosos Brasileiros (ELSI-Brasil) verificou que **25,1% de 4.533 idosos sofreram queda entre 2015 e 2016**, com 1,8% dos casos resultando em fratura de quadril ou fêmur, das quais 31,8% exigiram cirurgia com colocação de prótese. Extrapolando para a população urbana brasileira, os autores estimam **cerca de 6,2 milhões de idosos brasileiros caídos no período de um ano**. Entre 2002 e 2016, o SUS gastou **mais de R$ 1 bilhão** apenas com internações de pessoas idosas por fratura de fêmur.

O risco cresce com a idade. Entre as pessoas que caem, a distribuição por faixa etária é de 26,1% entre 60 e 69 anos, 32,4% entre 70 e 79 anos e 38,1% acima dos 80 — justamente o perfil predominante em instituições de longa permanência.

### O que agrava o desfecho é o tempo até o socorro

Não é apenas a queda que determina a gravidade, mas o intervalo entre ela e o atendimento. Uma pessoa idosa que cai sozinha e não consegue se levantar nem pedir ajuda pode permanecer horas no chão, o que eleva o risco de desidratação, hipotermia, complicações renais e agravamento de fraturas. A queda noturna, a caminho do banheiro, é das mais frequentes e costuma acontecer sem testemunhas.

### A desorientação súbita é o segundo problema

A queda não é o único evento repentino que expõe a pessoa idosa. Entre residentes com quadro demencial, a desorientação espacial faz com que a pessoa saia sozinha, perca a referência do caminho de volta e não consiga pedir ajuda nem informar onde mora. O intervalo entre a saída e a percepção de que ela não está mais no local determina a chance de encontrá-la, e esse intervalo depende hoje de alguém notar a ausência. Os desfechos vão da exposição prolongada ao sol ou ao frio até o atropelamento e o desaparecimento.

São problemas de naturezas distintas, mas de estrutura idêntica: um evento súbito, sem testemunha, em que o tempo de resposta define a gravidade. E ambos se resolvem com a mesma solução técnica, que é saber onde a pessoa está e ser avisado imediatamente.

### O mercado não atende quem mais precisa

O levantamento de preços realizado pelo grupo em setembro de 2026 identificou quatro categorias de solução disponíveis no Brasil:

| Categoria | Faixa de preço | Limitação observada |
|---|---|---|
| Relógios e pulseiras 4G importados, com GPS e detecção de queda | cerca de R$ 220 a R$ 230 | Aplicativo e servidor estrangeiros, sem base legal definida para o tratamento de dados no Brasil; configuração feita por comandos SMS que o familiar não domina; ausência de suporte; detecção no pulso com alta taxa de alarme falso |
| Kits de botão de emergência sem fio, com base receptora | cerca de R$ 380 a R$ 450 | Alcance limitado ao interior da residência, sem localização e sem detecção automática |
| Serviços de teleassistência com central 24 horas | mensalidade recorrente | Custo continuado incompatível com o orçamento de instituição filantrópica |
| Relógios inteligentes de linha | acima de R$ 2.500 | Preço inviável para o público atendido |

Entre o dispositivo importado barato, sem suporte e sem garantia de privacidade, e o serviço de teleassistência com mensalidade, não existe alternativa acessível. É nesse vão que o projeto se posiciona.

### Estágio do diagnóstico

O diagnóstico apresentado até aqui é documental, construído a partir de dados oficiais, literatura científica e levantamento de mercado. O diagnóstico de campo, com a escuta da instituição parceira, está previsto no cronograma para a segunda quinzena de setembro e será incorporado a este roteiro assim que realizado. Dele devem sair a caracterização precisa do público atendido, o histórico de quedas e de episódios de desorientação no local, os recursos hoje utilizados e as prioridades apontadas pela própria equipe.

### Problema priorizado

Pessoas idosas atendidas por instituições filantrópicas de Ribeirão Preto não dispõem de um meio confiável e financeiramente acessível de acionar socorro quando sofrem uma queda estando sozinhas, ou quando se afastam desorientadas do local onde vivem. As instituições que as atendem não têm como adquirir nem manter as soluções existentes no mercado.

---

## 1.3 Justificativa

### O que muda para a pessoa idosa

Cair sozinha e permanecer horas no chão sem conseguir pedir ajuda deixa de ser um desfecho possível. O dispositivo identifica a queda pela assinatura do próprio movimento e dispara o alerta em segundos, informando a localização, ainda que a pessoa esteja desacordada ou sem forças para acionar qualquer coisa. Para quem tem quadro demencial, o afastamento da área segura gera aviso imediato, enquanto ainda há tempo de alcançá-la.

### O que muda para o cuidador e para a família

Hoje a queda é descoberta por acaso: na ronda seguinte, quando alguém ouve o barulho, ou quando a instituição consegue telefonar para o familiar. Com o dispositivo, o aviso chega na hora e informa onde a pessoa está, o que transforma um resgate incerto em resposta dirigida. Para a instituição, isso significa cobrir mais residentes com a mesma equipe, sem ampliar a ronda noturna.

### Por que não simplesmente comprar pronto

As soluções de mercado cobram mensalidade, dependem de aplicativo e servidor hospedados fora do país e são configuradas por comandos SMS que ninguém na instituição domina. O desfecho prático é conhecido: o aparelho é comprado, ninguém consegue configurar, e termina na gaveta. Soma-se a isso a dependência de um fornecedor que pode encerrar o serviço a qualquer momento, sem qualquer garantia sobre o destino dos dados de localização dos residentes.

### Por que o projeto é aberto

Publicando o esquema elétrico, a lista de materiais com fornecedores, o modelo do case e o código-fonte sob licença GNU GPL v3, a instituição passa a conseguir montar as unidades seguintes por conta própria, pagando apenas o preço das peças, sem depender do grupo depois que o semestre acabar. Para uma organização filantrópica, essa autonomia vale mais do que receber um protótipo pronto.

### A lacuna foi verificada projeto a projeto

Em setembro de 2026 o grupo levantou os projetos abertos de detecção de queda publicados no GitHub e comparou cada um com os requisitos desta proposta:

| Projeto | O que faz | O que não cobre |
|---|---|---|
| Kartik9250/Fall_detection | ESP32 com MPU6050, buzzer, botão para cancelar o alarme, gerenciador de rede Wi-Fi e envio de SMS de emergência | Não tem GPS nem conectividade celular própria, e não há servidor nem painel de acompanhamento |
| shivaywadhawan/Fall-Detection | ESP32-S3 com MPU6050 posicionado no peito, voltado ao estudo do algoritmo de detecção | Entrega apenas o algoritmo: sem localização, sem alerta a distância e sem documentação de montagem |
| geoseiden/fall-detection-blynk | ESP32 com MPU6050 e monitoramento pela plataforma Blynk | Depende de plataforma comercial de terceiros, com dados hospedados fora do país e cobrança por dispositivo |
| tonlongthuat/Real-Time-Fall-Detection | Detecção por visão computacional, com ESP32-CAM e a rede YOLO | Exige câmera instalada no ambiente da pessoa idosa, o que levanta objeção de privacidade em quarto e banheiro; não é dispositivo vestível |

Nenhum dos quatro reúne, ao mesmo tempo, conectividade celular autônoma com localização, tratamento de dados hospedado no Brasil, configuração acessível a quem não é técnico e documentação voltada à replicação por uma organização social. Há ainda trabalhos acadêmicos próximos, como o sistema de detecção com ESP32 e Edge Impulse publicado pelo IEEE e o dispositivo vestível descrito no *International Journal of Engineering Inventions*, ambos centrados no desempenho do algoritmo e sem tratar da replicação por terceiros. O projeto, portanto, não parte do zero nem repete o que já existe.

### Relação com a formação e motivação do grupo

Resolver esse problema exige selecionar um dispositivo microcontrolado a partir de requisitos reais e conflitantes entre si, como consumo de energia, tamanho físico, custo unitário e periféricos disponíveis; desenvolver firmware em linguagem C; e integrar sensores por I²C e UART. São as competências centrais da disciplina, exercitadas sobre uma demanda concreta e não sobre um exercício montado para caber no conteúdo.

A motivação do grupo vem de uma constatação simples: a tecnologia necessária para resolver esse problema já existe, é barata e está ao alcance de estudantes de graduação. O que falta não é capacidade técnica, é alguém disposto a montar a solução para quem não pode pagar por ela. É um trabalho em que a competência técnica que estamos desenvolvendo tem efeito direto e verificável sobre a vida de pessoas concretas, e essa possibilidade foi o que levou o grupo a escolher o tema.

---

## 1.4 Objetivos, resultados e efeitos a serem alcançados

1. **Desenvolver** um dispositivo vestível de baixo custo capaz de detectar automaticamente a queda de uma pessoa idosa, alertar sobre o afastamento da área segura e acionar seus cuidadores informando a localização, permitindo também o acionamento manual por botão.

2. **Documentar** o hardware e o firmware como projeto aberto, sob licença GNU GPL v3, incluindo lista de materiais com fornecedores, roteiro de montagem e instruções de configuração, de modo que a instituição consiga replicar unidades adicionais sem apoio técnico externo.

3. **Capacitar** a equipe da instituição a montar, configurar, testar e operar o dispositivo, verificando essa capacitação por meio de oficina prática ao final do projeto.

### Participação do público na avaliação

O atingimento dos objetivos será verificado com a participação direta dos envolvidos, por três instrumentos. O primeiro é o teste assistido de detecção, em que voluntários da equipe simulam quedas em ambiente controlado, com registro de acertos, falhas e alarmes falsos. O segundo é o exercício de autonomia, em que um membro da equipe configura um dispositivo do zero, sem intervenção do grupo, com o tempo cronometrado. O terceiro é a avaliação de reação, por formulário aplicado à coordenação e aos cuidadores, complementada por depoimento em vídeo.

---

## 1.5 Referencial teórico

O projeto se apoia em cinco eixos teóricos: o envelhecimento populacional, a epidemiologia das quedas, a detecção automática por acelerometria, o projeto de sistemas embarcados e, por fim, a metodologia de condução somada ao marco legal aplicável.

**Envelhecimento populacional.** As Projeções da População do IBGE (2024) estabelecem a base demográfica do problema. A população brasileira deve parar de crescer em 2041, com máximo de 220,4 milhões de habitantes, enquanto a proporção de pessoas com 60 anos ou mais praticamente dobrou entre 2000 e 2023 e caminha para 37,8% em 2070. O dado sustenta a afirmação de que a demanda por soluções de cuidado tende a crescer de forma previsível nas próximas décadas.

**Epidemiologia e custo das quedas.** Silva et al. (2023), em *Ciência & Saúde Coletiva*, analisaram a série histórica de internações, óbitos e custos por quedas na população idosa entre 2000 e 2020, a partir do Sistema de Informações Hospitalares do SUS, com regressão por *joinpoint* e cálculo da variação percentual anual média. Encontraram crescimento em todos os segmentos analisados e projetaram, para 2025, cerca de 150 mil internações e R$ 260 milhões em custos. O trabalho é central para este projeto por dois motivos: quantifica o problema em termos que uma banca e uma instituição reconhecem, e demonstra que a tendência é de agravamento, o que justifica investir em detecção precoce em vez de apenas em atendimento posterior. O mesmo estudo reúne indicadores complementares, entre eles os do ELSI-Brasil, que apontam prevalência de queda de 25,1% em coorte de 4.533 idosos, e o gasto superior a R$ 1 bilhão do SUS com internações por fratura de fêmur entre 2002 e 2016.

**Detecção automática de queda por acelerometria.** Sucerquia, López e Vargas-Bonilla (2017), em "SisFall: A Fall and Movement Dataset", publicaram o conjunto de dados que se tornou referência na área, com registros de acelerômetro e giroscópio de quedas simuladas e de atividades cotidianas. O trabalho é relevante aqui por duas razões. Descreve a assinatura característica de uma queda, composta por queda livre, impacto, mudança de orientação e imobilidade posterior, e é essa sequência que fundamenta o algoritmo a ser implementado no firmware. E evidencia o problema central da área, que é distinguir a queda de atividades cotidianas de perfil semelhante, como sentar-se bruscamente. O posicionamento do sensor próximo ao centro de massa, adotado no conjunto de dados, orienta diretamente a decisão de projeto sobre onde o dispositivo deve ser usado.

**Sistemas embarcados e programação de microcontroladores.** Almeida (2016), em *Programação de Sistemas Embarcados*, fornece o método de seleção de dispositivo a partir de requisitos e as práticas de desenvolvimento de firmware em linguagem C, que é o núcleo do problema proposto pela disciplina. Monk (2017) e Zanco (2010) oferecem o contraponto entre famílias e arquiteturas distintas, necessário para que a escolha do microcontrolador seja justificada por comparação, e não por conveniência ou hábito.

**Metodologia e marco legal.** A condução do projeto segue Bender (2015), referência metodológica de aprendizagem baseada em projetos adotada pela disciplina. O tratamento dos dados pessoais dos participantes, em especial a localização, que é dado sensível pelo contexto de uso, observa a Lei nº 13.709/2018 (Lei Geral de Proteção de Dados) e a Lei nº 10.741/2003 (Estatuto da Pessoa Idosa), que fundamenta o dever de proteção e o direito à autonomia da pessoa idosa. Essa observância não é acessória: é o que distingue a solução proposta dos dispositivos importados que enviam a localização de idosos brasileiros a servidores fora do país sem base legal definida.

---

## Referências

ALMEIDA, Rodrigo Maximiniano A. **Programação de sistemas embarcados: desenvolvendo software para microcontroladores em linguagem C**. São Paulo: Grupo GEN, 2016.

BENDER, William N. **Aprendizagem baseada em projetos: educação diferenciada para o século XXI**. Porto Alegre: Penso, 2015.

BRASIL. **Lei nº 10.741, de 1º de outubro de 2003**. Dispõe sobre o Estatuto da Pessoa Idosa.

BRASIL. **Lei nº 13.709, de 14 de agosto de 2018**. Lei Geral de Proteção de Dados Pessoais (LGPD).

CONSELHO MUNICIPAL DO IDOSO DE RIBEIRÃO PRETO. **Organizações da sociedade civil cadastradas**. Ribeirão Preto: Secretaria da Assistência Social, 2026.

INSTITUTO BRASILEIRO DE GEOGRAFIA E ESTATÍSTICA. **Projeções da população do Brasil e unidades da federação por sexo e idade: 2000-2070**. Rio de Janeiro: IBGE, 2024.

MONK, Simon. **Programação com Arduino: começando com sketches**. 2. ed. Porto Alegre: Bookman, 2017.

SILVA, A. et al. Acidentes por quedas na população idosa: análise de tendência temporal de 2000 a 2020 e o impacto econômico estimado no sistema de saúde brasileiro em 2025. **Ciência & Saúde Coletiva**, v. 28, n. 11, p. 3101-3110, nov. 2023. DOI 10.1590/1413-812320232811.15722022.

SUCERQUIA, A.; LÓPEZ, J. D.; VARGAS-BONILLA, J. F. SisFall: a fall and movement dataset. **Sensors**, v. 17, n. 1, p. 198, 2017.

ZANCO, Wagner da Silva. **Microcontroladores PIC18 com linguagem C: uma abordagem prática e objetiva**. São Paulo: Érica, 2010.
