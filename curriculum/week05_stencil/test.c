#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>

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
    printf("[Week 05 Test] Testing 2D Convolutions & Edge Stencils...\n");

    // Test flat region (should have zero Sobel edge response)
    uint8_t flat[3][3] = {
        {100, 100, 100},
        {100, 100, 100},
        {100, 100, 100}
    };
    int16_t gx_flat = rl_sobel_dx_3x3(flat);
    int16_t gy_flat = rl_sobel_dy_3x3(flat);
    assert(gx_flat == 0);
    assert(gy_flat == 0);
    assert(rl_sobel_magnitude(gx_flat, gy_flat) == 0);

    // Test sharp vertical edge
    uint8_t vertical_edge[3][3] = {
        {0, 0, 255},
        {0, 0, 255},
        {0, 0, 255}
    };
    int16_t gx_vert = rl_sobel_dx_3x3(vertical_edge);
    int16_t gy_vert = rl_sobel_dy_3x3(vertical_edge);
    assert(gx_vert > 500); // Sharp horizontal delta
    assert(gy_vert == 0);  // No vertical delta
    assert(rl_sobel_magnitude(gx_vert, gy_vert) == 255); // Clamped to 255

    // Test box blur
    uint8_t blur_patch[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };
    assert(box_blur_3x3(blur_patch) == 50);

    printf("  \033[32m✔ Week 05 PASSED:\033[0m 2D convolution stencils & edge gradients verified.\n");
    return 0;
}
