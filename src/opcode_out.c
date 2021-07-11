#include "opcode_out.h"

#include <stdio.h>
#include <stdlib.h>

#include "intermediate.h"

/****************************************************
 *                                                  *
 *                       INDEX                      *
 *                                                  *
 ****************************************************/

int global_index = 0;

void clear_index(void) { global_index = 0; }

int current_index(void) { return global_index; }

int next_index(void) {
  global_index++;
  return global_index;
}

/****************************************************
 *                                                  *
 *                      OUTPUT                      *
 *                                                  *
 ****************************************************/

char *format_arg(ARG arg) {
  char *result = (char *)calloc(100, sizeof(char));
  switch (arg.type) {
    case at_int:
      sprintf(result, "int:%ld", arg.num);
      break;
    case at_real:
      sprintf(result, "real:%lf", arg.real_num);
      break;
    case at_bool:
      sprintf(result, "bool:%s", arg.num ? "true" : "false");
      break;
    case at_str:
      sprintf(result, "str:%s", arg.str);
      break;
    case at_type:
      sprintf(result, "type:%s", arg.str);
      break;
  }
  return result;
}

void output(FILE *fp, int index, OPCODE opcode, char *arg) {
  fprintf(fp, "%d,%d,%s\n", index, opcode, arg == NULL ? "null:" : arg);
}

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

void opout_type(FILE *fp, TYPE *type) {
  ARG temp;
  switch (type->type) {
    case tt_int:
      temp = (ARG){.type = at_type, .str = "int"};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      break;
    case tt_real:
      temp = (ARG){.type = at_type, .str = "real"};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      break;
    case tt_bool:
      temp = (ARG){.type = at_type, .str = "bool"};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      break;
    case tt_identifier:
      temp = (ARG){.type = at_str, .str = type->identifier->name};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      break;
    case tt_array:
      opout_type(fp, type->array->sub_type);
      temp = (ARG){.type = at_int, .num = type->array->array_end};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      temp = (ARG){.type = at_int, .num = type->array->array_start};
      output(fp, next_index(), opcode_load_const, format_arg(temp));
      output(fp, next_index(), opcode_build_array_type, (char *)NULL);
  }
}

void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare) {
  ARG temp;
  switch (const_declare->value->type) {
    case ct_int:
      temp = (ARG){.type = at_int, .num = const_declare->value->num};
      break;
    case ct_real:
      temp = (ARG){.type = at_real, .real_num = const_declare->value->real_num};
      break;
    case ct_bool:
      temp = (ARG){.type = at_bool, .num = const_declare->value->num};
      break;
  }
  output(fp, next_index(), opcode_load_const, format_arg(temp));
  temp = (ARG){.type = at_str, .str = const_declare->id->name};
  output(fp, next_index(), opcode_const_declare, format_arg(temp));
}

void opout_type_declare(FILE *fp, TYPE_DECLARE *type_declare) {
  ARG temp;
  opout_type(fp, type_declare->type);
  temp = (ARG){.type = at_str, .str = type_declare->id->name};
  output(fp, next_index(), opcode_type_declare, format_arg(temp));
}

void opout_var_declare(FILE *fp, VAR_DECLARE *var_declare) {
  ARG temp;
  opout_type(fp, var_declare->type);
  temp = (ARG){.type = at_str, .str = var_declare->id->name};
  output(fp, next_index(), opcode_var_declare, format_arg(temp));
}

void opout_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare) {
  ARG temp;
  output(fp, next_index(), opcode_block_start, (char *)NULL);
  NODE *node = procedure_declare->procedure->node_list;
  while (node != NULL) {
    opout_node(fp, node);
    node = node->next;
  }
  output(fp, next_index(), opcode_block_end, (char *)NULL);

  int param_count = 0;
  PARAM_LIST *param = procedure_declare->procedure->param_list;
  while (param != NULL) {
    opout_type(fp, param->type);
    temp = (ARG){.type = at_str, .str = param->id->name};
    output(fp, next_index(), opcode_param_declare, format_arg(temp));
    param_count++;
    param = param->next;
  }
  temp = (ARG){.type = at_str, .str = procedure_declare->id->name};
  output(fp, next_index(), opcode_load_const, format_arg(temp));
  temp = (ARG){.type = at_int, .num = param_count};
  output(fp, next_index(), opcode_procedure_declare, format_arg(temp));
}

void opout_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare) {
  ARG temp;
  output(fp, next_index(), opcode_block_start, (char *)NULL);
  NODE *node = function_declare->function->node_list;
  while (node != NULL) {
    opout_node(fp, node);
    node = node->next;
  }
  output(fp, next_index(), opcode_block_end, (char *)NULL);

  int param_count = 0;
  PARAM_LIST *param = function_declare->function->param_list;
  while (param != NULL) {
    opout_type(fp, param->type);
    temp = (ARG){.type = at_str, .str = param->id->name};
    output(fp, next_index(), opcode_param_declare, format_arg(temp));
    param_count++;
    param = param->next;
  }
  opout_type(fp, function_declare->function->return_type);
  temp = (ARG){.type = at_str, .str = function_declare->id->name};
  output(fp, next_index(), opcode_load_const, format_arg(temp));
  temp = (ARG){.type = at_int, .num = param_count};
  output(fp, next_index(), opcode_function_declare, format_arg(temp));
}

void opout_node(FILE *fp, NODE *node) {
  if (node == NULL) return;
  switch (node->op) {
    case op_nop:
      output(fp, next_index(), opcode_nop, (char *)NULL);
      break;
    case op_const_declare:
      opout_const_declare(fp, node->const_declare);
      break;
    case op_type_declare:
      opout_type_declare(fp, node->type_declare);
      break;
    case op_var_declare:
      opout_var_declare(fp, node->var_declare);
      break;
    case op_procedure_declare:
      opout_procedure_declare(fp, node->procedure_declare);
      break;
    case op_function_declare:
      opout_function_declare(fp, node->function_declare);
      break;
    default:
      break;
  }
}
