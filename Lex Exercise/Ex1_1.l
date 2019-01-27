%{
    #include<stdio.h>
    #define NEWLINE 1
    #define WORD 2
    #define CHARACTER 3
%}

%option noyywrap

%%

\n {return NEWLINE;}
[a-zA-Z]+ {return WORD;}
[^a-zA-Z\n] {return CHARACTER;}

%%

int main(int argc,char* argv[])
{
    yyin=fopen(argv[1],"r");
    int countLine=0,charCount=0,wordCount=0;
    int token = yylex();
    if(token) countLine++;
    while(token)
    {
        switch(token)
        {
            case NEWLINE:    countLine++;charCount++;break;
            case WORD:       charCount+=yyleng;wordCount++;break;
            case CHARACTER:  charCount++; 
        }
        token=yylex();
    }
    printf("Words: %d\nCharacters: %d\nLines: %d\n",wordCount,charCount,countLine);
}