#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
    printf("[Week 02 Test] Testing Linear Memory Arena...\n");

    uint8_t buffer[1024];
    RL_Arena arena;
    rl_arena_init(&arena, buffer, sizeof(buffer));

    assert(arena.capacity == 1024);
    assert(arena.offset == 0);

    // Allocation 1: 100 bytes aligned to 8
    void* p1 = rl_arena_alloc(&arena, 100, 8);
    assert(p1 != NULL);
    assert(((uintptr_t)p1 % 8) == 0);
    assert(arena.offset == 100);

    // Allocation 2: 50 bytes aligned to 64
    void* p2 = rl_arena_alloc(&arena, 50, 64);
    assert(p2 != NULL);
    assert(((uintptr_t)p2 % 64) == 0);
    assert(arena.offset >= 150);

    // Test mark and release (RL_ArenaTemp)
    RL_ArenaTemp temp = rl_arena_temp_begin(&arena);
    size_t saved = arena.offset;
    void* p3 = rl_arena_alloc(&arena, 200, 8);
    assert(p3 != NULL);
    assert(arena.offset >= saved + 200);
    rl_arena_temp_end(temp);
    assert(arena.offset == saved);

    // Reset arena
    rl_arena_reset(&arena);
    assert(arena.offset == 0);

    // Test out of capacity
    void* p_huge = rl_arena_alloc(&arena, 2000, 8);
    assert(p_huge == NULL);

    printf("  \033[32m✔ Week 02 PASSED:\033[0m Linear Arena, 64-byte alignment & O(1) reset verified.\n");
    return 0;
}
