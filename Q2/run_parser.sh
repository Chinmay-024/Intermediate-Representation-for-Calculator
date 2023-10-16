lex lex9.l && yacc parser9.y -d
g++ -w y.tab.c && ./a.out
rm a.out lex.yy.c y.tab.c y.tab.h