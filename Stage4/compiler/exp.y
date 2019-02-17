
/* <------------------------________________DECLARATIONS__________________-------------------------------> */

%{
    #define YYSTYPE struct tnode*
    #include "tnode.h"
    #include "symbolNode.h"
    #include "codegen.h"
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    void yyerror(char *mesg);
    void Install_variable_list(int dataType, struct tnode* varList);
    extern FILE *yyin;
    FILE* fout;
    struct tnode *root = NULL;
    struct symbolNode *symbolTable = NULL;
%}

/*
 * <--------------------------------------Token Declarations-------------------------------------------->
 *
 * # There are also some tokens declared here for the purpose of building AST
 * # These tokens are not explicitly returned by lex as tokens
 * # They are just identifiers needed for making AST nodes; Then why didn't I define them elsewhere?
 * # BISON declares all the tokens we give it in such a way that they've values that start after 256
 * # Thus, coveniently avoiding clashes with normal ascii characters
 * # It's also plain easy to just let BISON decide the identifier IDs instead of manually doing it
 * # Some identifiers that lex returns as tokens are also used to specify node type in AST
 * # Some identifiers are there for the sole purpose for being used in the dataType field (INTTYPE,STRTYPE,BOOLTYPE)
 *
 * <--------------------------------------------------------------------------------------------------->
*/

%token START END                                                /* begin and end keywords; never use BEGIN as a identifier; it clashes with an identifier used by BISON */
%token NUMBER STRING ID                                         /* for literals and variables */
%token DECL ENDDECL INT STR                                     /* all the declaration block keywords */
%token READ WRITE                                               /* read write keywords */
%token IF THEN ELSE ENDIF WHILE DO ENDWHILE BREAK CONTINUE      /* all the conditional statement keywords */
%token INTTYPE BOOLTYPE STRTYPE                                 /* dataType specifiers; not returned by lex; used for node building */
%token CONNECTOR                                                /* nodeType specifier for chaining statements; not returned by lex */
%nonassoc LT GT LE GE NE EQ                                     /* relational operator keywords */
%left '+' '-'
%left '*' '/' '%'
%start Program

%% /* <-------------------------------------END_OF_DECLARATIONS-----------------------------------------------------------> */
/* <-----------------------------------------------------------------------------------------------------------------------> */



/* <---------------------------------____________GRAMMAR___RULES__________-----------------------------------------------------> */


Program: START DeclBlock StatementList END      {root = $3;}
       ;

StatementList: Statement
             | StatementList Statement          {$$ = CreateTnode(CONNECTOR,0,0,NULL,NULL,$1,$2);}
             ;

Statement: ReadStatement
         | WriteStatement
         | IfStatement
         | WhileStatement
         | AssignStatement
         | BREAK ';'            {$$ = CreateTnode(BREAK,0,0,NULL,NULL,NULL,NULL);}
         | CONTINUE ';'         {$$ = CreateTnode(CONTINUE,0,0,NULL,NULL,NULL,NULL);}
         ;


WhileStatement: WHILE '(' expr ')' DO StatementList ENDWHILE ';'                {$$ = CreateTnode(WHILE,0,0,NULL,NULL,$3,$6);}
              ;

IfStatement: IF '(' expr ')' THEN StatementList ENDIF ';'                       {struct tnode* temp = CreateTnode(CONNECTOR,0,0,NULL,NULL,$6,NULL); $$ = CreateTnode(IF,0,0,NULL,NULL,$3,temp);}
           | IF '(' expr ')' THEN StatementList ELSE StatementList ENDIF ';'    {struct tnode* temp = CreateTnode(CONNECTOR,0,0,NULL,NULL,$6,$8); $$ = CreateTnode(IF,0,0,NULL,NULL,$3,temp);}
           ;

AssignStatement: expr '=' expr ';'            {$1->varNode = Lookup($1->stringVal); $$ = CreateTnode('=',0,0,NULL,NULL,$1,$3);}
               ;

ReadStatement: READ '(' expr ')' ';'        {$$ = CreateTnode(READ,0,0,NULL,NULL,$3,NULL);} 
             ;

WriteStatement: WRITE '(' expr ')' ';'      {$$ = CreateTnode(WRITE,0,0,NULL,NULL,$3,NULL);}
              ;

DeclBlock:
         | DECL DeclList ENDDECL
         ;

DeclList: Declaration
        | DeclList Declaration
        ;

Declaration: Type VariableList ';'          {Install_variable_list($1->dataType,$2);}
           ;

Type: INT                                   {$$ = CreateTnode(0,INTTYPE,0,NULL,NULL,NULL,NULL);}
    | STR                                   {$$ = CreateTnode(0,STRTYPE,0,NULL,NULL,NULL,NULL);}
    ;

VariableList: Variable
            | VariableList ',' Variable     {$$ = CreateTnode(CONNECTOR,0,0,NULL,NULL,$1,$3);}
            ;

Variable: ID                                    {$1->intVal = 1; $$ = $1;}               /* using the intVal field to specify variable size */
        | ID '[' NUMBER ']'                     {
                                                 if($3->intVal <= 0) {printf("ERROR: Invalid array size\n"); exit(1);}
                                                 $1->intVal = $3->intVal; $$ = $1;
                                                }
        | ID '[' NUMBER ']' '[' NUMBER ']'      {
                                                 if($3->intVal <= 0 || $6->intVal <=0) {printf("ERROR: Invalid array size\n"); exit(1);}
                                                 struct tnode *row = malloc(sizeof(struct tnode));
                                                 struct tnode *column = malloc(sizeof(struct tnode));
                                                 row = CreateTnode(NUMBER,0,$3->intVal,NULL,NULL,NULL,NULL);
                                                 column = CreateTnode(NUMBER,0,$6->intVal,NULL,NULL,NULL,NULL);
                                                 $1->intVal = $3->intVal * $6->intVal;
                                                 $1->left = row; $1->right = column; 
                                                 $$ = $1;
                                                }
        ;

expr: NUMBER
    | STRING
    | ID                            {$1->varNode = Lookup($1->stringVal); if($1->varNode == NULL) {printf("Undeclared Variable used\n"); exit(1);} $$ = $1;}
    | ID '[' expr ']'               {$$ = CreateTnode(ID,0,0,$1->stringVal,Lookup($1->stringVal),$3,NULL);}
    | ID '[' expr ']' '[' expr ']'  {$$ = CreateTnode(ID,0,0,$1->stringVal,Lookup($1->stringVal),$3,$6);}
    | '(' expr ')'                  {$$ = $2;}
    | expr '+' expr                 {$$ = CreateTnode('+',INTTYPE,0,NULL,NULL,$1,$3);}
    | expr '-' expr                 {$$ = CreateTnode('-',INTTYPE,0,NULL,NULL,$1,$3);}
    | expr '*' expr                 {$$ = CreateTnode('*',INTTYPE,0,NULL,NULL,$1,$3);}
    | expr '/' expr                 {$$ = CreateTnode('/',INTTYPE,0,NULL,NULL,$1,$3);}
    | expr '%' expr                 {$$ = CreateTnode('%',INTTYPE,0,NULL,NULL,$1,$3);}
    | expr EQ expr                  {$$ = CreateTnode(EQ,BOOLTYPE,0,NULL,NULL,$1,$3);}
    | expr NE expr                  {$$ = CreateTnode(NE,BOOLTYPE,0,NULL,NULL,$1,$3);}
    | expr LT expr                  {$$ = CreateTnode(LT,BOOLTYPE,0,NULL,NULL,$1,$3);}
    | expr GT expr                  {$$ = CreateTnode(GT,BOOLTYPE,0,NULL,NULL,$1,$3);}
    | expr LE expr                  {$$ = CreateTnode(LE,BOOLTYPE,0,NULL,NULL,$1,$3);}
    | expr GE expr                  {$$ = CreateTnode(GE,BOOLTYPE,0,NULL,NULL,$1,$3);}
    ;
    
%%

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./program <inputFile> <outputFile>\n");
        return 0;
    }

    yyin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");
    yyparse();
    Initialize();
    Set_stack();
    if(root != NULL) {printf("Tree is good in BISON\n"); printf("NodeType: %d\n",root->nodeType);}
    else printf("Tree is broken in BISON\n");
    Codegen(root);
    fprintf(fout,"INT 10\n");
}

void Install_variable_list(int dataType, struct tnode* varList)
{
    if(varList->nodeType == CONNECTOR)
    {
        Install_variable_list(dataType, varList->left);
        Install_variable_list(dataType, varList->right);
    }
    else 
    {
        Install(varList->stringVal,dataType,varList->intVal);
        if(varList->left != NULL)
        {
            struct symbolNode *temp = Lookup(varList->stringVal);
            temp->row = varList->left->intVal;
            temp->column = varList->right->intVal;
        }
    }
}

void yyerror(char *mesg)
{
    printf("ERROR: %s detected by BISON\n",mesg);
    exit(1);
}

/*
 * <-----------------IF Node Structure---------------------->
 * 
 *
 *                 (IF)                                                     
 *                 /  \
 *                /    \
 *               /      \
 *            (expr)     \
 *                        \
 *                     (CONNECTOR)
 *                      /       \
 *                     /         \
 *                    /           \
 *        (IF statement list)   (ELSE statement list )
 *                              (NULL if else condition is not present)   
 *
 *
 *
*/