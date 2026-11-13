# Week 1: Station 1 — The Silicon Grid & The Locker Room

> *"Before you can command the machine, you must see the hallway of memory."*

---

## 1. The Story: Opening the Silicon Door
Imagine walking into a high school with millions of lockers lining the hallway in one long, unbroken row. Each locker has an embossed metal number on the front: `0x1000`, `0x1001`, `0x1002`, and so on.

Inside each locker, you can place exactly **one byte** of data (8 tiny switches that can be ON or OFF, representing numbers from 0 to 255).

When people write code in high-level languages like Python or JavaScript, the computer hides this hallway behind smoke and mirrors. But in **C23**, you hold the master key. You can look at any locker, inspect its number, and place data directly inside.

---

## 2. The Metaphor: Variables and Addresses
* **A Variable Name** is just a sticky note you paste on a locker door so you don't have to remember the long number.
* **A Variable Type** tells you how many lockers the item occupies:
  * `uint8_t`: 1 locker (1 byte, 0 to 255)
  * `uint16_t`: 2 lockers in a row (2 bytes, 0 to 65,535)
  * `uint32_t`: 4 lockers in a row (4 bytes, 0 to 4.29 billion)
  * `float`: 4 lockers formatted for decimals
* **The Address-Of Operator (`&`)**: Asking the school office: *"What is the locker number for this variable?"*

---

## 3. Real Systems Connection: Why `rcre` Cares About Every Byte
In `rcre`, we process 4K camera streams at 60 frames per second. If we waste even 1 extra byte per pixel, an image buffer grows by megabytes, causing the CPU to choke on cache misses. By choosing the exact byte width for each number, `rcre` processes images with zero memory waste.

---

## 4. Code Sample: Inspecting Memory
```c
#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t player_level = 5;
    uint32_t score = 150000;

    printf("Variable 'player_level' holds value: %u\n", player_level);
    printf("It occupies %zu byte(s) at locker address: %p\n", sizeof(player_level), (void*)&player_level);

    printf("Variable 'score' holds value: %u\n", score);
    printf("It occupies %zu byte(s) at locker address: %p\n", sizeof(score), (void*)&score);

    return 0;
}
```

---

## 5. Your Mission: The Locker Swap
In `starter.c`, your goal is to swap the contents of two memory lockers using their addresses without losing any data!
