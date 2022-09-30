#ifndef STACK_H
#define STACK_H
#include <cstdint>

// #define VAR_INFO(var) {#var, __PRETTY_FUNCTION__, __FILE__, __LINE__}
// #define stack_ctor(stk, capacity) oper_stack_ctor(stk, capacity, VAR_INFO(stk))
#define DEF_CAPACITY 10
#define ASSERT_OK(stk,__PRETTY_FUNCTION__,__FILE__,__LINE__)  if (errors = stack_error(stk)) {                                  \
                                stack_dump(stk, errors, (char*) __PRETTY_FUNCTION__, (char*) __FILE__, __LINE__);               \
                        }                                                                                                       \

typedef int elem_t;

struct gnu_hash
{
        uint64_t hash_stack = 0;
        uint64_t hash_data  = 0;
};

struct var_info
{
        int line = 0;
        char *func = nullptr;
        char *file = nullptr;
        char *var  = nullptr;
};

struct stack
{
        int l_canary[1] = {};
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
        var_info info = {};
        // #ifdef HASH_ON
        gnu_hash *hash = nullptr;
        // #endif /*HASH*/
        int r_canary[1] = {};
};

void print_stack (stack *stk);
int stack_error (stack *stk);
void stack_dump (stack *stk, int errors, char *func, char *file, int line);
void oper_stack_ctor (stack *stk, size_t capacity, char *var, char *func, char *file, int line);
size_t stack_resize (stack *stk, size_t capacity);
elem_t stack_push_f (stack *stk, elem_t value);
elem_t stack_pop(stack *stk);
void fill_nan (stack *stk);

#endif /*STACK_H*/
