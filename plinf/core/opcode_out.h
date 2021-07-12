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
  /* push a variable onto stack
   * arg: var name
   */
  opcode_load_fast,
  /* consume that the following opcodes all in one block
   * do not run opcodes in block
   */
  opcode_block_start,
  /* pop all opcodes in block and push a block object onto stack */
  opcode_block_end,
  /* tos = -tos */
  opcode_unary_negative,
  /* tos = not tos */
  opcode_unary_not,
  /* tos = odd(tos) */
  opcode_unary_odd,
  /* tos = tos1 ** tos */
  opcode_binary_power,
  /* tos = tos1 * tos */
  opcode_binary_times,
  /* tos = tos1 / tos */
  opcode_binary_divide,
  /* tos = tos1 // tos */
  opcode_binary_floor_divide,
  /* tos = tos1 % tos */
  opcode_binary_modulo,
  /* tos = tos1 + tos */
  opcode_binary_plus,
  /* tos = tos1 - tos */
  opcode_binary_minus,
  /* tos = tos1[tos]*/
  opcode_binary_subscr,
  /* tos = tos1 and tos */
  opcode_binary_and,
  /* tos = tos1 or tos */
  opcode_binary_or,
  /* tos = tos1 op tos
   * arg: op
   */
  opcode_binary_compare,
  /* store value to variable
   * tos: var name
   * tos1: valeu to store
   */
  opcode_store_fast,
  /* jump anyway */
  opcode_jump,
  /* jump if true
   * tos: condition
   */
  opcode_jump_if_true,
  /* jump if false
   * tos: condition
   */
  opcode_jump_if_false,
  /* call function, store current operation index for jump back
   * jump to function block start
   * push new variable scope
   * predeclare param and return variables
   * arg: param count n
   * tos0~n-1: params
   * tosn: function name
   */
  opcode_call_function,
  /* return function, jump back to where function was called
   * push return variable onto stack
   * pop latest variable scope
   */
  opcode_return_function,
} OPCODE;

extern int global_index;

int current_index(void);
int next_index(void);

typedef enum { at_int, at_real, at_bool, at_str, at_type, at_tag } ARG_TYPE;

typedef struct {
  ARG_TYPE type;
  union {
    long num;         // int, bool, tag
    double real_num;  // real
    const char *str;  // string, type
  };
} ARG;

typedef struct {
  int id;
  ARG *value;
} TAG;

typedef struct tag_list {
  struct tag_list *next;
  TAG *tag;
} TAG_LIST;

typedef struct output_cache {
  struct output_cache *next;
  FILE *fp;
  int index;
  OPCODE opcode;
  ARG *arg;
} OUTPUT_CACHE;

typedef struct loop_stack {
  struct loop_stack *next;
  int tag_id;
} LOOP_STACK;

void store_tag(int tag);
void fill_tag(int tag, ARG *value);
ARG *pop_tag(int tag);
char *format_arg(ARG *arg);
void output_clear_cache(void);
void output(FILE *fp, int index, OPCODE opcode, ARG *arg);
void opout_type(FILE *fp, TYPE *type);
void opout_const(FILE *fp, CONST *value);
void opout_identifier_ref(FILE *fp, IDENTIFIER_REF *id_ref);
void opout_const_declare(FILE *fp, CONST_DECLARE *const_declare);
void opout_type_declare(FILE *fp, TYPE_DECLARE *type_declare);
void opout_var_declare(FILE *fp, VAR_DECLARE *var_declare);
void opout_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare);
void opout_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare);
void opout_assign(FILE *fp, ASSIGN *assign);
void opout_condition_jump(FILE *fp, CONDITION_JUMP *condition_jump);
void opout_node(FILE *fp, NODE *node);

void restart_opcode(void);

#endif
