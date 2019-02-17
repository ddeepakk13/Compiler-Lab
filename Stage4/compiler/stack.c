#include "stack.h"
#include<stdio.h>
#include<stdlib.h>

struct stack* Push_to_stack(struct stack* top,int label)
{
    struct stack *temp = malloc(sizeof(struct stack));
    temp->label = label;
    temp->next = NULL;
    if(top == NULL) return temp;
    temp->next = top;
    return temp;
}

struct stack* Pop_from_stack(struct stack *top)
{
    struct stack *temp = top->next;
    free(top);
    return temp;
}

int Peek(struct stack *top)
{
    return top->label;
}