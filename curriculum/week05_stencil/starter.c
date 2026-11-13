#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

/**
 * 3x3 Box Blur Stencil:
 * Computes the arithmetic mean of a 3x3 neighborhood.
 */
uint8_t box_blur_3x3(const uint8_t patch[3][3]) {
    // TODO: Add all 9 values in patch together and divide by 9!
    (void)patch;
    return 0;
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
