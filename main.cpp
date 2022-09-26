#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main ()
{
        stack stk1 = {};
        stack_info info = {};
        printf("Enter capacity\n");
        scanf("%lld", &(stk1.capacity));
        stack_ctor(&stk1);
        stack_push_f(&stk1, 1);
        printf("3\n");
        int value = stack_pop(&stk1, &info);

        free(stk1.data);
}
