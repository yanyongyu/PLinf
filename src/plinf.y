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

%token CONST TYPE VAR PROCEDURE FUNCTION
%token INTEGER REAL BOOLEAN ARRAY OF TRUE FALSE
%token IF THEN ELSE
%token WRITE READ
%token WHILE DO EXIT
%token OR AND NOT
%token DIV MOD
%token RELOP

%token PERIOD COLON SEMI COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token CALL ODD BLOCK_BEGIN BLOCK_END ASSIGN EQ PLUS MINUS DIVIDE TIMES

%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program: block PERIOD
  ;

block: declarepart BLOCK_BEGIN statements BLOCK_END
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

param_define: param_define COMMA IDENTIFIER COLON type
  | IDENTIFIER COLON type
  ;

statements: statements statement SEMI
  | statement SEMI
  ;

statement: identifier_ref ASSIGN expression
  | IF expression THEN statement %prec LOWER_THAN_ELSE
  | IF expression THEN statement ELSE statement
  | BLOCK_BEGIN statements BLOCK_END
  | WHILE expression DO statement
  | EXIT
  | CALL IDENTIFIER
  | CALL IDENTIFIER LPAREN params RPAREN
  | WRITE LPAREN params RPAREN
  | READ LPAREN identifier_refs RPAREN
  | /* empty statement */
  ;

identifier_refs: identifier_refs identifier_ref
  | identifier_ref
  ;

identifier_ref: IDENTIFIER
  | IDENTIFIER indexs
  ;

indexs: indexs LBRACE expression RBRACE
  | LBRACE expression RBRACE
  ;

params: params COMMA expression
  | expression
  ;

expression: simple_expression
  | simple_expression RELOP simple_expression
  | simple_expression EQ simple_expression
  ;

simple_expression: simple_expression PLUS term
  | simple_expression MINUS term
  | simple_expression OR term
  | PLUS term
  | MINUS term
  | term
  ;

term: term TIMES factor
  | term DIVIDE factor
  | term DIV factor
  | term MOD factor
  | term AND factor
  | factor
  ;

factor: identifier_ref
  | NUMBER
  | LPAREN expression RPAREN
  | NOT factor
  | CALL IDENTIFIER
  | CALL IDENTIFIER LPAREN params RPAREN
  | ODD LPAREN simple_expression RPAREN
  | TRUE
  | FALSE
  ;

%%
