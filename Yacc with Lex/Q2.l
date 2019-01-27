%{
    #ifndef YYSTYPE
    #define YYSTYPE char*
    #endif
    #include<stdio.h>
    #include<stdlib.h>
    #include "Q2.tab.h"
    #include<string.h>
    YYSTYPE yylval;
%}

%option noyywrap

%%

[a-zA-Z]+    {yylval=strdup(yytext); return WORD;}
[-+*/]       {yylval=strdup(yytext); return *yytext;}
[ \n\t]  
(.)          {printf("Invalid character __%c__ in input\n",*yytext); exit(1);}
