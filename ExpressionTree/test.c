#include<stdio.h>
#include<stdlib.h>
#include "exptree.h"
int x = 16;
int main()
{
    struct tnode* l = makeLeafNode(2);
    struct tnode* r = makeLeafNode(5);
    struct tnode* root = makeOperatorNode('*',l,r);
    int sum=evaluate(root);
    printf("%d\n%d\n",sum,x);
}