from typing import Optional
from enum import IntEnum, auto

class OPCODE(IntEnum):
    opcode_nop = 0
    opcode_const_declare = auto()
    opcode_type_declare = auto()
    opcode_var_declare = auto()
    opcode_procedure_declare = auto()
    opcode_function_declare = auto()
    opcode_param_declare = auto()
    opcode_build_array_type = auto()
    opcode_load_const = auto()
    opcode_load_fast = auto()
    opcode_block_start = auto()
    opcode_block_end = auto()
    opcode_unary_negative = auto()
    opcode_unary_not = auto()
    opcode_unary_odd = auto()
    opcode_binary_power = auto()
    opcode_binary_times = auto()
    opcode_binary_divide = auto()
    opcode_binary_floor_divide = auto()
    opcode_binary_modulo = auto()
    opcode_binary_plus = auto()
    opcode_binary_minus = auto()
    opcode_binary_subscr = auto()
    opcode_binary_and = auto()
    opcode_binary_or = auto()
    opcode_binary_compare = auto()
    opcode_store_fast = auto()
    opcode_store_subscr = auto()
    opcode_jump = auto()
    opcode_jump_if_true = auto()
    opcode_jump_if_false = auto()
    opcode_call_function = auto()
    opcode_return_function = auto()

def get_tree(code: str) -> Optional[str]: ...
def get_opcode(code: str) -> Optional[str]: ...
