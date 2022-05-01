%{
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int yylex(void);
void yyerror(char *);
%}
%token NUM
%token SIN COS TAN LOG
%left '+''-' %left '/''*' %start s
%%
s : exp {printf("RESULT %d", $$);}
;
exp : exp '+' exp {$$ = $1 + $3;}
| exp '-' exp {$$ = $1 - $3;}
| exp '*' exp {$$ = $1 * $3;}
| exp '/' exp {