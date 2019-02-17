#ifndef STACK_H
#define STACK_H

struct stack
{
    int label;
    struct stack *next;
};

struct stack* Push_to_stack(struct stack* top,int label);
struct stack* Pop_from_stack(struct stack *top);
int Peek(struct stack *top);

#endif