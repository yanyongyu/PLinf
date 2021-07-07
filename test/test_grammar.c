#include <stdio.h>

#include "plinf.tab.c"
#include "plinf.yy.c"

int main(int argc, char *argv[]) {
  FILE *f;
  f = fopen(argv[1], "r");
  yyset_in(f);
  yyparse();
  return 0;
}
