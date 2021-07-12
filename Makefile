LEX = flex
YACC = bison -d
CC = gcc
file = test/test.plinf

all: yacc lex cython

yacc:
	$(YACC) -o plinf/core/plinf.tab.c plinf/core/plinf.y

lex:
	$(LEX) -o plinf/core/plinf.yy.c plinf/core/plinf.l

cython:
	cythonize "plinf/**/*.pyx" -i -3

test_lex: yacc lex
	$(CC) test/test_lexical.c $(wildcard plinf/core/*.c) -Iplinf/core -o temp/test_lexical
	./temp/test_lexical

test_grammar: yacc lex
	$(CC) test/test_grammar.c $(wildcard plinf/core/*.c) -Iplinf/core -o temp/test_grammar
	./temp/test_grammar $(file)

test_opcode: yacc lex
	$(CC) test/test_opcode.c $(wildcard plinf/core/*.c) -Iplinf/core -o temp/test_opcode
	./temp/test_opcode $(file)

test_py: yacc lex cython
	python -m unittest discover -v -s test
