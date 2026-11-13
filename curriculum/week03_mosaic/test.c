#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
    printf("[Week 03 Test] Testing 15-bit Fixed-Point Color Spaces...\n");

    // Pure Red (255, 0, 0): 255 * 19595 = 4,996,725 >> 16 = 76
    uint8_t gray_red = rl_rgb_to_gray(255, 0, 0);
    assert(gray_red == 76);

    // Pure Green (0, 255, 0): 255 * 38469 = 9,809,595 >> 16 = 149
    uint8_t gray_green = rl_rgb_to_gray(0, 255, 0);
    assert(gray_green == 149);

    // Pure Blue (0, 0, 255): 255 * 7472 = 1,905,360 >> 16 = 29
    uint8_t gray_blue = rl_rgb_to_gray(0, 0, 255);
    assert(gray_blue == 29);

    // Pure White (255, 255, 255): 76 + 149 + 29 = 254 (due to rounding, clamped in range)
    uint8_t gray_white = rl_rgb_to_gray(255, 255, 255);
    assert(gray_white >= 254 && gray_white <= 255);

    // Pure Black (0, 0, 0): 0
    uint8_t gray_black = rl_rgb_to_gray(0, 0, 0);
    assert(gray_black == 0);

    printf("  \033[32m✔ Week 03 PASSED:\033[0m 15-bit fixed-point color space conversion exact.\n");
    return 0;
}
