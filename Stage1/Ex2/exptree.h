#ifndef EXPTREE_H
#define EXPTREE_H

struct tnode
{
    int value;
    char *op;               
    struct tnode* left;
    struct tnode* right;
};

struct tnode* makeLeafNode(int n);
struct tnode* makeOperatorNode(char op, struct tnode* l, struct tnode* r);
int evaluate(struct tnode* root);

#endif