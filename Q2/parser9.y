%{
#define YYDEBUG 0

#include <bits/stdc++.h>

int yyerror(char *s);

#include "helper.hpp"

#include "y.tab.h"
#include "lex.yy.c"
%}

%token PLUS MINUS MULT DIV MOD NUMBER EXP LEFT_PAREN RIGHT_PAREN END

%start exp

%union
{
    double val;
    Treenode* node;
}

%%
exp:        E END                       { 
                                            printf("%g\n", $<node>1->ans); 
                                            $<node>1->printDAG();
                                            $<node>1->printTree();
                                        }
E:          E PLUS T                    { 
                                            double ans = $<node>1->ans + $<node>3->ans;
                                            $<node>$ = new Treenode("+", ans, $<node>1, $<node>3);
                                        }
            | E MINUS T                 { 
                                            double ans = $<node>1->ans - $<node>3->ans; 
                                            $<node>$ = new Treenode("-", ans, $<node>1, $<node>3); 
                                        }
            | T                         { 
                                            $<node>$ = $<node>1; 
                                        }
T:          T MULT P                    { 
                                            double ans = $<node>1->ans * $<node>3->ans; 
                                            $<node>$ = new Treenode("*", ans, $<node>1, $<node>3); 
                                        }
            | T DIV P                   {   if ($<node>3->ans==0) { yyerror("Divide By Zero"); } else{ 
                                            double ans = $<node>1->ans / $<node>3->ans; 
                                            $<node>$ = new Treenode("/", ans, $<node>1, $<node>3);} 
                                        }
            | T MOD P                   {   if ($<node>3->ans==0) { yyerror("Modulo By Zero"); } else{ 
                                            double ans = fmod($<node>1->ans , $<node>3->ans); 
                                            $<node>$ = new Treenode("%", ans, $<node>1, $<node>3);} 
                                        }
            | P                         { 
                                            $<node>$ = $<node>1; 
                                        }
P:          F EXP P                     { 
                                            double ans = pow($<node>1->ans , $<node>3->ans); 
                                            $<node>$ = new Treenode("^", ans, $<node>1, $<node>3); 
                                        }
            | F                         { 
                                            $<node>$ = $<node>1; 
                                        }
F:          LEFT_PAREN E RIGHT_PAREN    { 
                                            double ans = $<node>2->ans; 
                                            $<node>$ = $<node>2; 
                                        }
            | PLUS F                    { 
                                            double ans = $<node>2->ans; 
                                            $<node>$ = new Treenode("+", ans, $<node>2,nullptr); 
                                        }
            | MINUS F                   { 
                                            double ans = $<node>2->ans * -1; 
                                            $<node>$ = new Treenode("-", ans, $<node>2,nullptr); 
                                        }
            | NUMBER                       { 
                                            $<node>$ = new Treenode($<val>1);
                                        }
%%

extern int yylex(), yyparse();

int yyerror(char *s)
{
	fprintf(stderr, "%s in line no : %d => '%s'\n", s, yylineno, yytext);
	exit(-1);
}

int main()
{
#if YYDEBUG
    yydebug = 1;
#endif

    extern FILE *yyin;
    yyin = fopen("input.txt", "r");

    if(yyin==NULL)
    {
        printf("Could not open 'input.txt'\n");
        return -1;
    }

    yyparse();

    return 0;
}