#include "nodeStructure.h"
#include<stdlib.h>

struct tnode* createNode(int nodeType, int dataType,int val, char* varName, struct tnode *l, struct tnode *r)
{
    struct tnode *pnode = (struct tnode*)malloc(sizeof(struct tnode));
    pnode->nodeType = nodeType;
    pnode->dataType = dataType;
    pnode->val = val;
    pnode->varName = varName;
    pnode->left = l;
    pnode->right = r;
    return pnode;
}