#include<stdio.h>
#include<stdlib.h>
#include "codegen.h"

int getReg()
{
    if(nextReg==20) {printf("Error: Register overflow\n");exit(1);}
    return nextReg++;
}

void freeReg()
{
    nextReg--;
}

int codegen(struct tnode* root, FILE* fout)
{
    if(root->op == NULL)
    {
        int reg = getReg();
        fprintf(fout,"MOV R%d, %d\n",reg,root->value);
        return reg;
    }
    int leftReg = codegen(root->left,fout);
    int rightReg = codegen(root->right,fout);
    switch(*(root->op))
    {
        case '+' : fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); freeReg(); break;
        case '-' : fprintf(fout,"SUB R%d, R%d\n",leftReg,rightReg); freeReg(); break;
        case '*' : fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); freeReg(); break;
        case '/' : fprintf(fout,"DIV R%d, R%d\n",leftReg,rightReg); freeReg(); break;
    }
    return leftReg;

}

void initialize(FILE* fout)
{
    fprintf(fout,"0\n2056\n0\n0\n0\n0\n0\n0\n");
}

void storeReg0(FILE *fout, char static_var)
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

void set_SP(FILE *fout)
{
    fprintf(fout,"MOV SP, %d\n",4096+26);
}