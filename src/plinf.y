%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;

int yylex(void);
void yyerror(const char *);
%}

%union {
  char *id;
  long num;
  double real_num;
}

%start program
%locations

%token <id> IDENTIFIER
%token <num> NUMBER
%token <real_num> REAL_NUMBER

%token CONST TYPE VAR PROCEDURE FUNCTION
%token INTEGER REAL BOOLEAN ARRAY OF TRUE FALSE
%token IF THEN ELSE
%token WRITE READ
%token WHILE DO EXIT
%token OR AND NOT
%token DIV MOD
%token RELOP

%token PERIOD PERIOD_PERIOD COLON SEMI COMMA
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

const_define: const_define SEMI num_definition
  | num_definition
  ;

num_definition: IDENTIFIER EQ NUMBER
  | IDENTIFIER EQ REAL_NUMBER
  ;

type_declare: TYPE type_define SEMI
  ;

type_define: type_define SEMI type_definition
  | type_definition
  ;

type_definition: IDENTIFIER EQ type_expression
  ;

type_expression: INTEGER
  | REAL
  | BOOLEAN
  | ARRAY LBRACE NUMBER RBRACE OF type_expression
  | ARRAY LBRACE NUMBER PERIOD_PERIOD NUMBER RBRACE OF type_expression
  ;

var_declare: VAR var_define SEMI
  ;

var_define: var_define SEMI identifier_list COLON type
  | identifier_list COLON type
  ;

identifier_list: identifier_list COMMA IDENTIFIER
  | IDENTIFIER
  ;

type: INTEGER
  | REAL
  | BOOLEAN
  | IDENTIFIER
  ;

procedure_declare: procedure_declare procedure_define
  | procedure_define
  ;

procedure_define: PROCEDURE IDENTIFIER SEMI program
  | PROCEDURE IDENTIFIER LPAREN param_define RPAREN SEMI program
  | FUNCTION IDENTIFIER COLON type SEMI program
  | FUNCTION IDENTIFIER LPAREN param_define RPAREN COLON type SEMI program
  ;

param_define: param_define COMMA IDENTIFIER COLON type
  | IDENTIFIER COLON type
  ;

statements: statements statement SEMI
  | /* empty statement */
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
  | REAL_NUMBER
  | LPAREN expression RPAREN
  | NOT factor
  | CALL IDENTIFIER
  | CALL IDENTIFIER LPAREN params RPAREN
  | ODD LPAREN simple_expression RPAREN
  | TRUE
  | FALSE
  ;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "%s at line %d\n", msg, yylineno);
}
