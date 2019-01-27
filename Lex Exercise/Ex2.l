%{
    #include<stdio.h>
    FILE* outFile;
%}

%option noyywrap

digit [0-9]

%%

{digit}+ {fprintf(outFile,"NUM");}
[+\-*/] {fprintf(outFile,"%s",yytext);}
[ \n\t] {fprintf(outFile,"%s",yytext);}

%%

int main(int argc,char* argv[])
{
    yyin=fopen(argv[1],"r");
    outFile=fopen(argv[2],"w");
    yylex();
}