#ifndef __PLINF_INTERMEDIATE
#define __PLINF_INTERMEDIATE

struct type;
struct identifier;
struct node;

// 操作类型
typedef enum {
  op_nop,
  op_const_declare,
  op_type_declare,
  op_var_declare,
  op_procedure_declare,
  op_function_declare,
  op_assign,
  op_if_then,
  op_if_then_else,
  op_while_do,
  op_continue,
  op_exit,
  op_call,
  op_le,
  op_leq,
  op_ge,
  op_geq,
  op_eq,
  op_neq,
  op_plus,
  op_minus,
  op_times,
  op_devide,
  op_div,
  op_mod,
  op_odd,
  op_and,
  op_or,
  op_not,
  op_load_const,
  op_load_identifier
} OPERATION;

// 类型类型
typedef enum { tt_int, tt_real, tt_bool, tt_array, tt_identifier } TYPE_TYPE;

typedef struct array_info {
  int array_start;
  int array_end;
  struct type *sub_type;
} ARRAY_INFO;

// 类型结构
typedef struct type {
  TYPE_TYPE type;
  union {
    ARRAY_INFO *array;
    struct identifier *identifier;
  };
} TYPE;

// 常量类型
typedef enum { ct_int, ct_real, ct_bool, ct_type } CONST_TYPE;

// 常量结构
typedef struct const_value {
  CONST_TYPE type;
  union {
    long num;
    double real_num;
    TYPE *type;
  };
} CONST;

// 标识符类型
typedef enum { it_identifier, it_temp } ID_TYPE;

// 标识符结构
typedef struct identifier {
  ID_TYPE type;
  char *name;
} IDENTIFIER;

// 变量引用
typedef struct array_offset {
  struct array_offset *next;
  struct node *expression;
} ARRAY_OFFSET;

typedef struct identifier_ref {
  IDENTIFIER *id;
  ARRAY_OFFSET *offset;
} IDENTIFIER_REF;

// 变量链表
typedef struct var_list {
  struct var_list *next;
  IDENTIFIER *id;
} VAR_LIST;

// 参数声明链表
typedef struct param_list {
  struct param_list *next;
  IDENTIFIER *id;
  TYPE *type;
} PARAM_LIST;

// 参数链表
typedef struct arg_list {
  struct arg_list *next;
  IDENTIFIER_REF *id_ref;
} ARG_LIST;

// 过程结构
typedef struct procedure {
  PARAM_LIST *param_list;
  struct node *node_list;
} PROCEDURE;

// 函数结构
typedef struct function {
  PARAM_LIST *param_list;
  TYPE *return_type;
  struct node *node_list;
} FUNCTION;

/****************************************************
 *                                                  *
 *                       NODES                      *
 *                                                  *
 ****************************************************/

typedef struct const_declare {
  IDENTIFIER *id;
  CONST *value;
} CONST_DECLARE;

typedef struct type_declare {
  IDENTIFIER *id;
  TYPE *type;
} TYPE_DECLARE;

typedef struct var_declare {
  IDENTIFIER *id;
  TYPE *type;
} VAR_DECLARE;

typedef struct procedure_declare {
  IDENTIFIER *id;
  PROCEDURE *procedure;
} PROCEDURE_DECLARE;

typedef struct function_declare {
  IDENTIFIER *id;
  FUNCTION *function;
} FUNCTION_DECLARE;

typedef struct assign {
  IDENTIFIER_REF *id_ref;
  struct node *expression;
} ASSIGN;

typedef struct binary_operate {
  struct node *first;
  struct node *second;
} BINARY_OPERATE;

typedef struct condition_jump {
  struct node *condition;
  struct node * true;
  struct node * false;
} CONDITION_JUMP;

typedef struct function_call {
  IDENTIFIER *id;
  struct node *args;
} FUNCTION_CALL;

typedef struct node {
  struct node *next;
  OPERATION op;
  union {
    CONST_DECLARE *const_declare;
    TYPE_DECLARE *type_declare;
    VAR_DECLARE *var_declare;
    PROCEDURE_DECLARE *procedure_declare;
    FUNCTION_DECLARE *function_declare;
    ASSIGN *assign;
    BINARY_OPERATE *binary_operate;

    IDENTIFIER_REF *id_ref;
    CONST *const_value;
    CONDITION_JUMP *condition_jump;
    FUNCTION_CALL *function_call;
  };
} NODE;

NODE *free_node(NODE *node);
void free_const_declare(CONST_DECLARE *);
void free_type_declare(TYPE_DECLARE *);
void free_var_declare(VAR_DECLARE *);
void free_procedure_declare(PROCEDURE_DECLARE *);
void free_function_declare(FUNCTION_DECLARE *);

#endif
