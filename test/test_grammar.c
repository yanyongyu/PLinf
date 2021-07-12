#include <stdio.h>

#include "intermediate.h"
#include "plinf.tab.h"
#include "tree_out.h"

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
      fprintf(stderr, "Error parsing: no result\n");
      return 0;
    }
    do {
      print_node(stdout, node, 0);
      node = free_node(node);
    } while (node);
  } else {
    fprintf(stderr, "Error parsing %d\n", success);
  }
  return 0;
}
