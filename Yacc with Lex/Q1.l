%{
    #ifndef YYSTYPE
    #define YYSTYPE char
    #endif
    #include<stdio.h>
    #include<stdlib.h>
    #include "Q1.tab.h"
    YYSTYPE yylval;
%}

%option noyywrap

%%

[a-zA-z] {yylval=*yytext; return CHARACTER;}
[-+*/]   {yylval=*yytext; return *yytext;}
[ \n\t]  
(.)      {printf("Invalid character in input\n"); exit(1);}
