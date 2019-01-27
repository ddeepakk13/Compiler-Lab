%{
    #include<stdio.h>
%}

%option noyywrap

%%

"//"(.)*\n {printf("\nFound:\n%s\n",yytext);}
"/*"(.|\n)*"*/" {printf("\nFound:\n%s\n",yytext);}

%%

int main(int argc,char* argv[])
{
    yyin=fopen(argv[1],"r");
    yylex();
    
}