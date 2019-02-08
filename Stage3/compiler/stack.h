#ifndef STACK_H
#define STACK_H

struct stack
{
    int label;
    struct stack *next;
};

struct stack* push_to_stack(struct stack* top,int label);
struct stack* pop_from_stack(struct stack *top, int* label);

#endif