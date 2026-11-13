#include <stdio.h>
#include <stdint.h>
#include <assert.h>

void swap_lockers(uint32_t* a, uint32_t* b) {
    if (!a || !b) return;
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    printf("[Week 01 Test] Testing Locker Room Swap & Addresses...\n");

    uint32_t x = 12345;
    uint32_t y = 67890;

    swap_lockers(&x, &y);
    assert(x == 67890);
    assert(y == 12345);

    // Test null safety
    swap_lockers(NULL, &y);
    assert(y == 12345);

    printf("  \033[32m✔ Week 01 PASSED:\033[0m Locker swap & pointer dereference verified.\n");
    return 0;
}
