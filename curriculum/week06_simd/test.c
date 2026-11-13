#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

int main(void) {
    printf("[Week 06 Test] Testing Dynamic Hardware Abstraction Layer (HAL)...\n");

    RL_HAL hal = rl_hal_init();
    assert(hal.backend_name != NULL);
    assert(hal.vector_add != NULL);
    assert(hal.vector_scale != NULL);

    printf("  Dispatched to: %s\n", hal.backend_name);

    float a[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    float b[8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
    float out_add[8];
    float out_scale[8];

    hal.vector_add(a, b, out_add, 8);
    for (int i = 0; i < 8; ++i) {
        assert(fabsf(out_add[i] - (a[i] + 0.5f)) < 1e-5f);
    }

    hal.vector_scale(a, 3.0f, out_scale, 8);
    for (int i = 0; i < 8; ++i) {
        assert(fabsf(out_scale[i] - (a[i] * 3.0f)) < 1e-5f);
    }

    printf("  \033[32m✔ Week 06 PASSED:\033[0m Dynamic HAL vector arithmetic verified.\n");
    return 0;
}
