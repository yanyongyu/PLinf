#include <stdio.h>

#include "intermediate.c"
#include "plinf.tab.c"
#include "plinf.yy.c"

int stringify_symbol(SYMBOL *symbol) {
  if (symbol == NULL) return -1;
  return symbol->type;
}

int main(int argc, char *argv[]) {
  FILE *f;
  int success;
  ICODE *node;
  f = fopen(argv[1], "r");
  yyset_in(f);
  success = yyparse();
  if (success == 0) {
    node = global_result;
    do {
      printf(
          "Index: %d\tOperation: %d\t Symbol1: %d\tSymbol2: %d\tSymbol3: %d\n",
          node->index, node->op, stringify_symbol(node->symbol[0]),
          stringify_symbol(node->symbol[1]), stringify_symbol(node->symbol[2]));
      node = free_icode(node);
    } while (node);
  } else {
    printf("Error parsing %d\n", success);
  }
  return 0;
}
