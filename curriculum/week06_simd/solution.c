#include "rcre_learn.h"
#include <stdio.h>

void vector_scale_custom(const float* a, float scale, float* out, size_t n) {
    if (!a || !out) return;
    for (size_t i = 0; i < n; ++i) {
        out[i] = a[i] * scale;
    }
}

int main(void) {
    RL_HAL hal = rl_hal_init();
    printf("Hardware HAL: %s\n", hal.backend_name);

    float data[4] = {1.5f, 2.5f, 3.5f, 4.5f};
    float result[4];

    vector_scale_custom(data, 2.0f, result, 4);
    for (int i = 0; i < 4; ++i) {
        printf("%.2f * 2.0 = %.2f\n", data[i], result[i]);
    }

    return 0;
}
