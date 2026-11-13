# Week 4: Station 4 — The Colored Pencil Box (SoA vs. AoS & Cache Lines)

> *"How you organize data in memory matters more than how clever your loops are."*

---

## 1. The Story: The Mystery of the Slow Loop
Two programmers wrote loops to compute the average brightness of an image.
Both loops had the exact same number of operations ($N$ additions and $N$ divisions).
Yet Programmer A's loop ran in **1.2 milliseconds**, while Programmer B's loop took **4.8 milliseconds**—four times slower!

Why? Because Programmer B ignored the **CPU Cache Line**.

---

## 2. The Metaphor: The Pencil Trays
When the CPU needs a byte from memory, it cannot grab just one byte. Physical memory buses always fetch a contiguous chunk of **64 bytes** at a time—called a **Cache Line**.

Imagine you are coloring an entire landscape and only need **Red pencils**:
* **AoS (Array of Structs)**: The pencils are packed in 3-packs: `[Red, Green, Blue]`, `[Red, Green, Blue]`, `[Red, Green, Blue]`...
  Every time you grab a pack for 1 Red pencil, you are forced to carry 2 pencils you don't need! **66% of your memory bandwidth is wasted.**
* **SoA (Struct of Arrays / Planar Bands)**: All Red pencils are lined up together in their own tray: `[Red, Red, Red, Red, Red...]`.
  When you grab a tray, **every single byte in the 64-byte cache line is 100% useful payload!**

```
AoS Memory:  [ R | G | B ][ R | G | B ][ R | G | B ]  <-- Strided, cache wasted
SoA Memory:  [ R | R | R | R | R | R ][ G | G | G ]  <-- 100% contiguous bandwidth!
```

---

## 3. Real Systems Connection: `rcvc`'s Planar Tile Engine
`rcvc` is architected around **SoA tiles**: flat planar sample arrays per channel.
By using "bands in, bands out" with no per-pixel AoS packing, `rcvc` saturates the CPU memory bus and outruns traditional image engines like GraphicsMagick.

---

## 4. Code Sample: SoA vs. AoS Layouts
```c
#include "rcre_learn.h"
#include <stdio.h>

// AoS Layout (Standard, but scattered memory access)
typedef struct { uint8_t r, g, b; } PixelAoS;
PixelAoS aos_image[1024];

// SoA Layout (Planar, 100% Cache Friendly)
typedef struct {
    uint8_t r[1024];
    uint8_t g[1024];
    uint8_t b[1024];
} ImagePlanarSoA;
```

---

## 5. Your Mission: Planar Band Averaging
In `starter.c`, calculate the average intensity of the Red channel across an SoA planar tile.
