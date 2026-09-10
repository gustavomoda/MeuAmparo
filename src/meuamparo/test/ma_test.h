#ifndef MA_TEST_H
#define MA_TEST_H

#include <math.h>
#include <stdio.h>

/*
 * Harness mínimo de teste. Sem framework externo de propósito: o objetivo é que
 * `make test` funcione numa máquina recém-formatada, com nada além do compilador.
 *
 * Os testes não param na primeira falha. Rodam todos e somam, porque quando um ajuste
 * de limiar quebra a detecção é útil ver de uma vez quantos casos regrediram.
 */

static int ma_test_failures = 0;

#define MA_CHECK(cond)                                                        \
    do {                                                                      \
        if (!(cond)) {                                                        \
            printf("  falhou %s:%d: %s\n", __FILE__, __LINE__, #cond);        \
            ma_test_failures++;                                               \
        }                                                                     \
    } while (0)

#define MA_CHECK_NEAR(got, want, tol)                                         \
    do {                                                                      \
        double _got = (got), _want = (want);                                  \
        if (fabs(_got - _want) > (tol)) {                                     \
            printf("  falhou %s:%d: %s = %g, esperado %g (tolerancia %g)\n",  \
                   __FILE__, __LINE__, #got, _got, _want, (double)(tol));     \
            ma_test_failures++;                                               \
        }                                                                     \
    } while (0)

#define MA_REPORT()                                                           \
    do {                                                                      \
        if (ma_test_failures == 0) {                                          \
            printf("  ok\n");                                                 \
            return 0;                                                         \
        }                                                                     \
        printf("  %d verificacao(oes) falharam\n", ma_test_failures);         \
        return 1;                                                             \
    } while (0)

#endif /* MA_TEST_H */
