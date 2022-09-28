#ifndef STACK_H
#define STACK_H

// #define VAR_INFO(var) {#var, __PRETTY_FUNCTION__, __FILE__, __LINE__}
// #define stack_ctor(stk, capacity) oper_stack_ctor(stk, capacity, VAR_INFO(stk))
#define DEF_CAPACITY 10
#define ASSERT_OK(stk)  if (errors = stack_error(stk)) {           \
                                stack_dump(stk, errors);                \
                        }                                               \

typedef int elem_t;

struct var_info
{
        int line = 0;
        char *func = nullptr;
        char *file = nullptr;
        char *var = nullptr;
};

struct stack
{
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
        var_info info = {};
};

void print_stack (stack *stk);
int stack_error (stack *stk);
void stack_dump (stack *stk, int errors);
void oper_stack_ctor (stack *stk, size_t capacity, char *var, char *func, char *file, int line);
size_t stack_resize (stack *stk, size_t capacity);
elem_t stack_push_f (stack *stk, elem_t value);
elem_t stack_pop(stack *stk);
void fill_nan (stack *stk);

#endif /*STACK_H*/
