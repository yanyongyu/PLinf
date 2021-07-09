#include <stdarg.h>
#include <stdio.h>

#include "intermediate.c"
#include "plinf.tab.c"
#include "plinf.yy.c"

void printf_with_indent(NODE *node, int indent) {
  for (int i = 0; i < indent; i++) printf("\t");
  switch (node->op) {
    case op_nop:
      printf("Operation: nop\n");
      break;
    case op_const_declare:
      printf("Operation: const_declare %s = ", node->const_declare->id->name);
      switch (node->const_declare->value->type) {
        case ct_int:
          printf("%d", node->const_declare->value->num);
          break;
        case ct_real:
          printf("%lf", node->const_declare->value->real_num);
          break;
        case ct_bool:
          printf(node->const_declare->value->num ? "true" : "false");
          break;
        default:
          printf("error const!");
          break;
      }
      printf("\n");
      break;
    case op_type_declare:
      printf("Operation: type_declare %s = ", node->type_declare->id->name);
      switch (node->type_declare->type->type) {
        case tt_int:
          printf("int");
          break;
        case tt_real:
          printf("real");
          break;
        case tt_bool:
          printf("bool");
        case tt_array:
          printf("array");
          break;
        case tt_identifier:
          printf("%s", node->type_declare->type->identifier->name);
          break;
      }
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
    do {
      printf_with_indent(node, 0);
      node = free_icode(node);
    } while (node);
  } else {
    printf("Error parsing %d\n", success);
  }
  return 0;
}
