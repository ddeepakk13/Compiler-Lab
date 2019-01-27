%{
    #ifndef YYSTYPE
    #define YYSTYPE struct tnode*
    #endif
    #include "nodeStructure.h"
    #include "exp.tab.h"
    #include<stdio.h>
    #include<stdlib.h>
    YYSTYPE yylval;
%}

%option noyywrap

%%

[a-z]   {char *c = malloc(sizeof(char)); *c = *yytext; yylval = createNode(VAR,0,0,c,NULL,NULL); return VAR;}
[0-9]+  {yylval = createNode(NUM,0,atoi(yytext),NULL,NULL,NULL);return NUM;}
[-+*/();=] {return *yytext;}
"read"  {return READ;}
"write" {return WRITE;}
"begin" {return START;}
"end"   {return END;}
[ \t\n] {}
(.)     {printf("Invalid expression\n");exit(1);}
