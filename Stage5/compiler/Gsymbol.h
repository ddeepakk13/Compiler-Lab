#ifndef GSYMBOL_H
#define GSYMBOL_H

#include"ParamStruct.h"

struct Gsymbol
{
    char* name;
    int type;
    int size;
    int binding;
    struct ParamStruct *paramList;
    int flabel;
    struct Gsymbol *next;
};

struct Gsymbol *GInstall(char *name, int type, int size);   // returns the newly installed node 
struct Gsymbol *GLookup(char* name);                        // returns the requested node; else null
void Print_GsymbolTable();

#endif