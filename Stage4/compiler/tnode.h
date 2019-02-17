#ifndef TNODE_H
#define TNODE_H

/*
 *   <------------------------------TNODE_H------------------------------->
 *   # The note that makes up the abstract syntax tree
 *   # Please note that stringVal may also masquerade as the variable name
 *   # I'm not sure about if it needs to be done like that; we'll see
*/

#include "symbolNode.h"

struct tnode
{
    int nodeType;                   // contains the nodetype identifier
    int dataType;                   // contains the datatype identifier
    int intVal;                     // stores the integer value of literals and integer type variables; at some instances stores size of variable
    char *stringVal;                // stores the string value of literals and string type variables and may also store the variable name when it's a variable node
    struct symbolNode *varNode;     // points to variable's symbol table entry
    struct tnode *left, *right;     // the left and right branches
};

/*
 * I might write an explanation for all the identifier types in yacc
 * So, check that out if you are confused about the identifiers used
*/


/*<-------------------Function Prototypes------------------------->*/

/* creates a tree node according to given specifications and returns it's address */
struct tnode *CreateTnode(int nodeType, int dataType, int intVal, char *stringVal, struct symbolNode *varNode, struct tnode *left, struct tnode *right);

#endif