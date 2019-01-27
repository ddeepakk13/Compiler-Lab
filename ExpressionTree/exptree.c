#include "exptree.h"
#include<stdio.h>
#include<stdlib.h>

struct tnode* makeLeafNode(int n)
{
    struct tnode* leafptr = malloc(sizeof(struct tnode));
    leafptr->value = n;
    leafptr->op = NULL;
    leafptr->left=NULL;
    leafptr->right=NULL;
    return leafptr;
}

struct tnode* makeOperatorNode(char c, struct tnode* l, struct tnode* r)
{
    struct tnode* nodeptr = malloc(sizeof(struct tnode));
    nodeptr->op = malloc(sizeof(char));
    *(nodeptr->op) = c;
    nodeptr->left = l;
    nodeptr->right = r;
    return nodeptr;
}

int evaluate(struct tnode* root)
{
    if (root->op == NULL) return root->value;
    switch(*(root->op))
    {
        case '+' : return evaluate(root->left) + evaluate(root->right);
        case '-' : return evaluate(root->left) - evaluate(root->right);
        case '*' : return evaluate(root->left) * evaluate(root->right);
        case '/' : return evaluate(root->left) / evaluate(root->right);
    }
}