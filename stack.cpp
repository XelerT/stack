#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

// #define ASSERT_OK(stk) if (stack_error(stk)) {\
//                         stack_dump(stk);       \
//                         }                       \
//

elem_t stack_push_f (stack *stk, elem_t value)
{
        assert(stk);

        // if (!ASSERT_OK(stk))
        //         return;
        elem_t *data = stk->data + (int) stk->size;
                printf("11 %d %d\n", stk->size, stk->capacity);
        if (stk->size >= stk->capacity)
                stack_resize(stk, stk->size + 20);
        printf("12 %d %d %d\n", stk->size, value, *data);
        assert(data);
        *data = value;
        printf("13 %d %d %d\n", stk->size, value, *data);
        stk->size++;

        // ASSERT_OK(stk);
        return value;
}

elem_t stack_pop(stack *stk, stack_info *err)
{
        assert(stk);

        elem_t a = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        return a;
}

size_t stack_resize (stack *stk, size_t capacity)
{
        assert(stk);

        stk = (stack*) realloc(stk, capacity);

        // ASSERT_OK(stk);
        return capacity;
}

void stack_ctor (stack *stk)
{
        assert(stk);

        stk->data = (elem_t*) calloc(stk->capacity, sizeof(stack)); // how to make it with voids
        // ASSERT_OK(stk);
}

void stack_dump (stack_info *stk)
{
        assert(stk);

}

int stack_error (stack *stk)
{
        assert(stk);

        return 0;
}

void print_stack (stack *stk)
{
        for (size_t i = 0; i < stk->capacity; i++) {
                printf("%d ", stk->data[i]);
        }
        printf("\n");
}


