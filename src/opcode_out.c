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

TAG_LIST *tag_wait;
TAG_LIST *tag_ready;
OUTPUT_CACHE *output_cache;

void store_tag(int tag) {
  TAG_LIST *temp;
  temp = (TAG_LIST *)calloc(1, sizeof(TAG_LIST));
  temp->next = tag_wait;
  temp->tag = (TAG *)calloc(1, sizeof(TAG));
  temp->tag->id = tag;
  tag_wait = temp;
}

void fill_tag(int tag, ARG *value) {
  TAG_LIST *previous = NULL;
  TAG_LIST *temp = tag_wait;
  while (temp && temp->tag->id != tag) {
    previous = temp;
    temp = temp->next;
  }
  if (temp == NULL) return;
  if (previous == NULL)
    tag_wait = temp->next;
  else
    previous->next = temp->next;
  temp->tag->value = value;
  temp->next = tag_ready;
  tag_ready = temp;
  if (tag_wait == NULL) output_clear_cache();
}

ARG *pop_tag(int tag) {
  TAG_LIST *temp = tag_ready;
  while (temp && temp->tag->id != tag) {
    temp = temp->next;
  }
  if (temp == NULL) return (ARG *)NULL;
  ARG *result = temp->tag->value;
  return result;
}

char *format_arg(ARG *arg) {
  if (arg == NULL) return "null:";
  char *result = (char *)calloc(100, sizeof(char));
  switch (arg->type) {
    case at_int:
      sprintf(result, "int:%ld", arg->num);
      break;
    case at_real:
      sprintf(result, "real:%lf", arg->real_num);
      break;
    case at_bool:
      sprintf(result, "bool:%s", arg->num ? "true" : "false");
      break;
    case at_str:
      sprintf(result, "str:%s", arg->str);
      break;
    case at_type:
      sprintf(result, "type:%s", arg->str);
      break;
    case at_tag:
      free(result);
      result = format_arg(pop_tag(arg->num));
      break;
  }
  return result;
}

void output_clear_cache() {
  OUTPUT_CACHE *cache = output_cache;
  while (cache != NULL) {
    fprintf(cache->fp, "%d,%d,%s\n", cache->index, cache->opcode,
            format_arg(cache->arg));
    cache = cache->next;
    free(output_cache);
    output_cache = cache;
  }
}

void output(FILE *fp, int index, OPCODE opcode, ARG *arg) {
  char *result;
  if (arg == NULL)
    result = "null:";
  else if (arg->type == at_tag) {
    store_tag(arg->num);
  } else {
    result = format_arg(arg);
  }
  if (tag_wait != NULL) {
    OUTPUT_CACHE *temp = output_cache;
    OUTPUT_CACHE *cache = (OUTPUT_CACHE *)calloc(1, sizeof(OUTPUT_CACHE));
    cache->fp = fp;
    cache->index = index;
    cache->opcode = opcode;
    cache->arg = arg;
    while (temp && temp->next != NULL) {
      temp = temp->next;
    }
    if (temp == NULL)
      output_cache = cache;
    else
      temp->next = cache;
  } else {
    output_clear_cache();
    fprintf(fp, "%d,%d,%s\n", index, opcode, result);
  }
}

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

void opout_type(FILE *fp, TYPE *type) {
  ARG *temp;
  switch (type->type) {
    case tt_int:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_type;
      temp->str = "int";
      output(fp, next_index(), opcode_load_const, temp);
      break;
    case tt_real:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_type;
      temp->str = "real";
      output(fp, next_index(), opcode_load_const, temp);
      break;
    case tt_bool:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_type;
      temp->str = "bool";
      output(fp, next_index(), opcode_load_const, temp);
      break;
    case tt_identifier:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_type;
      temp->str = type->identifier->name;
      output(fp, next_index(), opcode_load_fast, temp);
      break;
    case tt_array:
      opout_type(fp, type->array->sub_type);
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_int;
      temp->num = type->array->array_end;
      output(fp, next_index(), opcode_load_const, temp);
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_int;
      temp->num = type->array->array_start;
      output(fp, next_index(), opcode_load_const, temp);
      output(fp, next_index(), opcode_build_array_type, (ARG *)NULL);
  }
}

void opout_const(FILE *fp, CONST *value) {
  ARG *temp;
  switch (value->type) {
    case ct_int:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_int;
      temp->num = value->num;
      break;
    case ct_real:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_real;
      temp->real_num = value->real_num;
      break;
    case ct_bool:
      temp = (ARG *)calloc(1, sizeof(ARG));
      temp->type = at_bool;
      temp->num = value->num;
      temp = &(ARG){.type = at_bool, .num = value->num};
      break;
  }
  output(fp, next_index(), opcode_load_const, temp);
}

void opout_identifier_ref(FILE *fp, IDENTIFIER_REF *id_ref) {
  ARG *temp;
  ARRAY_OFFSET *offset = id_ref->offset;
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = id_ref->id->name;
  output(fp, next_index(), opcode_load_fast, temp);
  if (offset != NULL) {
    while (offset->next != NULL) {
      opout_node(fp, offset->expression);
      output(fp, next_index(), opcode_binary_subscr, (ARG *)NULL);
      offset = offset->next;
    }
    opout_node(fp, offset->expression);
    output(fp, next_index(), opcode_binary_subscr, (ARG *)NULL);
  }
}

void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare) {
  ARG *temp;
  opout_const(fp, const_declare->value);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = const_declare->id->name;
  output(fp, next_index(), opcode_const_declare, temp);
}

void opout_type_declare(FILE *fp, TYPE_DECLARE *type_declare) {
  ARG *temp;
  opout_type(fp, type_declare->type);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = type_declare->id->name;
  output(fp, next_index(), opcode_type_declare, temp);
}

void opout_var_declare(FILE *fp, VAR_DECLARE *var_declare) {
  ARG *temp;
  opout_type(fp, var_declare->type);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = var_declare->id->name;
  output(fp, next_index(), opcode_var_declare, temp);
}

void opout_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare) {
  ARG *temp;
  output(fp, next_index(), opcode_block_start, (ARG *)NULL);
  NODE *node = procedure_declare->procedure->node_list;
  while (node != NULL) {
    opout_node(fp, node);
    node = node->next;
  }
  output(fp, next_index(), opcode_block_end, (ARG *)NULL);

  int param_count = 0;
  PARAM_LIST *param = procedure_declare->procedure->param_list;
  while (param != NULL) {
    opout_type(fp, param->type);
    temp = (ARG *)calloc(1, sizeof(ARG));
    temp->type = at_str;
    temp->str = param->id->name;
    output(fp, next_index(), opcode_param_declare, temp);
    param_count++;
    param = param->next;
  }
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = procedure_declare->id->name;
  output(fp, next_index(), opcode_load_const, temp);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = param_count;
  temp = &(ARG){.type = at_int, .num = param_count};
  output(fp, next_index(), opcode_procedure_declare, temp);
}

void opout_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare) {
  ARG *temp;
  output(fp, next_index(), opcode_block_start, (ARG *)NULL);
  NODE *node = function_declare->function->node_list;
  while (node != NULL) {
    opout_node(fp, node);
    node = node->next;
  }
  output(fp, next_index(), opcode_block_end, (ARG *)NULL);

  int param_count = 0;
  PARAM_LIST *param = function_declare->function->param_list;
  while (param != NULL) {
    opout_type(fp, param->type);
    temp = (ARG *)calloc(1, sizeof(ARG));
    temp->type = at_str;
    temp->str = param->id->name;
    output(fp, next_index(), opcode_param_declare, temp);
    param_count++;
    param = param->next;
  }
  opout_type(fp, function_declare->function->return_type);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = function_declare->id->name;
  output(fp, next_index(), opcode_load_const, temp);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = param_count;
  output(fp, next_index(), opcode_function_declare, temp);
}

void opout_assign(FILE *fp, ASSIGN *assign) {
  opout_node(fp, assign->expression);
  opout_identifier_ref(fp, assign->id_ref);
  output(fp, next_index(), opcode_store_fast, (ARG *)NULL);
}

void opout_condition_jump(FILE *fp, CONDITION_JUMP *condition_jump) {
  ARG *temp;
  opout_node(fp, condition_jump->condition);
  int if_entry = current_index() + 1;
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = if_entry + 2;
  output(fp, next_index(), opcode_jump_if_true, temp);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_tag;
  temp->num = if_entry;
  output(fp, next_index(), opcode_jump, temp);
  opout_node(fp, condition_jump->true);
  int true_finish = current_index() + 1;
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_tag;
  temp->num = true_finish;
  output(fp, next_index(), opcode_jump, temp);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = current_index() + 1;
  fill_tag(if_entry, temp);
  if (condition_jump->false != NULL) {
    opout_node(fp, condition_jump->false);
  }
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = current_index() + 1;
  fill_tag(true_finish, temp);
}

void opout_while_do(FILE *fp, BINARY_OPERATE *binary_operate) {
  ARG *temp;
  int condition_position = current_index() + 1;
  opout_node(fp, binary_operate->first);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_tag;
  temp->num = condition_position;
  output(fp, next_index(), opcode_jump_if_false, temp);
  opout_node(fp, binary_operate->second);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = condition_position;
  output(fp, next_index(), opcode_jump, temp);
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = current_index() + 1;
  fill_tag(condition_position, temp);
}

void opout_function_call(FILE *fp, FUNCTION_CALL *function_call) {
  ARG *temp;
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_str;
  temp->str = function_call->id->name;
  output(fp, next_index(), opcode_load_const, temp);
  int arg_count = 0;
  NODE *arg = function_call->args;
  while (arg != NULL) {
    opout_node(fp, arg);
    arg_count++;
    arg = arg->next;
  }
  temp = (ARG *)calloc(1, sizeof(ARG));
  temp->type = at_int;
  temp->num = arg_count;
  output(fp, next_index(), opcode_call_function, temp);
}

void opout_node(FILE *fp, NODE *node) {
  if (node == NULL) return;
  switch (node->op) {
    case op_nop:
      output(fp, next_index(), opcode_nop, (ARG *)NULL);
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
    case op_assign:
      opout_assign(fp, node->assign);
      break;
    case op_if_then:
    case op_if_then_else:
      opout_condition_jump(fp, node->condition_jump);
      break;
    case op_call:
      opout_function_call(fp, node->function_call);
      break;
    case op_while_do:
      opout_while_do(fp, node->binary_operate);
      break;
    case op_load_const:
      opout_const(fp, node->const_value);
      break;
    case op_load_identifier:
      opout_identifier_ref(fp, node->id_ref);
      break;
    default:
      fprintf(fp, "unknown opcode %d\n", node->op);
      break;
  }
}

void restart_opcode() {
  global_index = 0;
  tag_wait = NULL;
  tag_ready = NULL;
  output_cache = NULL;
}
