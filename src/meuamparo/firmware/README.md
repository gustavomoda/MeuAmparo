# firmware

Só entra aqui código que roda no ESP32-S3. Se não vai para a placa, o lugar é `../simulator/`.

Responsabilidade: ler o MPU6050 por I2C, ler o GNSS por UART, alimentar o `core/` com esses dados
e executar o que o core decidir (acender LED, tocar buzzer, enviar alerta). A lógica de queda e de
área segura não mora aqui, mora em `../core/`.

O envio do alerta passa por uma interface de transporte com duas implementações: Wi-Fi, usada no
Wokwi, e modem 4G, usada na placa. O resto do firmware não sabe qual das duas está ativa.

Nenhum trace, mock ou cenário de teste entra nesta pasta.
