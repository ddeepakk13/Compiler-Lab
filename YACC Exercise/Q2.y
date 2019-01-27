%{
    #include<stdio.h>
    int yylex();
    void yyerror(const char *s);
%}

%token ALPHA DIGIT

%%

variable    : ALPHA characters {printf("\nVariable is accepted\n");}
            ;

characters  : 
            | characters DIGIT
            | characters ALPHA
            ;

%%

void yyerror(const char* s)
{
    printf("Invalid variable: %s \n",s);
}

int main()
{
    yyparse();
}