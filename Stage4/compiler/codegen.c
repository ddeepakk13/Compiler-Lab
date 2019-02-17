#include<stdio.h>
#include<stdlib.h>
#include "codegen.h"
#include "exp.tab.h"
#include "symbolNode.h"
#include "stack.h"

int GetReg();
void FreeReg();
int GetLabel();
int Get_reg_with_value(struct tnode* node);   // node is a ID node; function calculates the value from binding, and returns a register with the value
int Get_reg_with_binding(struct tnode* node); // returns reg with binding of supplied variable node
void Read_to_address_in_reg(int reg);
void Print_value_in_reg(int reg);
void VerifyIndex(struct tnode *node);         // check for out of bound array indexing
extern FILE *fout;
extern struct symbolNode *symbolTable;
static int nextReg = 0;
static int nextLabel = 0;
static struct stack *loop_entry_stack = NULL;
static struct stack *loop_exit_stack = NULL;

void Initialize()
{
    fprintf(fout,"0\n2056\n0\n0\n0\n0\n0\n0\n");
}

void Set_stack()
{
    int address = 4095;
    if(symbolTable == NULL) 
    {
        fprintf(fout,"MOV SP, %d\n",address);
        return;    
    }
    struct symbolNode *iterator = symbolTable;
    while(iterator != NULL)
    {
        if(iterator->next == NULL) address = iterator->binding + iterator->size - 1; 
        iterator = iterator->next;
    }
    fprintf(fout,"MOV SP, %d\n",address);
}

int GetReg()
{
    if(nextReg==20) {printf("Error: Register overflow\n");exit(1);}
    return nextReg++;
}

void FreeReg()
{
    nextReg--;
}

int GetLabel()
{
    return nextLabel++;
}

int Get_reg_with_value(struct tnode *node)
{
    VerifyIndex(node);
    int reg;
    if(node->right != NULL)
    {
        int bindReg = Get_reg_with_binding(node);
        fprintf(fout,"MOV R%d, [R%d]\n",bindReg,bindReg);
        return bindReg;
    }
    if(node->left != NULL)
    {
        reg = Codegen(node->left);
        fprintf(fout,"ADD R%d, %d\n",reg,node->varNode->binding);            
        fprintf(fout,"MOV R%d, [R%d]\n",reg,reg);
        return reg;
    }
    reg = GetReg();
    fprintf(fout,"MOV R%d, [%d]\n",reg,node->varNode->binding);
    return reg;
}

int Get_reg_with_binding(struct tnode *node)
{
    VerifyIndex(node);
    if(node->right != NULL)
    {
        int rowSize = node->varNode->row;
        int columnSize = node->varNode->column;
        if(rowSize == 0 || columnSize == 0) {printf("Error: Trying to access variable like 2d array\n"); exit(1);}
        int rowReg = Codegen(node->left);
        int columnReg = Codegen(node->right);
        fprintf(fout,"MUL R%d, %d\n",rowReg,columnSize);
        fprintf(fout,"ADD R%d, R%d\n", rowReg, columnReg);
        fprintf(fout,"ADD R%d, %d\n",rowReg, node->varNode->binding);
        FreeReg();
        return rowReg;
    }
    if(node->left != NULL)
    {
        int reg = Codegen(node->left);
        fprintf(fout,"ADD R%d, %d\n",reg,node->varNode->binding);            
        return reg;
    }
    int reg = GetReg();
    fprintf(fout,"MOV R%d, %d\n",reg,node->varNode->binding);
    return reg;
}

void Read_to_address_in_reg(int reg)
{
    int bufReg = GetReg();

    fprintf(fout,"MOV R%d, \"Read\"\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"MOV R%d, -1\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",reg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);

    FreeReg();
}

void Print_value_in_reg(int reg)
{
    int bufReg = GetReg();

    fprintf(fout,"MOV R%d, \"Write\"\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"MOV R%d,-2\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",reg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);

    FreeReg();
}

void VerifyIndex(struct tnode *node)    // check index>=0; size-index>0
{
    int size = node->varNode->size;
    if(node->left != NULL)
    {
        int exitLabel = GetLabel();
        int continueLabel = GetLabel();
        int reg = Codegen(node->left);
        int bufReg1 = GetReg();
        fprintf(fout,"MOV R%d, R%d\n",bufReg1,reg);
        int bufReg2 = GetReg();
        fprintf(fout,"MOV R%d, 0\n",bufReg2);
        fprintf(fout,"LE R%d, R%d\n",bufReg2,bufReg1); // 0 <= index
        fprintf(fout,"JZ R%d, L%d\n",bufReg2,exitLabel);
        fprintf(fout,"MOV R%d, %d\n",bufReg2,node->varNode->size);
        fprintf(fout,"SUB R%d, R%d\n",bufReg2,bufReg1);
        fprintf(fout,"MOV R%d, 0\n",bufReg1);
        fprintf(fout,"GT R%d, R%d\n",bufReg2,bufReg1); // size - index > 0
        fprintf(fout,"JZ R%d, L%d\n",bufReg2,exitLabel);
        fprintf(fout,"JMP L%d\n",continueLabel);
        fprintf(fout,"L%d: MOV R%d, \"index error\"\n",exitLabel,bufReg1);
        Print_value_in_reg(bufReg1);
        fprintf(fout,"INT 10\n");
        fprintf(fout,"L%d: ",continueLabel);
        FreeReg();
        FreeReg();
        FreeReg();
    }
}

int Codegen(struct tnode *node)
{
    if(node != NULL) printf("Tree is good in Codegen\n");
    else printf("Tree is broken in Codegen\n");
    if(node->nodeType == CONNECTOR)
    {
        printf("Entered CONNECTOR\n");
        Codegen(node->left);
        Codegen(node->right);
        return 0;
    }

    else if(node->nodeType == NUMBER)
    {
        printf("Entered NUMBER\n");
        int reg = GetReg();
        fprintf(fout,"MOV R%d, %d\n",reg,node->intVal);
        return reg;
    }

    else if(node->nodeType == STRING)
    {
        printf("Entered STRING\n");
        int reg = GetReg();
        fprintf(fout,"MOV R%d, \"%s\"\n",reg,node->stringVal);
        return reg;
    }

    else if(node->nodeType == ID)
    {
        printf("Entered ID\n");
        int reg = Get_reg_with_value(node);
        return reg;
    }

    else if(node->nodeType == READ)
    {
        printf("Entered READ\n");
        int binding = Get_reg_with_binding(node->left);
        Read_to_address_in_reg(binding);
        FreeReg();
        return 0;
    }

    else if(node->nodeType == WRITE)
    {
        printf("Entered WRITE\n");
        int reg = Codegen(node->left);
        Print_value_in_reg(reg);
        FreeReg();
        return 0;
    }

    else if(node->nodeType == '=')
    {
        printf("Entered =\n");
        int reg = Codegen(node->right);
        int binding = Get_reg_with_binding(node->left);
        fprintf(fout,"MOV [R%d], R%d\n",binding,reg);
        FreeReg();
        FreeReg();
        return 0;
    }

    else if(node->nodeType == IF)
    {
        printf("Entered IF\n");
        int label_1 = GetLabel();
        int reg = Codegen(node->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,label_1);
        FreeReg();
        Codegen(node->right->left);
        if(node->right->right == NULL)   fprintf(fout,"L%d: ",label_1);
        else
        {
            int label_2 = GetLabel();
            fprintf(fout,"JMP L%d\n",label_2);
            fprintf(fout,"L%d: ",label_1);
            Codegen(node->right->right);
            fprintf(fout,"L%d: ",label_2);
        }
        return 0;
    }

    else if(node->nodeType == WHILE)
    {
        printf("Entered WHILE\n");
        int loopEntry = GetLabel();
        int loopExit = GetLabel();
        loop_entry_stack = Push_to_stack(loop_entry_stack,loopEntry);
        loop_exit_stack = Push_to_stack(loop_exit_stack,loopExit);
        fprintf(fout,"L%d: ",loopEntry);
        int reg = Codegen(node->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,loopExit);
        FreeReg();
        Codegen(node->right);
        fprintf(fout,"JMP L%d\n",loopEntry);
        fprintf(fout,"L%d: ",loopExit);
        loop_entry_stack = Pop_from_stack(loop_entry_stack);
        loop_exit_stack = Pop_from_stack(loop_exit_stack);
        return 0;
    }

    else if(node->nodeType == BREAK)
    {
        printf("Entered BREAK\n");
        if(loop_exit_stack != NULL)
        {
            int exitLabel = Peek(loop_exit_stack);
            fprintf(fout,"JMP L%d\n",exitLabel);
        }
        return 0;
    }

    else if(node->nodeType == CONTINUE)
    {
        printf("Entered CONTINUE\n");
        if(loop_entry_stack != NULL)
        {
            int entryLabel = Peek(loop_entry_stack);
            fprintf(fout,"JMP L%d\n",entryLabel);
        }
        return 0;
    }

    else
    {
        printf("Entered operator section\n");
        int leftReg = Codegen(node->left);
        int rightReg = Codegen(node->right);
        switch(node->nodeType)
        {
            case '+' : fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); break;
            case '-' : fprintf(fout,"SUB R%d, R%d\n",leftReg,rightReg); break;
            case '*' : fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); break;
            case '/' : fprintf(fout,"DIV R%d, R%d\n",leftReg,rightReg); break;
            case '%' : fprintf(fout,"MOD R%d, R%d\n",leftReg,rightReg); break;
            case GT : fprintf(fout,"GT R%d, R%d\n",leftReg,rightReg); break;
            case LT : fprintf(fout,"LT R%d, R%d\n",leftReg,rightReg); break;
            case EQ : fprintf(fout,"EQ R%d, R%d\n",leftReg,rightReg); break;
            case NE : fprintf(fout,"NE R%d, R%d\n",leftReg,rightReg); break;
            case GE : fprintf(fout,"GE R%d, R%d\n",leftReg,rightReg); break;
            case LE : fprintf(fout,"LE R%d, R%d\n",leftReg,rightReg); break;
        }
        FreeReg();
        return leftReg;
    }
    
}

/* Before wrapping up check if all registers are freed; and every case returns int */