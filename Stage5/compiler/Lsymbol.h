#ifndef LSYMBOL_H
#define LSYMBOL_H

struct Lsymbol
{
    char *name;
    int type;
    int binding;
    struct Lsymbol *next;
};

struct Lsymbol *LInstall(char *name, int type);     // returns installed node
struct Lsymbol *LLookup(char *name);                // returns requested node; else NULL
void LParam_Install();
void Print_LsymbolTable();

#endif