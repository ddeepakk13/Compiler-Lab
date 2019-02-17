
/* <------------------------________________DECLARATIONS__________________-------------------------------> */

%{
    #define YYSTYPE struct tnode*
    #include "tnode.h"
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

[-+*/%();=[\],]           {return *yytext;}
"=="                    {return EQ;}
"!="                    {return NE;}
"<"                     {return LT;}
">"                     {return GT;}
"<="                    {return LE;}
">="                    {return GE;}
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
"decl"                  {return DECL;}
"enddecl"               {return ENDDECL;}
"int"                   {return INT;}
"str"                   {return STR;}
\"(.)*\"                {yylval = CreateTnode(STRING,STRTYPE,0,strdup(RemoveQuotes()),NULL,NULL,NULL); return STRING;}
[0-9]+                {yylval = CreateTnode(NUMBER,INTTYPE,atoi(yytext),NULL,NULL,NULL,NULL); return NUMBER;}
[A-Za-z_][A-Za-z0-9_]*  {yylval = CreateTnode(ID,0,0,strdup(yytext),NULL,NULL,NULL); return ID;}            /* Note that the stringVal field is used to store the ID name here; not good practice but I just want to make this work; hope the programming gods will forgive me */
[ \t\n]                 {}
(.)                     {printf("Flex Error: Invalid character \"%c\" found\n",*yytext); exit(1);}


%%

char *RemoveQuotes()
{
    yytext[yyleng-1] = '\0';        /* Destroy that last quote like Ben Shapiro destroys liberals */
    return yytext+1;                /* Return array head skipping the first quote */
}
