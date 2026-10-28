#ifndef MEUAMPARO_DISPLAY_H
#define MEUAMPARO_DISPLAY_H

#include <stdbool.h>

#include "esp_err.h"

/*
 * Visor do dispositivo. Faixa de cima fixa (logo, hora e bateria) e, abaixo, um título
 * grande e duas linhas pequenas para dizer à pessoa o que está acontecendo.
 *
 * O protótipo prevê um visor touch de 1,69". O Wokwi não tem essa peça, então a
 * simulação usa um OLED SSD1306 de 128x64 no mesmo barramento I2C do MPU6050. Trocar
 * de visor é reescrever display.c; quem chama só conhece este contrato.
 */

typedef struct {
    const char *clock;   /* "HH:MM" */
    int battery_pct;     /* 0 a 100; negativo esconde o indicador */
    const char *title;   /* até 10 caracteres */
    const char *line1;   /* até 21 caracteres */
    const char *line2;
    bool smile;          /* corpo só com uma carinha feliz: "está tudo bem", sem texto */
    bool alert;          /* corpo em vídeo inverso com ícone de alerta, para chamar
                            atenção de longe; o título cabe em até 7 caracteres */
} ma_display_frame_t;

esp_err_t ma_display_init(void);

void ma_display_draw(const ma_display_frame_t *f);

#endif /* MEUAMPARO_DISPLAY_H */
