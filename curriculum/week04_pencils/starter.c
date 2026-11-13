#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

/**
 * Calculate the average intensity of the Red band in an SoA tile.
 */
float compute_red_average(const RL_TileSoA* tile) {
    // TODO: Loop through the tile's Red channel (tile->width * tile->height)
    // Sum all red values and return the float average!
    (void)tile;
    return 0.0f;
}

int main(void) {
    RL_TileSoA tile;
    tile.width = RL_TILE_SIZE;
    tile.height = RL_TILE_SIZE;

    // Fill red channel with values
    for (size_t i = 0; i < RL_TILE_PIXELS; ++i) {
        tile.r[i] = (uint8_t)(i % 256);
        tile.g[i] = 0;
        tile.b[i] = 0;
    }

    float avg = compute_red_average(&tile);
    printf("Average Red Channel Intensity: %.2f\n", avg);
    return 0;
}
