#ifndef CODEGEN_H
#define CODEGEN_H

#include "exptree.h"
#include<stdio.h>

void initialize(FILE* fout);                       //initialize the code header
void set_SP(FILE *fout);                           //initialize SP so that 26 static variables are available
void storeReg0(FILE *fout, char static_var);       //store contents of Register 0 to static variable (a-z)
void print_static_var(FILE *fout, char static_var);
int codegen(struct tnode *root, FILE* fout);
int getReg();
void freeReg();
static int nextReg = 0;

#endif
