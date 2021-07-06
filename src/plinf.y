%{
#include <stdlib.h>
%}

%union {
  char *id;
  long num;
}

%start program

%token <id> IDENTIFIER
%token <num> NUMBER

%token CONST, TYPE, VAR, PROCEDURE, FUNCTION
%token INTEGER, REAL, BOOLEAN, ARRAY, OF, TRUE, FALSE
%token IF, THEN, ELSE
%token WRITE, READ
%token WHILE, DO, EXIT
%token OR, AND, NOT
%token DIV, MOD

%token PERIOD, COLON, SEMI, COMMA
%token LPAREN, RPAREN, LBRACE, RBRACE
%token CALL, ODD, BEGIN, END, ASSIGN, NEW, REQ, LEQ, RES, LES, EQ, PLUS, MINUS, DIVIDE, TIMES

%left PLUS, MINUS
%left TIMES, DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program: block PERIOD
  ;

block: declarepart BEGIN statements END
  ;

declarepart: const_declare type_declare var_declare procedure_declare
  | const_declare type_declare var_declare
  | const_declare type_declare procedure_declare
  | const_declare var_declare procedure_declare
  | type_declare var_declare procedure_declare
  | const_declare type_declare
  | const_declare procedure_declare
  | const_declare var_declare
  | type_declare procedure_declare
  | type_declare var_declare
  | var_declare procedure_declare
  | const_declare
  | type_declare
  | var_declare
  | procedure_declare
  |
  ;

const_declare: CONST const_define SEMI
  ;

const_define: const_define COMMA num_definition
  | num_definition
  ;

num_definition: IDENTIFIER EQ NUMBER
  ;

type_declare: TYPE type_define SEMI
  ;

type_define: type_define COMMA type_definition
  | type_definition
  ;

type_definition: IDENTIFIER EQ type_expression
  ;

type_expression: INTEGER
  | REAL
  | BOOLEAN
  | ARRAY LBRACE NUMBER RBRACE OF type_expression
  ;

var_declare: VAR var_define SEMI
  ;

var_define: var_define COMMA IDENTIFIER COLON type
  | IDENTIFIER COLON type
  ;

type: INTEGER
  | REAL
  | BOOLEAN
  | IDENTIFIER
  ;

procedure_declare: procedure_declare procedure_define
  | procedure_define
  ;

procedure_define: PROCEDURE IDENTIFIER SEMI block SEMI
  | PROCEDURE IDENTIFIER LPAREN param_define RPAREN SEMI block SEMI
  | FUNCTION IDENTIFIER COLON type SEMI block SEMI
  | FUNCTION IDENTIFIER LPAREN param_define RPAREN COLON type SEMI block SEMI
  ;

param_define:

statements: statements statement SEMI
  | statement SEMI
  ;

statement:

%%
