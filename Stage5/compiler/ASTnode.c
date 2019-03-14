#include "ASTnode.h"
#include <stdlib.h>
#include <stdio.h>
#include "exp.tab.h"

void TypecheckNode(struct ASTnode *node);
extern int decType;

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
    int leftType, rightType;
    switch (node->nodeType)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            leftType = Get_Data_Type(node->left);
            rightType = Get_Data_Type(node->right);
            if(leftType == INTTYPE && rightType == INTTYPE) return;
            printf("ERROR: Non int operand found in arithmetic operator\n");
            exit(1);
            break;

        case EQ:
        case NE:
        case LT:
        case GT:
        case LE:
        case GE:
            leftType = Get_Data_Type(node->left);
            rightType = Get_Data_Type(node->right);
            if(leftType == INTTYPE && rightType == INTTYPE) return;
            if(leftType == STRTYPE && rightType == STRTYPE) return;
            printf("ERROR: Type mismatch in logical operator node\n");
            exit(1);
            break;

        case AND:
        case OR :
            leftType = Get_Data_Type(node->left);
            rightType = Get_Data_Type(node->right);
            if(leftType == BOOLTYPE && rightType == BOOLTYPE) return;
            printf("ERROR: Type mismatch in AND/OR node\n");
            exit(1);
            break;

        case NOT:
            leftType = Get_Data_Type(node->left);
            if(leftType == BOOLTYPE)    return;
            printf("ERROR: not operator expects boolean input\n");
            exit(1);
            break;

        case RETURN:
            leftType = Get_Data_Type(node->left);
            if(leftType == decType)  return;                    // decType contains current return type
            printf("ERROR: Type mismatch in return statement\n");
            exit(1);
            break;

        case WRITE:
            leftType = Get_Data_Type(node->left);
            if(leftType == INTTYPE || leftType == STRTYPE)  return;
            printf("ERROR: Type mismatch in write statement\n");
            exit(1);
            break;

        case READ: break;           // No particular check needed

        case '=':
            leftType = Get_Data_Type(node->left);
            rightType = Get_Data_Type(node->right);
            if(leftType == INTTYPE && rightType == INTTYPE) return;
            if(leftType == STRTYPE && rightType == STRTYPE) return;
            printf("ERROR: Type mismatch in assignment statement\n");
            exit(1);
            break;

        case IF:
        case WHILE:
            leftType = Get_Data_Type(node->left);
            if(leftType == BOOLTYPE)    return;
            printf("ERROR: Conditional argument should be of Boolean type\n");
            exit(1);
            break;

        default:
            break;
    }
}

int Get_Data_Type(struct ASTnode *node)
{
    int dataType = node->dataType;
    if(node->nodeType == ID)
    {
        if(node->Lentry != NULL) dataType = node->Lentry->type;
        else if(node->Gentry != NULL)   dataType = node->Gentry->type;
    }
    return dataType;
}