#ifndef CODEGEN_H
#define CODEGEN_H

#include "nodeStructure.h"
#include<stdio.h>

void initialize();                                 //initialize the code header
void set_static_stack();                           //initialize SP so that 26 static variables are available
void store_reg_0(char static_var);               //store contents of Register 0 to static variable (a-z)
void store_to_static_variable(int reg,char static_var);
void print_static_var(char static_var);
void print_reg_0();
void read_to_variable(char static_var);
int codegen(struct tnode *root);
int getReg();
void freeReg();
int getLabel();
extern FILE* fout;

#endif