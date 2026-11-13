#include "rcre_learn.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
    float x, y, z;
    uint32_t id;
} Particle;

int main(void) {
    uint8_t memory_backing[4096];
    RL_Arena arena;
    rl_arena_init(&arena, memory_backing, sizeof(memory_backing));

    // Allocate 10 Particle structs aligned to 8 bytes
    Particle* particles = (Particle*)rl_arena_alloc(&arena, 10 * sizeof(Particle), 8);
    if (!particles) {
        printf("Failed to allocate particles!\n");
        return 1;
    }

    for (int i = 0; i < 10; ++i) {
        particles[i].x = (float)i;
        particles[i].y = (float)(i * 2);
        particles[i].z = 0.0f;
        particles[i].id = (uint32_t)(100 + i);
    }

    printf("Successfully allocated %d particles. Arena offset: %zu bytes\n", 10, arena.offset);

    // Instant O(1) wipeout
    rl_arena_reset(&arena);
    printf("Arena reset complete. Current offset: %zu bytes\n", arena.offset);

    return 0;
}
