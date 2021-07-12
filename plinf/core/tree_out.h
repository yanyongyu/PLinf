#include <stdio.h>

#include "intermediate.h"

void print_indent(FILE *fp, int indent);
void print_type(FILE *fp, TYPE *type);
void print_param_list(FILE *fp, PARAM_LIST *param_list);
void print_nop(FILE *fp, NODE *node, int indent);
void print_const_declare(FILE *fp, CONST_DECLARE *const_declare, int indent);
void print_type_declare(FILE *fp, TYPE_DECLARE *type_declare, int indent);
void print_var_declare(FILE *fp, VAR_DECLARE *var_declare, int indent);
void print_procedure_declare(FILE *fp, PROCEDURE_DECLARE *procedure_declare,
                             int indent);
void print_function_declare(FILE *fp, FUNCTION_DECLARE *function_declare,
                            int indent);
void print_assign(FILE *fp, ASSIGN *assign, int indent);
void print_condition_jump(FILE *fp, CONDITION_JUMP *condition_jump, int indent);
void print_function_call(FILE *fp, FUNCTION_CALL *function_call, int indent);
void print_binary_operate(FILE *fp, OPERATION op, BINARY_OPERATE *operation,
                          int indent);
void print_id_ref(FILE *fp, IDENTIFIER_REF *id_ref, int indent);
void print_const(FILE *fp, CONST *const_value, int indent);
void print_node(FILE *fp, NODE *node, int indent);
