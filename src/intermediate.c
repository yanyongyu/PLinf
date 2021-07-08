#include "intermediate.h"

#include <stdlib.h>

ICODE *free_icode(ICODE *icode) {
  if (icode == NULL) return (ICODE *)NULL;
  free_symbol(icode->symbol[0]);
  free_symbol(icode->symbol[1]);
  free_symbol(icode->symbol[2]);
  ICODE *temp = icode->next;
  free(icode);
  return temp;
}

void free_symbol(SYMBOL *symbol) {
  if (symbol == NULL) return;
  switch (symbol->type) {
    case st_identifier:
      free(symbol->identifier);
      break;
    case st_const:
      free_const(symbol->const_value);
      break;
    case st_type:
      free_type(symbol->type_value);
      break;
    case st_var:
      free_var(symbol->var_value);
      break;
    case st_procedure:
      free_procedure(symbol->procedure_value);
      break;
    case st_function:
      free_function(symbol->function_value);
      break;
  }
  free(symbol);
}

void free_const(CONST_VALUE *const_value) {
  if (const_value == NULL) return;
  if (const_value->type == ct_type) free_type(const_value->type_value);
  free(const_value);
}

void free_type(TYPE_VALUE *type_value) {
  if (type_value == NULL) return;
  if (type_value->type == tt_array) free_type(type_value->sub_value);
  free(type_value);
}

void free_var(VAR_VALUE *var_value) {
  if (var_value == NULL) return;
  if (var_value->type == vt_type)
    free_type(var_value->detail);
  else if (var_value->type == vt_identifier)
    free(var_value->identifier);
  free(var_value);
}

void free_procedure(PROCEDURE_VALUE *procedure_value) {
  if (procedure_value == NULL) return;
  PARAM_LIST *temp = procedure_value->param_list;
  while (temp) {
    free(temp->name);
    free_var(temp->var_value);
    temp = temp->next;
  }
  free_icode(procedure_value->icode_list);
  free(procedure_value);
}

void free_function(FUNCTION_VALUE *function_value) {
  if (function_value == NULL) return;
  PARAM_LIST *temp = function_value->param_list;
  while (temp) {
    free(temp->name);
    free_var(temp->var_value);
    temp = temp->next;
  }
  free_var(function_value->return_var);
  free_icode(function_value->icode_list);
  free(function_value);
}
