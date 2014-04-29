/* Scanner for the formula analyzer. 
 *
 * Author: Erick Daniel Corona Garcia. 210224314.
 */

%{
#include <stdio.h>
#include <stdlib.h>

#include "formulas.tab.h"
%}

%option noyywrap

%%
[&\|]|->|<-|<->    { return BINOP; }
~                  { return NOT; }
[@#]               { return QUANT; }
[A-Z][a-zA-Z0-9_]* { return VAR; }
[a-z][a-zA-Z0-9_]* { return CONST; }
[\(\)]             { return DELIM; }
[ \t\n]+           { }
.                  { fprintf(stderr, "Lexical Error!\n"); }
%%

int yyerror(const char *p) { fprintf(stderr, "Syntax error!\n"); }
