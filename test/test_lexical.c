#include <stdio.h>

#include "plinf.tab.c"
#include "plinf.yy.c"

int main() {
  int token;
  while (token = yylex()) {
    printf("token = %d\n", token);
  }
  return 0;
}
