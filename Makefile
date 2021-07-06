LEX = flex
YACC = bison -d
CC = gcc

all: yacc lex

yacc:
	$(YACC) -o src/plinf.tab.c src/plinf.y

lex:
	$(LEX) -o src/plinf.yy.c src/plinf.l
