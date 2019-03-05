#ifndef PARAMSTRUCT_H
#define PARAMSTRUCT_H

struct ParamStruct
{
    char *name;
    int type;
    struct ParamStruct *next;
};

void InstallParam(char *name, int type);
void Check_Param_Equality(struct ParamStruct *p1, struct ParamStruct *p2);
void Print_Param(struct ParamStruct *node);
#endif