%{
    #ifndef YYSTYPE
    #define YYSTYPE struct tnode*
    #endif
    #include "nodeStructure.h"
    #include "codegen.h"
    #include<stdio.h>
    int yylex();
    void yyerror(char *mesg);
    extern FILE *yyin;
    FILE* fout;
    struct tnode* headNode;

%}

%token VAR NUM READ WRITE START END CONNECTOR
%left '+' '-'
%left '*' '/'
%start program

%%

program: START statementList END {headNode = $2;}
       | START END
       ;

statementList: statement
             | statementList statement {$$ = createNode(CONNECTOR,0,0,NULL,$1,$2);}
             ;

statement: READ '(' VAR ')' ';'   {$$ = createNode(READ,0,0,NULL,$3,NULL);}
         | WRITE '(' expr ')' ';' {$$ = createNode(WRITE,0,0,NULL,$3,NULL);}
         | VAR '=' expr ';'       {$$ = createNode('=',0,0,NULL,$1,$3);}
         ;

expr: NUM
    | VAR
    | '(' expr ')'  {$$ = $2;}
    | expr '+' expr {$$ = createNode('+',0,0,NULL,$1,$3);}
    | expr '-' expr {$$ = createNode('-',0,0,NULL,$1,$3);}
    | expr '*' expr {$$ = createNode('*',0,0,NULL,$1,$3);}
    | expr '/' expr {$$ = createNode('/',0,0,NULL,$1,$3);}
    ;

%%

int main(int argc, char* argv[])
{
    yyin = fopen(argv[1],"r");
    yyparse();
    evaluate(headNode);
    
}

void yyerror(char* msg)
{
    printf("Bad expression: %s\n",msg);
}