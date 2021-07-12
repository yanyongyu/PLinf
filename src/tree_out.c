#include "tree_out.h"

#include <stdio.h>

void print_indent(FILE *fp, int indent) {
  for (int i = 0; i < indent; i++) fprintf(fp, "\t");
}

void print_type(FILE *fp, TYPE *type) {
  switch (type->type) {
    case tt_int:
      fprintf(fp, "int");
      break;
    case tt_real:
      fprintf(fp, "real");
      break;
    case tt_bool:
      fprintf(fp, "bool");
      break;
    case tt_array:
      fprintf(fp, "array[range:%d-%d, type:", type->array->array_start,
              type->array->array_end);
      print_type(fp, type->array->sub_type);
      fprintf(fp, "]");
      break;
    case tt_identifier:
      fprintf(fp, "%s", type->identifier->name);
      break;
  }
}

void print_param_list(FILE *fp, PARAM_LIST *param_list) {
  if (param_list == NULL) return;
  PARAM_LIST *temp = param_list;
  do {
    fprintf(fp, "%s: ", temp->id->name);
    print_type(fp, temp->type);
    fprintf(fp, ", ");
    temp = temp->next;
  } while (temp);
}

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

void print_nop(FILE *fp, NODE *node, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: nop\n");
}

void print_const_declare(FILE *fp, CONST_DECLARE *const_declare, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: const_declare %s = ", const_declare->id->name);
  switch (const_declare->value->type) {
    case ct_int:
      fprintf(fp, "%ld", const_declare->value->num);
      break;
    case ct_real:
      fprintf(fp, "%lf", const_declare->value->real_num);
      break;
    case ct_bool:
      fprintf(fp, const_declare->value->num ? "true" : "false");
      break;
    default:
      fprintf(fp, "error const!");
      break;
  }
  fprintf(fp, "\n");
}

void print_type_declare(FILE *fp, TYPE_DECLARE *type_declare, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: type_declare %s = ", type_declare->id->name);
  print_type(fp, type_declare->type);
  fprintf(fp, "\n");
}

void print_var_declare(FILE *fp, VAR_DECLARE *var_declare, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: var_declare %s: ", var_declare->id->name);
  print_type(fp, var_declare->type);
  fprintf(fp, "\n");
}

void print_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare,
                             int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: procedure_declare %s ( ", procedure_declare->id->name);
  print_param_list(fp, procedure_declare->procedure->param_list);
  fprintf(fp, "):\n");
  NODE *temp = procedure_declare->procedure->node_list;
  do {
    print_node(fp, temp, indent + 1);
    temp = temp->next;
  } while (temp != NULL);
}

void print_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare,
                            int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: function_declare %s ( ", function_declare->id->name);
  print_param_list(fp, function_declare->function->param_list);
  fprintf(fp, ") -> ");
  print_type(fp, function_declare->function->return_type);
  fprintf(fp, ":\n");
  NODE *temp = function_declare->function->node_list;
  do {
    print_node(fp, temp, indent + 1);
    temp = temp->next;
  } while (temp != NULL);
}

void print_assign(FILE *fp, ASSIGN *assign, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: assign\n");
  print_id_ref(fp, assign->id_ref, indent + 1);
  print_indent(fp, indent + 1);
  fprintf(fp, ":=\n");
  print_node(fp, assign->expression, indent + 1);
}

void print_condition_jump(FILE *fp, CONDITION_JUMP *condition_jump,
                          int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: if\n");
  print_node(fp, condition_jump->condition, indent + 2);
  print_indent(fp, indent + 1);
  fprintf(fp, "then\n");
  NODE *temp = condition_jump->true;
  do {
    print_node(fp, temp, indent + 2);
    temp = temp->next;
  } while (temp != NULL);
  if (condition_jump->false != NULL) {
    print_indent(fp, indent + 1);
    fprintf(fp, "else\n");
    NODE *temp = condition_jump->false;
    do {
      print_node(fp, temp, indent + 2);
      temp = temp->next;
    } while (temp != NULL);
  }
}

void print_function_call(FILE *fp, FUNCTION_CALL *function_call, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "Op: call %s\n", function_call->id->name);
  if (function_call->args == NULL) return;
  print_indent(fp, indent + 1);
  fprintf(fp, "(\n");
  NODE *temp = function_call->args;
  while (temp != NULL) {
    print_node(fp, temp, indent + 2);
    print_indent(fp, indent + 2);
    fprintf(fp, ",\n");
    temp = temp->next;
  }
  print_indent(fp, indent + 1);
  fprintf(fp, ")\n");
}

void print_binary_operate(FILE *fp, OPERATION op, BINARY_OPERATE *operation,
                          int indent) {
  print_indent(fp, indent);
  switch (op) {
    case op_while_do:
      fprintf(fp, "Op: while\n");
      print_node(fp, operation->first, indent + 2);
      print_indent(fp, indent + 1);
      fprintf(fp, "do\n");
      NODE *temp = operation->second;
      while (temp != NULL) {
        print_node(fp, temp, indent + 2);
        temp = temp->next;
      }
      break;
    case op_le:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "<\n");
      print_node(fp, operation->second, indent);
      break;
    case op_leq:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "<=\n");
      print_node(fp, operation->second, indent);
      break;
    case op_ge:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, ">\n");
      print_node(fp, operation->second, indent);
      break;
    case op_geq:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, ">=\n");
      print_node(fp, operation->second, indent);
      break;
    case op_eq:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "==\n");
      print_node(fp, operation->second, indent);
      break;
    case op_neq:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "!=\n");
      print_node(fp, operation->second, indent);
      break;
      break;
    case op_plus:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "+\n");
      print_node(fp, operation->second, indent);
      break;
    case op_minus:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "-\n");
      print_node(fp, operation->second, indent);
      break;
    case op_times:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "*\n");
      print_node(fp, operation->second, indent);
      break;
    case op_power:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "**\n");
      print_node(fp, operation->second, indent);
      break;
    case op_divide:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "/\n");
      print_node(fp, operation->second, indent);
      break;
    case op_div:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "div\n");
      print_node(fp, operation->second, indent);
      break;
    case op_mod:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "mod\n");
      print_node(fp, operation->second, indent);
      break;
    case op_odd:
      fprintf(fp, "odd\n");
      print_node(fp, operation->second, indent);
      break;
    case op_and:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "and\n");
      print_node(fp, operation->second, indent);
      break;
    case op_or:
      print_node(fp, operation->first, 0);
      print_indent(fp, indent);
      fprintf(fp, "or\n");
      print_node(fp, operation->second, indent);
      break;
    case op_not:
      fprintf(fp, "not\n");
      print_node(fp, operation->second, indent);
      break;
  }
}

void print_id_ref(FILE *fp, IDENTIFIER_REF *id_ref, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "%s\n", id_ref->id->name);
  ARRAY_OFFSET *temp = id_ref->offset;
  while (temp != NULL) {
    print_indent(fp, indent);
    fprintf(fp, "[\n");
    print_node(fp, temp->expression, indent + 1);
    print_indent(fp, indent);
    fprintf(fp, "]\n");
    temp = temp->next;
  };
}

void print_const(FILE *fp, CONST *const_value, int indent) {
  print_indent(fp, indent);
  switch (const_value->type) {
    case ct_int:
      fprintf(fp, "%ld\n", const_value->num);
      break;
    case ct_real:
      fprintf(fp, "%lf\n", const_value->real_num);
      break;
    case ct_bool:
      fprintf(fp, "%s\n", const_value->num ? "true" : "false");
      break;
  }
}

void print_node(FILE *fp, NODE *node, int indent) {
  if (node == NULL) return;
  switch (node->op) {
    case op_nop:
      print_nop(fp, node, indent);
      break;
    case op_const_declare:
      print_const_declare(fp, node->const_declare, indent);
      break;
    case op_type_declare:
      print_type_declare(fp, node->type_declare, indent);
      break;
    case op_var_declare:
      print_var_declare(fp, node->var_declare, indent);
      break;
    case op_procedure_declare:
      print_procedure_declare(fp, node->procedure_declare, indent);
      break;
    case op_function_declare:
      print_function_declare(fp, node->function_declare, indent);
      break;
    case op_assign:
      print_assign(fp, node->assign, indent);
      break;
    case op_if_then:
    case op_if_then_else:
      print_condition_jump(fp, node->condition_jump, indent);
      break;
    case op_call:
      print_function_call(fp, node->function_call, indent);
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
    case op_power:
    case op_divide:
    case op_div:
    case op_mod:
    case op_odd:
    case op_and:
    case op_or:
    case op_not:
      print_binary_operate(fp, node->op, node->binary_operate, indent);
      break;
    case op_load_identifier:
      print_id_ref(fp, node->id_ref, indent);
      break;
    case op_load_const:
      print_const(fp, node->const_value, indent);
      break;
    case op_continue:
      print_indent(fp, indent);
      fprintf(fp, "continue\n");
      break;
    case op_exit:
      print_indent(fp, indent);
      fprintf(fp, "exit\n");
      break;
  }
}
