/* Parser for the formula analyzer. 
 *
 * Author: Erick Daniel Corona Garcia. 210224314.
 */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(); 
int yyerror(const char *p) { fprintf(stderr, "Syntax error!\n"); }
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
  printf("Enter the expression to evaluate\n>> ");
  yyparse();
  printf("\n");

  if (yynerrs > 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

