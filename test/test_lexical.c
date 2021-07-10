#include <stdio.h>

#include "plinf.tab.h"

extern int yylex(void);

int main() {
  int token;
  while (token = yylex()) {
    printf("token = %d\n", token);
  }
  return 0;
}
