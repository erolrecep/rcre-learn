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

    // TODO: Allocate an array of 10 Particle structs from the arena with 8-byte alignment!
    Particle* particles = NULL; // Replace with rl_arena_alloc(...)

    if (!particles) {
        printf("Failed to allocate particles!\n");
        return 1;
    }

    printf("Successfully allocated particles. Current offset: %zu bytes\n", arena.offset);

    // TODO: Reset the arena with one command!

    printf("Arena reset complete. Current offset: %zu bytes\n", arena.offset);
    return 0;
}
