#include <stdint.h>
#include <stdio.h>

/**
 * Capstone Mission: Apply a stylized Cyberpunk Duo-Tone filter
 * to an RGBA pixel buffer!
 *
 * If gray > 128: Color becomes Neon Cyan (R: 0, G: 255, B: 255)
 * If gray <= 128: Color becomes Dark Magenta (R: 120, G: 0, B: 120)
 */
void apply_duotone_filter(uint8_t* rgba, int count) {
    // TODO: Loop through all pixels, compute grayscale, and apply duo-tone colors!
    (void)rgba;
    (void)count;
}

int main(void) {
    uint8_t buffer[8] = {
        200, 200, 200, 255, // Pixel 0: Bright
        50, 50, 50, 255     // Pixel 1: Dark
    };

    apply_duotone_filter(buffer, 2);
    printf("Pixel 0: R=%u, G=%u, B=%u\n", buffer[0], buffer[1], buffer[2]);
    printf("Pixel 1: R=%u, G=%u, B=%u\n", buffer[4], buffer[5], buffer[6]);

    return 0;
}
