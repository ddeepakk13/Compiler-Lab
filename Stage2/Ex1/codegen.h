#ifndef CODEGEN_H
#define CODEGEN_H

#include "nodeStructure.h"
#include<stdio.h>

void initialize(FILE* fout);                                 //initialize the code header
void set_static_stack(FILE *fout);                           //initialize SP so that 26 static variables are available
void store_reg_0(FILE *fout, char static_var);               //store contents of Register 0 to static variable (a-z)
void store_to_static_variable(FILE *fout,int reg,char static_var);
void print_static_var(FILE *fout, char static_var);
void print_reg_0(FILE *fout);
void read_to_variable(FILE *fout, char static_var);
int codegen(FILE* fout, struct tnode *root);
int getReg();
void freeReg();
static int nextReg = 0;

#endif