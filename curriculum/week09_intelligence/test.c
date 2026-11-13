#include "rcre_learn.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

void update_parameter(RL_Node* param, float learning_rate) {
    if (!param) return;
    param->val -= (learning_rate * param->grad);
    param->grad = 0.0f;
}

int main(void) {
    printf("[Week 09 Test] Testing Computational Graph & Autograd Backprop...\n");

    // Equation: y = a * b + c
    RL_Node a, b, c;
    rl_node_init(&a, 3.0f);
    rl_node_init(&b, 4.0f);
    rl_node_init(&c, 5.0f);

    RL_Node mul = rl_node_mul(&a, &b);
    assert(fabsf(mul.val - 12.0f) < 1e-5f);

    RL_Node y = rl_node_add(&mul, &c);
    assert(fabsf(y.val - 17.0f) < 1e-5f);

    // Backprop
    rl_node_backward(&y);

    assert(fabsf(y.grad - 1.0f) < 1e-5f);
    assert(fabsf(c.grad - 1.0f) < 1e-5f); // dy/dc = 1
    assert(fabsf(b.grad - 3.0f) < 1e-5f); // dy/db = a = 3
    assert(fabsf(a.grad - 4.0f) < 1e-5f); // dy/da = b = 4

    // Parameter update test
    update_parameter(&a, 0.1f);
    assert(fabsf(a.val - (3.0f - 0.4f)) < 1e-5f); // 3.0 - 0.1*4.0 = 2.6
    assert(a.grad == 0.0f);

    printf("  \033[32m✔ Week 09 PASSED:\033[0m Autograd topological backpropagation verified.\n");
    return 0;
}
