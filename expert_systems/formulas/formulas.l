/* Scanner for the formula analyzer. 
 *
 * Author: Erick Daniel Corona Garcia. 210224314. Sistemas Expertos 14A.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "formulas.tab.h"

extern "C" unsigned int lineno;
extern "C" unsigned int rowno;
%}

%option noyywrap

%%
"&"|"|"                    { ++rowno; return BINOP; }
"->"|"<-"|"<->"            { rowno += 2; return BINOP; }
"<"|">"                    { ++rowno; return COMPOP; }
"<="|">="|"="|"!="         { rowno += 2; return COMPOP; }
"~"                        { ++rowno; return NOT; }
[@#]                       { ++rowno; return QUANT; }
[A-Z][a-zA-Z0-9_]*         { rowno += strlen(yytext); return VAR; }
[a-z][a-zA-Z0-9_]*         { rowno += strlen(yytext); return CONST; }
"("                        { ++rowno; return OPAREN; }
")"                        { ++rowno; return CPAREN; }
","                        { ++rowno; return DELIM; }
[ \t]                      { ++rowno; }
[\n\r]+                      { ++lineno; }
.                          { fprintf(stderr,
                                     "error: invalid symbol at: %u\n", rowno); }
%%

