#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
    printf("[Week 07 Test] Testing Fat-Pointer Slices & Zero-Copy Splitting...\n");

    const char* text = "apple,banana,cherry,dragonfruit";
    RL_Slice stream = rl_slice_from_cstr(text);

    RL_Slice token;
    bool ok1 = rl_slice_split_next(&stream, ',', &token);
    assert(ok1);
    assert(token.len == 5);
    assert(rl_slice_equals(token, rl_slice_from_cstr("apple")));

    bool ok2 = rl_slice_split_next(&stream, ',', &token);
    assert(ok2);
    assert(token.len == 6);
    assert(rl_slice_equals(token, rl_slice_from_cstr("banana")));

    bool ok3 = rl_slice_split_next(&stream, ',', &token);
    assert(ok3);
    assert(token.len == 6);
    assert(rl_slice_equals(token, rl_slice_from_cstr("cherry")));

    bool ok4 = rl_slice_split_next(&stream, ',', &token);
    assert(ok4);
    assert(token.len == 11);
    assert(rl_slice_equals(token, rl_slice_from_cstr("dragonfruit")));

    // Stream should now be exhausted
    bool ok5 = rl_slice_split_next(&stream, ',', &token);
    assert(!ok5);

    printf("  \033[32m✔ Week 07 PASSED:\033[0m Fat-pointer slices & zero-copy tokenizer verified.\n");
    return 0;
}
