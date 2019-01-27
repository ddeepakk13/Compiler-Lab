%option noyywrap
%{
	#include <stdlib.h>
	#include <stdio.h>
%}
	
number [0-9]+
 
%%
 
{number}*[02468] {printf("Even : %d\n",atoi(yytext));}
{number}*[13579] {printf("Odd : %d\n",atoi(yytext));}
 
%%
 
int main()
{
	yylex();
	return 1;
}
