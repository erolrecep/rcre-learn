#include "rcre_learn.h"
#include <stdio.h>

/**
 * Count how many comma-separated tokens exist in `stream`.
 */
size_t count_tokens(RL_Slice stream, char delimiter) {
    // TODO: Use rl_slice_split_next to count tokens without copying!
    (void)stream;
    (void)delimiter;
    return 0;
}

int main(void) {
    const char* data = "chr1:100234,chr2:504211,chr3:902123,chrX:12001";
    RL_Slice slice = rl_slice_from_cstr(data);

    size_t count = count_tokens(slice, ',');
    printf("Total tokens found: %zu\n", count);
    return 0;
}
