#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_SLOTS 4

typedef struct {
    uint32_t active_jobs[MAX_SLOTS];
    uint32_t active_count;
    uint32_t max_capacity;
} WorkerPool;

bool pool_schedule(WorkerPool* pool, uint32_t job_id) {
    if (!pool || pool->active_count >= pool->max_capacity) {
        return false; // Backpressure: All cores busy!
    }

    for (uint32_t i = 0; i < pool->max_capacity; ++i) {
        if (pool->active_jobs[i] == 0) {
            pool->active_jobs[i] = job_id;
            pool->active_count++;
            return true;
        }
    }
    return false;
}

bool pool_complete(WorkerPool* pool, uint32_t job_id) {
    if (!pool) return false;
    for (uint32_t i = 0; i < pool->max_capacity; ++i) {
        if (pool->active_jobs[i] == job_id) {
            pool->active_jobs[i] = 0;
            pool->active_count--;
            return true;
        }
    }
    return false;
}

int main(void) {
    WorkerPool pool = { .active_jobs = {0}, .active_count = 0, .max_capacity = MAX_SLOTS };

    printf("Scheduling jobs to 4-core pool...\n");
    for (uint32_t j = 1; j <= 6; ++j) {
        bool ok = pool_schedule(&pool, j);
        printf("Job %u: %s\n", j, ok ? "SCHEDULED (RUNNING)" : "HELD (WAITING FOR SLOT)");
    }

    return 0;
}
