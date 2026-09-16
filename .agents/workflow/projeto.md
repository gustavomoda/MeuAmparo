# O projeto

MeuAmparo é uma proposta de dispositivo vestível de baixo custo para pessoas idosas: detectar
quedas, permitir pedido manual de ajuda e avisar cuidadores sobre a localização e a saída de uma
área segura, principalmente em casos de desorientação. O projeto de extensão prevê parceria com uma
instituição de Ribeirão Preto, documentação aberta sob licença GNU GPL v3 e uma oficina para que a equipe
consiga montar, configurar e operar o dispositivo.

Disciplina Programação de Microcontroladores (ARA4710), Estácio Ribeirão Preto, semestre 2026.2,
orientação do Prof. Omar Sacilotto Donaires.

Discentes:

- Luis Gustavo Moda
- Isabelly Vitoria

O grupo está definido. Menção a "discentes a definir" ou "grupo em formação" em qualquer arquivo
está desatualizada.

## Arquitetura prevista

ESP32, sensor inercial MPU6050, GNSS, conectividade 4G, bateria 18650, botão de pânico, buzzer e
LED. Firmware em C com ESP-IDF. Backend e painel web de alertas e histórico também estão previstos,
sem stack definida. A proposta fala em cuidado com dados pessoais e hospedagem no Brasil; isso não
comprova conformidade com a LGPD e não deve ser apresentado como se comprovasse.

## Metas documentadas

Detectar pelo menos 90% das quedas simuladas, menos de um alarme falso por dia, alerta de saída da
área segura em até dois minutos, autonomia mínima de oito horas, configuração independente em menos
de 15 minutos e avaliação de pelo menos 4/5.

São metas, não resultados. O protocolo do case usa outra métrica de alarme falso, medida por
atividade; são critérios diferentes e não devem ser somados nem confundidos.

## Divergências abertas

Em 16/09/2026 o grupo escolheu a Waveshare ESP32-S3-SIM7670G-4G como plataforma de referência,
com estimativa de R$ 597 a R$ 622 por unidade, e decidiu não comprar: não há tempo hábil até a
entrega. Não existe hardware físico neste semestre; não fale em compra, montagem ou teste físico
como algo previsto. Os dois canvas, o Roteiro 2 em Word e o Markdown de compras ainda
citam a LilyGO T-A7670G R2 importada (R$ 419, teto de R$ 500); isso é texto desatualizado, não
alternativa em aberto. Os valores são estimativas de setembro de 2026, não preço atual nem
comprovante de compra.

O desenvolvimento e os testes são só em simulação, no Wokwi, que é o caminho previsto no roteiro
da disciplina. O roteiro cita software livre e o Wokwi não é; a
escolha ainda precisa ser confirmada com o professor. O Wokwi não tem peça de GNSS nem de modem
celular.

O calendário oficial foi atualizado na Aula 04: seminário de diagnóstico (workshop de canvas) em
02/09, entrega do diagnóstico em 09/09, seminário de planejamento em 16/09, entrega do planejamento
em 23/09, seminário de desenvolvimento em 28/10 e entrega final com seminário de avaliação em
25/11/2026. A Aula 01 e o Canvas trazem as datas antigas (26/08, 02/09 e 21/10).

## Hardware e case

Existem documentos de diagnóstico, planejamento, canvas, prospecção de instituições, cotação,
identidade visual e o modelo paramétrico do case em OpenSCAD, com STL da base e da tampa. O case foi
desenhado para a Waveshare: medidas e encaixes precisam ser conferidos com a placa física antes de
mandar fabricar.

Cintura, peito e braço são posições propostas para avaliação, não decididas. O cordão precisa de
engate de segurança. Teste de queda usa adulto saudável em ambiente controlado, nunca pessoa idosa.

## Parte interessada

Em 09/09/2026 a instituição parceira ainda estava pendente. Casa do Vovô, Lar Padre Euclides e Lar
do Vovô Albano aparecem como candidatas. Prospecção não é parceria firmada, rascunho de e-mail não é
mensagem enviada, atividade planejada não é atividade realizada. A escuta da instituição orienta os
requisitos e a avaliação, com registro das evidências e das autorizações.

## Entrega

Os documentos preveem envio em PDF pela SAVA e citam simulação como alternativa à montagem física.
Confirme a exigência da disciplina e a compatibilidade do simulador antes de depender dessa
alternativa.
