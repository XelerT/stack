#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <cstdint>

#include "security.h"
#ifdef HASH_ON
static const char N_ERRORS = 7;
#elif  CANARY_ON
static const char N_ERRORS = 5;
#else
static const char N_ERRORS = 4;
#endif  /*HASH_ON*/
static int errors = 0;

elem_t stack_push_f (stack *stk, elem_t value)
{
        assert(stk);
        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);

        elem_t *data = stk->data + (int) stk->size;
        *data = value;
        stk->size++;

        if (stk->size + DEF_CAPACITY / 2 >= stk->capacity)
                stack_resize(stk, stk->capacity + DEF_CAPACITY);

        #ifdef HASH_ON
        stk->hash->hash_data  = gnu_hash_data  (stk, SEED);
        #endif /*HASH_ON*/

        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);
        return value;
}

elem_t stack_pop(stack *stk)
{
        assert(stk);
        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);

        elem_t a = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        (stk->size)--;

        if (stk->size + 2 * DEF_CAPACITY <= stk->capacity)
                stk->capacity = (stk, stk->capacity - 2 * DEF_CAPACITY);

        #ifdef HASH_ON
        stk->hash->hash_data  = gnu_hash_data  (stk, SEED);
        #endif /*HASH_ON*/

        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);

        return a;
}

size_t stack_resize (stack *stk, size_t capacity)
{
        assert(stk);

        stk->capacity = capacity;
        stk->data = (elem_t*) realloc(stk->data, stk->capacity);

        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);

        return capacity;
}

void oper_stack_ctor (stack *stk, size_t capacity, char *var, char *func, char *file, int line)
{
        assert(stk);

        stk->capacity = capacity + DEF_CAPACITY * 2;
        stk->data = (elem_t*) calloc(stk->capacity, sizeof(stack)); // how to make it with voids
        fill_nan (stk);
        stk->info.line = line;
        stk->info.file = file;
        stk->info.func = func;
        stk->info.var = var;

        #ifdef HASH_ON
        stk->hash = (gnu_hash*) calloc(1, sizeof(gnu_hash));
        stk->hash->hash_stack = gnu_hash_stack (stk, SEED);
        stk->hash->hash_data  = gnu_hash_data  (stk, SEED);
        #endif /*HASH_ON*/

        get_canaries(stk);

        ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__);
}

void stack_dump (stack *stk, int errors, char *func, char *file, int line) // print all info
{
        unsigned char err[N_ERRORS] = {0};
        printf("\nError:\n");
        for (int i = 1; i < N_ERRORS + 1; i++) {
                err[i - 1] = (errors >> (N_ERRORS - i)) & ~(~0 << 1);
        }
        for (int i = 0, swap = 0; i < N_ERRORS / 2; i++) {
                swap = err[i];
                err[i] = err[N_ERRORS - i - 1];
                err[N_ERRORS - i - 1] = swap;
        }

        if (err[0] == 1) {
                printf(" Stack pointer is null.\n\n");
                exit(-1); // how to beautifully exit the program?
        } else if (err[1] == 1) {
                printf(" Data pointer in null.\n\n");
                exit(-1); // how to beautifully exit the program?
        }
        int multp_errors = 0;
        for (int i = 0; i < N_ERRORS; i++) {
                if (err[i] != 0) {
                        multp_errors = 1;
                        if (multp_errors) {
                                printf(" %s at %s (%d):\n"
                                       " Stack[%x] (%s)\n"
                                       " %s at %s at %s (%d)\n"
                                       " size = %lld,"
                                       " capacity = %lld,"
                                       " data[%x]\n", func, file, line,
                                       (stk == nullptr) ? 0: stk, (stk == nullptr) ? "mistake": "ok", stk->info.var,
                                       stk->info.func, stk->info.file, stk->info.line, stk->size, stk->capacity, (stk->data == nullptr) ? 0: stk->data);
                                #ifdef HASH_ON
                                printf("Required stack hash: %lld\nActual   stack hash: %lld\n", stk->hash->hash_stack, gnu_hash_stack (stk, SEED));
                                printf("Required  data hash: %lld\nActual    data hash: %lld\n", stk->hash->hash_data,  gnu_hash_data  (stk, SEED));
                                #endif /*HASH_ON*/
                                for (int j = 0; j < stk->capacity; j++) {
                                        if (isnan(stk->data[j]))
                                                        printf("[%d] = NAN(POISON)\n", j);
                                        else
                                                printf("*[%d] = %d\n", j, stk->data[j]);
                                }
                        }
                        switch (i) {
                        case 2:
                                printf(" Stack size is negative.\n\n");
                                break;
                        case 3:
                                printf(" Stack capacity is negative.\n\n");
                                break;
                        #ifdef CANARY_ON
                        case 4:
                                printf(" Canary has been changed.\n\n");
                                exit(-1);
                                break;
                        #endif /*CANARY_ON*/
                        #ifdef HASH_ON
                        case 5:
                                printf(" Hash of data has been changed.\n\n");
                                break;
                        case 6:
                                printf(" Hash of struct has been changed.\n\n");
                                exit(-1);
                                break;
                        #endif /*HASH_ON*/
                       }
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
#ifdef CANARY_ON
        if (check_canaries(stk)) {
                error = error | 16;
                return error;
        }
#endif /*CANARY_ON*/
#ifdef HASH_ON
        if (check_data_hash(stk, SEED)) {
                error = error | 32;
        }
        if (check_stack_hash(stk, SEED)) {
                error = error | 64;
                return error;
        }
#endif /*HASH_ON*/
        if (stk->data == nullptr)
                error = error |  2;
        if (stk->size < 0)
                error = error |  4;
        if (stk->capacity < 0)
                error = error |  8;

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
                        stk->data[i] = NAN; //?????
}
