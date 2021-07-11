#ifndef __PLINF_OPCODE
#define __PLINF_OPCODE

#include <stdio.h>

#include "intermediate.h"

typedef enum {
  opcode_nop,
  opcode_const_declare,
  opcode_load_const,
} OPCODE;

extern int global_index;

void clear_index(void);
int current_index(void);
int next_index(void);

typedef enum { at_int, at_real, at_bool, at_str } ARG_TYPE;

typedef struct {
  ARG_TYPE type;
  union {
    long num;
    double real_num;
    const char *str;
  };
} ARG;

char *format_arg(ARG arg);
void output(FILE *fp, int index, OPCODE opcode, char *arg);
void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare);
void opout_node(FILE *fp, NODE *node);

#endif
