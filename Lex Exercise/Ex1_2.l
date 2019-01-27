%{
    #include<stdio.h>
    #define INTEGER 1
    #define FLOAT 2
%}

%option noyywrap

number [0-9]+

%%

{number}"."{number}[ \n\t] {return FLOAT;}
{number}[ \n\t] {return INTEGER;}

%%

int main(int argc,char* argv[])
{
    int intCount=0,floatCount=0;
    yyin=fopen(argv[1],"r");
    int token = yylex();
    while(token)
    {
        switch(token)
        {
            case INTEGER:    intCount++;break;
            case FLOAT:      floatCount++;
        }
        token=yylex();
    }
    printf("\nIntegers: %d\nFloats: %d\n",intCount,floatCount);
}