%{
#include <stdio.h>
#include <stdlib.h>

#include "intermediate.h"

int icode_index = 0;
extern ICODE *global_result;
extern int yylineno;

int yylex(void);
void yyerror(const char *);
%}

%union {
  char *id;
  ID_LIST *id_list;
  ICODE *icode;
  VAR_VALUE *var_value;
  TYPE_VALUE *type_value;
  CONST_VALUE *const_value;
}

%start program
%locations

%token <id> IDENTIFIER
%token <type_value> INTEGER REAL BOOLEAN ARRAY
%token <const_value> NUMBER REAL_NUMBER TRUE FALSE

%token CONST TYPE VAR PROCEDURE FUNCTION
%token OF
%token IF THEN ELSE
%token WRITE READ
%token WHILE DO EXIT
%token OR AND NOT
%token DIV MOD
%token RELOP

%token PERIOD PERIOD_PERIOD COLON SEMI COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token CALL ODD BLOCK_BEGIN BLOCK_END ASSIGN EQ PLUS MINUS DIVIDE TIMES

%type <icode> block declarepart
%type <icode> const_declare const_define const_definition
%type <icode> type_declare type_define type_definition
%type <type_value> type_expression
%type <icode> var_declare var_define
%type <id_list> identifier_list
%type <var_value> type

%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program: before_program block PERIOD {
      global_result = $2;
    }
  ;

before_program: {
      // clear icode index and begin a new analysis
      icode_index = 0;
    }
  ;

block: declarepart BLOCK_BEGIN statements BLOCK_END {
      $$ = $1;
    }
  ;

declarepart: const_declare type_declare var_declare procedure_declare {
      $$ = concat_icode($1, concat_icode($2, concat_icode($3, concat_icode($4))));
    }
  | const_declare type_declare var_declare {
      $$ = concat_icode($1, concat_icode($2, concat_icode($3)));
    }
  | const_declare type_declare procedure_declare {
      $$ = concat_icode($1, concat_icode($2, concat_icode($3)));
    }
  | const_declare var_declare procedure_declare {
      $$ = concat_icode($1, concat_icode($2, concat_icode($3)));
    }
  | type_declare var_declare procedure_declare {
      $$ = concat_icode($1, concat_icode($2, concat_icode($3)));
    }
  | const_declare type_declare {
      $$ = concat_icode($1, $2);
    }
  | const_declare procedure_declare {
      $$ = concat_icode($1, $2);
    }
  | const_declare var_declare {
      $$ = concat_icode($1, $2);
    }
  | type_declare procedure_declare {
      $$ = concat_icode($1, $2);
    }
  | type_declare var_declare {
      $$ = concat_icode($1, $2);
    }
  | var_declare procedure_declare {
      $$ = concat_icode($1, $2);
    }
  | const_declare {
      $$ = $1;
    }
  | type_declare {
      $$ = $1;
    }
  | var_declare {
      $$ = $1;
    }
  | procedure_declare {
      $$ = $1;
    }
  | {
      $$ = create_icode(op_nop);
    }
  ;

const_declare: CONST const_define SEMI {
      $$ = $2;
    }
  ;

const_define: const_define SEMI const_definition {
      $$ = concat_icode($1, $3);
    }
  | const_definition {
      $$ = $1;
    }
  ;

const_definition: IDENTIFIER EQ NUMBER {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->name = $1;
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = $3;
      $$ = temp;
    }
  | IDENTIFIER EQ REAL_NUMBER {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = $3;
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->name = $1;
      $$ = temp;
    }
  | IDENTIFIER EQ TRUE {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = $3;
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->name = $1;
      $$ = temp;
    }
  | IDENTIFIER EQ FALSE {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = $3;
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->name = $1;
      $$ = temp;
    }
  ;

type_declare: TYPE type_define SEMI {
      $$ = $2;
    }
  ;

type_define: type_define SEMI type_definition {
      $$ = concat_icode($1, $3);
    }
  | type_definition {
      $$ = $1;
    }
  ;

type_definition: IDENTIFIER EQ type_expression {
      ICODE *temp = create_icode(op_type_declare);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      SYMBOL *type = create_symbol(st_type);
      temp->symbol[0] = type;
      type->type_value = $3;
      $$ = temp;
    }
  ;

type_expression: INTEGER {
      $$ = $1;
    }
  | REAL {
      $$ = $1;
    }
  | BOOLEAN {
      $$ = $1;
    }
  | ARRAY LBRACE NUMBER RBRACE OF type_expression {
      $1->array_start = 0;
      $1->array_end = $3->num - 1;
      $1->sub_value = $6;
      $$ = $1;
    }
  | ARRAY LBRACE NUMBER PERIOD_PERIOD NUMBER RBRACE OF type_expression {
      $1->array_start = $3->num;
      $1->array_end = $5->num;
      $1->sub_value = $8;
      $$ = $1;
    }
  ;

var_declare: VAR var_define SEMI
  ;

var_define: var_define SEMI identifier_list COLON type
  | identifier_list COLON type
  ;

identifier_list: identifier_list COMMA IDENTIFIER {
      ID_LIST *temp = (ID_LIST *)malloc(sizeof(ID_LIST));
      temp->name = $3;
      $$ = concat_id_list($1, temp);
    }
  | IDENTIFIER {
      ID_LIST *temp = (ID_LIST *)malloc(sizeof(ID_LIST));
      temp->name = $1;
      $$ = temp;
    }
  ;

type: INTEGER {
      VAR_VALUE *temp = (VAR_VALUE *)malloc(sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = $1;
      $$ = temp;
    }
  | REAL {
      VAR_VALUE *temp = (VAR_VALUE *)malloc(sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = $1;
      $$ = temp;
    }
  | BOOLEAN {
      VAR_VALUE *temp = (VAR_VALUE *)malloc(sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = $1;
      $$ = temp;
    }
  | IDENTIFIER {
      VAR_VALUE *temp = (VAR_VALUE *)malloc(sizeof(VAR_VALUE));
      temp->type = vt_identifier;
      temp->identifier = $1;
      $$ = temp;
    }
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

SYMBOL *create_symbol(SYMBOL_TYPE type) {
  SYMBOL *symbol = (SYMBOL *)malloc(sizeof(SYMBOL));
  symbol->type = type;
  return symbol;
}

ICODE *create_icode(OPERATION operation) {
  ICODE *icode = (ICODE *)malloc(sizeof(ICODE));
  icode->index = icode_index;
  icode->op = operation;
  icode_index++;
  return icode;
}

ICODE *concat_icode(ICODE *first, ICODE *second) {
  ICODE *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

ID_LIST *concat_id_list(ID_LIST *first, ID_LIST *second) {
  ID_LIST *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}
