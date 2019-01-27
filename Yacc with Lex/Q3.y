%{
    #ifndef YYSTYPE
    #define YYSTYPE char*
    #endif
    #include<stdio.h>
    FILE* outfile;
    extern FILE* yyin;
    void yyerror(char *mesg);
    int yylex();
    char result[50];
    char buffer[50];
%}

%token WORD
%left '+' '-'
%left '*' '/'
%start expr

%%

expr : expr '\n'        {}
     | WORD             {$$=$1;}
     | expr '+' expr    { } 
     | expr '-' expr    {fprintf(outfile,"%c ",*$2);}
     | expr '*' expr    {fprintf(outfile,"%c ",*$2);}
     | expr '/' expr    {fprintf(outfile,"%c ",*$2);}
     ;

%%