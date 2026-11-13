#include "rcre_learn.h"
#include <stdio.h>

size_t count_tokens(RL_Slice stream, char delimiter) {
    size_t count = 0;
    RL_Slice token;
    while (rl_slice_split_next(&stream, delimiter, &token)) {
        count++;
    }
    return count;
}

int main(void) {
    const char* data = "chr1:100234,chr2:504211,chr3:902123,chrX:12001";
    RL_Slice slice = rl_slice_from_cstr(data);

    size_t count = count_tokens(slice, ',');
    printf("Total tokens found: %zu\n", count);
    return 0;
}
