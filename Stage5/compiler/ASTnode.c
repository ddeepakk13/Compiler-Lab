#include "ASTnode.h"
#include <stdlib.h>

void TypecheckNode(struct ASTnode *node);

struct ASTnode *CreateNode(int nodeType, int dataType, struct ASTnode *left, struct ASTnode *right)
{
    struct ASTnode *temp = malloc(sizeof(struct ASTnode));

    temp->nodeType = nodeType;
    temp->dataType = dataType;
    temp->left = left;
    temp->right = right;
    temp->name = NULL;
    temp->intVal = 0;
    temp->stringVal = NULL;
    temp->argList = NULL;
    temp->Gentry = NULL;
    temp->Lentry = NULL;

    TypecheckNode(temp); 

    return temp;
}

void TypecheckNode(struct ASTnode *node)
{

}