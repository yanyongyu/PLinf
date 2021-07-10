%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intermediate.h"

NODE *global_result;
extern int yylineno;

int yylex(void);
void yyerror(const char *);
NODE *create_node(OPERATION);
NODE *concat_node(NODE *, NODE *);
VAR_LIST *concat_var_list(VAR_LIST *, VAR_LIST *);
PARAM_LIST *concat_param_list(PARAM_LIST *, PARAM_LIST *);
ARRAY_OFFSET *concat_array_offset(ARRAY_OFFSET *first, ARRAY_OFFSET *second);
%}

%code requires {
  #include "intermediate.h"
}

%union {
  VAR_LIST *var_list;
  PARAM_LIST *param_list;
  NODE *node;
  TYPE *type;
  ARRAY_OFFSET *offset;
  CONST *const_value;
  IDENTIFIER *id;
  IDENTIFIER_REF *id_ref;
}

%start program
%locations

%token <id> IDENTIFIER_ WRITE READ
%token <type> INTEGER REAL BOOLEAN ARRAY
%token <const_value> NUMBER REAL_NUMBER TRUE FALSE

%token CONST_ TYPE_ VAR_ PROCEDURE_ FUNCTION_
%token OF
%token IF THEN ELSE
%token WHILE DO CONTINUE EXIT
%token OR AND NOT
%token DIV MOD
%token LE LEQ GE GEQ EQ NEQ PLUS MINUS DIVIDE TIMES

%token PERIOD PERIOD_PERIOD COLON SEMI COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token CALL ODD BLOCK_BEGIN BLOCK_END ASSIGN_

%type <node> block declarepart

%type <node> const_declare const_define const_definition

%type <node> type_declare type_define type_definition
%type <type> type_expression

%type <node> var_declare var_define
%type <var_list> identifier_list
%type <type> type

%type <node> procedure_declare procedure_define
%type <param_list> param_define

%type <node> statements statement args identifier_refs
%type <id_ref> identifier_ref
%type <offset> indexs

%type <node> expression simple_expression term factor

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
      // clear result
      global_result = (NODE *)NULL;
    }
  ;

block: declarepart BLOCK_BEGIN statements BLOCK_END {
      $$ = concat_node($1, $3);
    }
  ;

declarepart: const_declare type_declare var_declare procedure_declare {
      $$ = concat_node($1, concat_node($2, concat_node($3, $4)));
    }
  | const_declare type_declare var_declare {
      $$ = concat_node($1, concat_node($2, $3));
    }
  | const_declare type_declare procedure_declare {
      $$ = concat_node($1, concat_node($2, $3));
    }
  | const_declare var_declare procedure_declare {
      $$ = concat_node($1, concat_node($2, $3));
    }
  | type_declare var_declare procedure_declare {
      $$ = concat_node($1, concat_node($2, $3));
    }
  | const_declare type_declare {
      $$ = concat_node($1, $2);
    }
  | const_declare procedure_declare {
      $$ = concat_node($1, $2);
    }
  | const_declare var_declare {
      $$ = concat_node($1, $2);
    }
  | type_declare procedure_declare {
      $$ = concat_node($1, $2);
    }
  | type_declare var_declare {
      $$ = concat_node($1, $2);
    }
  | var_declare procedure_declare {
      $$ = concat_node($1, $2);
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
      $$ = create_node(op_nop);
    }
  ;

const_declare: CONST_ const_define SEMI {
      $$ = $2;
    }
  ;

const_define: const_define SEMI const_definition {
      $$ = concat_node($1, $3);
    }
  | const_definition {
      $$ = $1;
    }
  ;

const_definition: IDENTIFIER_ EQ NUMBER {
      NODE *temp = create_node(op_const_declare);
      CONST_DECLARE *declare = (CONST_DECLARE *)calloc(1, sizeof(CONST_DECLARE));
      declare->id = $1;
      declare->value = $3;
      temp->const_declare = declare;
      $$ = temp;
    }
  | IDENTIFIER_ EQ REAL_NUMBER {
      NODE *temp = create_node(op_const_declare);
      CONST_DECLARE *declare = (CONST_DECLARE *)calloc(1, sizeof(CONST_DECLARE));
      declare->id = $1;
      declare->value = $3;
      temp->const_declare = declare;
      $$ = temp;
    }
  | IDENTIFIER_ EQ TRUE {
      NODE *temp = create_node(op_const_declare);
      CONST_DECLARE *declare = (CONST_DECLARE *)calloc(1, sizeof(CONST_DECLARE));
      declare->id = $1;
      declare->value = $3;
      temp->const_declare = declare;
      $$ = temp;
    }
  | IDENTIFIER_ EQ FALSE {
      NODE *temp = create_node(op_const_declare);
      CONST_DECLARE *declare = (CONST_DECLARE *)calloc(1, sizeof(CONST_DECLARE));
      declare->id = $1;
      declare->value = $3;
      temp->const_declare = declare;
      $$ = temp;
    }
  ;

type_declare: TYPE_ type_define SEMI {
      $$ = $2;
    }
  ;

type_define: type_define SEMI type_definition {
      $$ = concat_node($1, $3);
    }
  | type_definition {
      $$ = $1;
    }
  ;

type_definition: IDENTIFIER_ EQ type_expression {
      NODE *temp = create_node(op_type_declare);
      TYPE_DECLARE *declare = (TYPE_DECLARE *)calloc(1, sizeof(TYPE_DECLARE));
      declare->id = $1;
      declare->type = $3;
      temp->type_declare = declare;
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
      $1->array->array_start = 0;
      $1->array->array_end = $3->num - 1;
      $1->array->sub_type = $6;
      $$ = $1;
    }
  | ARRAY LBRACE NUMBER PERIOD_PERIOD NUMBER RBRACE OF type_expression {
      $1->array->array_start = $3->num;
      $1->array->array_end = $5->num;
      $1->array->sub_type = $8;
      $$ = $1;
    }
  ;

var_declare: VAR_ var_define SEMI {
      $$ = $2;
    }
  ;

var_define: var_define SEMI identifier_list COLON type {
      NODE *define, *start, *temp = create_node(op_nop);
      VAR_DECLARE *declare;
      VAR_LIST *var_list = $3;
      start = temp;
      do {
        define = temp->next = create_node(op_var_declare);
        declare = (VAR_DECLARE *)calloc(1, sizeof(VAR_DECLARE));
        declare->id = var_list->id;
        declare->type = copy_type($5);
        define->var_declare = declare;
        temp = temp->next;
        var_list = var_list->next;
      } while (var_list);
      free_type($5);
      $$ = concat_node($1, start->next);
    }
  | identifier_list COLON type {
      NODE *define, *start, *temp = create_node(op_nop);
      VAR_DECLARE *declare;
      VAR_LIST *var_list = $1;
      start = temp;
      do {
        define = temp->next = create_node(op_var_declare);
        declare = (VAR_DECLARE *)calloc(1, sizeof(VAR_DECLARE));
        declare->id = var_list->id;
        declare->type = copy_type($3);
        define->var_declare = declare;
        temp = temp->next;
        var_list = var_list->next;
      } while (var_list);
      free_type($3);
      $$ = start->next;
    }
  ;

identifier_list: identifier_list COMMA IDENTIFIER_ {
      VAR_LIST *temp = (VAR_LIST *)calloc(1, sizeof(VAR_LIST));
      temp->id = $3;
      $$ = concat_var_list($1, temp);
    }
  | IDENTIFIER_ {
      VAR_LIST *temp = (VAR_LIST *)calloc(1, sizeof(VAR_LIST));
      temp->id = $1;
      $$ = temp;
    }
  ;

type: INTEGER {
      $$ = $1;
    }
  | REAL {
      $$ = $1;
    }
  | BOOLEAN {
      $$ = $1;
    }
  | IDENTIFIER_ {
      TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
      temp->type = tt_identifier;
      temp->identifier = $1;
      $$ = temp;
    }
  ;

procedure_declare: procedure_declare procedure_define {
      $$ = concat_node($1, $2);
    }
  | procedure_define {
      $$ = $1;
    }
  ;

procedure_define: PROCEDURE_ IDENTIFIER_ SEMI block SEMI {
      NODE *temp = create_node(op_procedure_declare);
      PROCEDURE *procedure = (PROCEDURE *)calloc(1, sizeof(PROCEDURE));
      procedure->node_list = $4;
      PROCEDURE_DECLARE *procedure_declare = (PROCEDURE_DECLARE *)calloc(1, sizeof(PROCEDURE_DECLARE));
      procedure_declare->id = $2;
      procedure_declare->procedure = procedure;
      temp->procedure_declare = procedure_declare;
      $$ = temp;
    }
  | PROCEDURE_ IDENTIFIER_ LPAREN param_define RPAREN SEMI block SEMI {
      NODE *temp = create_node(op_procedure_declare);
      PROCEDURE *procedure = (PROCEDURE *)calloc(1, sizeof(PROCEDURE));
      procedure->param_list = $4;
      procedure->node_list = $7;
      PROCEDURE_DECLARE *procedure_declare = (PROCEDURE_DECLARE *)calloc(1, sizeof(PROCEDURE_DECLARE));
      procedure_declare->id = $2;
      procedure_declare->procedure = procedure;
      temp->procedure_declare = procedure_declare;
      $$ = temp;
    }
  | FUNCTION_ IDENTIFIER_ COLON type SEMI block SEMI {
      NODE *temp = create_node(op_function_declare);
      FUNCTION *function = (FUNCTION *)calloc(1, sizeof(FUNCTION));
      function->return_type = $4;
      function->node_list = $6;
      FUNCTION_DECLARE *function_declare = (FUNCTION_DECLARE *)calloc(1, sizeof(FUNCTION_DECLARE));
      function_declare->id = $2;
      function_declare->function = function;
      temp->function_declare = function_declare;
      $$ = temp;
    }
  | FUNCTION_ IDENTIFIER_ LPAREN param_define RPAREN COLON type SEMI block SEMI {
      NODE *temp = create_node(op_function_declare);
      FUNCTION *function = (FUNCTION *)calloc(1, sizeof(FUNCTION));
      function->param_list = $4;
      function->return_type = $7;
      function->node_list = $9;
      FUNCTION_DECLARE *function_declare = (FUNCTION_DECLARE *)calloc(1, sizeof(FUNCTION_DECLARE));
      function_declare->id = $2;
      function_declare->function = function;
      temp->function_declare = function_declare;
      $$ = temp;
    }
  ;

param_define: param_define COMMA IDENTIFIER_ COLON type {
      PARAM_LIST *temp = (PARAM_LIST *)calloc(1, sizeof(PARAM_LIST));
      temp->id = $3;
      temp->type = $5;
      $$ = concat_param_list($1, temp);
    }
  | IDENTIFIER_ COLON type {
      PARAM_LIST *temp = (PARAM_LIST *)calloc(1, sizeof(PARAM_LIST));
      temp->id = $1;
      temp->type = $3;
      $$ = temp;
    }
  ;

statements: statements statement SEMI {
      $$ = concat_node($1, $2);
    }
  | /* empty statement */ {
      $$ = create_node(op_nop);
    }
  ;

statement: identifier_ref ASSIGN_ expression {
      NODE *temp = create_node(op_assign);
      ASSIGN *assign = (ASSIGN *)calloc(1, sizeof(ASSIGN));
      assign->id_ref = $1;
      assign->expression = $3;
      temp->assign = assign;
      $$ = temp;
    }
  | IF expression THEN statement %prec LOWER_THAN_ELSE {
      NODE *temp = create_node(op_if_then);
      CONDITION_JUMP *jump = (CONDITION_JUMP *)calloc(1, sizeof(CONDITION_JUMP));
      jump->condition = $2;
      jump->true = $4;
      temp->condition_jump = jump;
      $$ = temp;
    }
  | IF expression THEN statement ELSE statement {
      NODE *temp = create_node(op_if_then);
      CONDITION_JUMP *jump = (CONDITION_JUMP *)calloc(1, sizeof(CONDITION_JUMP));
      jump->condition = $2;
      jump->true = $4;
      jump->false = $6;
      temp->condition_jump = jump;
      $$ = temp;
    }
  | BLOCK_BEGIN statements BLOCK_END {
      $$ = $2;
    }
  | WHILE expression DO statement {
      NODE *temp = create_node(op_while_do);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $2;
      operation->second = $4;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | CONTINUE {
      $$ = create_node(op_continue);
    }
  | EXIT {
      $$ = create_node(op_exit);
    }
  | CALL IDENTIFIER_ {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $2;
      temp->function_call = call;
      $$ = temp;
    }
  | CALL IDENTIFIER_ LPAREN args RPAREN {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $2;
      call->args = $4;
      temp->function_call = call;
      $$ = temp;
    }
  | WRITE LPAREN args RPAREN {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $1;
      call->args = $3;
      temp->function_call = call;
      $$ = temp;
    }
  | READ LPAREN identifier_refs RPAREN {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $1;
      call->args = $3;
      temp->function_call = call;
      $$ = temp;
    }
  | /* empty statement */ {
      $$ = create_node(op_nop);
    }
  ;

identifier_refs: identifier_refs identifier_ref {
      NODE *temp = create_node(op_load_identifier);
      temp->id_ref = $2;
      $$ = concat_node($1, temp);
    }
  | identifier_ref {
      NODE *temp = create_node(op_load_identifier);
      temp->id_ref = $1;
      $$ = temp;
    }
  ;

identifier_ref: IDENTIFIER_ {
      IDENTIFIER_REF *id_ref = (IDENTIFIER_REF *)calloc(1, sizeof(IDENTIFIER_REF));
      id_ref->id = $1;
      $$ = id_ref;
    }
  | IDENTIFIER_ indexs {
      IDENTIFIER_REF *id_ref = (IDENTIFIER_REF *)calloc(1, sizeof(IDENTIFIER_REF));
      id_ref->id = $1;
      id_ref->offset = $2;
      $$ = id_ref;
    }
  ;

indexs: indexs LBRACE expression RBRACE {
      ARRAY_OFFSET *index = (ARRAY_OFFSET *)calloc(1, sizeof(ARRAY_OFFSET));
      index->expression = $3;
      $$ = concat_array_offset($1, index);
    }
  | LBRACE expression RBRACE {
      ARRAY_OFFSET *index = (ARRAY_OFFSET *)calloc(1, sizeof(ARRAY_OFFSET));
      index->expression = $2;
      $$ = index;
    }
  ;

args: args COMMA expression {
      $$ = concat_node($1, $3);
    }
  | expression {
      $$ = $1;
    }
  ;

expression: simple_expression {
      $$ = $1;
    }
  | simple_expression LE simple_expression {
      NODE *temp = create_node(op_le);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression LEQ simple_expression {
      NODE *temp = create_node(op_leq);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression GE simple_expression {
      NODE *temp = create_node(op_ge);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression GEQ simple_expression {
      NODE *temp = create_node(op_geq);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression EQ simple_expression {
      NODE *temp = create_node(op_eq);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression NEQ simple_expression {
      NODE *temp = create_node(op_neq);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  ;

simple_expression: simple_expression PLUS term {
      NODE *temp = create_node(op_plus);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression MINUS term {
      NODE *temp = create_node(op_minus);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | simple_expression OR term {
      NODE *temp = create_node(op_or);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | PLUS term {
      $$ = $2;
    }
  | MINUS term {
      NODE *temp = create_node(op_minus);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->second = $2;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | term {
      $$ = $1;
    }
  ;

term: term TIMES factor {
      NODE *temp = create_node(op_times);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | term DIVIDE factor {
      NODE *temp = create_node(op_devide);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | term DIV factor {
      NODE *temp = create_node(op_div);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | term MOD factor {
      NODE *temp = create_node(op_mod);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | term AND factor {
      NODE *temp = create_node(op_and);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->first = $1;
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | factor {
      $$ = $1;
    }
  ;

factor: identifier_ref {
      NODE *temp = create_node(op_load_identifier);
      temp->id_ref = $1;
      $$ = temp;
    }
  | NUMBER {
      NODE *temp = create_node(op_load_const);
      temp->const_value = $1;
      $$ = temp;
    }
  | REAL_NUMBER {
      NODE *temp = create_node(op_load_const);
      temp->const_value = $1;
      $$ = temp;
    }
  | LPAREN expression RPAREN {
      $$ = $2;
    }
  | NOT factor {
      NODE *temp = create_node(op_not);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->second = $2;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | CALL IDENTIFIER_ {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $2;
      temp->function_call = call;
      $$ = temp;
    }
  | CALL IDENTIFIER_ LPAREN args RPAREN {
      NODE *temp = create_node(op_call);
      FUNCTION_CALL *call = (FUNCTION_CALL *)calloc(1, sizeof(FUNCTION_CALL));
      call->id = $2;
      call->args = $4;
      temp->function_call = call;
      $$ = temp;
    }
  | ODD LPAREN simple_expression RPAREN {
      NODE *temp = create_node(op_odd);
      BINARY_OPERATE *operation = (BINARY_OPERATE *)calloc(1, sizeof(BINARY_OPERATE));
      operation->second = $3;
      temp->binary_operate = operation;
      $$ = temp;
    }
  | TRUE {
      NODE *temp = create_node(op_load_const);
      temp->const_value = $1;
      $$ = temp;
    }
  | FALSE {
      NODE *temp = create_node(op_load_const);
      temp->const_value = $1;
      $$ = temp;
    }
  ;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "%s at line %d\n", msg, yylineno);
}

NODE *create_node(OPERATION operation) {
  NODE *node = (NODE *)calloc(1, sizeof(NODE));
  node->op = operation;
  return node;
}

NODE *concat_node(NODE *first, NODE *second) {
  NODE *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

VAR_LIST *concat_var_list(VAR_LIST *first, VAR_LIST *second) {
  VAR_LIST *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

PARAM_LIST *concat_param_list(PARAM_LIST *first, PARAM_LIST *second) {
  PARAM_LIST *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

ARRAY_OFFSET *concat_array_offset(ARRAY_OFFSET *first, ARRAY_OFFSET *second) {
  ARRAY_OFFSET *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}
