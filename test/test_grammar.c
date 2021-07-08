#include <stdio.h>

#include "plinf.tab.c"
#include "plinf.yy.c"

int main(int argc, char *argv[]) {
  int success;
  FILE *f;
  f = fopen(argv[1], "r");
  yyset_in(f);
  success = yyparse();
  if (success == 0) {
    do {
      printf("\n");
    } while (global_result->next);
  } else {
    printf("Error parsing %d\n", success);
  }
  return 0;
}
