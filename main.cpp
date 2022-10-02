#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main ()
{
        stack stk1 = {};
        size_t capacity = 0;
        printf("Enter capacity your capacity.\n");
        scanf("%lld", &capacity);
        if (oper_stack_ctor(&stk1, capacity, (char*) "stk1", (char*) __PRETTY_FUNCTION__, (char*) __FILE__,__LINE__))
                return CTOR_ERROR;
        for (int i = 0; i < 50; i++)
                if (stack_push_f(&stk1, i))
                        return PUSH_ERROR;
        print_stack(&stk1);

        int value = 0;
        if ((value = stack_pop(&stk1)) == POP_ERROR)
                return POP_ERROR;

        print_stack(&stk1);
        printf("POPPED: %d\n", value);

        free_stack(&stk1);

        return 0;
}
