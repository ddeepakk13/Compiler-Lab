#ifndef TNODE_H
#define TNODE_H

/*
 *   <------------------------------TNODE_H------------------------------->
 *   # The node that makes up the abstract syntax tree
 *   # Please note that stringVal may also masquerade as the variable name
 *   # I'm not sure about if it needs to be done like that; we'll see
*/

struct tnode
{
    /*
     * I might write an explanation for all the identifier types in yacc
     * So, check that out if you are confused about the identifiers used
    */
    int nodeType;                   // contains the nodetype identifier
    int dataType;                   // contains the datatype identifier
    int intVal;                     // stores the integer value of literals and integer type variables
    char *stringVal;                // stores the string value of literals and string type variables and may also store the variable name when it's a variable node
    struct tnode *left, *right;     // the left and right branches
};

/*before writing tnode functions comlete symbolNode*/

#endif