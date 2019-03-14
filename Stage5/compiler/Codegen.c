#include "Codegen.h"
#include "ASTnode.h"
#include "Gsymbol.h"
#include "Lsymbol.h"
#include "ASTLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include "exp.tab.h"
#include "stack.h"

int GetReg();
void FreeReg();
int GetLabel();
int Get_Sizeof_Global_Variables();
int Get_Local_Variable_Count();
int Get_Variable_Binding_in_Register(struct ASTnode *node);
int Get_Variable_Value_in_Register(struct ASTnode *node);
int Evaluate_Function(struct ASTnode *node);
void Push_Registers_in_Use(int regCount);
void Pop_Registers_in_Use(int regCount);
void Read_to_address_in_reg(int reg);
void Print_value_in_reg(int reg);


extern FILE *fout;
extern struct Gsymbol *GsymbolTable;
extern struct Lsymbol *LsymbolTable;
static int nextReg = 0;
static int nextLabel = 0;
static struct stack *loop_entry_stack = NULL;
static struct stack *loop_exit_stack = NULL;

void Initialize()
{
    int sizeof_global_variables = Get_Sizeof_Global_Variables();
    int stack_init_address = sizeof_global_variables + 4095;
    fprintf(fout,"0\n2056\n0\n0\n0\n0\n0\n0\n");
    fprintf(fout,"MOV SP, %d\n",stack_init_address);
    fprintf(fout,"MOV BP, %d\n",stack_init_address);
    fprintf(fout,"PUSH R0\n");
    fprintf(fout,"CALL MAIN\n");
    fprintf(fout,"INT 10\n");
}

void Generate_Function_Code(struct ASTnode *node)
{
    fprintf(fout,"PUSH BP\n");
    fprintf(fout,"MOV BP, SP\n");
    int local_variable_count = Get_Local_Variable_Count();
    fprintf(fout,"ADD SP, %d\n",local_variable_count);
    Codegen(node);
}

int Codegen(struct ASTnode *node)
{
    if(node == NULL)
        printf("Tree is broken in Codegen\n");

    if(node->nodeType == CONNECTOR)
    {
        printf("Entered CONNECTOR\n");
        Codegen(node->left);
        Codegen(node->right);
        return 0;
    }

    else if(node->nodeType == NUMBER)
    {
        printf("Entered NUMBER\n");
        int reg = GetReg();
        fprintf(fout,"MOV R%d, %d\n",reg,node->intVal);
        return reg;
    }

    else if(node->nodeType == STRING)
    {
        printf("Entered STRING\n");
        int reg = GetReg();
        fprintf(fout,"MOV R%d, \"%s\"\n",reg,node->stringVal);
        return reg;
    }

    else if(node->nodeType == RETURN)
    {
        printf("Entered RETURN\n");
        int reg = Codegen(node->left);
        int treg = GetReg();
        fprintf(fout,"MOV R%d, BP\n",treg);
        fprintf(fout,"SUB R%d, 2\n",treg);
        fprintf(fout,"MOV [R%d], R%d\n",treg,reg);
        FreeReg();
        FreeReg();
        int local_variable_count = Get_Local_Variable_Count();
        fprintf(fout,"SUB SP, %d\n",local_variable_count);
        fprintf(fout,"POP BP\n");
        fprintf(fout,"RET\n");
    }

    else if(node->nodeType == ID)
    {
        printf("Entered ID\n");
        if(node->Lentry != NULL)
        {
            printf("ID '%s' is a local Variable\n",node->name);
            int reg = Get_Variable_Value_in_Register(node);
            return reg;
        }
        else if(node->Gentry != NULL)
        {
            if(node->Gentry->designation == VARIABLE || node->Gentry->designation == ARRAY)
            {
                printf("ID '%s' is global Variable\n",node->name);
                int reg = Get_Variable_Value_in_Register(node);
                return reg;
            }
            else if(node->Gentry->designation == FUNCTION)
            {
                printf("ID '%s' is function\n",node->name);
                int reg = Evaluate_Function(node);
                return reg;
            }
        }
    }

    else if(node->nodeType == READ)
    {
        printf("Entered READ\n");
        int reg = Get_Variable_Binding_in_Register(node->left);
        Read_to_address_in_reg(reg);
        FreeReg();
    }

    else if(node->nodeType == WRITE)
    {
        printf("Entered WRITE\n");
        int reg = Codegen(node->left);
        Print_value_in_reg(reg);
        FreeReg();
    }

    else if(node->nodeType == '=')
    {
        printf("Entered =\n");
        int rightReg = Codegen(node->right);
        int leftReg = Get_Variable_Binding_in_Register(node->left);
        fprintf(fout,"MOV [R%d], R%d\n",leftReg,rightReg);
        FreeReg();
        FreeReg();
    }

    else if(node->nodeType == IF)
    {
        printf("Entered IF\n");
        int label_1 = GetLabel();
        int reg = Codegen(node->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,label_1);
        FreeReg();
        Codegen(node->right->left);
        if(node->right->right == NULL)   fprintf(fout,"L%d: ",label_1);
        else
        {
            int label_2 = GetLabel();
            fprintf(fout,"JMP L%d\n",label_2);
            fprintf(fout,"L%d: ",label_1);
            Codegen(node->right->right);
            fprintf(fout,"L%d: ",label_2);
        }
    }

    else if(node->nodeType == WHILE)
    {
        printf("Entered WHILE\n");
        int loopEntry = GetLabel();
        int loopExit = GetLabel();
        loop_entry_stack = Push_to_stack(loop_entry_stack,loopEntry);
        loop_exit_stack = Push_to_stack(loop_exit_stack,loopExit);
        fprintf(fout,"L%d: ",loopEntry);
        int reg = Codegen(node->left);
        fprintf(fout,"JZ R%d, L%d\n",reg,loopExit);
        FreeReg();
        Codegen(node->right);
        fprintf(fout,"JMP L%d\n",loopEntry);
        fprintf(fout,"L%d: ",loopExit);
        loop_entry_stack = Pop_from_stack(loop_entry_stack);
        loop_exit_stack = Pop_from_stack(loop_exit_stack);
    }

    else if(node->nodeType == BREAK)
    {
        printf("Entered BREAK\n");
        if(loop_exit_stack != NULL)
        {
            int exitLabel = Peek(loop_exit_stack);
            fprintf(fout,"JMP L%d\n",exitLabel);
        }
    }

    else if(node->nodeType == CONTINUE)
    {
        printf("Entered CONTINUE\n");
        if(loop_entry_stack != NULL)
        {
            int entryLabel = Peek(loop_entry_stack);
            fprintf(fout,"JMP L%d\n",entryLabel);
        }
    }

    else if(node->nodeType == NOT)
    {
        int reg = Codegen(node->left);
        int label1 = GetLabel();
        int label2 = GetLabel();
        fprintf(fout,"JZ R%d, L%d\n",reg,label1);
        fprintf(fout,"MOV R%d, 0\n",reg);
        fprintf(fout,"JMP L%d\n",label2);
        fprintf(fout,"L%d: MOV R%d, 1\n",label1,reg);
        fprintf(fout,"L%d: ",label2);
        return reg;
    }

    else
    {
        printf("Entered operator section\n");
        int leftReg = Codegen(node->left);
        int rightReg = Codegen(node->right);
        switch(node->nodeType)
        {
            case '+' : fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); break;
            case '-' : fprintf(fout,"SUB R%d, R%d\n",leftReg,rightReg); break;
            case '*' : fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); break;
            case '/' : fprintf(fout,"DIV R%d, R%d\n",leftReg,rightReg); break;
            case '%' : fprintf(fout,"MOD R%d, R%d\n",leftReg,rightReg); break;
            case GT : fprintf(fout,"GT R%d, R%d\n",leftReg,rightReg); break;
            case LT : fprintf(fout,"LT R%d, R%d\n",leftReg,rightReg); break;
            case EQ : fprintf(fout,"EQ R%d, R%d\n",leftReg,rightReg); break;
            case NE : fprintf(fout,"NE R%d, R%d\n",leftReg,rightReg); break;
            case GE : fprintf(fout,"GE R%d, R%d\n",leftReg,rightReg); break;
            case LE : fprintf(fout,"LE R%d, R%d\n",leftReg,rightReg); break;
            case AND: fprintf(fout,"MUL R%d, R%d\n",leftReg,rightReg); break;
            case OR:  fprintf(fout,"ADD R%d, R%d\n",leftReg,rightReg); break;
        }
        FreeReg();
        return leftReg;
    }

    return 0;
}

int Get_Sizeof_Global_Variables()
{
    struct Gsymbol *iterator = GsymbolTable;
    int Gsize = 0;
    while(iterator != NULL)
    {
        if(iterator->size > 0)
            Gsize += iterator->size;
        iterator = iterator->next;
    }
    printf("Gsize is %d\n",Gsize);
    return Gsize;
}

int Get_Local_Variable_Count()
{
    struct Lsymbol *iterator = LsymbolTable;
    int Lcount = 0;
    while(iterator != NULL)
    {
        Lcount++;
        iterator = iterator->next;
    }
    return Lcount;
}

int Get_Variable_Binding_in_Register(struct ASTnode *node)
{
    if(node->Lentry != NULL)
    {
        int binding = node->Lentry->binding;
        int reg = GetReg();
        fprintf(fout,"MOV R%d, BP\n",reg);
        fprintf(fout,"ADD R%d, %d\n",reg,binding);
        return reg;
    }
    else if(node->Gentry != NULL)
    {
        int binding = node->Gentry->binding;
        int reg = GetReg();
        fprintf(fout,"MOV R%d, %d\n",reg,binding);
        if(node->left != NULL)
        {
            int reg1 = Codegen(node->left);
            fprintf(fout,"ADD R%d, R%d\n",reg,reg1);
            FreeReg();
        }
        return reg;
    }
}

int Get_Variable_Value_in_Register(struct ASTnode *node)
{
    int reg = Get_Variable_Binding_in_Register(node);
    fprintf(fout,"MOV R%d, [R%d]\n",reg,reg);
    return reg;
}

void Push_Registers_in_Use(int regCount)
{
    for(int i = 0; i < regCount; i++)
        fprintf(fout,"PUSH R%d\n",i);
}

void Pop_Registers_in_Use(int regCount)
{
    for(int i = regCount-1; i >= 0; i--)
        fprintf(fout,"POP R%d\n",i);
}

int Evaluate_Function(struct ASTnode *node)
{
    int current_next_reg = nextReg;
    Push_Registers_in_Use(current_next_reg);
    nextReg = 0;
    struct ASTLinkedList *iterator = node->argList;
    while(iterator != NULL)                                  // Push arguments
    {
        int reg = Codegen(iterator->node);
        fprintf(fout,"PUSH R%d\n",reg);
        FreeReg();
        iterator = iterator->next;
    }
    fprintf(fout,"PUSH R0\n");                               // Return value
    fprintf(fout,"CALL F%d\n",node->Gentry->flabel);         // Call function
    fprintf(fout,"POP R%d\n",current_next_reg);              // Return Value
    nextReg = current_next_reg + 1;
    iterator = node->argList;
    while(iterator != NULL)                                  // Pop arguments
    {
        int treg = GetReg();
        fprintf(fout,"POP R%d\n",treg);
        FreeReg();
        iterator = iterator->next;
    }
    Pop_Registers_in_Use(current_next_reg);
    return current_next_reg;
}

void Read_to_address_in_reg(int reg)
{
    int bufReg = GetReg();

    fprintf(fout,"MOV R%d, \"Read\"\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"MOV R%d, -1\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",reg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);

    FreeReg();
}

void Print_value_in_reg(int reg)
{
    int bufReg = GetReg();

    fprintf(fout,"MOV R%d, \"Write\"\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"MOV R%d,-2\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",reg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"PUSH R%d\n",bufReg);
    fprintf(fout,"CALL 0\n");
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);
    fprintf(fout,"POP R%d\n",bufReg);

    FreeReg();
}

int GetReg()
{
    if(nextReg==20) {printf("Error: Register overflow\n");exit(1);}
    return nextReg++;
}

void FreeReg()
{
    nextReg--;
}

int GetLabel()
{
    return nextLabel++;
}