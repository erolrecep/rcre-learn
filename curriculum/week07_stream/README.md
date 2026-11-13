# Week 7: Station 7 — The Stream Laser (Safe Slices & High-Speed Splitting)

> *"The fastest way to copy text is not to copy it at all."*

---

## 1. The Story: The Billion-Dollar Null-Terminator Bug
In old C (C89/C99), text strings were defined as characters ending in a zero byte (`'\0'`).
To find out how long a string was, the computer had to walk letter-by-letter until it hit zero (`strlen()`).
If the zero byte was missing or corrupted? The computer kept reading until it crashed or exposed passwords (**Heartbleed / Buffer Overflow vulnerabilities**).

Worse, to split a sentence into words, old textbooks teach you to copy each word into new memory buffers.
When processing a **100 Gigabyte bioinformatics file** with millions of DNA sequences, copying text freezes the computer.

---

## 2. The Metaphor: The Flashlight Window (Fat Pointers)
Instead of cutting up a book with scissors, you hold a piece of cardboard with a transparent window over the sentence:
* **`data`**: Pointer to where the word begins.
* **`len`**: Exactly how many characters long it is.

```
Original Buffer: [ A | T | G | C | \n | G | G | A | C | \n ]
Slice 1:         [ A | T | G | C ]      (len = 4, zero copies!)
Slice 2:         [ G | G | A | C ]      (len = 4, zero copies!)
```
This is called a **Fat-Pointer Slice** (`RL_Slice`).

---

## 3. Real Systems Connection: `gnew-parallel`
In `gnew-parallel`, we split massive genomic files (FASTA/FASTQ) into parallel tasks at **3.24 Gigabytes per second**.
We do this using SIMD byte scanners (`find_byte`) and fat-pointer slices without allocating a single byte of heap memory or calling `strlen()`.

---

## 4. Code Sample: Zero-Copy String Slicing
```c
#include "rcre_learn.h"
#include <stdio.h>

int main(void) {
    const char* log_line = "ERROR,DATABASE_TIMEOUT,RETRY_COUNT_3";
    RL_Slice stream = rl_slice_from_cstr(log_line);
    RL_Slice token;

    printf("Original Stream: %s\n", log_line);
    while (rl_slice_split_next(&stream, ',', &token)) {
        printf("Parsed Token: %.*s (Length: %zu)\n", (int)token.len, token.data, token.len);
    }
    return 0;
}
```

---

## 5. Your Mission: The DNA Sequence Counter
In `starter.c`, parse a continuous DNA sequence stream and count how many times a given token appears!
