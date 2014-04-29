/* Parser for the formula analyzer. 
 *
 * Author: Erick Daniel Corona Garcia. 210224314. Sistemas Expertos 14A.
 */

%{
#include <stdio.h>
#include <stdlib.h>

unsigned int lineno = 1;
unsigned int rowno = 1;

int yylex(); 
void yyerror(const char* string)
{
  fprintf(stderr, "error [%u,%u]: %s\n", lineno, rowno, string);
}
%}

%union {
  int var;
}

%error-verbose

%token NOT OPAREN CPAREN BINOP QUANT VAR CONST COMPOP DELIM
%type <var> input logexp quant atom term termlist func

%%
input:
  input logexp
| logexp
;

logexp:
  NOT logexp
| OPAREN logexp CPAREN
| logexp BINOP logexp
| quant logexp
| atom
;

quant:
  QUANT VAR
;

atom:
  CONST OPAREN termlist CPAREN
| comp
;

comp:
  term COMPOP term
;

termlist:
  term
| term DELIM termlist
;

term:
  func
| VAR
| CONST
;

func:
  CONST OPAREN termlist CPAREN
;
%%


int main()
{
  printf("Enter the expression to evaluate\n");
  yyparse();
  printf("\n");

  if (yynerrs > 0)
  {
    printf("The expression is NOT a Well-Formed Formula.\n");
    return EXIT_FAILURE;
  }

  printf("The expression is a Well-Formed Formula.\n");
  return EXIT_SUCCESS;
}
