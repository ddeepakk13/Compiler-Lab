%{
    #ifndef YYSTYPE
    #define YYSTYPE struct tnode*
    #endif
    #include "exptree.h"
    #include "codegen.h"
    #include<stdio.h>
    int yylex();
    void yyerror(char *mesg);
    extern FILE *yyin;
    FILE* fout;
    struct tnode* root;

%}

%token NUM
%left '+' '-'
%left '*' '/'
%start program

%%
program : expr '\n'       {root = $1;}
        ;

expr : NUM
     | '(' expr ')'  {$$ = $2;}
     | '+' expr expr {$$ = makeOperatorNode('+',$2,$3);}
     | '-' expr expr {$$ = makeOperatorNode('-',$2,$3);}
     | '*' expr expr {$$ = makeOperatorNode('*',$2,$3);}
     | '/' expr expr {$$ = makeOperatorNode('/',$2,$3);}
     ;

%%

int main(int argc, char* argv[])
{
    yyin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");
    yyparse();
    initialize(fout);
    set_SP(fout);
    codegen(root,fout);
    storeReg0(fout,'a');
    print_static_var(fout,'a');
    fprintf(fout,"INT 10\n");
}

void yyerror(char* msg)
{
    printf("Bad expression: %s\n",msg);
}