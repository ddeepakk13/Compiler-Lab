/*
 *   <------------------______________tnode.c_______________------------------------>
 *   # The note that makes up the abstract syntax tree
 *   # Please note that stringVal may also masquerade as the variable name
 *   # I'm not sure about if it needs to be done like that; we'll see...
 *   # Note that typechecking for all the nodes will be done here
 *   # The node is only returned after it passes through the Typecheck function
 *   # If any node fails typecheck, process is instatntly terminated
*/

#include "tnode.h"
#include<stdlib.h>
#include<stdio.h>
#include "exp.tab.h"

void Typecheck(struct tnode* node);

/* creates a tree node according to given specifications and returns it's address */
struct tnode *CreateTnode(int nodeType, int dataType, int intVal, char *stringVal, struct symbolNode *varNode, struct tnode *left, struct tnode *right)
{
    struct tnode* temp = malloc(sizeof(struct tnode));  
    temp->nodeType = nodeType;
    temp->dataType = dataType;
    temp->intVal = intVal;
    temp->stringVal = stringVal;
    temp->varNode = varNode;
    temp->left = left;
    temp->right = right;
    Typecheck(temp);                   // call Typecheck on the newly created node to check if it's acceptable type format
    return temp;
};


/* Checks whether the node has acceptable type format; process is terminated if node is unacceptable */
void Typecheck(struct tnode* node)
{
    int leftDataType, rightDataType;
    switch (node->nodeType)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            if(node->left->nodeType == ID)  leftDataType = node->left->varNode->dataType;
            else leftDataType = node->left->dataType;
            if(node->right->nodeType == ID)  rightDataType = node->right->varNode->dataType;
            else rightDataType = node->right->dataType;
            if(leftDataType == rightDataType)   return;
            printf("Error: Type mismatch in aritmetic operator node\n"); exit(1);           
            break;

        case LT:
        case GT:
        case LE:
        case GE:
        case NE:
        case EQ:
            if(node->left->nodeType == ID)  leftDataType = node->left->varNode->dataType;
            else leftDataType = node->left->dataType;
            if(node->right->nodeType == ID)  rightDataType = node->right->varNode->dataType;
            else rightDataType = node->right->dataType;
            if(leftDataType == rightDataType) if(leftDataType != BOOLTYPE) return;
            printf("Error: Type mismatch in logical operator node\n"); exit(1);
            break;

        case IF:
        case WHILE:
            if(node->left->dataType == BOOLTYPE) return;
            printf("Error: Type mismatch in if/while node\n"); exit(1);
            break;

        case READ:                                                             
            if(node->left->nodeType == ID) return;
            printf("Error: type mismatch in Read node\n"); exit(1);
            break;

        case WRITE:
            if(node->left->nodeType == ID)    if(node->left->varNode->dataType == INTTYPE || node->left->varNode->dataType == STRTYPE)    return;
            if(node->left->dataType == INTTYPE || node->left->dataType == STRTYPE) return;
            printf("Error: Type mismatch in Write node\n"); exit(1);
            break;

        case ID:
            if(node->right != NULL)
            {

                if(node->right->nodeType == ID) rightDataType = node->right->varNode->dataType;
                else rightDataType = node->right->dataType;
                if(node->left->nodeType == ID) leftDataType = node->left->varNode->dataType;
                else leftDataType = node->left->dataType;
                if(leftDataType == rightDataType && rightDataType == INTTYPE) return;
            }
            else if(node->left != NULL)
            {
                if(node->left->nodeType == ID) leftDataType = node->left->varNode->dataType;
                else leftDataType = node->left->dataType;
                if(leftDataType == INTTYPE) return;
            }
            else {return;}
            printf("ERROR: Type mismatch in array declaration index\n");printf("%d,%d\n",leftDataType,rightDataType); exit(1);    
            break;
    
        case '=':
            if(node->left->nodeType == ID)
            {
                leftDataType = node->left->varNode->dataType;
                if(node->right->nodeType == ID) rightDataType = node->right->varNode->dataType;
                else rightDataType = node->right->dataType;
                if(leftDataType == rightDataType) return;
            }
            printf("Error: Type mismatch in assignment node\n"); exit(1);
            break;

        default:
            break;
    }
}