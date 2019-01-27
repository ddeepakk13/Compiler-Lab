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
	
	if(fptr!=NULL)	
	{
		fptr=NULL;
		yyin=stdin;
		return 0;
	}
	return 1;
}

int main(int argc,char* argv[])
{
	if(argc>1) filename=argv[1];
	fptr=fopen(filename,"r");
	yyin=fptr;
  	yylex();
  	return 1;
}
