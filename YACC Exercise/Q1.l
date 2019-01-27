%{
    #include<stdio.h>
    #include "Q1.tab.h"
%}

%option noyywrap

%%

s {return STMNT;}
c {return COND;}
"IF" {return IF;}
[(){}] {return *yytext;}
[ \n\t]
(.)    {printf("Invalid character \n");exit(1);}

