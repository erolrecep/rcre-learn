#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

float compute_red_average(const RL_TileSoA* tile) {
    if (!tile) return 0.0f;
    size_t total_pixels = (size_t)tile->width * tile->height;
    if (total_pixels == 0) return 0.0f;

    uint64_t sum = 0;
    // Sequential, contiguous memory read — saturates CPU cache lines!
    for (size_t i = 0; i < total_pixels; ++i) {
        sum += tile->r[i];
    }

    return (float)sum / (float)total_pixels;
}

int main(void) {
    RL_TileSoA tile;
    tile.width = RL_TILE_SIZE;
    tile.height = RL_TILE_SIZE;

    for (size_t i = 0; i < RL_TILE_PIXELS; ++i) {
        tile.r[i] = 128;
        tile.g[i] = 0;
        tile.b[i] = 0;
    }

    float avg = compute_red_average(&tile);
    printf("Average Red Channel Intensity: %.2f\n", avg);
    return 0;
}
