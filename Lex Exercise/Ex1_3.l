%{
    #include<stdio.h>
%}

%option noyywrap

word [a-zA-Z]

%%

[^A-Za-z]A({word}{2})[ \n\t] {printf("\n\nFound:%s\n",yytext);}

%%

int main(int argc,char* argv[])
{
    yyin=fopen(argv[1],"r");
    yylex();
    
}