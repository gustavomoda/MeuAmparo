# MeuAmparo — Cotação e estratégia de compra

Levantamento feito em setembro de 2026. Preços mudam; confirme antes de fechar.

---

## 1. A regra de importação mudou a favor do projeto

Desde **12 e 13 de maio de 2026**, a Medida Provisória nº 1.357 **zerou o Imposto de Importação federal para compras internacionais de até US$ 50**, quando feitas em sites certificados no Programa Remessa Conforme (AliExpress e Amazon internacional estão no programa).

| Faixa | Imposto federal | ICMS |
|---|---|---|
| Até US$ 50 | **0%** | 17% a 20% conforme o estado (SP: 18%) |
| Acima de US$ 50 | 30% a 60%, conforme a fonte | 17% a 20% |

A placa que interessa custa entre **US$ 32 e US$ 38**. Fica abaixo do limite, então paga só ICMS. É por isso que importar continua valendo a pena mesmo com o frete.

**Regra prática:** faça pedidos separados, cada um abaixo de US$ 50. Dois itens somando US$ 60 num pedido só entram na faixa cara. Separados, os dois ficam isentos do federal.

> A Receita tem uma calculadora oficial no portal de Compras Internacionais. Use antes de fechar, porque a alíquota estadual e o frete entram na conta.

---

## 2. A estratégia: dividir a compra em dois

O erro clássico é comprar tudo no mesmo lugar. Nenhum canal ganha em tudo.

**Importe da China só a placa 4G/GPS.** É o item caro, é o que não tem equivalente nacional a preço aceitável, e é o único que justifica esperar.

**Compre no Brasil todo o resto.** Sensor, bateria, botão, buzzer, fios: são baratos, chegam em dias, e o frete nacional é menor que a dor de cabeça de esperar.

---

## 3. Comparação dos canais

| | AliExpress (China) | Mercado Livre | Amazon BR | Lojas maker nacionais |
|---|---|---|---|---|
| Preço da placa 4G/GPS | **US$ 32-38** (~R$ 230-270 com ICMS e frete) | R$ 250-400, revenda de importado | pouca oferta de maker | **R$ 590 a R$ 719** |
| Prazo | 20 a 45 dias | 3 a 10 dias | 2 a 7 dias | 3 a 10 dias |
| Nota fiscal | não | sim | sim | sim |
| Garantia na prática | nenhuma | ML te cobre | Amazon te cobre | sim, com suporte |
| Risco de variante errada | **alto** | alto | médio | baixo |
| Componentes pequenos | baratos, mas prazo longo | bom preço e prazo | caro | **melhor opção** |

**Lojas maker nacionais que valem consulta:** Curto Circuito, Eletrogate, Smart Kits, Usinainfo, Baú da Eletrônica, Robocore, Autocore Robótica.

---

## 4. Lista de compras, por canal

### Importar (AliExpress) — pedir hoje

| Item | Especificação exata | Preço |
|---|---|---|
| Placa principal | **LilyGO T-A7670G R2, variante G ou SA, opção COM GPS** | US$ 32-38 |

Já vem com antena 4G, antena GPS, cabo PH2.0, barras de pinos e o conversor USB CH9102F.

### Comprar no Brasil — chega em dias

| Item | Onde | Preço de referência |
|---|---|---|
| MPU6050 (acelerômetro e giroscópio) | Curto Circuito, Eletrogate, ML | R$ 28 |
| Bateria 18650 3500 mAh, marca genuína | ML, lojas de bateria | R$ 45-70 |
| Botão táctil 12 mm, buzzer 5 V, LED RGB | qualquer loja maker | R$ 15 |
| Barras de pinos, jumpers, parafusos M2 | qualquer loja maker | R$ 10 |
| Filamento PETG para o case | ML | R$ 15 (fração do rolo) |
| Cordão com engate de segurança | papelaria, ML | R$ 15 |

### Depois, se o projeto avançar

- Placa portadora, lote de 5 na JLCPCB: cerca de R$ 12 por unidade
- Chip M2M de dados: Arqia, Allcom ou Vivo M2M

---

## 5. Cuidados que evitam prejuízo

**A variante do módulo.** Peça **A7670G** (global) ou **A7670SA** (América do Sul). O **A7670E é europeu** e vai ter cobertura ruim nas bandas brasileiras, principalmente a B28 de 700 MHz, que é a que pega no interior. Mande mensagem ao vendedor confirmando a variante antes de pagar, e guarde o print.

**A opção com GPS.** A mesma placa é vendida com e sem GPS, muitas vezes no mesmo anúncio, com o mesmo preço na vitrine. Confira o seletor antes de finalizar.

**Bateria 18650 falsificada.** Anúncio de 9900 mAh por R$ 15 é mentira: a maior 18650 real do mercado tem cerca de 3600 mAh. Compre Samsung, LG ou Sony de vendedor com reputação, ou a autonomia do projeto vira ficção.

**Disponibilidade nacional é instável.** No levantamento, dois dos três itens que consultei em loja nacional estavam esgotados. Para um kit que ONGs vão replicar, isso precisa constar da documentação com fornecedor alternativo indicado.

**Compre duas placas.** Uma queima na bancada, uma trava na alfândega, e você fica sem protótipo na semana da entrega. A segunda unidade custa menos que o risco.

---

## 6. Prazo, contado de hoje

Pedido feito em **09/set** chega entre **29/set e 24/out**. A entrega final do detalhamento técnico é **25/nov**. Cabe, com folga de três a oito semanas.

E há uma rede de segurança: o Roteiro de Extensão aceita **desenvolvimento e teste por simulação computacional** em software livre, citando o SimulIDE. A montagem física aparece como "eventualmente, se houver recursos disponíveis". Se a placa atrasar ou não chegar, a entrega não cai — o protótipo físico é bônus, não requisito.

---

## Fontes

- Receita Federal — Remessas postal e expressa, regras vigentes desde 12/05/2026
- Contábeis — fim da taxa das blusinhas, compras até US$ 50 isentas de imposto federal
- Curto Circuito — módulo SIM7600G 4G LTE GPS, R$ 719
- Curto Circuito — MPU6050, R$ 28,10
- Smart Kits — LilyGO T-SIM7000G, R$ 589,90
- Importe Eletrônicos — LilyGO T-A7670G/E/SA R2, R$ 169
- Bot'n Roll — T-A7670G R2 com GPS L76K, € 55,50 (referência europeia)
