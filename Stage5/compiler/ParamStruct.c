#include "ParamStruct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exp.tab.h"
extern struct ParamStruct *paramHead;

void InstallParam(char *name, int type)
{
    struct ParamStruct *temp = malloc(sizeof(struct ParamStruct));
    temp->name = name;
    temp->type = type;
    temp->next = NULL;

    if(paramHead == NULL)
    {
        paramHead = temp;
        return;
    }

    struct ParamStruct *iterator = paramHead;
    while(iterator != NULL)
    {
        if(!strcmp(iterator->name,name))
        {
            printf("ERROR: Multiple instances of variable '%s' found as function parameter\n",name);
            exit(1);
        }
        iterator = iterator->next;
    }
    temp->next = paramHead;
    paramHead = temp;
}

void Check_Param_Equality(struct ParamStruct *p1, struct ParamStruct *p2)
{
    if(p1==NULL && p2==NULL)    return;

    while(p1 != NULL && p2 != NULL)
    {
        if(p1->type == p2->type)
            if(!(strcmp(p1->name,p2->name)))
            {
                p1 = p1->next;
                p2 = p2->next;
                continue;
            }
        printf("ERROR: Parameter mismatch between function definition and declaration\n");
        exit(1);
    }

    if(!(p1 == NULL && p2 == NULL))
    {
        printf("ERROR: Parameter mismatch between function definition and declaration\n");
        exit(1);
    }
}

void Print_Param(struct ParamStruct *node)
{
    struct ParamStruct *iterator = node;
    if(iterator!=NULL) printf("Parameter List:\n");
    while(iterator != NULL)
    {
        char *name = iterator->name;
        int type = iterator->type;
        if(type == INTTYPE) printf("int ");
        else if(type == STRTYPE) printf("str ");
        printf("%s, ",name);
        iterator = iterator->next;
    }
    printf("\n");
}