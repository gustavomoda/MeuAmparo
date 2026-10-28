#include "display.h"

#include <stdio.h>
#include <string.h>

#include "esp_check.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_ssd1306.h"
#include "font5x7.h"
#include "i2c_bus.h"

#define OLED_ADDR   0x3C
#define OLED_W      128
#define OLED_H      64

static const char *TAG = "display";
static esp_lcd_panel_handle_t panel;

/* Quadro inteiro em memória, no formato de página do SSD1306: cada byte é uma coluna de
 * 8 pixels na vertical. Desenha-se aqui e manda-se tudo de uma vez. */
static uint8_t fb[OLED_W * OLED_H / 8];

esp_err_t ma_display_init(void)
{
    i2c_master_bus_handle_t bus;
    ESP_RETURN_ON_ERROR(ma_i2c_bus_get(&bus), TAG, "barramento I2C");

    esp_lcd_panel_io_handle_t io;
    esp_lcd_panel_io_i2c_config_t io_cfg = {
        .dev_addr = OLED_ADDR,
        .scl_speed_hz = 400000,
        .control_phase_bytes = 1,
        .dc_bit_offset = 6,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_i2c(bus, &io_cfg, &io), TAG, "io i2c");

    esp_lcd_panel_ssd1306_config_t ssd_cfg = {.height = OLED_H};
    esp_lcd_panel_dev_config_t panel_cfg = {
        .bits_per_pixel = 1,
        .reset_gpio_num = -1,
        .vendor_config = &ssd_cfg,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_ssd1306(io, &panel_cfg, &panel), TAG, "painel");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(panel), TAG, "reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(panel), TAG, "init");
    /* Sem espelhar nos dois eixos o texto sai de cabeça para baixo no SSD1306 do Wokwi.
     * Num módulo físico a orientação precisa ser conferida de novo. */
    ESP_RETURN_ON_ERROR(esp_lcd_panel_mirror(panel, true, true), TAG, "espelha");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(panel, true), TAG, "liga");
    return ESP_OK;
}

/* Marca do MeuAmparo (as duas figuras abraçadas) reduzida a 16x16, no mesmo formato de
 * página do quadro. Gerada a partir de docs/projeto/04-identidade-visual/icones. */
static const uint8_t LOGO16[32] = {
    0x80, 0xC0, 0xE0, 0xFE, 0xFE, 0xDE, 0x8C, 0x00, 0x00, 0x00, 0x98, 0xBC, 0xFC, 0xD8, 0xC0, 0x80,
    0x07, 0x1F, 0x3F, 0x3F, 0x79, 0x71, 0x63, 0x61, 0x62, 0x27, 0x47, 0x63, 0x73, 0x3F, 0x1F, 0x0F,
};

static void pixel(int x, int y, bool on)
{
    if (x < 0 || x >= OLED_W || y < 0 || y >= OLED_H) {
        return;
    }
    uint8_t *b = &fb[x + (y / 8) * OLED_W];
    const uint8_t bit = (uint8_t)(1u << (y % 8));
    *b = on ? (uint8_t)(*b | bit) : (uint8_t)(*b & ~bit);
}

static void rect(int x, int y, int w, int h, bool fill, bool on)
{
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (fill || i == 0 || j == 0 || i == w - 1 || j == h - 1) {
                pixel(x + i, y + j, on);
            }
        }
    }
}

/* Escreve texto a partir de (x, y), ampliando cada pixel da fonte em scale x scale.
 * on=false escreve apagando, para texto escuro sobre fundo aceso. */
static void text(int x, int y, int scale, const char *s, int max_chars, bool on)
{
    for (int n = 0; s != NULL && s[n] != '\0' && n < max_chars; n++) {
        unsigned char c = (unsigned char)s[n];
        if (c < MA_FONT_FIRST || c > MA_FONT_LAST) {
            c = '?';
        }
        const uint8_t *glyph = ma_font5x7[c - MA_FONT_FIRST];
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row < 7; row++) {
                if (glyph[col] & (1u << row)) {
                    rect(x + col * scale, y + row * scale, scale, scale, true, on);
                }
            }
        }
        x += 6 * scale;  /* 5 colunas do glifo e 1 de espaço */
    }
}

static void logo(int x, int y)
{
    for (int col = 0; col < 16; col++) {
        for (int bit = 0; bit < 16; bit++) {
            const uint8_t byte = LOGO16[col + (bit / 8) * 16];
            if (byte & (1u << (bit % 8))) {
                pixel(x + col, y + bit, true);
            }
        }
    }
}

/* Pilha de 14x8 com terminal à direita e preenchimento proporcional à carga. */
static void battery(int x, int y, int pct)
{
    rect(x, y, 14, 8, false, true);
    rect(x + 14, y + 2, 2, 4, true, true);
    const int fill = pct * 10 / 100;
    if (fill > 0) {
        rect(x + 2, y + 2, fill, 4, true, true);
    }
}

/* Anel de raio r1 a r2 em volta de (cx, cy); com only_below, só a metade de baixo. */
static void ring(int cx, int cy, int r1, int r2, int only_below_y)
{
    for (int x = cx - r2; x <= cx + r2; x++) {
        for (int y = cy - r2; y <= cy + r2; y++) {
            const int d2 = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if (d2 >= r1 * r1 && d2 <= r2 * r2 && y >= only_below_y) {
                pixel(x, y, true);
            }
        }
    }
}

/* Carinha feliz no centro do corpo. Para quem usa, "está tudo bem" se lê de longe e
 * sem óculos; a fase do detector e o |a| ficam só no serial. */
static void smile(int cx, int cy)
{
    ring(cx, cy, 18, 20, -1000);           /* rosto */
    ring(cx - 7, cy - 6, 0, 3, -1000);     /* olho esquerdo */
    ring(cx + 7, cy - 6, 0, 3, -1000);     /* olho direito */
    ring(cx, cy, 10, 12, cy + 4);          /* sorriso: só o arco de baixo */
}

/* Triângulo de alerta com "!" vazado, desenhado apagado sobre o fundo aceso. Largura de
 * 24 e altura de 21 pixels: o maior que cabe ao lado do título no corpo de 44. */
static void warning_icon(int x, int y)
{
    const int h = 21, cx = x + 12;
    for (int r = 0; r < h; r++) {
        const int half = r * 12 / (h - 1);
        rect(cx - half, y + r, 2 * half + 1, 1, true, false);
    }
    rect(cx - 1, y + 6, 3, 8, true, true);   /* haste do "!" */
    rect(cx - 1, y + 16, 3, 3, true, true);  /* ponto do "!" */
}

void ma_display_draw(const ma_display_frame_t *f)
{
    if (panel == NULL) {
        return;
    }
    memset(fb, 0, sizeof fb);

    /* Faixa de cima: logo, hora e bateria. */
    logo(0, 0);
    text(22, 5, 1, f->clock, 5, true);
    if (f->battery_pct >= 0) {
        char pct[12];
        snprintf(pct, sizeof pct, "%d%%", f->battery_pct);
        text(110 - 6 * (int)strlen(pct), 5, 1, pct, 4, true);
        battery(111, 4, f->battery_pct);
    }
    rect(0, 18, OLED_W, 1, true, true);

    /* Corpo: em alerta, fundo aceso e texto apagado. */
    const bool on = !f->alert;
    if (f->smile) {
        smile(OLED_W / 2, 42);
    } else if (f->alert) {
        rect(0, 20, OLED_W, OLED_H - 20, true, true);
        warning_icon(4, 22);
        text(34, 25, 2, f->title, 7, on);
        text(4, 46, 1, f->line1, 21, on);
        text(4, 55, 1, f->line2, 21, on);
    } else {
        text(4, 22, 2, f->title, 10, on);
        text(4, 40, 1, f->line1, 21, on);
        text(4, 52, 1, f->line2, 21, on);
    }

    esp_lcd_panel_draw_bitmap(panel, 0, 0, OLED_W, OLED_H, fb);
}
