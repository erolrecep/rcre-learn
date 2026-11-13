# Week 9: Station 9 — Teaching Silicon to Learn (Tensors & Autograd)

> *"Artificial Intelligence is not magic; it is millions of simple multiplications tuning themselves."*

---

## 1. The Story: Unmasking the AI Mystery
When you chat with an AI or see a neural network classify an image, what is actually happening?
Underneath all the hype, every neural network is made of two simple passes:
1. **The Forward Pass**: Data flows forward through a chain of multiplications ($x \cdot w$) and additions ($+ b$).
2. **The Backward Pass (Autograd)**: The output is compared against the target answer. The error (gradient) flows backward through the chain of operations, using the **Chain Rule of Calculus** to tell each number: *"You were a little too big, decrease by 0.01"* or *"You were a little too small, increase by 0.05"*.

---

## 2. The Metaphor: The Pinball Machine
Imagine a wooden pinball board with hundreds of tiny tilting pegs.
* You drop a marble at the top (the input image or word).
* The marble bounces down the pegs (forward pass) and lands in a bucket at the bottom (the prediction).
* If it lands in the wrong bucket, you don't rebuild the board from scratch! You trace the marble's path backward, slightly nudge the tilt of each peg along the path (backward pass), and drop the marble again.
* After 1,000 drops, the pegs are tilted so perfectly that the marble lands in the bullseye every single time!

---

## 3. Real Systems Connection: `rcre`'s Autograd & NanoGPT
`rcre` contains a full **Micrograd-style scalar computation graph** and a **NanoGPT transformer** written in pure C23 with zero heap allocations during inference.
Instead of relying on multi-gigabyte Python frameworks, `rcre` builds neural graphs directly in C memory arenas.

---

## 4. Code Sample: Minimal Autograd Node
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    // Equation: y = a * b + c
    RL_Node a, b, c;
    rl_node_init(&a, 3.0f);
    rl_node_init(&b, 4.0f);
    rl_node_init(&c, 5.0f);

    RL_Node mul = rl_node_mul(&a, &b); // 3 * 4 = 12
    RL_Node y   = rl_node_add(&mul, &c); // 12 + 5 = 17

    printf("Forward Pass: 3.0 * 4.0 + 5.0 = %.2f\n", y.val);

    // Backward Pass: Propagate gradients!
    rl_node_backward(&y);

    printf("Gradients:\n");
    printf("  dy/dc = %.2f (Should be 1.0)\n", c.grad);
    printf("  dy/db = %.2f (Should be a.val = 3.0)\n", b.grad);
    printf("  dy/da = %.2f (Should be b.val = 4.0)\n", a.grad);

    return 0;
}
```

---

## 5. Your Mission: The Learning Neuron
In `starter.c`, implement a single-step gradient descent update on a weight parameter!
