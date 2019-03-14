
/* <------------------------________________DECLARATIONS__________________-------------------------------> */

%{
    #define YYSTYPE struct ASTnode*
    #include "ASTnode.h"
    #include "exp.tab.h"
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    YYSTYPE yylval;
    char *RemoveQuotes();
%}

%option noyywrap    

%%  /* <----------------------------------END_OF_DECLARATIONS-------------------------------------------> */
    /* <------------------------------------------------------------------------------------------------> */

[-+*/%(){};=[\],]       {return *yytext;}
"=="                    {return EQ;}
"!="                    {return NE;}
"<"                     {return LT;}
">"                     {return GT;}
"<="                    {return LE;}
">="                    {return GE;}
"OR"                    {return OR;}
"AND"                   {return AND;}
"NOT"                   {return NOT;}
"begin"                 {return START;}
"end"                   {return END;}
"read"                  {return READ;}
"write"                 {return WRITE;}
"if"                    {return IF;}
"then"                  {return THEN;}
"else"                  {return ELSE;}
"endif"                 {return ENDIF;}
"while"                 {return WHILE;}
"do"                    {return DO;}
"endwhile"              {return ENDWHILE;}
"break"                 {return BREAK;}
"continue"              {return CONTINUE;}
"main"                  {return MAIN;}
"return"                {return RETURN;}
"decl"                  {return DECL;}
"enddecl"               {return ENDDECL;}
"int"                   {return INT;}
"str"                   {return STR;}
\"(.)*\"                {yylval = CreateNode(STRING,STRTYPE,NULL,NULL); yylval->stringVal = strdup(RemoveQuotes()); return STRING;}
[0-9]+                  {yylval = CreateNode(NUMBER,INTTYPE,NULL,NULL); yylval->intVal = atoi(yytext); return NUMBER;}
[A-Za-z_][A-Za-z0-9_]*  {yylval = CreateNode(ID,0,NULL,NULL); yylval->name = strdup(yytext); return ID;}
[ \t\n]                 {}
(.)                     {printf("Flex Error: Invalid character \"%c\" found\n",*yytext); exit(1);}

%%

char *RemoveQuotes()
{
    yytext[yyleng-1] = '\0';        /* Destroy that last quote like Ben Shapiro destroys liberals */
    return yytext+1;                /* Return array head skipping the first quote */
}
