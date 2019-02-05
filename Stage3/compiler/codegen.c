#include<stdio.h>
#include<stdlib.h>
#include "codegen.h"
#include "exp.tab.h"
#include "stack.h"
static int nextReg = 0;
static int nextLabel = 0;
struct stack *loop_entry = NULL;
struct stack *loop_exit = NULL;

void initialize()
{
    fprintf(fout,"0\n2056\n0\n0\n0\n0\n0\n0\n");
}

void set_static_stack()
{
    fprintf(fout,"MOV SP, %d\n",4095+26);
}

void store_reg_0(char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV [%d], R0\n",address);
}

void print_static_var(char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV R1, \"Write\"\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"MOV R1,-2\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"MOV R0,[%d]\n",address);
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
}

void print_reg_0()
{
    fprintf(fout,"MOV R1, \"Write\"\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"MOV R1,-2\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
}

int getReg()
{
    if(nextReg==20) {printf("Error: Register overflow\n");exit(1);}
    return nextReg++;
}

void freeReg()
{
    nextReg--;
}

int getLabel()
{
    return nextLabel++;
}

void store_to_static_variable(int reg,char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV [%d], R%d\n",address,reg);
}

void read_to_variable(char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV R1, \"Read\"\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"MOV R1,-1\n");
    fprintf(fout,"PUSH R1\n");
    fprintf(fout,"MOV R0, %d\n",address);
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
    fprintf(fout,"POP R0\n");
}

int codegen(struct tnode* root)
{   
    if(root->nodeType == NUM)
    {
        int reg = getReg();
        fprintf(fout,"MOV R%d, %d\n",reg,root->val);
        return reg;
    }

    else if(root->nodeType == VAR)
    {
        int address = 4096 + *(root->varName) - 'a';
        int reg = getReg();
        fprintf(fout,"MOV R%d, [%d]\n",reg,address);
        return reg;
    }

    else if(root->nodeType == CONNECTOR)
    {
        codegen(root->left);
        codegen(root->right);
        return 0;
    }

    else if(root->nodeType == READ)
    {
        read_to_variable(*(root->left->varName));
        return 0;
    }

    
    else if(root->nodeType == WRITE)
    {
        int reg = codegen(root->left);   //returns 0 all the time; There isn't any point in storing it
        print_reg_0(fout);
        freeReg();
        return 0;
    }

    else if(root->nodeType == '=')
    {
        int reg = codegen(root->right);
        store_to_static_variable(0, *(root->left->varName));
        freeReg();
        return 0;
    }

    else if(root->nodeType == IF)
    {
        int label_1 = getLabel();
        int reg = codegen(root->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,label_1);
        freeReg();
        codegen(root->right->left);
        if(root->right->right == NULL)
        {
            fprintf(fout,"L%d: ",label_1);
        }

        else
        {
            int label_2 = getLabel();
            fprintf(fout,"JMP L%d\n",label_2);
            fprintf(fout,"L%d: ",label_1);
            codegen(root->right->right);
            fprintf(fout,"L%d: ",label_2);
        }
        return 0;
    }

    else if(root->nodeType == WHILE)
    {
        int label_1 = getLabel();
        int label_2 = getLabel();
        loop_entry = push_to_stack(loop_entry,label_1);
        loop_exit = push_to_stack(loop_exit,label_2);
        fprintf(fout,"L%d: ",label_1);
        int reg = codegen(root->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,label_2);
        freeReg();
        codegen(root->right);
        fprintf(fout,"JMP L%d\n",label_1);
        fprintf(fout,"L%d: ",label_2);
        return 0;
    }

    else if(root->nodeType == BREAK)
    {
        int exit_label;
        loop_exit = pop_from_stack(loop_exit,&exit_label);
        fprintf(fout,)
    }

    // for all the rest node types
    else
    {
        int leftReg = codegen(root->left);
        int rightReg = codegen(root->right);
        switch(root->nodeType)
        {
            case '+' : fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); break;
            case '-' : fprintf(fout,"SUB R%d, R%d\n",leftReg,rightReg); break;
            case '*' : fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); break;
            case '/' : fprintf(fout,"DIV R%d, R%d\n",leftReg,rightReg); break;
            case GT : fprintf(fout,"GT R%d, R%d\n",leftReg,rightReg);break;
            case LT : fprintf(fout,"LT R%d, R%d\n",leftReg,rightReg);break;
            case EQ : fprintf(fout,"EQ R%d, R%d\n",leftReg,rightReg);break;
            case NE : fprintf(fout,"NE R%d, R%d\n",leftReg,rightReg);break;
            case GE : fprintf(fout,"GE R%d, R%d\n",leftReg,rightReg);break;
            case LE : fprintf(fout,"LE R%d, R%d\n",leftReg,rightReg);break;
        }
        freeReg();
        return leftReg;
    }
    
}