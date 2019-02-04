#include "nodeStructure.h"
#include "exp.tab.h"
#include<stdlib.h>
#include<stdio.h>

struct tnode* createNode(int nodeType, int dataType,int val, char* varName, struct tnode *l, struct tnode *r)
{
    if(nodeType == IF || nodeType == WHILE)
    {
        if(l->dataType != BOOLTYPE)
        {
            printf("Error: Type mismatch in if/while/write\n");
            exit(1);
        } 
    }

    else if(nodeType == WRITE)
    {
        if(l->dataType != INTTYPE)
        {
            printf("Error: Type mismatch in if/while/write\n");
            exit(1);
        }
    }

    else if(nodeType == '=')
    {
        if(r->dataType != INTTYPE)
        {
            printf("Error: Type mismatch in '='\n");
            exit(1);
        }
    }

    struct tnode *pnode = malloc(sizeof(struct tnode));
    pnode->nodeType = nodeType;
    pnode->dataType = dataType;
    pnode->val = val;
    pnode->varName = varName;
    pnode->left = l;
    pnode->right = r;
    return pnode;
}