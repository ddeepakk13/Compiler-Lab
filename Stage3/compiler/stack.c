#include "stack.h"
#include<stdio.h>
#include<stdlib.h>

struct stack* push_to_stack(struct stack* top,int label)
{
    struct stack *temp = malloc(sizeof(struct stack));
    temp->label = label;
    temp->next = NULL;
    if(top == NULL) return temp;
    temp->next = top;
    return temp;
}

struct stack* pop_from_stack(struct stack *top, int* label)
{
    *label = top->label;
    struct stack *temp = top->next;
    free(top);
    return temp;
}