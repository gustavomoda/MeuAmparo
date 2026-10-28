# simulator

Nada aqui roda na placa. É a bancada de simulação e demonstração.

```
wokwi/
  diagram.json   o circuito: ESP32-S3, MPU6050, visor OLED, botão, buzzer e LED
  wokwi.toml     aponta o Wokwi para o firmware compilado em ../../firmware/build
  scenarios/     testes de integração: cada .yaml mexe no sensor e no botão e
                 confere a linha certa no serial
```

O Wokwi roda o binário real gerado por `../firmware/`, não uma reimplementação.

Três jeitos de usar, todos a partir da raiz do repositório:

- `make sim` roda os cenários sem tela, pelo `wokwi-cli`. É a verificação: passa ou falha.
- A extensão Wokwi do VS Code, abrindo esta pasta `wokwi/`, mostra o circuito e deixa
  apertar o botão e mexer nos sliders do MPU6050 com o mouse.
- `make web` gera um `.bin` único para subir no wokwi.com.

## Mexendo nos sliders do MPU6050

O detector só olha a magnitude `√(x² + y² + z²)`, em g. Não importa qual eixo carrega o
valor, importa a soma. Rotação e temperatura não entram no algoritmo: mexer neles não faz nada.
Os limiares estão em `core/src/fall.c`.

| Fase | Magnitude | Tempo |
|---|---|---|
| Queda livre | < 0,5 g | pelo menos 60 ms seguidos |
| Impacto | ≥ 2,5 g | até 1 s depois da queda livre |
| Imobilidade | entre 0,7 e 1,3 g | 1,5 s, ignorando os 500 ms de rebote |

O que cada fase significa para os três sliders de aceleração:

- Parado (idle): magnitude ≈ 1. Chip deitado: X=0, Y=0, Z=1. Chip de lado: X=1, Y=0, Z=0. Dá
  na mesma.
- Queda livre: os três perto de 0. X=0, Y=0, Z=0.1 → 0,1 g. Com Z=0.1 e Y=0.5 já dá 0,51 g e
  não conta.
- Impacto: qualquer combinação que passe de 2,5. Z=4 sozinho (4 g). Ou X=2, Y=2, Z=0 (2,83 g).
  Ou X=1.5, Y=1.5, Z=1.5 (2,6 g). X=0, Y=1.6, Z=2 dá 2,56 g e passa por pouco.
- Imobilidade: de volta a ≈ 1 e quieto. O `queda.yaml` usa Z=0, X=1: pessoa caída de lado, a
  gravidade mudou de eixo. Poderia ser Y=1 ou Z=1, o detector não distingue.

O slider da extensão vai só até 2 g por eixo, abaixo do impacto. Para passar de 2,5 g na mão é
preciso somar eixos: X=2 e Z=2 dão 2,83 g. Os cenários não têm esse limite, por isso usam Z=4.

Na mão, pela extensão: Z para 0.1, conte meio segundo, X e Z para 2, logo em seguida X para 0 e
Z para 1 e não mexa em nada por 2 s. Qualquer slider que oscile nesse intervalo quebra a imobilidade e o
detector volta a idle, como no `pulo.yaml`. Subir um slider sozinho para 3 g, sem a queda livre
antes, também não alarma: a sequência é obrigatória.

O Wokwi não tem GNSS nem modem 4G. Por isso a posição é fixa no firmware e o alerta sai no
serial. Um custom chip de GNSS ou de reprodução de trace do MPU6050 entraria aqui, numa pasta
própria, se o projeto chegar a precisar.
