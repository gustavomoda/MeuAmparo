#include <stdint.h>

#include "ma_test.h"
#include "meuamparo/fall.h"

/*
 * Testes do detector de queda com traces SINTÉTICOS. Cada atividade é desenhada aqui,
 * em código, a partir da forma de onda descrita na literatura: queda livre, pico de
 * impacto, imobilidade. Servem para provar que a lógica das três fases faz o que
 * promete e para pegar regressão quando um limiar mudar.
 *
 * O número que sai no final NÃO é a taxa de detecção da meta de 90%. Essa só vale
 * medida contra registros reais de pessoas (SisFall ou FallAllD, com licença conferida).
 * Aqui os traces foram escritos sabendo como o detector funciona.
 */

#define RATE_HZ 50
#define DT_MS (1000 / RATE_HZ)

/* Gerador pseudoaleatório fixo: o mesmo trace em toda execução e em toda máquina. */
static uint32_t rng_state;

static float rnd(void)
{
    rng_state = rng_state * 1664525u + 1013904223u;
    return (float)(rng_state >> 8) / 16777216.0f;
}

static float uniform(float lo, float hi)
{
    return lo + (hi - lo) * rnd();
}

typedef struct {
    ma_fall_detector_t det;
    uint32_t t;
    int detections;
} run_t;

static void run_init(run_t *r)
{
    ma_fall_config_t cfg = ma_fall_default_config();
    ma_fall_init(&r->det, &cfg);
    r->t = 0;
    r->detections = 0;
}

/* Alimenta o detector com uma magnitude por amostra, mais ruído de sensor. O valor vai
 * todo no eixo Z porque o detector só olha o módulo do vetor. */
static void feed(run_t *r, float mag, int ms)
{
    for (int i = 0; i < ms / DT_MS; i++) {
        ma_imu_sample_t s = {r->t, 0.0f, 0.0f, mag + uniform(-0.05f, 0.05f), 0, 0, 0};
        if (ma_fall_update(&r->det, &s)) {
            r->detections++;
        }
        r->t += DT_MS;
    }
}

static void still(run_t *r, int ms) { feed(r, 1.0f, ms); }

static void walk(run_t *r, int ms, float amp)
{
    /* Passada de ~2 Hz: a magnitude oscila em torno de 1 g. */
    for (int i = 0; i < ms / DT_MS; i++) {
        const int phase = i % 25;
        const float m = 1.0f + amp * (phase < 12 ? (float)phase / 12 : (float)(25 - phase) / 13) -
                        amp / 2;
        feed(r, m, DT_MS);
    }
}

/* ---------------------------------------------------------------- quedas */

static void fall_hard(run_t *r)
{
    walk(r, 2000, 0.4f);
    feed(r, uniform(0.1f, 0.4f), (int)uniform(200, 400));  /* queda livre */
    feed(r, uniform(2.8f, 4.5f), 60);                      /* impacto */
    feed(r, uniform(1.3f, 1.8f), 200);                     /* rebote */
    still(r, 3000);                                        /* caído, sem levantar */
}

/* Queda amortecida (tapete, cama, apoio no braço): impacto mais fraco. Parte desses casos
 * fica abaixo do limiar de propósito, para que o teste mostre o limite do método. */
static void fall_soft(run_t *r)
{
    walk(r, 2000, 0.3f);
    feed(r, uniform(0.2f, 0.45f), (int)uniform(150, 300));
    feed(r, uniform(2.0f, 3.0f), 60);
    still(r, 3000);
}

/* ---------------------------------------------- atividades do dia a dia */

static void adl_walk(run_t *r) { walk(r, 10000, 0.5f); }

static void adl_sit_hard(run_t *r)
{
    /* Sentar de uma vez: vale curto que não chega a queda livre, impacto moderado. */
    walk(r, 2000, 0.3f);
    feed(r, uniform(0.55f, 0.75f), 300);
    feed(r, uniform(1.8f, 2.4f), 60);
    still(r, 3000);
}

static void adl_jump(run_t *r)
{
    /* Pulo tem queda livre e impacto de verdade. O que salva é voltar a andar. */
    walk(r, 2000, 0.3f);
    feed(r, 1.8f, 100);
    feed(r, uniform(0.1f, 0.3f), 300);
    feed(r, uniform(2.8f, 3.8f), 60);
    walk(r, 3000, 0.6f);
}

static void adl_lie_down(run_t *r)
{
    walk(r, 2000, 0.3f);
    feed(r, 0.8f, 400);
    feed(r, 1.2f, 400);
    still(r, 4000);
}

static void adl_run(run_t *r)
{
    /* Corrida: cada passada tem fase aérea e pisada forte. */
    for (int i = 0; i < 12; i++) {
        feed(r, uniform(0.3f, 0.5f), 120);
        feed(r, uniform(2.5f, 3.2f), 60);
        feed(r, 1.0f, 200);
    }
}

static void adl_fall_and_get_up(run_t *r)
{
    /* Caiu e levantou logo: não deve gerar alerta automático. Se precisar, há o botão. */
    walk(r, 2000, 0.3f);
    feed(r, 0.2f, 300);
    feed(r, 3.5f, 60);
    feed(r, 1.0f, 600);
    walk(r, 3000, 0.6f);
}

/* ----------------------------------------------------------------- testes */

static void test_phases(void)
{
    /* Caso feito à mão, sem ruído aleatório escondendo o motivo de uma falha. */
    rng_state = 1;
    run_t r;
    run_init(&r);
    still(&r, 1000);
    MA_CHECK(r.det.phase == MA_FALL_IDLE);
    feed(&r, 0.1f, 300);
    MA_CHECK(r.det.phase == MA_FALL_FREEFALL);
    feed(&r, 4.0f, 40);
    MA_CHECK(r.det.phase == MA_FALL_SETTLE);
    still(&r, 3000);
    MA_CHECK(r.detections == 1);
    MA_CHECK(r.det.phase == MA_FALL_IDLE);
}

static void test_single_noise_dip_ignored(void)
{
    rng_state = 2;
    run_t r;
    run_init(&r);
    still(&r, 1000);
    feed(&r, 0.1f, DT_MS);  /* uma amostra só: ruído, não queda */
    feed(&r, 4.0f, 40);
    still(&r, 3000);
    MA_CHECK(r.detections == 0);
}

typedef void (*activity_fn)(run_t *);

static int count_detected(activity_fn fn, int trials, uint32_t seed)
{
    int hits = 0;
    rng_state = seed;
    for (int i = 0; i < trials; i++) {
        run_t r;
        run_init(&r);
        fn(&r);
        hits += r.detections > 0;
    }
    return hits;
}

static void test_synthetic_rates(void)
{
    const int n = 50;

    const int hard = count_detected(fall_hard, n, 10);
    const int soft = count_detected(fall_soft, n, 11);

    struct {
        const char *name;
        activity_fn fn;
    } adls[] = {
        {"andar", adl_walk},
        {"sentar com forca", adl_sit_hard},
        {"pular", adl_jump},
        {"deitar devagar", adl_lie_down},
        {"correr", adl_run},
        {"cair e levantar", adl_fall_and_get_up},
    };

    printf("  traces sinteticos, %d por atividade (nao e a metrica da meta de 90%%)\n", n);
    printf("    queda forte       %2d/%d detectadas\n", hard, n);
    printf("    queda amortecida  %2d/%d detectadas\n", soft, n);

    int false_pos = 0, adl_total = 0;
    for (size_t i = 0; i < sizeof adls / sizeof adls[0]; i++) {
        const int fp = count_detected(adls[i].fn, n, 100 + (uint32_t)i);
        printf("    %-17s %2d/%d alarmes falsos\n", adls[i].name, fp, n);
        false_pos += fp;
        adl_total += n;
    }

    const double sens = 100.0 * (hard + soft) / (2 * n);
    const double spec = 100.0 * (adl_total - false_pos) / adl_total;
    printf("    sensibilidade %.1f%%  especificidade %.1f%%\n", sens, spec);

    /* Queda forte é o caso que o método promete pegar sempre. A amortecida não entra na
     * verificação: ela existe para mostrar o limite, não para passar. */
    MA_CHECK(hard == n);
    MA_CHECK(false_pos == 0);
}

int main(void)
{
    test_phases();
    test_single_noise_dip_ignored();
    test_synthetic_rates();
    MA_REPORT();
}
