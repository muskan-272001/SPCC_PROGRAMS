%option noyywrap
%{
#include<stdio.h>
#include<stdlib.h>
%}
digit [0-9]
alphabet [_a-zA-Z]+
%%
#include<{alphabet}.h> {printf("header file: %s\n", yytext);}
int|float|char|void|double {printf("Datatypes: %s\n",yytext);}
{digit}+ {printf("Numbers: %s\n",yytext);}
"["|"]"|"{"|"}"|"("|")" {printf("Brackets: %s\n",yytext);}
"=" {printf("Assignment: %s\n",yytext);}
[;,] {printf("Delimeter: %s\n",yytext);}
if|else|continue|break|main|while|do|for|printf|switch|return
{printf("Keywords: %s\n",yytext);}
\".*\" {printf("String: %s\n",yytext);}
[ \n\t]
%%
int main(void)
{
FILE *fp;
fp = fopen("parser.c","r");
yyin=fp;
yylex();
return 0;
}