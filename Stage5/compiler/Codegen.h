#ifndef CODEGEN_H
#define CODEGEN_H

#include "ASTnode.h"

void Initialize();
void Generate_Function_Code(struct ASTnode *node);
int Codegen(struct ASTnode *node);

#endif