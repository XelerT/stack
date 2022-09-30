#include <stdio.h>
#include <cstdint>

#include "security.h"

#ifdef CANARY_ON
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
                return DEAD_CANARY;
        return 0;
}
#endif /*CANARY_ON*/


#ifdef HASH_ON
uint64_t gnu_hash_stack (const void *ptr, uint64_t seed)
{
        stack *stk = (stack*) ptr;
        uint64_t h = seed;

        h = ((h << 5) + h) + sizeof(stack);

        return h & 0xffffffff;
}

uint64_t gnu_hash_data (const void *ptr, uint64_t seed)
{
        stack *stk = (stack*) ptr;
        elem_t *data = (elem_t*) stk->data;
        uint64_t h = seed;

        for (size_t i = 0; i < stk->capacity; i++)
                h = ((h << 5) + h) + data[i];

        return h & 0xffffffff;
}

uint64_t check_data_hash (const void *ptr, uint64_t seed)
{
        stack *stk = (stack*) ptr;
        elem_t *data = (elem_t*) stk->data;
        uint64_t new_hash = gnu_hash_data(stk, seed);
        if (new_hash != stk->hash->hash_data)
                return 1;
        return 0;
}

uint64_t check_stack_hash (const void *ptr, uint64_t seed)
{
        stack *stk = (stack*) ptr;
        elem_t *data = (elem_t*) stk->data;
        uint64_t new_hash = gnu_hash_stack(stk, seed);
        if (new_hash != stk->hash->hash_stack)
                return 1;
        return 0;
}
#endif /*HASH_ON*/
