#include "Gsymbol.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ParamStruct.h"
#include "exp.tab.h"

extern struct Gsymbol *GsymbolTable;
int nextFlabel = 0;
int getFlabel();

struct Gsymbol *GInstall(char *name, int type, int size)   // returns the newly installed node 
{
    struct Gsymbol *temp = malloc(sizeof(struct Gsymbol));
    temp->name = name;
    temp->type = type;
    temp->size = size;
    temp->binding = 4096;
    temp->paramList = NULL;
    if(size == -1) temp->flabel = getFlabel();    // functions are assigned -1 size
    temp->designation = 0;
    temp->next = NULL;

    if(GsymbolTable == NULL)
    {
        GsymbolTable = temp;
        return temp;
    }

    struct Gsymbol *iterator = GsymbolTable;
    while(1)
    {
        if(!strcmp(iterator->name,name))        // checking for multiple definitions
        {
            printf("Error: Multiple instances of global symbol '%s' was declared\n",name);
            exit(1);
        }
        if(iterator->size > 0)
            temp->binding += iterator->size;
        if(iterator->next == NULL) break;
        iterator = iterator->next;
    }
    iterator->next = temp;
    return temp;
}

struct Gsymbol *GLookup(char* name)             // returns the requested node; else null
{
    if(GsymbolTable == NULL)
    {
        printf("ERROR: Trying to access empty Global symbol table\n");
        exit(1);
    }

    struct Gsymbol *iterator = GsymbolTable;
    while(iterator != NULL)
    {
        if(!strcmp(iterator->name,name))    return iterator;
        iterator = iterator->next;
    }
    return NULL;
}

int getFlabel()
{
    return nextFlabel++;
}

void Print_GsymbolTable()
{
    struct Gsymbol *iterator = GsymbolTable;
    if(iterator != NULL)    printf("Global Symbol Table:\n");
    while(iterator != NULL)
    {
        if(iterator->type == INTTYPE)   printf("int ");
        else if(iterator->type == STRTYPE)  printf("str ");
        printf(" %s (%d)\n",iterator->name,iterator->binding);
        if(iterator->designation == FUNCTION)                                // functions are assigned -1 size 
        {
            printf("F%d\n",iterator->flabel);
            Print_Param(iterator->paramList);
        }
        iterator = iterator->next;
    }
}