#include "rcre_learn.h"
#include <stdio.h>

/**
 * Perform a single gradient descent parameter update:
 * w_new = w - learning_rate * grad
 */
void update_parameter(RL_Node* param, float learning_rate) {
    // TODO: Update param->val by subtracting (learning_rate * param->grad)
    (void)param;
    (void)learning_rate;
}

int main(void) {
    RL_Node weight;
    rl_node_init(&weight, 2.5f);
    weight.grad = 0.8f; // Error indicated we need to decrease weight

    printf("Weight before update: %.4f\n", weight.val);
    update_parameter(&weight, 0.1f);
    printf("Weight after update:  %.4f\n", weight.val);

    return 0;
}
