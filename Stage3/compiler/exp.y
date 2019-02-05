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
    struct tnode* root;

%}

%token VAR NUM READ WRITE START END CONNECTOR IF THEN ELSE ENDIF WHILE DO ENDWHILE INTTYPE BOOLTYPE BREAK CONTINUE
%nonassoc LT GT LE GE NE EQ
%left '+' '-'
%left '*' '/'
%start program

%%

program: START statementList END {root = $2;}
       | START END
       ;

statementList: statement
             | statementList statement {$$ = createNode(CONNECTOR,0,0,NULL,$1,$2);}
             ;

statement: READ '(' VAR ')' ';'   {$$ = createNode(READ,0,0,NULL,$3,NULL);}
         | WRITE '(' expr ')' ';' {$$ = createNode(WRITE,0,0,NULL,$3,NULL);}
         | VAR '=' expr ';'       {$$ = createNode('=',0,0,NULL,$1,$3);}
         | whileStatement
         | ifStatement
         | BREAK ';'              {$$ = createNode(BREAK,0,0,NULL,NULL,NULL);}
         | CONTINUE ';'           {$$ = createNode(CONTINUE,0,0,NULL,NULL,NULL);}  
         ;

whileStatement: WHILE '(' expr ')' DO statementList ENDWHILE ';' {$$ = createNode(WHILE,0,0,NULL,$3,$6);}
              ;

ifStatement: IF '(' expr ')' THEN statementList ELSE statementList ENDIF ';' {struct tnode* temp = createNode(CONNECTOR,0,0,NULL,$6,$8);
                                                                              $$ = createNode(IF,0,0,NULL,$3,temp);}
           | IF '(' expr ')' THEN statementList ENDIF ';' {struct tnode* temp = createNode(CONNECTOR,0,0,NULL,$6,NULL);
                                                           $$ = createNode(IF,0,0,NULL,$3,temp);}
           ;

expr: NUM
    | VAR
    | '(' expr ')'  {$$ = $2;}
    | expr '+' expr {$$ = createNode('+',INTTYPE,0,NULL,$1,$3);}
    | expr '-' expr {$$ = createNode('-',INTTYPE,0,NULL,$1,$3);}
    | expr '*' expr {$$ = createNode('*',INTTYPE,0,NULL,$1,$3);}
    | expr '/' expr {$$ = createNode('/',INTTYPE,0,NULL,$1,$3);}
    | expr LT expr  {$$ = createNode(LT,BOOLTYPE,0,NULL,$1,$3);}
    | expr GT expr  {$$ = createNode(GT,BOOLTYPE,0,NULL,$1,$3);}
    | expr LE expr  {$$ = createNode(LE,BOOLTYPE,0,NULL,$1,$3);}
    | expr GE expr  {$$ = createNode(GE,BOOLTYPE,0,NULL,$1,$3);}
    | expr NE expr  {$$ = createNode(NE,BOOLTYPE,0,NULL,$1,$3);}
    | expr EQ expr  {$$ = createNode(EQ,BOOLTYPE,0,NULL,$1,$3);}
    ;

%%

int main(int argc, char* argv[])
{
    yyin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");
    yyparse();
    initialize();
    set_static_stack();
    codegen(root);
    fprintf(fout,"INT 10\n");
}

void yyerror(char* msg)
{
    printf("Bad expression: %s\n",msg);
}