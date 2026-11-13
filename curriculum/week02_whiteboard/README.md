# Week 2: Station 2 — The Endless Whiteboard (Arena Allocators)

> *"Why pick up crumbs one by one when you can wipe the whole table clean in one swipe?"*

---

## 1. The Story: The Nightmare of Malloc
In traditional C programming, whenever you need memory for a new character, bullet, or image filter, textbooks tell you to call `malloc()`.
Calling `malloc()` is like renting a hotel room:
1. The operating system has to search its books for a vacant room of the right size.
2. It gives you the key (a pointer).
3. If you forget to check out (`free()`), that room stays locked forever (a **memory leak**).
4. Worse, if you check out thousands of tiny rooms, your memory becomes like Swiss cheese (**fragmentation**).

In high-performance engines like **`rcre`** and **`gnew-parallel`**, `malloc()` is strictly forbidden in hot loops!

---

## 2. The Metaphor: The Whiteboard Arena
Instead of renting individual hotel rooms, imagine you buy a giant whiteboard:
* When you need space for 10 numbers, you take a marker, draw a box, and slide a pointer (`offset`) to the right.
* When you need space for an image, you draw another box and slide the pointer further.
* When the frame or task finishes? You don't erase every word individually. **You take one giant dry-erase eraser and wipe the marker back to zero in a single swipe ($O(1)$)!**

This is called a **Linear Memory Arena**.

---

## 3. Real Systems Connection: `RCRE_Arena`
In `rcre`, all video frames, tensor intermediate activations, and convolution buffers are allocated on an `RCRE_Arena`.
* Time to allocate: **~1 nanosecond** (just incrementing an offset).
* Memory leaks possible: **Zero** (the whole arena is reclaimed as a unit).

---

## 4. Code Sample: The Arena in Action
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    uint8_t memory_pool[1024]; // 1 KB of stack memory
    RL_Arena arena;
    rl_arena_init(&arena, memory_pool, sizeof(memory_pool));

    // Allocate space for 5 floating-point numbers
    float* scores = (float*)rl_arena_alloc(&arena, 5 * sizeof(float), 8);
    scores[0] = 98.5f;

    printf("Allocated 5 floats. Arena offset: %zu bytes.\n", arena.offset);

    // Instant O(1) bulk reset!
    rl_arena_reset(&arena);
    printf("After reset: Arena offset = %zu bytes.\n", arena.offset);

    return 0;
}
```

---

## 5. Your Mission: The Particle Arena
In `starter.c`, complete the arena allocation logic to allocate an array of particles, verify alignment, and reset the arena!
