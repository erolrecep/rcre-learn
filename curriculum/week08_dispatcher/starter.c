#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_SLOTS 4

typedef struct {
    uint32_t active_jobs[MAX_SLOTS];
    uint32_t active_count;
    uint32_t max_capacity;
} WorkerPool;

/**
 * Attempt to schedule a job id into an available worker slot.
 * Returns true if scheduled, false if pool is at full capacity.
 */
bool pool_schedule(WorkerPool* pool, uint32_t job_id) {
    // TODO: If active_count < max_capacity, place job_id in the first empty slot
    // and increment active_count!
    (void)pool;
    (void)job_id;
    return false;
}

int main(void) {
    WorkerPool pool = { .active_count = 0, .max_capacity = MAX_SLOTS };

    printf("Scheduling jobs to 4-core pool...\n");
    for (uint32_t j = 1; j <= 6; ++j) {
        bool ok = pool_schedule(&pool, j);
        printf("Job %u: %s\n", j, ok ? "SCHEDULED (RUNNING)" : "HELD (WAITING FOR SLOT)");
    }

    return 0;
}
