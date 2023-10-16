%{
#include<stdio.h>
#include "y.tab.h"
%}

digit           [0-9]
digits          {digit}+
number          {digits}(\.{digits})?(E[+-]?{digits})?
exp             \^
plus            \+
minus           \-
mult            \*
div             \/
mod             \%
left_paren      \(
right_paren     \)
whitespace      [ \t]
newline         [\n]

%%

{number}        {
                    yylval.val=atof(yytext);
                    return NUMBER;
                }
{exp}           {return EXP; }
{plus}          { return PLUS; }
{minus}         { return MINUS; }
{mult}          { return MULT; }
{mod}           { return MOD; }
{div}           { return DIV; }
{left_paren}    { return LEFT_PAREN; }
{right_paren}   { return RIGHT_PAREN; }
{whitespace}    { }
{newline}       { return END; }
.               {
                    yyerror("Invalid character encountered"); 
                    return -1;
                }

%%

int yywrap() {
    return 1;
}