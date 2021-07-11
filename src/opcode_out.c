#include "opcode_out.h"

#include <stdio.h>
#include <stdlib.h>

#include "intermediate.h"

/****************************************************
 *                                                  *
 *                       INDEX                      *
 *                                                  *
 ****************************************************/

int global_index = 0;

void clear_index(void) { global_index = 0; }

int current_index(void) { return global_index; }

int next_index(void) {
  global_index++;
  return global_index;
}

/****************************************************
 *                                                  *
 *                      OUTPUT                      *
 *                                                  *
 ****************************************************/

char *format_arg(ARG arg) {
  char *result = (char *)calloc(100, sizeof(char));
  switch (arg.type) {
    case at_int:
      sprintf(result, "int:%ld", arg.num);
      break;
    case at_real:
      sprintf(result, "real:%lf", arg.real_num);
      break;
    case at_bool:
      sprintf(result, "bool:%s", arg.num ? "true" : "false");
      break;
    case at_str:
      sprintf(result, "str:%s", arg.str);
      break;
  }
  return result;
}

void output(FILE *fp, int index, OPCODE opcode, char *arg) {
  fprintf(fp, "%d,%d,%s\n", index, opcode, arg == NULL ? "null:" : arg);
}

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare) {
  ARG temp;
  switch (const_declare->value->type) {
    case ct_int:
      temp = (ARG){.type = at_int, .num = const_declare->value->num};
      break;
    case ct_real:
      temp = (ARG){.type = at_real, .real_num = const_declare->value->real_num};
      break;
    case ct_bool:
      temp = (ARG){.type = at_bool, .num = const_declare->value->num};
      break;
  }
  output(fp, next_index(), opcode_load_const, format_arg(temp));
  temp = (ARG){.type = at_str, .str = const_declare->id->name};
  output(fp, next_index(), opcode_const_declare, format_arg(temp));
}

void opout_node(FILE *fp, NODE *node) {
  if (node == NULL) return;
  switch (node->op) {
    case op_nop:
      output(fp, next_index(), opcode_nop, (char *)NULL);
      break;
    case op_const_declare:
      opout_const_declare(fp, node->const_declare);
      break;
    default:
      break;
  }
}
