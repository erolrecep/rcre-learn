#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

/**
 * Convert an array of RGB pixels to Grayscale using 15-bit fixed-point math!
 */
void convert_rgb_array_to_gray(const uint8_t* r, const uint8_t* g, const uint8_t* b, uint8_t* out_gray, size_t count) {
    // TODO: Loop through all pixels and compute grayscale using the formula:
    // (19595 * R + 38469 * G + 7472 * B) >> 16
    (void)r;
    (void)g;
    (void)b;
    (void)out_gray;
    (void)count;
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
