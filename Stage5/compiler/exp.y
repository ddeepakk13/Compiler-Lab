
/* <------------------------________________DECLARATIONS__________________-------------------------------> */

%{
    #define YYSTYPE struct ASTnode*
    #include "ASTnode.h"
    #include "Gsymbol.h"
    #include "Lsymbol.h"
    #include "ParamStruct.h"
    #include "Codegen.h"
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    void yyerror(char *mesg);
    extern FILE *yyin;
    FILE* fout;
    struct Gsymbol *GsymbolTable = NULL;
    struct Lsymbol *LsymbolTable = NULL;
    struct ParamStruct *paramHead = NULL;
    int currentType;                        // for making symbol table and parameter entries  
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

GDecl: Type GIdList ';'
     ;

Type: INT   {currentType = INTTYPE;}
    | STR   {currentType = STRTYPE;}
    ;

GIdList: GId
       | GIdList ',' GId
       ;

GId: ID                     {GInstall($1->name,currentType,1);}
   | ID '[' NUMBER ']'      {GInstall($1->name,currentType,$3->intVal);}
   | ID '(' ParamList ')'   {struct Gsymbol *temp = GInstall($1->name,currentType,0);
                             temp->paramList = paramHead;
                             paramHead = NULL;}
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

FDef: Type ID '(' ParamList ')'             {struct Gsymbol *tfunc = GLookup($2->name);
                                             if(tfunc == NULL) {printf("ERROR: '%s' function is not declared\n",$2->name); exit(1);}
                                             if(currentType != tfunc->type) {printf("ERROR: Return type mismatch in '%s' function\n",tfunc->name); exit(1);}
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
    ;

/*<-------------------------------------------------->*/

MainBlock: INT MAIN '(' ')' {printf("<-------------MAIN------------->\n");} '{' LDeclBlock Body '}'
         ;

StatementList: Statement
             | StatementList Statement          
             ;

Statement: ReadStatement
         | WriteStatement
         | IfStatement
         | WhileStatement
         | AssignStatement
         | ReturnStatement
         | BREAK ';'            
         | CONTINUE ';'         
         ;


WhileStatement: WHILE '(' expr ')' DO StatementList ENDWHILE ';'                
              ;

IfStatement: IF '(' expr ')' THEN StatementList ENDIF ';'                       
           | IF '(' expr ')' THEN StatementList ELSE StatementList ENDIF ';'    
           ;

AssignStatement: expr '=' expr ';'            
               ;

ReadStatement: READ '(' expr ')' ';'        
             ;

WriteStatement: WRITE '(' expr ')' ';'      
              ;

ReturnStatement: RETURN expr ';'
               ;


expr: NUMBER
    | STRING
    | ID                           
    | ID '[' expr ']'               
    | ID '(' ArgList ')'
    | '(' expr ')'                  
    | expr '+' expr                 
    | expr '-' expr                 
    | expr '*' expr                 
    | expr '/' expr                 
    | expr '%' expr                 
    | expr EQ expr                  
    | expr NE expr                  
    | expr LT expr                  
    | expr GT expr                  
    | expr LE expr                  
    | expr GE expr                  
    | expr AND expr
    | expr OR expr 
    ;

ArgList: expr
       | ArgList ',' expr
       ;
    
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