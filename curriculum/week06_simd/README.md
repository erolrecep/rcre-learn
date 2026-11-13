# Week 6: Station 6 — The 8-Lane Highway (SIMD & The Dynamic HAL)

> *"Why add numbers one by one when you can stamp 8 additions in a single heartbeat?"*

---

## 1. The Story: The Speed of Light Limit
For decades, computer chips got faster by increasing their clock speed (1 MHz $\rightarrow$ 1 GHz $\rightarrow$ 3 GHz).
Around 2005, chips hit the "thermal wall": running them any faster would melt the silicon!
Chip architects realized: **to go faster, we must do more work per clock cycle.**
This birthed **SIMD**: Single Instruction, Multiple Data.

---

## 2. The Metaphor: The 8-Arm Robotic Press
* **Scalar Code (1-Lane Country Road)**: A worker picks up number $A_0$ and $B_0$, adds them, and stores the result. Then moves to $A_1$ and $B_1$. To add 8 numbers, it takes 8 steps.
* **SIMD Vector Code (8-Lane Superhighway)**: A robotic press lowers 8 arms at once. In one single clock tick, it adds $(A_0+B_0, A_1+B_1, \dots, A_7+B_7)$ simultaneously!

### The Challenge: Different Silicon Speaks Different Languages
* Apple Silicon uses **ARM NEON** (128-bit vectors, 4 floats at a time).
* Intel & AMD use **x86 AVX2** (256-bit vectors, 8 floats at a time) or **AVX-512** (16 floats).
* Web browsers use **WebAssembly SIMD128**.

### The Solution: The Dynamic Hardware Abstraction Layer (HAL)
Instead of writing separate apps for every computer, we write an **Engine Dispatch Table**.
At program startup, the engine queries the CPU:
> *"Are you an Apple chip? Great, use NEON. Are you an Intel chip? Use AVX2. If unknown, use our reliable scalar loop."*

---

## 3. Real Systems Connection: `rcre_hal`
`rcre` and `rcvc` use this exact dynamic HAL structure. A single function pointer call dispatches into tuned vector kernels with zero branching overhead inside the loop.

---

## 4. Code Sample: The Dynamic HAL
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    RL_HAL hal = rl_hal_init();
    printf("Detected Hardware Acceleration Backend: %s\n", hal.backend_name);

    float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float b[4] = {10.0f, 20.0f, 30.0f, 40.0f};
    float out[4];

    hal.vector_add(a, b, out, 4);
    for (int i = 0; i < 4; ++i) {
        printf("Index %d: %.1f + %.1f = %.1f\n", i, a[i], b[i], out[i]);
    }

    return 0;
}
```

---

## 5. Your Mission: Vector Scaling
In `starter.c`, complete the vector scalar multiplication kernel and connect it through the HAL dispatch table.
