#include "intermediate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ARRAY_INFO *copy_array_info(ARRAY_INFO *a) {
  ARRAY_INFO *temp = (ARRAY_INFO *)calloc(1, sizeof(ARRAY_INFO));
  temp->array_start = a->array_start;
  temp->array_end = a->array_end;
  if (a->sub_type != NULL) temp->sub_type = copy_type(a->sub_type);
  return temp;
}

TYPE *copy_type(TYPE *a) {
  TYPE *temp = (TYPE *)calloc(1, sizeof(TYPE));
  temp->type = a->type;
  switch (a->type) {
    case tt_array:
      temp->array = copy_array_info(a->array);
      break;
    case tt_identifier:
      temp->identifier = copy_identifier(a->identifier);
      break;
  }
  return temp;
}

IDENTIFIER *copy_identifier(IDENTIFIER *a) {
  IDENTIFIER *temp = (IDENTIFIER *)calloc(1, sizeof(IDENTIFIER));
  temp->type = a->type;
  temp->name = strdup(a->name);
  return temp;
}

void free_array_info(ARRAY_INFO *a) {
  if (a == NULL) return;
  if (a->sub_type != NULL) free_type(a->sub_type);
  free(a);
}

void free_type(TYPE *a) {
  if (a == NULL) return;
  switch (a->type) {
    case tt_array:
      free_array_info(a->array);
      break;
    case tt_identifier:
      free_identifier(a->identifier);
      break;
  }
  free(a);
}

void free_const(CONST *a) {
  if (a == NULL) return;
  free(a);
}

void free_identifier(IDENTIFIER *a) {
  if (a == NULL) return;
  free(a->name);
  free(a);
}

void free_array_offset(ARRAY_OFFSET *a) {
  if (a == NULL) return;
  free_array_offset(a->next);
  free_node(a->expression);
  free(a);
}

void free_identifier_ref(IDENTIFIER_REF *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_array_offset(a->offset);
  free(a);
}

void free_var_list(VAR_LIST *a) {
  if (a == NULL) return;
  free_var_list(a->next);
  free_identifier(a->id);
  free(a);
}

void free_param_list(PARAM_LIST *a) {
  if (a == NULL) return;
  free_param_list(a->next);
  free_identifier(a->id);
  free_type(a->type);
  free(a);
}

void free_procedure(PROCEDURE *a) {
  if (a == NULL) return;
  free_param_list(a->param_list);
  NODE *temp = a->node_list;
  while (temp != NULL) temp = free_node(temp);
  free(a);
}

void free_function(FUNCTION *a) {
  if (a == NULL) return;
  free_param_list(a->param_list);
  free_type(a->return_type);
  NODE *temp = a->node_list;
  while (temp != NULL) temp = free_node(temp);
  free(a);
}

void free_const_declare(CONST_DECLARE *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_const(a->value);
  free(a);
}

void free_type_declare(TYPE_DECLARE *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_type(a->type);
  free(a);
}

void free_var_declare(VAR_DECLARE *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_type(a->type);
  free(a);
}

void free_procedure_declare(PROCEDURE_DECLARE *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_procedure(a->procedure);
  free(a);
}

void free_function_declare(FUNCTION_DECLARE *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_function(a->function);
  free(a);
}

void free_assign(ASSIGN *a) {
  if (a == NULL) return;
  free_identifier_ref(a->id_ref);
  free_node(a->expression);
  free(a);
}

void free_binary_operate(BINARY_OPERATE *a) {
  if (a == NULL) return;
  free_node(a->first);
  free_node(a->second);
  free(a);
}

void free_condition_jump(CONDITION_JUMP *a) {
  if (a == NULL) return;
  free_node(a->condition);
  free_node(a->true);
  free_node(a->false);
  free(a);
}

void free_function_call(FUNCTION_CALL *a) {
  if (a == NULL) return;
  free_identifier(a->id);
  free_node(a->args);
  free(a);
}

NODE *free_node(NODE *node) {
  if (node == NULL) return (NODE *)NULL;
  NODE *temp = node->next;
  switch (node->op) {
    case op_nop:
    case op_continue:
    case op_exit:
      break;
    case op_const_declare:
      free_const_declare(node->const_declare);
      break;
    case op_type_declare:
      free_type_declare(node->type_declare);
      break;
    case op_var_declare:
      free_var_declare(node->var_declare);
      break;
    case op_procedure_declare:
      free_procedure_declare(node->procedure_declare);
      break;
    case op_function_declare:
      free_function_declare(node->function_declare);
      break;
    case op_assign:
      free_assign(node->assign);
      break;
    case op_if_then:
    case op_if_then_else:
      free_condition_jump(node->condition_jump);
      break;
    case op_call:
      free_function_call(node->function_call);
      break;
    case op_while_do:
    case op_le:
    case op_leq:
    case op_ge:
    case op_geq:
    case op_eq:
    case op_neq:
    case op_plus:
    case op_minus:
    case op_times:
    case op_divide:
    case op_div:
    case op_mod:
    case op_odd:
    case op_and:
    case op_or:
    case op_not:
      free_binary_operate(node->binary_operate);
      break;
    case op_load_const:
      free_const(node->const_value);
      break;
    case op_load_identifier:
      free_identifier_ref(node->id_ref);
      break;
    default:
      printf("unknown node type %d\n", node->op);
  }
  free(node);
  return temp;
}
