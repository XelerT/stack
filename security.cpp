#include <stdio.h>

#include "stack.h"

static const int CANARY = -2147443648;
static const int DEAD_CANARY = 16;

void get_canaries (stack *stk)
{
        int value = CANARY;
        stk->l_canary[0] = value;
        stk->r_canary[0] = value;
}

int check_canaries (stack *stk)
{
        if (stk->l_canary[0] != CANARY || stk->r_canary[0] != CANARY)
                return 16;
        return 0;
}
