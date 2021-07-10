LEX = flex
YACC = bison -d
CC = gcc
file = test/test.plinf

all: yacc lex

yacc:
	$(YACC) -o src/plinf.tab.c src/plinf.y

lex:
	$(LEX) -o src/plinf.yy.c src/plinf.l

test_lex: yacc lex
	$(CC) test/test_lexical.c $(wildcard src/*.c) -Isrc -o temp/test_lexical
	./temp/test_lexical

test_grammar: yacc lex
	$(CC) test/test_grammar.c $(wildcard src/*.c) -Isrc -o temp/test_grammar
	./temp/test_grammar $(file)
