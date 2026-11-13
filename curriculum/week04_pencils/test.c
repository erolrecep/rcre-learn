#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>

float compute_red_average(const RL_TileSoA* tile) {
    if (!tile) return 0.0f;
    size_t total_pixels = (size_t)tile->width * tile->height;
    if (total_pixels == 0) return 0.0f;
    uint64_t sum = 0;
    for (size_t i = 0; i < total_pixels; ++i) sum += tile->r[i];
    return (float)sum / (float)total_pixels;
}

int main(void) {
    printf("[Week 04 Test] Testing SoA Planar Tiles & Spatial Locality...\n");

    RL_TileSoA tile;
    tile.width = 32;
    tile.height = 32;

    // Fill red channel with constant value 200
    for (size_t i = 0; i < 1024; ++i) {
        tile.r[i] = 200;
        tile.g[i] = 50;
        tile.b[i] = 25;
    }

    float avg = compute_red_average(&tile);
    assert(avg == 200.0f);

    // Test conversion to gray
    uint8_t gray_buffer[1024];
    rl_tile_to_gray(&tile, gray_buffer);

    // Red 200, Green 50, Blue 25:
    // (200*19595 + 50*38469 + 25*7472) >> 16 = (3919000 + 1923450 + 186800) >> 16 = 6029250 >> 16 = 91
    assert(gray_buffer[0] == 91);
    assert(gray_buffer[1023] == 91);

    printf("  \033[32m✔ Week 04 PASSED:\033[0m SoA planar tile memory access & conversion verified.\n");
    return 0;
}
