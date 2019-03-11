
/* <------------------------________________DECLARATIONS__________________-------------------------------> */

%{
    #define YYSTYPE struct ASTnode*
    #include "ASTnode.h"
    #include "Gsymbol.h"
    #include "Lsymbol.h"
    #include "ParamStruct.h"
    #include "Codegen.h"
    #include "ASTLinkedList.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex();
    void yyerror(char *mesg);
    extern FILE *yyin;
    FILE* fout;
    struct Gsymbol *GsymbolTable = NULL;
    struct Lsymbol *LsymbolTable = NULL;
    struct ParamStruct *paramHead = NULL;                   // head of parameter list; definition time
    struct ASTLinkedList *argHead = NULL;                   // head of argument list; usage time
    int currentType;                                        // for making symbol table and parameter entries  
    void Pre_Typecheck_Array_Index(struct ASTnode *node);         // checks whether array index is of int type
    void Pre_Typecheck_Function(struct ASTnode *node);      // compares argument types
    void Confirm_ID_Exists(struct ASTnode *node);           // checks whether the said ID exists in symbol list
    void Confirm_Variable(struct ASTnode *node);
    void Confirm_Array(struct ASTnode *node);
    void Confirm_Function(struct ASTnode *node);
    int Get_Designation(char *IDname);
    int decType;                                            // tracks the declaration type(/return type)
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
%token NUMBER STRING ID                                         /* for literals and variables and functions */
%token DECL ENDDECL INT STR                                     /* all the declaration block keywords */
%token READ WRITE                                               /* read write keywords */
%token IF THEN ELSE ENDIF WHILE DO ENDWHILE BREAK CONTINUE      /* all the conditional statement keywords */
%token MAIN RETURN
%token INTTYPE BOOLTYPE STRTYPE                                 /* dataType specifiers; not returned by lex; used for node building */
%token VARIABLE ARRAY FUNCTION
%token CONNECTOR                                                /* nodeType specifier for chaining statements; not returned by lex */
%left AND OR                                                    /* logical operators */
%nonassoc LT GT LE GE NE EQ                                     /* relational operator keywords */
%left '+' '-'
%left '*' '/' '%'
%start Program

%% /* <-------------------------------------END_OF_DECLARATIONS-----------------------------------------------------------> */
/* <-----------------------------------------------------------------------------------------------------------------------> */



/* <---------------------------------____________GRAMMAR___RULES__________-----------------------------------------------------> */


Program: GDeclBlock FDefBlock MainBlock
       | GDeclBlock MainBlock
       | MainBlock
       ;

/*<------------------------------------------------------->*/

GDeclBlock: DECL ENDDECL
          | DECL GDeclList ENDDECL  {Print_GsymbolTable();}
          ;

GDeclList: GDecl
         | GDeclList GDecl
         ;

GDecl: Type {decType = currentType;} GIdList ';'
     ;

Type: INT   {currentType = INTTYPE;}
    | STR   {currentType = STRTYPE;}
    ;

GIdList: GId
       | GIdList ',' GId
       ;

GId: ID                     {struct Gsymbol *temp = GInstall($1->name,decType,1);
                             temp->designation = VARIABLE;}
   | ID '[' NUMBER ']'      {int size = $3->intVal;
                             if(size<=0){printf("ERROR: Array '%s' should be initialised with valid size\n",$1->name); exit(1);}
                             struct Gsymbol *temp = GInstall($1->name,decType,size);
                             temp->designation = ARRAY;}
   | ID '(' ParamList ')'   {struct Gsymbol *temp = GInstall($1->name,decType,-1);
                             temp->paramList = paramHead;
                             paramHead = NULL;
                             temp->designation = FUNCTION;}
   ;

ParamList:
         | Param
         | ParamList ',' Param
         ;

Param: Type ID              {InstallParam($2->name,currentType);}
     ;

/*<------------------------------------------------------>*/

FDefBlock: FDef
         | FDefBlock FDef
         ;

FDef:         Type ID                       {decType = currentType;}
             '(' ParamList ')'              {struct Gsymbol *tfunc = GLookup($2->name);
                                             if(tfunc == NULL) {printf("ERROR: '%s' function is not declared\n",$2->name); exit(1);}
                                             if(tfunc->type != decType){printf("ERROR: Return type mismatch in '%s' function\n",tfunc->name); exit(1);}
                                             Check_Param_Equality(paramHead,tfunc->paramList);
                                             LParam_Install();
                                             paramHead = NULL;
                                             printf("<------------%s------------->\n",$2->name);}
            '{' LDeclBlock Body '}'
    ;

LDeclBlock:
          | DECL ENDDECL
          | DECL LDeclList ENDDECL
          ;

LDeclList: LDecl
         | LDeclList LDecl
         ;

LDecl: Type LIdList ';'
     ;

LIdList: ID                                 {LInstall($1->name,currentType);}
       | LIdList ',' ID                     {LInstall($3->name,currentType);}
       ;

Body: START StatementList ReturnStatement END   {Print_LsymbolTable();
                                                 Codegen($2);
                                                 Codegen($3);
                                                 LsymbolTable = NULL;}
    | START ReturnStatement END                 {Print_LsymbolTable();
                                                 Codegen($2);
                                                 LsymbolTable = NULL;}
    ;

/*<-------------------------------------------------->*/

MainBlock: INT MAIN '(' ')' {printf("<-------------MAIN------------->\n"); decType = INTTYPE;} '{' LDeclBlock Body '}'
         ;

StatementList: Statement
             | StatementList Statement          {{$$ = CreateNode(CONNECTOR,0,$1,$2);}}
             ;

Statement: ReadStatement
         | WriteStatement
         | IfStatement
         | WhileStatement
         | AssignStatement
         | ReturnStatement
         | BREAK ';'            {$$ = CreateNode(BREAK,0,NULL,NULL);}
         | CONTINUE ';'         {$$ = CreateNode(CONTINUE,0,NULL,NULL);}
         ;


WhileStatement: WHILE '(' expr ')' DO StatementList ENDWHILE ';'                {$$ = CreateNode(WHILE,0,$3,$6);}
              ;

IfStatement: IF '(' expr ')' THEN StatementList ENDIF ';'                       {struct ASTnode *temp = CreateNode(CONNECTOR,0,$6,NULL);
                                                                                 $$ = CreateNode(IF,0,$3,temp);}
           | IF '(' expr ')' THEN StatementList ELSE StatementList ENDIF ';'    {struct ASTnode *temp = CreateNode(CONNECTOR,0,$6,$8);
                                                                                 $$ = CreateNode(IF,0,$3,temp);}
           ;

AssignStatement: Variable '=' expr ';'              {$$ = CreateNode('=',0,$1,$2);}
               ;

ReadStatement: READ '(' Variable ')' ';'        {$$ = CreateNode(READ,0,$3,NULL);}
             ;

WriteStatement: WRITE '(' expr ')' ';'          {$$ = CreateNode(WRITE,0,$3,NULL);}
              ;

ReturnStatement: RETURN expr ';'                {$$ = CreateNode(RETURN,0,$2,NULL);}
               ;

Variable: ID                       {$1->Gentry = GLookup($1->name);
                                    $1->Lentry = LLookup($1->name);
                                    Confirm_ID_Exists($1);
                                    Confirm_Variable($1);
                                    $$ = $1;}
        | ID '[' expr ']'          {$1->Gentry = GLookup($1->name);    
                                    $1->Lentry = LLookup($1->name);
                                    Confirm_ID_Exists($1);
                                    Confirm_Array($1);
                                    $1->left = $3;
                                    Pre_Typecheck_Array_Index($3);
                                    $$ = $1;}
        ;

expr: NUMBER
    | STRING
    | Variable
    | ID '(' ArgList ')'            {$1->Gentry = GLookup($1->name);
                                     $1->Lentry = LLookup($1->name);
                                     Confirm_ID_Exists($1);
                                     Confirm_Function($1);
                                     $1->argList = argHead;
                                     Pre_Typecheck_Function($1);
                                     argHead = NULL;
                                     $$ = $1;}
    | '(' expr ')'                  {$$ = $2;}
    | expr '+' expr                 {$$ = CreateNode('+',INTTYPE,$1,$3);}
    | expr '-' expr                 {$$ = CreateNode('-',INTTYPE,$1,$3);}
    | expr '*' expr                 {$$ = CreateNode('*',INTTYPE,$1,$3);}
    | expr '/' expr                 {$$ = CreateNode('/',INTTYPE,$1,$3);}
    | expr '%' expr                 {$$ = CreateNode('%',INTTYPE,$1,$3);}
    | expr EQ expr                  {$$ = CreateNode(EQ,BOOLTYPE,$1,$3);}
    | expr NE expr                  {$$ = CreateNode(NE,BOOLTYPE,$1,$3);}
    | expr LT expr                  {$$ = CreateNode(LT,BOOLTYPE,$1,$3);}
    | expr GT expr                  {$$ = CreateNode(GT,BOOLTYPE,$1,$3);}
    | expr LE expr                  {$$ = CreateNode(LE,BOOLTYPE,$1,$3);}
    | expr GE expr                  {$$ = CreateNode(GE,BOOLTYPE,$1,$3);}
    | expr AND expr                 {$$ = CreateNode(AND,BOOLTYPE,$1,$3);}
    | expr OR expr                  {$$ = CreateNode(OR,BOOLTYPE,$1,$3);}
    ;

ArgList: 
       | expr               {InstallArgument($1);}
       | ArgList ',' expr   {InstallArgument($3);}
       ;

/*<---------------------------------------------[[[END OF RULES]]]--------------------------------------------------------------------->*/

%%

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./expCompiler <inputFile> <outputFile>\n");
        return 0;
    }

    yyin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");
    yyparse();
}

void yyerror(char *mesg)
{
    printf("ERROR: %s detected by BISON\n",mesg);
    exit(1);
}

void Confirm_ID_Exists(struct ASTnode *node)
{
    if(node->Lentry == NULL)
        if(node->Gentry == NULL)
        {
            printf("ERROR: '%s' ID does not exist\n",node->name);
            exit(1);
        }
}

void Pre_Typecheck_Array_Index(struct ASTnode *node)
{
    int dataType = Get_Data_Type(node);
    if(dataType != INTTYPE)
    {
        printf("ERROR: Index of array '%s' should be int type\n",node->name);
        exit(1);
    }
}

void Pre_Typecheck_Function(struct ASTnode *node)
{
    struct ParamStruct *paramList = node->Gentry->paramList;
    struct ASTLinkedList *argList = Get_ArgumentList_Tail();

    if(paramList == NULL && argList == NULL)    return;

    while(paramList != NULL && argList != NULL)
    {
        if(paramList->type == Get_Data_Type(argList->node))
        {
            paramList = paramList->next;
            argList = argList->previous;
            continue;
        }
        printf("ERROR: Parameter mismatch in '%s' function usage\n",node->name);
        exit(1);
    }
    if(!(paramList == NULL && argList == NULL))
    {
        printf("ERROR: Parameter mismatch in '%s' function usage\n",node->name);
        exit(1);
    }
}

void Confirm_Variable(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != VARIABLE)
    {
        printf("ERROR: ID '%s' cannot be used as like a variable\n",node->name);
        exit(1);
    }  
}

void Confirm_Array(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != ARRAY)
    {
        printf("ERROR: ID '%s' cannot be used as like a ARRAY\n",node->name);
        exit(1);
    }
}

void Confirm_Function(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != FUNCTION)
    {
        printf("ERROR: ID '%s' cannot be used as like a function\n",node->name);
        exit(1);
    }
}

int Get_Designation(char *IDname)
{
    struct Lsymbol *Literator = LsymbolTable;
    while(Literator != NULL)
    {
        if(!(strcmp(IDname,Literator->name)))
        {
            return VARIABLE;
        }  
        Literator =  Literator->next;
    }

    struct Gsymbol *iterator = GsymbolTable;
    while(iterator != NULL)
    {
        if(!(strcmp(IDname,iterator->name)))
        {
            return iterator->designation;
        }
        iterator = iterator->next;
    }
    return 0;
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