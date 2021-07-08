// 操作类型
typedef enum {
  op_nop,
  op_const_declare,
  op_type_declare,
  op_var_declare,
  op_procedure_declare,
  op_function_declare
} OPERATION;

// 常量类型
typedef enum { ct_int, ct_real, ct_bool, ct_type } CONST_TYPE;

// 常量结构
typedef struct const_value {
  CONST_TYPE type;
  union {
    long num;
    double real_num;
    TYPE_VALUE *type_value;
  };
} CONST_VALUE;

// 类型类型
typedef enum { tt_int, tt_real, tt_bool, tt_array } TYPE_TYPE;

// 类型结构
typedef struct type_value {
  TYPE_TYPE type;
  int array_start;
  int array_end;
  TYPE_VALUE *sub_value;
} TYPE_VALUE;

// 变量类型
typedef enum { vt_type, vt_identifier } VAR_TYPE;

// 变量结构
typedef struct var_value {
  VAR_TYPE type;
  union {
    TYPE_VALUE *detail;
    char *identifier;
  };
} VAR_VALUE;

// 变量链表
typedef struct id_list {
  ID_LIST *next;
  char *name;
} ID_LIST;

// 参数链表
typedef struct param_list {
  PARAM_LIST *next;
  char *name;
  VAR_VALUE *var_value;
} PARAM_LIST;

// 过程结构
typedef struct procedure_value {
  PARAM_LIST *param_list;
  ICODE icode_list;
} PROCEDURE_VALUE;

// 函数结构
typedef struct function_value {
  PARAM_LIST *param_list;
  VAR_VALUE *return_var;
  ICODE icode_list;
} FUNCTION_VALUE;

// 符号类型
typedef enum {
  st_identifier,
  st_const,
  st_type,
  st_var,
  st_procedure,
  st_function
} SYMBOL_TYPE;

// 符号结构
typedef struct symbol {
  SYMBOL_TYPE type;
  union {
    char *identifier;
    CONST_VALUE *const_value;
    TYPE_VALUE *type_value;
    VAR_VALUE *var_value;
    PROCEDURE_VALUE *procedure_value;
    FUNCTION_VALUE *function_value;
  };
} SYMBOL;

typedef struct icode {
  ICODE *next;
  int index;
  OPERATION op;
  SYMBOL *symbol[3];
} ICODE;
