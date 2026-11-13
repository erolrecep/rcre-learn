#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

void convert_rgb_array_to_gray(const uint8_t* r, const uint8_t* g, const uint8_t* b, uint8_t* out_gray, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        uint32_t val = ((uint32_t)r[i] * 19595u + (uint32_t)g[i] * 38469u + (uint32_t)b[i] * 7472u);
        out_gray[i] = (uint8_t)(val >> 16);
    }
}

int main(void) {
    uint8_t r[3] = {255, 0, 100};
    uint8_t g[3] = {0, 255, 150};
    uint8_t b[3] = {0, 0, 200};
    uint8_t gray[3];

    convert_rgb_array_to_gray(r, g, b, gray, 3);
    for (int i = 0; i < 3; ++i) {
        printf("Pixel %d: RGB(%u,%u,%u) -> Gray: %u\n", i, r[i], g[i], b[i], gray[i]);
    }
    return 0;
}
