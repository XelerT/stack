#ifndef STACK_H
#define STACK_H

typedef int elem_t;

static const char MAX_NAME_LEN = 20;

struct stack
{
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
};

struct stack_info
{
        elem_t *data = nullptr;
        size_t size = 0;
        size_t capacity = 0;
        int line = 0;
        char func[MAX_NAME_LEN] = {'\0'};
        char file[MAX_NAME_LEN] = {'\0'};
};

void print_stack (stack *stk);
int stack_error (stack stk);
void stack_dump (stack_info stk);
void stack_ctor (stack *stk);
size_t stack_resize (stack *stk, size_t capacity);
elem_t stack_push_f (stack *stk, elem_t value);
elem_t stack_pop(stack *stk, stack_info *err);

#endif /*STACK_H*/
