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
        stack_push_f(&stk1, 2);
        print_stack(&stk1);
        int value = stack_pop(&stk1, &info);
        print_stack(&stk1);
        printf("%d\n", value);

        free(stk1.data);
}
