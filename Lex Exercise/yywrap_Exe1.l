%{
	#include<stdio.h>
	#include<stdlib.h>
	char* filename;
	FILE* fptr;
%}

%%

[0-9]+ 	{printf("number:%d\n",atoi(yytext));}

%%

int yywrap()
{
	
	if(fptr==NULL)	
	{
		fptr=fopen(filename,"r");
		yyin=fptr;
		return 0;
	}
	return 1;
}

int main(int argc,char* argv[])
{
	if(argc>1) filename=argv[1];
  	yylex();
  	return 1;
}
