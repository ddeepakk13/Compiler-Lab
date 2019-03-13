#include "Lsymbol.h"
#include "Gsymbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ParamStruct.h"
#include "exp.tab.h"

extern struct Lsymbol *LsymbolTable;
extern struct Gsymbol *GsymbolTable;
extern struct ParamStruct *paramHead;

struct Lsymbol *LInstall(char *name, int type)      // returns installed node
{
    struct Lsymbol *temp = malloc(sizeof(struct Lsymbol));
    temp->name = name;
    temp->type = type;
    temp->binding = 1;
    temp->next = NULL;

    if(LsymbolTable == NULL)
    {
        LsymbolTable = temp;
        return temp;
    }

    struct Gsymbol *Giterator = GsymbolTable;
    while(Giterator != NULL)
    {
        if(Giterator->designation == FUNCTION)               // if function
            if(!strcmp(Giterator->name,name))
            {
                printf("ERROR: Local variable '%s' cannot assume name of a function\n",name);
                exit(1);
            }
        Giterator = Giterator->next;
    }

    struct Lsymbol *iterator = LsymbolTable;
    while(1)
    {
        if(!strcmp(iterator->name,name))
        {
            printf("ERROR: Multiple instances of local variable '%s' was declared\n",name);
            exit(1);
        }

        if(iterator->next == NULL)  break;
        iterator = iterator->next;
    }
    if(iterator->binding >= 1)
    temp->binding = iterator->binding + 1;
    iterator->next = temp;
    return temp;
}

struct Lsymbol *LLookup(char *name)                // returns requested node; else NULL
{
    if(LsymbolTable == NULL)
    {
        return NULL;
    }

    struct Lsymbol *iterator = LsymbolTable;
    while(iterator != NULL)
    {
        if(!strcmp(iterator->name,name))    return iterator;
        iterator = iterator->next;
    }
    return NULL;
}

void LParam_Install()
{
    if(paramHead != NULL)
    {
        int i = -3;
        struct ParamStruct *iterator = paramHead;
        while(iterator != NULL)
        {
            int type = iterator->type;
            char *name = iterator->name;
            struct Lsymbol *temp = LInstall(name, type);
            temp->binding = i--;
            iterator = iterator->next;
        }
    }
}

void Print_LsymbolTable()
{
    if(LsymbolTable!=NULL)  printf("Local Symbol Table:\n");
    struct Lsymbol *iterator = LsymbolTable;
    while(iterator != NULL)
    {
        if(iterator->type == INTTYPE)   printf("int ");
        else if(iterator->type == STRTYPE)  printf("str ");
        printf("%s (%d)\n",iterator->name,iterator->binding);
        iterator = iterator->next;
    }
}