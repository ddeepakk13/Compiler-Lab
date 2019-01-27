%{
    #ifndef YYSTYPE
    #define YYSTYPE char
    #endif
    #include<stdio.h>
    FILE* outfile;
    extern FILE* yyin;
    void yyerror(char *mesg);
    int yylex();
%}

%token CHARACTER
%left '+' '-'
%left '*' '/'
%start expr

%%


expr : CHARACTER        {fprintf(outfile,"%c",$1);}
     | expr '+' expr    {fprintf(outfile,"%c",$2);}
     | expr '-' expr    {fprintf(outfile,"%c",$2);}
     | expr '*' expr    {fprintf(outfile,"%c",$2);}
     | expr '/' expr    {fprintf(outfile,"%c",$2);}
     ;

%%

int main(int argc, char* argv[])
{
    yyin = fopen(argv[1],"r");
    outfile = fopen(argv[2],"w");
    yyparse();
}

void yyerror(char* msg)
{
    printf("Bad expression: %s\n",msg);
}
