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

[a-z]   {char *c = malloc(sizeof(char)); *c = *yytext; yylval = createNode(VAR,INTTYPE,0,c,NULL,NULL); return VAR;}
[0-9]+  {yylval = createNode(NUM,INTTYPE,atoi(yytext),NULL,NULL,NULL);return NUM;}
[-+*/();=] {return *yytext;}
"=="    {return EQ;}
"!="    {return NE;}
"<"     {return LT;}
">"     {return GT;}
"<="    {return LE;}
">="    {return GE;}
"read"  {return READ;}
"write" {return WRITE;}
"begin" {return START;}
"end"   {return END;}
"if"    {return IF;}
"then"  {return THEN;}
"else"  {return ELSE;}
"endif" {return ENDIF;}
"while" {return WHILE;}
"do"    {return DO;}
"endwhile" {return ENDWHILE;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
[ \t\n] {}
(.)     {printf("Invalid expression\n");exit(1);}
