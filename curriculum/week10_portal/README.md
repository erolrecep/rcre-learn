# Week 10: Station 10 — The Alchemist's Portal (WebAssembly & The Capstone)

> *"Your C code is no longer trapped on your laptop; it is ready to run in any browser on Earth."*

---

## 1. The Story: The Grand Unification
Over the past 9 weeks, you have learned the deepest secrets of physical silicon:
1. Numbered memory lockers & pointers.
2. Zero-waste linear whiteboard arenas.
3. 15-bit fixed-point color calculations.
4. Struct-of-Arrays planar cache saturation.
5. 2D convolution edge detection stencils.
6. Multi-lane SIMD vector highways & dynamic HALs.
7. Safe fat-pointer text slices.
8. Master process orchestration & core sympathy.
9. Artificial neurons & reverse-mode autograd.

Now comes the ultimate step: **Deploying your systems code to the entire world.**

---

## 2. The Metaphor: The Universal Portal (WebAssembly)
For decades, web browsers could only understand JavaScript. JavaScript is flexible, but it cannot directly control memory or run SIMD instructions at bare-metal speeds.

**WebAssembly (WASM)** is a universal portal:
* You compile your C23 code into a compact `.wasm` binary.
* Any web browser (Chrome, Safari, Firefox, Edge) loads the binary into an isolated, high-speed virtual machine.
* Your C code runs at **near-native bare-metal speed**, directly processing webcam video, neural networks, and 3D graphics!

---

## 3. Real Systems Connection: The `rcre` Web Playground
In `rcre`, the entire computer vision and machine learning engine compiles to `rcre.wasm`.
Users can open an interactive web playground, turn on their camera, and see real-time edge detection, corner tracking, and neural inference running directly on their device without installing any software.

---

## 4. Code Sample: The WASM Foreign Function Interface (FFI)
```c
#include <stdint.h>

/**
 * An exported C function that processes an RGBA image buffer
 * passed directly from a JavaScript HTML5 Canvas or Webcam!
 */
void process_frame_wasm(uint8_t* rgba, int width, int height) {
    int total_pixels = width * height;
    for (int i = 0; i < total_pixels * 4; i += 4) {
        // Fast Grayscale tint directly in video buffer
        uint8_t r = rgba[i];
        uint8_t g = rgba[i+1];
        uint8_t b = rgba[i+2];
        uint8_t gray = (uint8_t)(((uint32_t)r * 19595 + (uint32_t)g * 38469 + (uint32_t)b * 7472) >> 16);

        rgba[i]   = gray;
        rgba[i+1] = gray;
        rgba[i+2] = gray;
        // rgba[i+3] is Alpha (opacity), left untouched
    }
}
```

---

## 5. Your Mission: The Interactive Filter Capstone
In `starter.c`, complete the in-memory video frame tint filter that will run in the `rcre-learn` web app!
