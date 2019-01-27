%{
    #include<stdio.h>
    #include "Q2.tab.h"
    #include<stdlib.h>
    void yyerror(const char *s);
%}

%option noyywrap

%%

[0-9]    {return DIGIT;}
[a-zA-Z] {return ALPHA;}
(.)      {yyerror("Invalid character\n"); exit(1);}
%%