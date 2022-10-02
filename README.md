<img src="https://github.com/XelerT/stack/blob/main/img/canary.gif" alt="Canary" width="200"/>

# Stack

This is simple stack, created with array. You can turn on/off canary or hash protections

## Install and run

- `$ git clone https://github.com/XelerT/stack.git`
- `$ make`
- `$ make run`

## INFO
- After running program you will need to enter initial capacity of stack.

### How to use.
- Stack is structure named stack. Created it like this: `stack stk1 = {};`
- You have 2 stack functions: push, pop, oper_stack_ctor.
#### Constructor
- `oper_stack_ctor(&stk1, capacity, (char*) "stk1", (char*) __PRETTY_FUNCTION__, (char*) __FILE__,__LINE__)` Gets adress of stack, initial capacity and information about place of creation.
#### Push
- `stack_push_f(&stk1, i)` - The first argument gets adress of stack, the second gets value, you want to put in stack.
- If error occurs returns PUSH_ERROR.
#### Pop
- `stack_pop(&stk1)` - Function gets only adress of stack.
- If error occurs returns POP_ERROR.

### Protection
- You can turn on Canary or Hash protection using preprocessor.
- To turn on/off protection you need to open `stack.h` and change defines:
        - ```#define FULL_SECURITY``` will turn on canaries and hashes;
        - ```#define CANARY_ON``` will turn on only canary protection;
        - ```#define HASH_ON``` will turn on only hash protection.
        <img src="https://github.com/XelerT/stack/blob/main/img/example.png" alt="example" width="200"/>

### Error analytics
- `stack_dump()` will give you all information about stack condition in case of error.


## Credits
- Created by Alex Taranov as the third task in X course.
