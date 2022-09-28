#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main ()
{
        stack stk1 = {};
        size_t capacity = 0;
        printf("Enter capacity\n");
        scanf("%lld", &capacity);
        oper_stack_ctor(&stk1, capacity, (char*) "stk1", (char*) __PRETTY_FUNCTION__, (char*) __FILE__,__LINE__);
        stack_push_f(&stk1, 1);
        stack_push_f(&stk1, 2);
        print_stack(&stk1);
        int value = stack_pop(&stk1);
        print_stack(&stk1);
        printf("%d\n", value);

        free(stk1.data);
}
