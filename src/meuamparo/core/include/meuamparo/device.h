#ifndef MEUAMPARO_DEVICE_H
#define MEUAMPARO_DEVICE_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Máquina de estados do dispositivo. Recebe eventos já decididos (queda confirmada,
 * botão apertado, saída da área segura) e diz o que fazer com LED, buzzer e alerta.
 *
 * Depois de uma queda existe uma janela de cancelamento: LED e buzzer avisam a própria
 * pessoa, e o botão cancela o alerta se ela estiver bem. É a defesa contra alarme falso
 * que não depende de afinar limiar. Fora dessa janela o botão é pedido de ajuda e o
 * alerta sai na hora, sem pergunta.
 *
 * A saída da área segura não toca o buzzer. A pessoa desorientada não precisa de um
 * apito na rua; quem precisa saber é o cuidador.
 */

typedef enum {
    MA_ALERT_FALL,
    MA_ALERT_PANIC,
    MA_ALERT_GEOFENCE,
} ma_alert_kind_t;

typedef enum {
    MA_DEV_MONITORING,
    MA_DEV_FALL_PENDING,  /* queda detectada, dentro da janela de cancelamento */
    MA_DEV_ALARM,         /* alerta enviado, aviso local ligado */
} ma_dev_state_t;

typedef struct {
    uint32_t cancel_window_ms;  /* 0 envia o alerta de queda sem janela */
    uint32_t alarm_ms;          /* quanto tempo o aviso local fica ligado depois do envio */
    uint32_t blink_ms;          /* meio período do pisca durante a janela */
} ma_device_config_t;

typedef struct {
    ma_device_config_t cfg;
    ma_dev_state_t state;
    uint32_t t_state;
    bool buzzer_in_alarm;  /* geofence liga só o LED */
} ma_device_t;

typedef struct {
    bool fall;           /* ma_fall_update devolveu true nesta amostra */
    bool button;         /* borda de apertar do botão, não o nível */
    bool geofence_exit;  /* ma_geofence_update devolveu true nesta posição */
} ma_device_input_t;

typedef struct {
    bool led;
    bool buzzer;
    bool send;              /* enviar alerta agora, do tipo em kind */
    ma_alert_kind_t kind;
    bool cancelled;         /* a pessoa cancelou um alerta de queda nesta chamada */
} ma_device_output_t;

ma_device_config_t ma_device_default_config(void);

void ma_device_init(ma_device_t *d, const ma_device_config_t *cfg);

/* Um passo da máquina. Chamado a cada amostra, com ou sem evento. */
ma_device_output_t ma_device_step(ma_device_t *d, uint32_t t_ms, ma_device_input_t in);

const char *ma_alert_kind_name(ma_alert_kind_t k);

#endif /* MEUAMPARO_DEVICE_H */
