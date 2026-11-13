# Week 3: Station 3 — The Digital Mosaic (Pixels & 15-bit Fixed-Point Math)

> *"Every digital masterpiece is just a grid of tiny numbers."*

---

## 1. The Story: How Computers See Light
When your phone takes a photo, light hits a silicon sensor array. The sensor splits the light into Red, Green, and Blue channels.
To the computer, an image is not a JPEG or a PNG—it is simply a 2D matrix of numbers:
* Width: Number of columns (e.g. 1920)
* Height: Number of rows (e.g. 1080)
* Each pixel has 3 values: $R \in [0, 255]$, $G \in [0, 255]$, $B \in [0, 255]$.

---

## 2. The Metaphor: The Flashlight Formula
Human eyes are not equally sensitive to all colors!
* We are super sensitive to **Green** (trees, plants).
* Moderately sensitive to **Red**.
* Much less sensitive to **Blue**.

The standard mathematical formula to convert color to grayscale is:
$$Y = 0.299 \cdot R + 0.587 \cdot G + 0.114 \cdot B$$

### The Systems Dilemma: Why Floats Are Slow
Multiplying floating-point numbers ($0.299$, $0.587$) requires floating-point units. On tiny microcontrollers, edge chips, or high-throughput batch servers, float arithmetic consumes extra clock cycles and power.

### The Alchemist's Trick: 15-bit Fixed-Point Arithmetic
What if we multiply everything by $65,536$ ($2^{16}$) and work entirely in integers?
* $0.299 \times 65536 \approx 19595$
* $0.587 \times 65536 \approx 38469$
* $0.114 \times 65536 \approx 7472$

Formula:
$$Y = (19595 \cdot R + 38469 \cdot G + 7472 \cdot B) \gg 16$$
By shifting right by 16 bits (`>> 16`), we divide by $65,536$ in a **single clock cycle**!

---

## 3. Real Systems Connection: `rcre` Bit-Exact Parity
`rcre` uses this exact 15-bit fixed-point formula. It achieves **0 LSB discrepancy** against OpenCV's `cv2.cvtColor(..., cv2.COLOR_RGB2GRAY)`, running at maximum hardware throughput without floating-point rounding errors.

---

## 4. Code Sample: Fast Integer Grayscale
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    uint8_t red   = 255;
    uint8_t green = 200;
    uint8_t blue  = 50;

    uint8_t gray = rl_rgb_to_gray(red, green, blue);
    printf("Color (RGB %u, %u, %u) -> Grayscale: %u\n", red, green, blue, gray);
    return 0;
}
```

---

## 5. Your Mission: The Palette Inverter
In `starter.c`, implement the fixed-point grayscale transformation and an image color inverter!
