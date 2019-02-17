/*
 * <--------------------------____________symbolNode.c__________---------------------------------->
 * 
 * # The node that makes up symbol list containing variables
 * # The fuctions for adding variables and looking up variables from the symol tabel is defined here
 * 
*/

#include "symbolNode.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern struct symbolNode *symbolTable;                  // head of the symbol table linked list; defined in yacc and initialized to NULL

void Install(char *varName, int dataType, int size)    // adds a variable to the symbol table; raises error if variable is already present
{
    struct symbolNode *temp = malloc(sizeof(struct symbolNode));
    temp->varName = varName;
    temp->dataType = dataType;
    temp->size = size;
    temp->binding = 4096;                              // variable bindings start from 4096
    temp->next = NULL;
    temp->row = 0;
    temp->column = 0;
    if(symbolTable == NULL)                            // initial empty symbol table condition; just assign temp as the head node of symbol table
    {
        symbolTable = temp;
        return;
    }
    struct symbolNode *iterator = symbolTable;
    while(1)                                                                                // iterate through symbol table
    {
        if(!(strcmp(iterator->varName,varName)))                                            // if variable is already entered in table produce error and terminate process
        {
            printf("Error: Multiple instances of variable '%s' is declared\n",varName);
            exit(1);
        }
        temp->binding += iterator->size;                                                    // otherwise binding of temp is to be updated taking into account the space previous variables will take up
        if(iterator->next == NULL) break;                                                   // break away at the last node
        iterator = iterator->next;
    }
    iterator->next = temp;                                                                  // if all goes well slap the new variable node on to the back of symbol table and we're done. TEEHEE!
}

struct symbolNode *Lookup(char * varName)                                                   // lookup a particular variable and return its node address; returns NULL if not found
{
    if(symbolTable == NULL)
    {
        printf("ERROR: Trying to access empty symbol table\n");
        exit(1);
    }
    struct symbolNode *iterator = symbolTable;
    while(iterator != NULL)                                                                 // iterate through symbol table
    {
        if(!(strcmp(iterator->varName,varName)))                                            // find matching entry
        {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;                                                                            // return NULL if not found
}
