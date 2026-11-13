#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define MAX_SLOTS 4

typedef struct {
    uint32_t active_jobs[MAX_SLOTS];
    uint32_t active_count;
    uint32_t max_capacity;
} WorkerPool;

bool pool_schedule(WorkerPool* pool, uint32_t job_id) {
    if (!pool || pool->active_count >= pool->max_capacity) return false;
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
    printf("[Week 08 Test] Testing Master Dispatcher & Core Worker Pools...\n");

    WorkerPool pool = { .active_jobs = {0}, .active_count = 0, .max_capacity = 4 };

    // Schedule 4 jobs to saturate pool
    assert(pool_schedule(&pool, 101));
    assert(pool_schedule(&pool, 102));
    assert(pool_schedule(&pool, 103));
    assert(pool_schedule(&pool, 104));
    assert(pool.active_count == 4);

    // 5th job should be rejected (backpressure active)
    assert(!pool_schedule(&pool, 105));

    // Finish job 102
    assert(pool_complete(&pool, 102));
    assert(pool.active_count == 3);

    // Now 105 can be scheduled
    assert(pool_schedule(&pool, 105));
    assert(pool.active_count == 4);

    printf("  \033[32m✔ Week 08 PASSED:\033[0m Process worker pool backpressure & scheduler verified.\n");
    return 0;
}
