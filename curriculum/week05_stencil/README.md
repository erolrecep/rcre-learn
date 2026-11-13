# Week 5: Station 5 — The Magic Stencil (2D Convolutions & Edge Detection)

> *"Slide a tiny window across an image, and the computer begins to see shapes and boundaries."*

---

## 1. The Story: How Self-Driving Cars See Lane Markers
A self-driving car’s camera sees millions of colored pixels every second. How does it know where the road ends and the curb begins?
It looks for **edges**—places where bright colors suddenly turn dark.
To find edges, the computer applies a mathematical tool called a **2D Convolution Stencil**.

---

## 2. The Metaphor: The Magnifying Glass Stencil
Imagine a small card with a $3 \times 3$ grid of cutouts. Each cutout has a tiny weight written on it:
```
Horizontal Sobel Kernel (Gx):
[ -1   0  +1 ]
[ -2   0  +2 ]
[ -1   0  +1 ]
```
You slide this card over every pixel in the image:
1. Multiply the pixel numbers underneath each cutout by the weight on the card.
2. Sum all 9 products together.
3. If the region is flat (e.g. all pixels are white), the positive and negative weights cancel out to **0** (no edge!).
4. If there is a sharp boundary (left is dark, right is bright), the sum explodes into a large positive number (**an edge!**).

---

## 3. Real Systems Connection: `rcre` Computer Vision
In `rcre`, convolutions power everything:
* Gaussian blurring (smoothing camera noise)
* Sobel edge gradients (finding outlines)
* Harris corner detection (tracking features across video frames)

---

## 4. Code Sample: 3x3 Stencil Evaluation
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    // A vertical edge: left side dark (0), right side bright (255)
    uint8_t patch[3][3] = {
        {0, 128, 255},
        {0, 128, 255},
        {0, 128, 255}
    };

    int16_t gx = rl_sobel_dx_3x3(patch);
    int16_t gy = rl_sobel_dy_3x3(patch);
    uint8_t edge_strength = rl_sobel_magnitude(gx, gy);

    printf("Horizontal gradient (Gx): %d\n", gx);
    printf("Vertical gradient   (Gy): %d\n", gy);
    printf("Total edge strength:      %u / 255\n", edge_strength);

    return 0;
}
```

---

## 5. Your Mission: The Box Blur Stencil
In `starter.c`, implement a $3 \times 3$ Box Blur filter that averages the 9 neighboring pixels!
