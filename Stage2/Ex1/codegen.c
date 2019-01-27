#include<stdio.h>
#include<stdlib.h>
#include "codegen.h"
#include "exp.tab.h"

void initialize(FILE* fout)
{
    fprintf(fout,"0\n2056\n0\n0\n0\n0\n0\n0\n");
}

void set_static_stack(FILE *fout)
{
    fprintf(fout,"MOV SP, %d\n",4095+26);
}

void store_reg_0(FILE *fout, char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV [%d], R0\n",address);
}

void print_static_var(FILE *fout, char static_var)
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

void print_reg_0(FILE *fout)
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

void store_to_static_variable(FILE *fout,int reg,char static_var)
{
    int address = 4096 + static_var - 'a';
    fprintf(fout,"MOV [%d], R%d\n",address,reg);
}

void read_to_variable(FILE *fout, char static_var)
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

int codegen(FILE* fout, struct tnode* root)
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
        codegen(fout,root->left);
        codegen(fout,root->right);
        return 0;
    }

    else if(root->nodeType == READ)
    {
        read_to_variable(fout, *(root->left->varName));
        return 0;
    }

    
    else if(root->nodeType == WRITE)
    {
        int reg = codegen(fout, root->left);   //returns 0 all the time; There isn't any point in storing it
        print_reg_0(fout);
        freeReg();
        return 0;
    }

    else if(root->nodeType == '=')
    {
        int reg = codegen(fout, root->right);
        store_to_static_variable(fout, 0, *(root->left->varName));
        freeReg();
        return 0;
    }

    // for all the rest node types
    else
    {
        int leftReg = codegen(fout, root->left);
        int rightReg = codegen(fout, root->right);
        switch(root->nodeType)
        {
            case '+' : fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); freeReg(); break;
            case '-' : fprintf(fout,"SUB R%d, R%d\n",leftReg,rightReg); freeReg(); break;
            case '*' : fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); freeReg(); break;
            case '/' : fprintf(fout,"DIV R%d, R%d\n",leftReg,rightReg); freeReg(); break;
        }
        return leftReg;
    }
    
}