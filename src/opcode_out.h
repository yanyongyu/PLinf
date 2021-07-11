#ifndef __PLINF_OPCODE
#define __PLINF_OPCODE

#include <stdio.h>

#include "intermediate.h"

typedef enum {
  /* do nothing */
  opcode_nop,
  /* declare a const variable
   * arg: const name
   * tos: const value
   */
  opcode_const_declare,
  /* declare a type variable
   * arg: type name
   * tos: type
   */
  opcode_type_declare,
  /* declare a variable with type
   * arg: var name
   * tos: var type
   */
  opcode_var_declare,
  /* declare a procedure
   * arg: param count n
   * tos: procedure name
   * tos1~n: params
   * tosn+1: block object
   */
  opcode_procedure_declare,
  /* declare a function
   * arg: param count n
   * tos: function name
   * tos1: function return type
   * tos2~n+1: params
   * tosn+2: block object
   */
  opcode_function_declare,
  /* declare a procedure or function param
   * push param object back onto stack
   * arg: param name
   * tos: param type
   */
  opcode_param_declare,
  /* build array type and push type onto stack
   * tos: array start index
   * tos1: array end index
   * tos2: array arg type
   */
  opcode_build_array_type,
  /* push const value onto stack */
  opcode_load_const,
  /* consume that the following opcodes all in one block
   * do not run opcodes in block
   */
  opcode_block_start,
  /* pop all opcodes in block and push a block object onto stack */
  opcode_block_end,
} OPCODE;

extern int global_index;

void clear_index(void);
int current_index(void);
int next_index(void);

typedef enum { at_int, at_real, at_bool, at_str, at_type } ARG_TYPE;

typedef struct {
  ARG_TYPE type;
  union {
    long num;         // int, bool
    double real_num;  // real
    const char *str;  // string, type
  };
} ARG;

char *format_arg(ARG arg);
void output(FILE *fp, int index, OPCODE opcode, char *arg);
void opout_type(FILE *fp, TYPE *type);
void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare);
void opout_type_declare(FILE *fp, TYPE_DECLARE *type_declare);
void opout_var_declare(FILE *fp, VAR_DECLARE *var_declare);
void opout_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare);
void opout_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare);
void opout_node(FILE *fp, NODE *node);

#endif
