#include <stdint.h>
#include <stdio.h>

void apply_duotone_filter(uint8_t* rgba, int count) {
    if (!rgba) return;
    for (int i = 0; i < count * 4; i += 4) {
        uint8_t r = rgba[i];
        uint8_t g = rgba[i+1];
        uint8_t b = rgba[i+2];

        // 15-bit fixed point grayscale
        uint8_t gray = (uint8_t)(((uint32_t)r * 19595 + (uint32_t)g * 38469 + (uint32_t)b * 7472) >> 16);

        if (gray > 128) {
            rgba[i]   = 0;   // Cyan
            rgba[i+1] = 255;
            rgba[i+2] = 255;
        } else {
            rgba[i]   = 120; // Magenta
            rgba[i+1] = 0;
            rgba[i+2] = 120;
        }
    }
}

int main(void) {
    uint8_t buffer[8] = {
        200, 200, 200, 255, // Pixel 0: Bright
        50, 50, 50, 255     // Pixel 1: Dark
    };

    apply_duotone_filter(buffer, 2);
    printf("Pixel 0: R=%u, G=%u, B=%u (Expected Cyan: 0, 255, 255)\n", buffer[0], buffer[1], buffer[2]);
    printf("Pixel 1: R=%u, G=%u, B=%u (Expected Magenta: 120, 0, 120)\n", buffer[4], buffer[5], buffer[6]);

    return 0;
}
