from typing import Optional
from enum import IntEnum, auto

class OPCODE(IntEnum):
    op_nop = 0
    op_const_declare = auto()
    op_type_declare = auto()
    op_var_declare = auto()
    op_procedure_declare = auto()
    op_function_declare = auto()
    op_param_declare = auto()
    op_build_array_type = auto()
    op_load_const = auto()
    op_load_fast = auto()
    op_block_start = auto()
    op_block_end = auto()
    op_unary_negative = auto()
    op_unary_not = auto()
    op_unary_odd = auto()
    op_binary_power = auto()
    op_binary_times = auto()
    op_binary_divide = auto()
    op_binary_floor_divide = auto()
    op_binary_modulo = auto()
    op_binary_plus = auto()
    op_binary_minus = auto()
    op_binary_subscr = auto()
    op_binary_and = auto()
    op_binary_or = auto()
    op_binary_compare = auto()
    op_store_fast = auto()
    op_jump = auto()
    op_jump_if_true = auto()
    op_jump_if_false = auto()
    op_call_function = auto()
    op_return_function = auto()

def get_tree(code: str) -> Optional[str]: ...
def get_opcode(code: str) -> Optional[str]: ...
