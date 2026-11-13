#include "rcre_learn.h"
#include <stdio.h>

void update_parameter(RL_Node* param, float learning_rate) {
    if (!param) return;
    param->val -= (learning_rate * param->grad);
    param->grad = 0.0f; // Clear gradient for next iteration
}

int main(void) {
    RL_Node weight;
    rl_node_init(&weight, 2.5f);
    weight.grad = 0.8f;

    printf("Weight before update: %.4f\n", weight.val);
    update_parameter(&weight, 0.1f);
    printf("Weight after update:  %.4f\n", weight.val);

    return 0;
}
