#include <stdio.h>

#include "intermediate.h"
#include "opcode_out.h"
#include "plinf.tab.h"

extern NODE *global_result;
extern void yyset_in(FILE *);

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
      opout_node(stdout, node);
      node = free_node(node);
    } while (node);
  } else {
    printf("Error parsing %d\n", success);
  }
  return 0;
}
