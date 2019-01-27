%{
	#include<stdio.h>
	#include<stdlib.h>
	int flag=0;
%}

%%

[0-9]+ 	{printf("number:%d\n",atoi(yytext));}

%%

int yywrap()
{
	if(flag==0){flag=1;return 0;}
	return 1;
}

int main(int argc,char* argv[])
{
  	yylex();
  	return 1;
}
