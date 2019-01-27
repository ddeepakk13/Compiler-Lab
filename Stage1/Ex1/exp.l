%{
    #ifndef YYSTYPE
    #define YYSTYPE struct tnode*
    #endif  
    #include "exptree.h"
    #include "exp.tab.h"
    #include<stdio.h>
    #include<stdlib.h>
    YYSTYPE yylval;
%}

%option noyywrap

%%

[0-9]+ { int n = atoi(yytext);
         yylval = makeLeafNode(n);
         return NUM; }

[-+*/()\n] {return *yytext;}
[ \t]      {}
(.)        {printf("Invalid expression\n");exit(1);}
%%