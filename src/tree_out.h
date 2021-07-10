#include "intermediate.h"

void print_indent(int indent);
void print_type(TYPE *type);
void print_param_list(PARAM_LIST *param_list);
void print_nop(NODE *node, int indent);
void print_const_declare(CONST_DECLARE *const_declare, int indent);
void print_type_declare(TYPE_DECLARE *type_declare, int indent);
void print_var_declare(VAR_DECLARE *var_declare, int indent);
void print_procedure_declare(PROCEDURE_DECLARE *procedure_declare, int indent);
void print_function_declare(FUNCTION_DECLARE *function_declare, int indent);
void print_assign(ASSIGN *assign, int indent);
void print_condition_jump(CONDITION_JUMP *condition_jump, int indent);
void print_function_call(FUNCTION_CALL *function_call, int indent);
void print_binary_operate(OPERATION op, BINARY_OPERATE *operation, int indent);
void print_id_ref(IDENTIFIER_REF *id_ref, int indent);
void print_const(CONST *const_value, int indent);
void print_node(NODE *node, int indent);
