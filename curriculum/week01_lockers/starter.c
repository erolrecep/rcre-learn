#include <stdio.h>
#include <stdint.h>

/**
 * Mission: Swap the values stored in two memory lockers!
 *
 * Parameters:
 *   a - Pointer to locker A
 *   b - Pointer to locker B
 */
void swap_lockers(uint32_t* a, uint32_t* b) {
    // TODO: Write code to swap the values stored at address `a` and address `b`.
    // Hint: You might need a temporary variable to hold one value while swapping!
    (void)a;
    (void)b;
}

int main(void) {
    uint32_t locker_101 = 42;
    uint32_t locker_102 = 99;

    printf("Before swap: Locker 101 = %u, Locker 102 = %u\n", locker_101, locker_102);
    swap_lockers(&locker_101, &locker_102);
    printf("After swap:  Locker 101 = %u, Locker 102 = %u\n", locker_101, locker_102);

    return 0;
}
