#include <string.h>

#include "ma_test.h"
#include "meuamparo/alert.h"
#include "meuamparo/device.h"

static const ma_device_input_t NONE = {false, false, false};
static const ma_device_input_t FALL = {true, false, false};
static const ma_device_input_t BUTTON = {false, true, false};
static const ma_device_input_t GEO = {false, false, true};

static void setup(ma_device_t *d)
{
    ma_device_config_t cfg = ma_device_default_config();
    ma_device_init(d, &cfg);
}

static void test_panic_sends_immediately(void)
{
    ma_device_t d;
    setup(&d);
    ma_device_output_t o = ma_device_step(&d, 1000, BUTTON);
    MA_CHECK(o.send && o.kind == MA_ALERT_PANIC);
    MA_CHECK(o.led && o.buzzer);

    /* O aviso local desliga sozinho depois de alarm_ms. */
    o = ma_device_step(&d, 1000 + d.cfg.alarm_ms, NONE);
    MA_CHECK(d.state == MA_DEV_MONITORING);
    MA_CHECK(!o.led && !o.buzzer);
}

static void test_fall_waits_cancel_window(void)
{
    ma_device_t d;
    setup(&d);
    ma_device_output_t o = ma_device_step(&d, 0, FALL);
    MA_CHECK(!o.send);
    MA_CHECK(d.state == MA_DEV_FALL_PENDING);
    MA_CHECK(o.led && o.buzzer);  /* começa aceso, para a pessoa perceber na hora */

    o = ma_device_step(&d, d.cfg.cancel_window_ms - 20, NONE);
    MA_CHECK(!o.send);
    o = ma_device_step(&d, d.cfg.cancel_window_ms, NONE);
    MA_CHECK(o.send && o.kind == MA_ALERT_FALL);
}

static void test_button_cancels_fall(void)
{
    ma_device_t d;
    setup(&d);
    ma_device_step(&d, 0, FALL);
    ma_device_output_t o = ma_device_step(&d, 3000, BUTTON);
    MA_CHECK(o.cancelled && !o.send);
    MA_CHECK(d.state == MA_DEV_MONITORING);

    /* Cancelado não volta a disparar quando a janela original venceria. */
    o = ma_device_step(&d, d.cfg.cancel_window_ms + 100, NONE);
    MA_CHECK(!o.send);
}

static void test_no_window_sends_fall_at_once(void)
{
    ma_device_config_t cfg = ma_device_default_config();
    cfg.cancel_window_ms = 0;
    ma_device_t d;
    ma_device_init(&d, &cfg);
    ma_device_output_t o = ma_device_step(&d, 0, FALL);
    MA_CHECK(o.send && o.kind == MA_ALERT_FALL);
}

static void test_geofence_is_silent(void)
{
    ma_device_t d;
    setup(&d);
    ma_device_output_t o = ma_device_step(&d, 0, GEO);
    MA_CHECK(o.send && o.kind == MA_ALERT_GEOFENCE);
    MA_CHECK(o.led && !o.buzzer);
}

static void test_button_during_alarm_is_new_request(void)
{
    ma_device_t d;
    setup(&d);
    ma_device_step(&d, 0, GEO);
    ma_device_output_t o = ma_device_step(&d, 1000, BUTTON);
    MA_CHECK(o.send && o.kind == MA_ALERT_PANIC);
    MA_CHECK(o.buzzer);
}

static void test_alert_json(void)
{
    ma_alert_t a = {"ma-01", MA_ALERT_FALL, 12840, {-21.1775, -47.8103}};
    char buf[160];
    const int n = ma_alert_format(buf, sizeof buf, &a);
    MA_CHECK(n > 0 && (size_t)n < sizeof buf);
    MA_CHECK(strcmp(buf, "{\"device\":\"ma-01\",\"kind\":\"fall\",\"t_ms\":12840,"
                         "\"lat\":-21.177500,\"lon\":-47.810300}") == 0);

    /* Buffer curto: o retorno avisa que cortou. */
    char small[16];
    MA_CHECK(ma_alert_format(small, sizeof small, &a) >= (int)sizeof small);
}

int main(void)
{
    test_panic_sends_immediately();
    test_fall_waits_cancel_window();
    test_button_cancels_fall();
    test_no_window_sends_fall_at_once();
    test_geofence_is_silent();
    test_button_during_alarm_is_new_request();
    test_alert_json();
    MA_REPORT();
}
