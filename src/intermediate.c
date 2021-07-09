#include "intermediate.h"

#include <stdlib.h>

#include "intermediate.h"

void free_array_info(ARRAY_INFO* a) {
  if (a->sub_type != NULL) free_type(a->sub_type);
  free(a);
}

void free_type(TYPE* a) {
  free_array_info(a->array);
  free_identifier(a->identifier);
}

void free_const(CONST* a) { free_type(a->type); }

void free_identifier(IDENTIFIER* a) { free(a->name); }

void free_array_offset(ARRAY_OFFSET* a) {
  free_array_offset(a->next);
  free_node(a->expression);
}

void free_identifier_ref(IDENTIFIER_REF* a) {
  free_identifier(a->id);
  free_array_offset(a->offset);
}

void free_var_list(VAR_LIST* a) {
  free_var_list(a->next);
  free_identifier(a->id);
}

void free_param_list(PARAM_LIST* a) {
  free_param_list(a->next);
  free_identifier(a->id);
  free_type(a->type);
}

void free_arg_list(ARG_LIST* a) {
  free_arg_list(a->next);
  free_identifier_ref(a->id_ref);
}

void free_procedure(PROCEDURE* a) {
  free_param_list(a->param_list);
  free_node(a->node_list);
}

void free_function(FUNCTION* a) {
  free_param_list(a->param_list);
  free_type(a->return_type);
  free_node(a->node_list);
}

void free_const_declare(CONST_DECLARE* a) {
  free_identifier(a->id);
  free_const(a->value);
}

void free_type_declare(TYPE_DECLARE* a) {
  free_identifier(a->id);
  free_type(a->type);
}

void free_var_declare(VAR_DECLARE* a) {
  free_identifier(a->id);
  free_type(a->type);
}

void free_procedure_declare(PROCEDURE_DECLARE* a) {
  free_identifier(a->id);
  free_procedure(a->procedure);
}

void free_function_declare(FUNCTION_DECLARE* a) {
  free_identifier(a->id);
  free_function(a->function);
}

void free_assign(ASSIGN* a) {
  free_identifier_ref(a->id_ref);
  free_node(a->expression);
}

void free_binary_operate(BINARY_OPERATE* a) {
  free_node(a->first);
  free_node(a->second);
}

void free_condition_jump(CONDITION_JUMP* a) {
  free_node(a->condition);
  free_node(a->true);
  free_node(a->false);
}

void free_function_call(FUNCTION_CALL* a) {
  free_identifier(a->id);
  free_node(a->args);
}

NODE* free_node(NODE* node) {
  NODE* temp = node->next;
  switch (temp->op) {
    case op_const_declare:
      free_const_declare(temp->const_declare);
      break;
    case op_type_declare:
      free_type_declare(temp->type_declare);
      break;
    case op_var_declare:
      free_var_declare(temp->var_declare);
      break;
    case op_procedure_declare:
      free_procedure_declare(temp->procedure_declare);
      break;
    case op_function_declare:
      free_function_declare(temp->function_declare);
      break;
    default:
      printf("free error\n");
  }
}
