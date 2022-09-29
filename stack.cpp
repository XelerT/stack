#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "stack.h"
#include "security.h"

static const char N_ERRORS = 5;
static int errors = 0;

elem_t stack_push_f (stack *stk, elem_t value)
{
        ASSERT_OK(stk);

        elem_t *data = stk->data + (int) stk->size;
        *data = value;
        stk->size++;

        if (stk->size + DEF_CAPACITY / 2 >= stk->capacity)
                stack_resize(stk, stk->capacity + DEF_CAPACITY);

        ASSERT_OK(stk);
        return value;
}

elem_t stack_pop(stack *stk)
{
        ASSERT_OK(stk);

        elem_t a = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        (stk->size)--;

        if (stk->size + 2*DEF_CAPACITY <= stk->capacity)
                stack_resize(stk, stk->capacity - DEF_CAPACITY);

        return a;
}

size_t stack_resize (stack *stk, size_t capacity)
{
        ASSERT_OK(stk);

        stk->capacity = capacity;
        stk->data = (elem_t*) realloc(stk->data, stk->capacity);

        ASSERT_OK(stk);
        return capacity;
}

void oper_stack_ctor (stack *stk, size_t capacity, char *var, char *func, char *file, int line)
{
        ASSERT_OK(stk);

        stk->capacity = capacity;
        stk->data = (elem_t*) calloc(stk->capacity, sizeof(stack)); // how to make it with voids
        fill_nan (stk);
        stk->info.line = line;
        stk->info.file = file;
        stk->info.func = func;
        stk->info.var = var;

        get_canaries(stk);

        ASSERT_OK(stk);
}

void stack_dump (stack *stk, int errors) // print all info
{

        unsigned char err[N_ERRORS] = {0};
        printf("\nError:\n");
        for (int i = 1; i < N_ERRORS + 1; i++)
                err[i - 1] = (errors >> (N_ERRORS - i)) & ~(~0 << 1);

        for (int i = 0; i < N_ERRORS; i++) {
                        if (err[i] != 0 && i != N_ERRORS - 1) {
                                printf(" %s at %s (%d):\n"
                                        " Stack[%x] (%s)\n"
                                        " %s at %s at %s (%d)\n"
                                        " size = %d,"
                                        " capacity = %lld,"
                                        " data[%x]\n", __PRETTY_FUNCTION__, __FILE__, __LINE__,
                                        (stk == nullptr) ? 0: stk, (stk == nullptr) ? "mistake": "ok", stk->info.var,
                                        stk->info.func, stk->info.file, stk->info.line, stk->size, stk->capacity, stk->data);
                                for (int j = 0; j < stk->capacity; j++) {
                                        if (isnan(stk->data[j]))
                                                printf("[%d] = NAN(POISON)\n", j);
                                        else
                                                printf("*[%d] = %d\n", j, stk->data[j]);
                                }
                                switch (i) {
                                case 3:
                                        printf(" Stack size is negative.\n\n");
                                        break;
                                case 2:
                                        printf(" Stack capacity is negative.\n\n");
                                        break;
                                case 1:
                                        printf(" Data pointer in null.\n\n");
                                        exit(-1); // how to beautifully exit the program?
                                        break;
                                case 0:
                                        printf(" Canary has been changed.\n\n");
                                        exit(-1);
                                        break;
                                }
                        } else {
                                printf(" Stack pointer is null.\n\n");
                                exit(-1); // how to beautifully exit the program?
                        }
        }
        printf("\n");
}

int stack_error (stack *stk) // check have an error
{
        int error = 0;

        if (stk == nullptr) {
                error = error |  1;
                return error;
        }
        if (stk->size < 0)
                error = error |  2;
        if (stk->capacity < 0)
                error = error |  4;
        if (stk->data == nullptr)
                error = error |  8;
        if (check_canaries(stk))
                error = error | 16;

        return error;
}

void print_stack (stack *stk)
{
        for (size_t i = 0; i < stk->capacity; i++) {
                printf("%d ", stk->data[i]);
        }
        printf("\n");
}

void fill_nan (stack *stk)
{
        for (size_t i = stk->size + 1; i < stk->capacity; i++)
                if (stk->data[i] == 0)
                        stk->data[i] = NAN;
}
