#include <stdio.h>

#include "intermediate.h"
#include "plinf.tab.h"

extern NODE *global_result;
extern void yyset_in(FILE *);

void print_node(NODE *, int);
void print_id_ref(IDENTIFIER_REF *, int);

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
  printf("Operation: nop\n");
}

void print_const_declare(CONST_DECLARE *const_declare, int indent) {
  print_indent(indent);
  printf("Operation: const_declare %s = ", const_declare->id->name);
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
  printf("Operation: type_declare %s = ", type_declare->id->name);
  print_type(type_declare->type);
  printf("\n");
}

void print_var_declare(VAR_DECLARE *var_declare, int indent) {
  print_indent(indent);
  printf("Operation: var_declare %s: ", var_declare->id->name);
  print_type(var_declare->type);
  printf("\n");
}

void print_procedure_declare(PROCEDURE_DECLARE *procedure_declare, int indent) {
  print_indent(indent);
  printf("Operation: procedure_declare %s ( ", procedure_declare->id->name);
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
  printf("Operation: function_declare %s ( ", function_declare->id->name);
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
  printf("Operation: assign\n");
  print_id_ref(assign->id_ref, indent + 1);
  print_indent(indent + 1);
  printf(":=\n");
  print_node(assign->expression, indent + 1);
}

void print_condition_jump(CONDITION_JUMP *condition_jump, int indent) {}

void print_function_call(FUNCTION_CALL *function_call, int indent) {}

void print_binary_operate(BINARY_OPERATE *operation, int indent) {}

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
    case op_load_identifier:
      print_id_ref(node->id_ref, indent);
      break;
    case op_load_const:
      print_const(node->const_value, indent);
      break;
  }
}

int main(int argc, char *argv[]) {
  FILE *f;
  int success;
  NODE *node;
  f = fopen(argv[1], "r");
  yyset_in(f);
  success = yyparse();
  if (success == 0) {
    node = global_result;
    if (node == NULL) {
      printf("Error parsing: no result\n");
      return 0;
    }
    do {
      print_node(node, 0);
      node = free_node(node);
    } while (node);
  } else {
    printf("Error parsing %d\n", success);
  }
  return 0;
}
