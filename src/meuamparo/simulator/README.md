# simulator

Nada aqui roda na placa. É a bancada de simulação e demonstração.

```
wokwi/    diagram.json e wokwi.toml: o circuito que aparece na tela
chips/    custom chips do Wokwi. GNSS emitindo NMEA, MPU6050 reproduzindo trace gravado
traces/   datasets de queda e de atividade normal
tools/    replayer, gerador de cenário e seeder do painel
```

O Wokwi roda o binário real gerado por `../firmware/`. Os custom chips existem porque o Wokwi não
tem GPS nem modem na biblioteca de peças, e porque o MPU6050 nativo só responde a slider — não
reproduz uma queda gravada.

O objetivo do cenário automático é a demo rodar do play até o alerta chegar no painel, sem ninguém
mexer em nada durante a apresentação.
