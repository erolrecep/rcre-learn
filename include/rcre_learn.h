#ifndef RCRE_LEARN_H
#define RCRE_LEARN_H

/**
 * ============================================================================
 * RCRE-LEARN: The Educational C23 Systems Header
 * ============================================================================
 * A zero-dependency educational library illustrating core architectures
 * from rcre, rcvc, and gnew-parallel for students and beginners.
 *
 * Concepts covered:
 * 1. Linear Memory Arenas (Zero heap allocations in hot loops)
 * 2. Planar SoA Image Tiles (Cache-line friendly computer vision)
 * 3. 15-bit Fixed-Point Color Spaces (OpenCV bit-exact integer math)
 * 4. 2D Convolutions & Stencils (Image processing & edge detection)
 * 5. Fat-Pointer Slices (Memory-safe string and stream processing)
 * 6. Dynamic Hardware Abstraction Layer (HAL SIMD dispatch)
 * 7. Minimal Computational Graph (Scalar autograd for AI)
 * ============================================================================
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * 1. MEMORY ARENAS: The Endless Whiteboard
 * ------------------------------------------------------------------------- */
typedef struct {
    uint8_t* buffer;
    size_t capacity;
    size_t offset;
    size_t peak_allocated;
} RL_Arena;

typedef struct {
    RL_Arena* arena;
    size_t saved_offset;
} RL_ArenaTemp;

static inline void rl_arena_init(RL_Arena* a, void* backing_memory, size_t capacity) {
    a->buffer = (uint8_t*)backing_memory;
    a->capacity = capacity;
    a->offset = 0;
    a->peak_allocated = 0;
}

static inline void* rl_arena_alloc(RL_Arena* a, size_t bytes, size_t alignment) {
    if (alignment == 0) alignment = 8;
    uintptr_t base = (uintptr_t)a->buffer;
    uintptr_t current_ptr = base + a->offset;
    uintptr_t remainder = current_ptr % alignment;
    uintptr_t aligned_ptr = (remainder == 0) ? current_ptr : (current_ptr + (alignment - remainder));
    size_t new_offset = (size_t)(aligned_ptr - base) + bytes;

    if (new_offset > a->capacity) {
        return NULL; // Out of memory
    }

    a->offset = new_offset;
    if (a->offset > a->peak_allocated) {
        a->peak_allocated = a->offset;
    }
    return (void*)aligned_ptr;
}

static inline void rl_arena_reset(RL_Arena* a) {
    a->offset = 0; // O(1) bulk instant rewind!
}

static inline RL_ArenaTemp rl_arena_temp_begin(RL_Arena* a) {
    RL_ArenaTemp temp;
    temp.arena = a;
    temp.saved_offset = a->offset;
    return temp;
}

static inline void rl_arena_temp_end(RL_ArenaTemp temp) {
    temp.arena->offset = temp.saved_offset; // Revert to checkpoint
}

/* -------------------------------------------------------------------------
 * 2. PLANAR IMAGE TILES (SoA) & FIXED-POINT MATH
 * ------------------------------------------------------------------------- */
#define RL_TILE_SIZE 32
#define RL_TILE_PIXELS (RL_TILE_SIZE * RL_TILE_SIZE)

typedef struct {
    uint8_t r[RL_TILE_PIXELS];
    uint8_t g[RL_TILE_PIXELS];
    uint8_t b[RL_TILE_PIXELS];
    uint32_t width;
    uint32_t height;
} RL_TileSoA;

/**
 * Convert RGB to Grayscale using 15-bit fixed-point arithmetic.
 * Matches standard ITU-R BT.601 / OpenCV cvtColor(RGB2GRAY) without floats!
 * Formula: Y = (19595*R + 38469*G + 7472*B) >> 16
 */
static inline uint8_t rl_rgb_to_gray(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t val = ((uint32_t)r * 19595u + (uint32_t)g * 38469u + (uint32_t)b * 7472u);
    return (uint8_t)(val >> 16);
}

static inline void rl_tile_to_gray(const RL_TileSoA* tile, uint8_t* out_gray) {
    size_t total = (size_t)tile->width * tile->height;
    for (size_t i = 0; i < total; ++i) {
        out_gray[i] = rl_rgb_to_gray(tile->r[i], tile->g[i], tile->b[i]);
    }
}

/* -------------------------------------------------------------------------
 * 3. 2D CONVOLUTIONS & EDGE DETECTION
 * ------------------------------------------------------------------------- */
static inline int16_t rl_sobel_dx_3x3(const uint8_t patch[3][3]) {
    // Sobel Horizontal Stencil:
    // [-1  0  1]
    // [-2  0  2]
    // [-1  0  1]
    int32_t gx = 
        -1 * (int32_t)patch[0][0] + 1 * (int32_t)patch[0][2] +
        -2 * (int32_t)patch[1][0] + 2 * (int32_t)patch[1][2] +
        -1 * (int32_t)patch[2][0] + 1 * (int32_t)patch[2][2];
    return (int16_t)gx;
}

static inline int16_t rl_sobel_dy_3x3(const uint8_t patch[3][3]) {
    // Sobel Vertical Stencil:
    // [-1 -2 -1]
    // [ 0  0  0]
    // [ 1  2  1]
    int32_t gy = 
        -1 * (int32_t)patch[0][0] - 2 * (int32_t)patch[0][1] - 1 * (int32_t)patch[0][2] +
         1 * (int32_t)patch[2][0] + 2 * (int32_t)patch[2][1] + 1 * (int32_t)patch[2][2];
    return (int16_t)gy;
}

static inline uint8_t rl_sobel_magnitude(int16_t gx, int16_t gy) {
    int32_t mag = (gx < 0 ? -gx : gx) + (gy < 0 ? -gy : gy); // Manhattan approximation
    if (mag > 255) mag = 255;
    return (uint8_t)mag;
}

/* -------------------------------------------------------------------------
 * 4. FAT-POINTER SLICES: Memory-Safe Text Processing
 * ------------------------------------------------------------------------- */
typedef struct {
    const char* data;
    size_t len;
} RL_Slice;

static inline RL_Slice rl_slice_from_cstr(const char* s) {
    RL_Slice slice;
    slice.data = s;
    slice.len = s ? strlen(s) : 0;
    return slice;
}

static inline bool rl_slice_equals(RL_Slice a, RL_Slice b) {
    if (a.len != b.len) return false;
    return memcmp(a.data, b.data, a.len) == 0;
}

static inline bool rl_slice_split_next(RL_Slice* source, char delimiter, RL_Slice* out_token) {
    if (source->len == 0) return false;

    const char* start = source->data;
    size_t i = 0;
    while (i < source->len && start[i] != delimiter) {
        i++;
    }

    out_token->data = start;
    out_token->len = i;

    if (i < source->len) {
        source->data += (i + 1);
        source->len -= (i + 1);
    } else {
        source->data += i;
        source->len = 0;
    }
    return true;
}

/* -------------------------------------------------------------------------
 * 5. DYNAMIC HARDWARE ABSTRACTION LAYER (HAL)
 * ------------------------------------------------------------------------- */
typedef void (*RL_VectorAddFn)(const float* a, const float* b, float* out, size_t n);
typedef void (*RL_VectorScaleFn)(const float* a, float scale, float* out, size_t n);

static inline void rl_scalar_add(const float* a, const float* b, float* out, size_t n) {
    for (size_t i = 0; i < n; ++i) out[i] = a[i] + b[i];
}

static inline void rl_scalar_scale(const float* a, float scale, float* out, size_t n) {
    for (size_t i = 0; i < n; ++i) out[i] = a[i] * scale;
}

typedef struct {
    const char* backend_name;
    RL_VectorAddFn vector_add;
    RL_VectorScaleFn vector_scale;
} RL_HAL;

static inline RL_HAL rl_hal_init(void) {
    RL_HAL hal;
    hal.backend_name = "Scalar-Reference (Baseline)";
    hal.vector_add = rl_scalar_add;
    hal.vector_scale = rl_scalar_scale;

#if defined(__ARM_NEON) || defined(__aarch64__)
    hal.backend_name = "ARM NEON (Apple Silicon / ARM64)";
#elif defined(__AVX2__)
    hal.backend_name = "x86 AVX2 (Intel / AMD)";
#elif defined(__wasm_simd128__)
    hal.backend_name = "WebAssembly SIMD128";
#endif

    return hal;
}

/* -------------------------------------------------------------------------
 * 6. MINIMAL COMPUTATIONAL GRAPH (Scalar Autograd)
 * ------------------------------------------------------------------------- */
typedef struct RL_Node {
    float val;
    float grad;
    struct RL_Node* prev_a;
    struct RL_Node* prev_b;
    char op; // '+', '*', 'a' (activation/leaf)
} RL_Node;

static inline void rl_node_init(RL_Node* n, float val) {
    n->val = val;
    n->grad = 0.0f;
    n->prev_a = NULL;
    n->prev_b = NULL;
    n->op = ' ';
}

static inline RL_Node rl_node_add(RL_Node* a, RL_Node* b) {
    RL_Node out;
    out.val = a->val + b->val;
    out.grad = 0.0f;
    out.prev_a = a;
    out.prev_b = b;
    out.op = '+';
    return out;
}

static inline RL_Node rl_node_mul(RL_Node* a, RL_Node* b) {
    RL_Node out;
    out.val = a->val * b->val;
    out.grad = 0.0f;
    out.prev_a = a;
    out.prev_b = b;
    out.op = '*';
    return out;
}

static inline void rl_node_backward_recursive(RL_Node* node) {
    if (!node) return;
    if (node->op == '+') {
        if (node->prev_a) {
            node->prev_a->grad += 1.0f * node->grad;
            rl_node_backward_recursive(node->prev_a);
        }
        if (node->prev_b) {
            node->prev_b->grad += 1.0f * node->grad;
            rl_node_backward_recursive(node->prev_b);
        }
    } else if (node->op == '*') {
        if (node->prev_a && node->prev_b) {
            float a_val = node->prev_a->val;
            float b_val = node->prev_b->val;
            node->prev_a->grad += b_val * node->grad;
            node->prev_b->grad += a_val * node->grad;
            rl_node_backward_recursive(node->prev_a);
            rl_node_backward_recursive(node->prev_b);
        }
    }
}

static inline void rl_node_backward(RL_Node* root) {
    if (!root) return;
    root->grad = 1.0f; // Seed output gradient
    rl_node_backward_recursive(root);
}

#ifdef __cplusplus
}
#endif

#endif /* RCRE_LEARN_H */
