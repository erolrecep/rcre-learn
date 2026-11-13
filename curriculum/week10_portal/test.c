#include <stdint.h>
#include <stdio.h>
#include <assert.h>

void apply_duotone_filter(uint8_t* rgba, int count) {
    if (!rgba) return;
    for (int i = 0; i < count * 4; i += 4) {
        uint8_t r = rgba[i];
        uint8_t g = rgba[i+1];
        uint8_t b = rgba[i+2];
        uint8_t gray = (uint8_t)(((uint32_t)r * 19595 + (uint32_t)g * 38469 + (uint32_t)b * 7472) >> 16);

        if (gray > 128) {
            rgba[i]   = 0;
            rgba[i+1] = 255;
            rgba[i+2] = 255;
        } else {
            rgba[i]   = 120;
            rgba[i+1] = 0;
            rgba[i+2] = 120;
        }
    }
}

int main(void) {
    printf("[Week 10 Test] Testing WASM FFI Pixel Processing & Capstone Filter...\n");

    uint8_t pixels[8] = {
        255, 255, 255, 255, // Pixel 0: Bright white
        0, 0, 0, 255        // Pixel 1: Pure black
    };

    apply_duotone_filter(pixels, 2);

    // Pixel 0 should become Cyan
    assert(pixels[0] == 0);
    assert(pixels[1] == 255);
    assert(pixels[2] == 255);
    assert(pixels[3] == 255); // Alpha preserved

    // Pixel 1 should become Magenta
    assert(pixels[4] == 120);
    assert(pixels[5] == 0);
    assert(pixels[6] == 120);
    assert(pixels[7] == 255); // Alpha preserved

    printf("  \033[32m✔ Week 10 PASSED:\033[0m WASM buffer mutation & image filter pipeline verified.\n");
    return 0;
}
