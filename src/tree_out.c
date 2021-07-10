#include "tree_out.h"

#include <stdio.h>

void print_indent(int indent) {
  for (int i = 0; i < indent; i++) printf("\t");
}

void print_type(TYPE *type) {
  switch (type->type) {
    case tt_int:
      printf("int");
      break;
    case tt_real:
      printf("real");
      break;
    case tt_bool:
      printf("bool");
      break;
    case tt_array:
      printf("array[range:%d-%d, type:", type->array->array_start,
             type->array->array_end);
      print_type(type->array->sub_type);
      printf("]");
      break;
    case tt_identifier:
      printf("%s", type->identifier->name);
      break;
  }
}

void print_param_list(PARAM_LIST *param_list) {
  if (param_list == NULL) return;
  PARAM_LIST *temp = param_list;
  do {
    printf("%s: ", temp->id->name);
    print_type(temp->type);
    printf(", ");
    temp = temp->next;
  } while (temp);
}

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

void print_nop(NODE *node, int indent) {
  print_indent(indent);
  printf("Op: nop\n");
}

void print_const_declare(CONST_DECLARE *const_declare, int indent) {
  print_indent(indent);
  printf("Op: const_declare %s = ", const_declare->id->name);
  switch (const_declare->value->type) {
    case ct_int:
      printf("%ld", const_declare->value->num);
      break;
    case ct_real:
      printf("%lf", const_declare->value->real_num);
      break;
    case ct_bool:
      printf(const_declare->value->num ? "true" : "false");
      break;
    default:
      printf("error const!");
      break;
  }
  printf("\n");
}

void print_type_declare(TYPE_DECLARE *type_declare, int indent) {
  print_indent(indent);
  printf("Op: type_declare %s = ", type_declare->id->name);
  print_type(type_declare->type);
  printf("\n");
}

void print_var_declare(VAR_DECLARE *var_declare, int indent) {
  print_indent(indent);
  printf("Op: var_declare %s: ", var_declare->id->name);
  print_type(var_declare->type);
  printf("\n");
}

void print_procedure_declare(PROCEDURE_DECLARE *procedure_declare, int indent) {
  print_indent(indent);
  printf("Op: procedure_declare %s ( ", procedure_declare->id->name);
  print_param_list(procedure_declare->procedure->param_list);
  printf("):\n");
  NODE *temp = procedure_declare->procedure->node_list;
  do {
    print_node(temp, indent + 1);
    temp = temp->next;
  } while (temp != NULL);
}

void print_function_declare(FUNCTION_DECLARE *function_declare, int indent) {
  print_indent(indent);
  printf("Op: function_declare %s ( ", function_declare->id->name);
  print_param_list(function_declare->function->param_list);
  printf(") -> ");
  print_type(function_declare->function->return_type);
  printf(":\n");
  NODE *temp = function_declare->function->node_list;
  do {
    print_node(temp, indent + 1);
    temp = temp->next;
  } while (temp != NULL);
}

void print_assign(ASSIGN *assign, int indent) {
  print_indent(indent);
  printf("Op: assign\n");
  print_id_ref(assign->id_ref, indent + 1);
  print_indent(indent + 1);
  printf(":=\n");
  print_node(assign->expression, indent + 1);
}

void print_condition_jump(CONDITION_JUMP *condition_jump, int indent) {
  print_indent(indent);
  printf("Op: if\n");
  print_node(condition_jump->condition, indent + 2);
  print_indent(indent + 1);
  printf("then\n");
  NODE *temp = condition_jump->true;
  do {
    print_node(temp, indent + 2);
    temp = temp->next;
  } while (temp != NULL);
  if (condition_jump->false != NULL) {
    print_indent(indent + 1);
    printf("else\n");
    NODE *temp = condition_jump->false;
    do {
      print_node(temp, indent + 2);
      temp = temp->next;
    } while (temp != NULL);
  }
}

void print_function_call(FUNCTION_CALL *function_call, int indent) {
  print_indent(indent);
  printf("Op: call %s\n", function_call->id->name);
  if (function_call->args == NULL) return;
  print_indent(indent + 1);
  printf("(\n");
  NODE *temp = function_call->args;
  while (temp != NULL) {
    print_node(temp, indent + 2);
    print_indent(indent + 2);
    printf(",\n");
    temp = temp->next;
  }
  print_indent(indent + 1);
  printf(")\n");
}

void print_binary_operate(OPERATION op, BINARY_OPERATE *operation, int indent) {
  print_indent(indent);
  switch (op) {
    case op_while_do:
      printf("Op: while\n");
      print_node(operation->first, indent + 2);
      print_indent(indent + 1);
      printf("do\n");
      NODE *temp = operation->second;
      while (temp != NULL) {
        print_node(temp, indent + 2);
        temp = temp->next;
      }
      break;
    case op_le:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("<\n");
      print_node(operation->second, indent);
      break;
    case op_leq:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("<=\n");
      print_node(operation->second, indent);
      break;
    case op_ge:
      print_node(operation->first, 0);
      print_indent(indent);
      printf(">\n");
      print_node(operation->second, indent);
      break;
    case op_geq:
      print_node(operation->first, 0);
      print_indent(indent);
      printf(">=\n");
      print_node(operation->second, indent);
      break;
    case op_eq:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("==\n");
      print_node(operation->second, indent);
      break;
    case op_neq:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("!=\n");
      print_node(operation->second, indent);
      break;
      break;
    case op_plus:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("+\n");
      print_node(operation->second, indent);
      break;
    case op_minus:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("-\n");
      print_node(operation->second, indent);
      break;
    case op_times:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("*\n");
      print_node(operation->second, indent);
      break;
    case op_devide:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("/\n");
      print_node(operation->second, indent);
      break;
    case op_div:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("div\n");
      print_node(operation->second, indent);
      break;
    case op_mod:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("mod\n");
      print_node(operation->second, indent);
      break;
    case op_odd:
      printf("odd\n");
      print_node(operation->second, indent);
      break;
    case op_and:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("and\n");
      print_node(operation->second, indent);
      break;
    case op_or:
      print_node(operation->first, 0);
      print_indent(indent);
      printf("or\n");
      print_node(operation->second, indent);
      break;
    case op_not:
      printf("not\n");
      print_node(operation->second, indent);
      break;
  }
}

void print_id_ref(IDENTIFIER_REF *id_ref, int indent) {
  print_indent(indent);
  printf("%s\n", id_ref->id->name);
  ARRAY_OFFSET *temp = id_ref->offset;
  while (temp != NULL) {
    print_indent(indent);
    printf("[\n");
    print_node(temp->expression, indent + 1);
    print_indent(indent);
    printf("]\n");
    temp = temp->next;
  };
}

void print_const(CONST *const_value, int indent) {
  print_indent(indent);
  switch (const_value->type) {
    case ct_int:
      printf("%ld\n", const_value->num);
      break;
    case ct_real:
      printf("%lf\n", const_value->real_num);
      break;
    case ct_bool:
      printf("%s\n", const_value->num ? "true" : "false");
      break;
  }
}

void print_node(NODE *node, int indent) {
  if (node == NULL) return;
  switch (node->op) {
    case op_nop:
      print_nop(node, indent);
      break;
    case op_const_declare:
      print_const_declare(node->const_declare, indent);
      break;
    case op_type_declare:
      print_type_declare(node->type_declare, indent);
      break;
    case op_var_declare:
      print_var_declare(node->var_declare, indent);
      break;
    case op_procedure_declare:
      print_procedure_declare(node->procedure_declare, indent);
      break;
    case op_function_declare:
      print_function_declare(node->function_declare, indent);
      break;
    case op_assign:
      print_assign(node->assign, indent);
      break;
    case op_if_then:
    case op_if_then_else:
      print_condition_jump(node->condition_jump, indent);
      break;
    case op_call:
      print_function_call(node->function_call, indent);
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
    case op_devide:
    case op_div:
    case op_mod:
    case op_odd:
    case op_and:
    case op_or:
    case op_not:
      print_binary_operate(node->op, node->binary_operate, indent);
      break;
    case op_load_identifier:
      print_id_ref(node->id_ref, indent);
      break;
    case op_load_const:
      print_const(node->const_value, indent);
      break;
    case op_continue:
      print_indent(indent);
      printf("continue\n");
      break;
    case op_exit:
      print_indent(indent);
      printf("exit\n");
      break;
  }
}
