#include <stdio.h>
#include <stdint.h>

void swap_lockers(uint32_t* a, uint32_t* b) {
    if (a == NULL || b == NULL) return;
    uint32_t temp = *a; // Open locker A and put contents in temporary box
    *a = *b;            // Move contents of locker B into locker A
    *b = temp;          // Put box contents into locker B
}

int main(void) {
    uint32_t locker_101 = 42;
    uint32_t locker_102 = 99;

    printf("Before swap: Locker 101 = %u, Locker 102 = %u\n", locker_101, locker_102);
    swap_lockers(&locker_101, &locker_102);
    printf("After swap:  Locker 101 = %u, Locker 102 = %u\n", locker_101, locker_102);

    return 0;
}
