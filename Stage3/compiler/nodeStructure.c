#include "nodeStructure.h"
#include "exp.tab.h"
#include<stdlib.h>
#include<stdio.h>

struct tnode* createNode(int nodeType, int dataType,int val, char* varName, struct tnode *l, struct tnode *r)
{
    struct tnode *temp = malloc(sizeof(struct tnode));
    temp->nodeType = nodeType;
    temp->dataType = dataType;
    temp->val = val;
    temp->varName = varName;
    temp->left = l;
    temp->right = r;
    typecheck(temp);
    return temp;
}

void typecheck(struct tnode* node)
{
    switch (node->nodeType)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            if(node->left->dataType == INTTYPE && node->right->dataType==INTTYPE) return;
            printf("Error: Type mismatch in aritmetic operator node\n"); exit(1);           //would probably never happen
            break;
        
        case LT:
        case GT:
        case LE:
        case GE:
        case NE:
        case EQ:
            if(node->left->dataType == INTTYPE && node->right->dataType == INTTYPE) return;
            printf("Error: Type mismatch in logical operator node\n"); exit(1);
            break;

        case IF:
        case WHILE:
            if(node->left->dataType == BOOLTYPE) return;
            printf("Error: Type mismatch in if/while node\n"); exit(1);
            break;

        case READ:                                                              // I doubt this would ever happen; Atleast for now the grammar rules are enough
            if(node->left->nodeType == VAR) return;
            printf("Error: type mismatch in Read node\n"); exit(1);
            break;

        case WRITE:
            if(node->left->dataType == INTTYPE) return;
            printf("Error: Type mismatch in Write node\n"); exit(1);
            break;

        case '=':
            if(node->left->nodeType == VAR)                                     // Again grammar rules ensure this doesn't happen
                if(node->left->dataType == node->right->dataType) return;
            printf("Error: Type mismatch in assignment node\n"); exit(1);
            break;

        default:
            break;
    }
}