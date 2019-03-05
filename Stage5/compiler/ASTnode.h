#ifndef ASTNODE_H
#define ASTNODE_H

#include "Gsymbol.h"
#include "Lsymbol.h"


struct ASTnode
{
    int nodeType;
    int dataType;
    char *name;
    int intVal;
    char *stringVal;
    struct ASTnode *argList;
    struct ASTnode *left, *right;
    struct Gsymbol *Gentry;
    struct Lsymbol *Lentry;
};

struct ASTnode *CreateNode(int nodeType, int dataType, struct ASTnode *left, struct ASTnode *right);

#endif