#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

uint8_t box_blur_3x3(const uint8_t patch[3][3]) {
    uint32_t sum = 0;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            sum += patch[y][x];
        }
    }
    return (uint8_t)(sum / 9);
}

int main(void) {
    uint8_t patch[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };

    uint8_t blurred = box_blur_3x3(patch);
    printf("Center pixel before: 50 | After 3x3 Box Blur: %u\n", blurred);
    return 0;
}
