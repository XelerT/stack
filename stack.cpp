#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

static const char N_ERRORS = 4;
static int errors = 0;

elem_t stack_push_f (stack *stk, elem_t value)
{
        assert(stk);
        ASSERT_OK(stk);

        elem_t *data = stk->data + (int) stk->size;
        if (stk->size >= stk->capacity)
                stack_resize(stk, stk->size + 20);
        *data = value;
        stk->size++;

        ASSERT_OK(stk);
        return value;
}

elem_t stack_pop(stack *stk)
{
        assert(stk);

        elem_t a = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        return a;
}

size_t stack_resize (stack *stk, size_t capacity)
{
        assert(stk);

        stk->data = (elem_t*) realloc(stk, capacity);

        ASSERT_OK(stk);
        return capacity;
}

void oper_stack_ctor (stack *stk, size_t capacity, char *var, char *func, char *file, int line)
{
        assert(stk);

        stk->capacity = capacity;
        stk->data = (elem_t*) calloc(stk->capacity, sizeof(stack)); // how to make it with voids
        stk->info.line = line;
        stk->info.file = file;
        stk->info.func = func;
        stk->info.var = var;

        ASSERT_OK(stk);
}

void stack_dump (stack *stk, int errors) // print all info
{
        assert(stk);

        unsigned char err[N_ERRORS] = {0};
        printf("Error: ");
        for (int i = 1; i < N_ERRORS + 1; i++) {
                err[i - 1] = (errors >> (N_ERRORS - i)) & ~(~0 << 1);
                printf("%d ", err[i - 1]);
        }
        printf("\n");
}

int stack_error (stack *stk) // check have an error
{
        int error = 0;

        if (stk == nullptr)
                error = error | 1;
        if (stk->size < 0)
                error = error | 2;
        if (stk->capacity < 0)
                error = error | 4;
        if (stk->data == nullptr)
                error = error | 8;
error = 8;
        return error;
}

void print_stack (stack *stk)
{
        for (size_t i = 0; i < stk->capacity; i++) {
                printf("%d ", stk->data[i]);
        }
        printf("\n");
}


