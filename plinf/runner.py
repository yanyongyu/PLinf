import sys
import operator
from enum import Enum, IntEnum, auto
from typing import Any, List, Type, Union, Tuple, Generic, TypeVar, Optional, Callable

from .core import OPCODE


class Symbol:
    class SymbolType(IntEnum):
        const = auto()
        type = auto()
        variable = auto()
        procedure = auto()
        function = auto()

    def __init__(self, name: str, type: SymbolType, value: Any):
        self._name = name
        self._type = type
        self._value = value

    def __str__(self) -> str:
        return f"Symbol(name: {self.name}, type: {self.type.name}, value: {self.value})"

    def __repr__(self) -> str:
        return str(self)

    @property
    def name(self) -> str:
        return self._name

    @property
    def type(self) -> SymbolType:
        return self._type

    @property
    def value(self) -> Any:
        return self._value

    @value.setter
    def value(self, value: Any):
        if self.type != Symbol.SymbolType.variable:
            raise RuntimeError(f"Can't set value of type {self.type}")
        var: VAR = self.value
        var.value = value


class SymbolTable:
    def __init__(self):
        self.scope: List[List[Symbol]] = [[]]

    def push_scope(self):
        self.scope.append([])

    def pop_scope(self) -> List[Symbol]:
        return self.scope.pop()

    def push_symbol(self, symbol: Symbol):
        self.scope[-1].append(symbol)

    def find_symbol(self, symbol_name: str) -> Optional[Symbol]:
        for i in range(-1, -len(self.scope) - 1, -1):
            current_scope = self.scope[i]
            for symbol in current_scope:
                if symbol.name == symbol_name:
                    return symbol
        return None

    def to_list(self) -> List[List[str]]:
        result: List[List[str]] = []
        for i, scope in enumerate(self.scope):
            for symbol in scope:
                if symbol.type in (Symbol.SymbolType.const, Symbol.SymbolType.variable):
                    value = symbol.value.value
                else:
                    value = str(symbol.value)
                result.append([symbol.name, symbol.type.name, value, str(i)])
        return result


# stack accept type
class StackType:
    def __repr__(self) -> str:
        return str(self)


CT = TypeVar("CT", int, float, bool, str)


class CONST(StackType, Generic[CT]):
    class CONST_TYPE(Enum):
        int = int
        real = float
        bool = bool
        str = str

    def __init__(self, type: CONST_TYPE, value: Union[str, CT]):
        self._type: CONST.CONST_TYPE = type
        self._value: CT = self.convert_value(value)

    def __str__(self) -> str:
        return f"Const(type: {self.type}, value: {self.value})"

    @property
    def type(self) -> Type[CT]:
        return self._type.value

    @property
    def type_name(self) -> str:
        return self._type.name

    @property
    def value(self) -> CT:
        return self._value

    def convert_value(self, value: Union[str, CT]) -> CT:
        return self.type(value)


class BLOCK(StackType):
    def __init__(self, start_index: int, end_index):
        self._start_index = start_index
        self._end_index = end_index

    def __str__(self) -> str:
        return f"Block[{self.start_index} ~ {self.end_index}]"

    @property
    def start_index(self) -> int:
        return self._start_index

    @property
    def end_index(self) -> int:
        return self._end_index


class TYPE(StackType):
    class TYPE_TYPE(str, Enum):
        int = "int"
        real = "real"
        bool = "bool"
        array = "array"

    def __init__(self, type: Union[str, TYPE_TYPE]):
        self._type: TYPE.TYPE_TYPE = TYPE.TYPE_TYPE(type)

    def __str__(self) -> str:
        return f"<type {self.type.value}>"

    def __call__(self) -> Any:
        if self.type == TYPE.TYPE_TYPE.int:
            return 0
        elif self.type == TYPE.TYPE_TYPE.real:
            return 0.0
        elif self.type == TYPE.TYPE_TYPE.bool:
            return False

    @property
    def type(self) -> TYPE_TYPE:
        return self._type

    def check_type(self, value: Any) -> bool:
        checkers = {"int": int, "real": float, "bool": bool, "array": list}
        return isinstance(value, checkers[self.type])


class TYPE_ARRAY(TYPE):
    def __init__(self, array_start: int, array_end: int, sub_type: TYPE):
        super(TYPE_ARRAY, self).__init__(TYPE.TYPE_TYPE.array)
        self._array_start = array_start
        self._array_end = array_end
        self._sub_type = sub_type

    def __str__(self) -> str:
        return f"<type {self.type.value}[{self.sub_type}]>"

    def __call__(self) -> list:
        return [self.sub_type() for _ in range(self.array_end - self.array_start + 1)]

    @property
    def array_start(self) -> int:
        return self._array_start

    @property
    def array_end(self) -> int:
        return self._array_end

    @property
    def sub_type(self) -> TYPE:
        return self._sub_type

    def check_type(self, value: Any) -> bool:
        return isinstance(value, list) and all(
            map(lambda x: self.sub_type.check_type(x), value)
        )


class VAR(StackType):
    def __init__(self, type: TYPE):
        self._type = type
        self._value = self._type()

    def __str__(self) -> str:
        return f"VAR(type: {self.type}, value: {self._value!r})"

    @property
    def type(self) -> TYPE:
        return self._type

    @property
    def value(self) -> Any:
        if self._value is None:
            raise RuntimeError("Get variable value before setting")
        return self._value

    @value.setter
    def value(self, value: Any) -> None:
        if not self.type.check_type(value):
            raise ValueError(f"Value {value!r} is incompatible with type {self.type}")
        self._value = value


class PARAM(StackType):
    def __init__(self, name: str, type: TYPE):
        self._name = name
        self._type = type

    def __str__(self) -> str:
        return f"PARAM(name: {self.name}, type: {self.type})"

    @property
    def name(self) -> str:
        return self._name

    @property
    def type(self) -> TYPE:
        return self._type


class Procedure:
    def __init__(self, params: List[PARAM], block: BLOCK):
        self._params = params
        self._block = block

    def __str__(self) -> str:
        return f"Procedure(params: {self.params}, block: {self.block})"

    @property
    def params(self) -> List[PARAM]:
        return self._params

    @property
    def block(self) -> BLOCK:
        return self._block


class Function:
    def __init__(self, params: List[PARAM], return_type: TYPE, block: BLOCK):
        self._params = params
        self._return_type = return_type
        self._block = block

    def __str__(self) -> str:
        return f"Function(params: {self.params}, return_type: {self.return_type} block: {self.block})"

    @property
    def params(self) -> List[PARAM]:
        return self._params

    @property
    def return_type(self) -> TYPE:
        return self._return_type

    @property
    def block(self) -> BLOCK:
        return self._block


F = Callable[..., None]

# operation class
class OperationList(List[Optional["Operation"]]):
    def __init__(self, operations: List["Operation"]):
        super(OperationList, self).__init__(self.filter_operations(operations))
        self.input = sys.stdin
        self.output = sys.stdout
        self.input_callback = None
        self.output_callback = None
        self.reset()

    def reset(self):
        self._current_index = 0
        self._block_stack: List[Operation] = []
        self._function_call_stack: List[Tuple[str, int]] = []
        self._stack: List[StackType] = []
        self._symbol_table = SymbolTable()

    def on_input(self, func: F) -> F:
        self.input_callback = func
        return func

    def on_output(self, func: F) -> F:
        self.output_callback = func
        return func

    @property
    def current_operation(self) -> Optional["Operation"]:
        return self[self._current_index]

    @property
    def finished(self) -> bool:
        return self._current_index >= len(self)

    @classmethod
    def filter_operations(
        cls, operations: List["Operation"]
    ) -> List[Optional["Operation"]]:
        max_index = max(*operations, key=lambda x: x.index).index
        op_list: List[Optional[Operation]] = [None] * (max_index + 1)
        for op in operations:
            op_list[op.index] = op
        return op_list

    def push_stack(self, stack: StackType):
        self._stack.append(stack)

    def pop_stack(self, num: int) -> Tuple[StackType, ...]:
        if num > len(self._stack):
            raise RuntimeError("No more stack elements can be popped")
        result = tuple(reversed(self._stack[-num:]))
        del self._stack[-num:]
        return result

    def push_symbol(self, symbol: Symbol):
        self._symbol_table.push_symbol(symbol)

    def get_symbol(self, symbol_name: str) -> Optional[Symbol]:
        return self._symbol_table.find_symbol(symbol_name)

    def push_scope(self, call: str, jump_back: int):
        self._function_call_stack.append((call, jump_back))
        self._symbol_table.push_scope()

    def pop_scope(self) -> Tuple[str, List[Symbol]]:
        call, jump_back = self._function_call_stack.pop()
        self._current_index = jump_back
        return call, self._symbol_table.pop_scope()

    def push_block(self, operation: "Operation"):
        self._block_stack.append(operation)

    def pop_block(self) -> "Operation":
        return self._block_stack.pop()

    def run_operation(self):
        op = self.current_operation
        self._current_index += 1
        if op is None:
            return
        if self._block_stack and op.opcode != OPCODE.opcode_block_end:
            return
        if op.opcode == OPCODE.opcode_nop:
            pass
        elif op.opcode == OPCODE.opcode_const_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, CONST) or value.type is str:
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            var = VAR(TYPE(value.type_name))
            var.value = value.value
            symbol = Symbol(name.value, Symbol.SymbolType.const, var)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.opcode_type_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, TYPE):
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            symbol = Symbol(name.value, Symbol.SymbolType.type, value)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.opcode_var_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, TYPE):
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            var = VAR(value)
            symbol = Symbol(name.value, Symbol.SymbolType.variable, var)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.opcode_procedure_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")
            param_count: CONST[int] = op.arg
            procedure_name, *params, block = self.pop_stack(param_count.value + 2)
            if not isinstance(procedure_name, CONST) or procedure_name.type is not str:
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {procedure_name}"
                )
            elif not all(map(lambda x: isinstance(x, PARAM), params)):
                raise RuntimeError(
                    f"{op} failed because unexpected procedure param {params}"
                )
            elif not isinstance(block, BLOCK):
                raise RuntimeError(
                    f"{op} failed because unexpected procedure block {block}"
                )

            procedure = Procedure(params, block)  # type: ignore

            symbol = Symbol(
                procedure_name.value, Symbol.SymbolType.procedure, procedure
            )
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.opcode_function_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")
            param_count: CONST[int] = op.arg
            function_name, return_type, *params, block = self.pop_stack(
                param_count.value + 3
            )
            if not isinstance(function_name, CONST) or function_name.type is not str:
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {function_name}"
                )
            elif not isinstance(return_type, TYPE):
                raise RuntimeError(
                    f"{op} failed because unexpected function return type {return_type}"
                )
            elif not all(map(lambda x: isinstance(x, PARAM), params)):
                raise RuntimeError(
                    f"{op} failed because unexpected function param {params}"
                )
            elif not isinstance(block, BLOCK):
                raise RuntimeError(
                    f"{op} failed because unexpected function block {block}"
                )

            function = Function(params, return_type, block)  # type: ignore

            symbol = Symbol(function_name.value, Symbol.SymbolType.function, function)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.opcode_param_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, TYPE):
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            param = PARAM(name.value, value)
            self.push_stack(param)
        elif op.opcode == OPCODE.opcode_build_array_type:
            start, end, sub_type = self.pop_stack(3)
            if not isinstance(start, CONST) or start.type is not int:
                raise RuntimeError(
                    f"{op} failed because unexpected array start {start}"
                )
            elif not isinstance(end, CONST) or end.type is not int:
                raise RuntimeError(f"{op} failed because unexpected array end {end}")
            elif not isinstance(sub_type, TYPE):
                raise RuntimeError(f"{op} with unexpected array subtype {sub_type}")

            array_type = TYPE_ARRAY(start.value, end.value, sub_type)
            self.push_stack(array_type)
        elif op.opcode == OPCODE.opcode_load_const:
            if not op.arg:
                raise RuntimeError(f"{op} failed because unexpected arg {op.arg}")
            self.push_stack(op.arg)
        elif op.opcode == OPCODE.opcode_load_fast:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg

            symbol = self.get_symbol(name.value)
            if not symbol:
                print(self._symbol_table.scope)
                raise RuntimeError(f"Can't find symbol {name.value}! {op}")
            elif not isinstance(symbol.value, StackType):
                raise RuntimeError(
                    f"Can't load symbol {name.value} with type {symbol.type}!"
                )
            self.push_stack(symbol.value)
        elif op.opcode == OPCODE.opcode_block_start:
            self.push_block(op)
        elif op.opcode == OPCODE.opcode_block_end:
            start_index = self.pop_block().index + 1
            end_index = op.index
            block = BLOCK(start_index, end_index)
            self.push_stack(block)
        elif op.opcode == OPCODE.opcode_unary_negative:
            tos, *_ = self.pop_stack(1)
            if not isinstance(tos, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            if isinstance(value, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, -value))
            elif isinstance(value, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, -value))
            else:
                raise RuntimeError(f"{op} with unexpected TOS {tos}")
        elif op.opcode == OPCODE.opcode_unary_not:
            tos, *_ = self.pop_stack(1)
            if not isinstance(tos, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            if isinstance(value, bool):
                self.push_stack(CONST(CONST.CONST_TYPE.bool, not value))
            else:
                raise RuntimeError(f"{op} with unexpected TOS {tos}")
        elif op.opcode == OPCODE.opcode_unary_odd:
            tos, *_ = self.pop_stack(1)
            if not isinstance(tos, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            if isinstance(value, int):
                self.push_stack(CONST(CONST.CONST_TYPE.bool, value & 1 == 1))
            else:
                raise RuntimeError(f"{op} with unexpected TOS {tos}")
        elif op.opcode == OPCODE.opcode_binary_power:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 ** value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_times:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 * value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_divide:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 / value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_floor_divide:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 // value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_modulo:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 % value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_plus:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 + value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_minus:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 - value
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
        elif op.opcode == OPCODE.opcode_binary_subscr:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, VAR):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, int) or not isinstance(value1, list):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1[value]
            if isinstance(result, int):
                self.push_stack(CONST(CONST.CONST_TYPE.int, result))
            elif isinstance(result, float):
                self.push_stack(CONST(CONST.CONST_TYPE.real, result))
            elif isinstance(result, bool):
                self.push_stack(CONST(CONST.CONST_TYPE.bool, result))
            elif isinstance(result, list):
                array_type: TYPE_ARRAY = tos1.type  # type: ignore
                var = VAR(array_type.sub_type)
                var.value = result
                self.push_stack(var)
        elif op.opcode == OPCODE.opcode_binary_and:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, bool) or not isinstance(value1, bool):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 and value
            self.push_stack(CONST(CONST.CONST_TYPE.bool, result))
        elif op.opcode == OPCODE.opcode_binary_or:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, bool) or not isinstance(value1, bool):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )
            result = value1 or value
            self.push_stack(CONST(CONST.CONST_TYPE.bool, result))
        elif op.opcode == OPCODE.opcode_binary_compare:
            if (
                not isinstance(op.arg, CONST)
                or op.arg.type is not int
                or op.arg.value > 5
            ):
                raise RuntimeError(f"{op} with unexpected argument type")

            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, (CONST, VAR)) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            value = tos.value
            value1 = tos1.value
            if not isinstance(value, (int, float)) or not isinstance(
                value1, (int, float)
            ):
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {tos} TOS1 {tos1}"
                )

            cmp_op = [
                operator.lt,
                operator.le,
                operator.gt,
                operator.ge,
                operator.eq,
                operator.ne,
            ][op.arg.value]
            result = cmp_op(value1, value)
            self.push_stack(CONST(CONST.CONST_TYPE.bool, result))
        elif op.opcode == OPCODE.opcode_store_fast:
            tos, tos1 = self.pop_stack(2)
            if not isinstance(tos, VAR) or not isinstance(tos1, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos} TOS1 {tos1}")

            tos.value = tos1.value
        elif op.opcode == OPCODE.opcode_store_subscr:
            tos, tos1, tos2 = self.pop_stack(3)
            if (
                not isinstance(tos, (CONST, VAR))
                or not isinstance(tos1, VAR)
                or tos1.type.type != TYPE.TYPE_TYPE.array
                or not isinstance(tos2, (CONST, VAR))
            ):
                raise RuntimeError(
                    f"{op} with unexpected TOS {tos} TOS1 {tos1} TOS2 {tos2}"
                )

            if not tos1.type.sub_type.check_type(tos2.value):  # type: ignore
                raise RuntimeError(
                    f"{op} with unexpected TOS {tos} TOS1 {tos1} TOS2 {tos2}"
                )

            tos1.value[tos.value - tos1.type.array_start] = tos2.value  # type: ignore
        elif op.opcode == OPCODE.opcode_jump:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")
            self._current_index = op.arg.value
        elif op.opcode == OPCODE.opcode_jump_if_true:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")

            tos, *_ = self.pop_stack(1)
            if not isinstance(tos, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            if tos.value:
                self._current_index = op.arg.value
        elif op.opcode == OPCODE.opcode_jump_if_false:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")

            tos, *_ = self.pop_stack(1)
            if not isinstance(tos, (CONST, VAR)):
                raise RuntimeError(f"{op} with unexpected TOS {tos}")

            if not tos.value:
                self._current_index = op.arg.value
        elif op.opcode == OPCODE.opcode_call_function:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")
            param_count: CONST[int] = op.arg
            *args, function_name = self.pop_stack(param_count.value + 1)  # type: ignore
            if not isinstance(function_name, CONST) or function_name.type is not str:
                raise RuntimeError(
                    f"{op} failed because unexpected TOS {function_name}"
                )
            elif not all(map(lambda x: isinstance(x, (CONST, VAR)), args)):
                raise RuntimeError(
                    f"{op} failed because unexpected function args {args}"
                )

            if function_name.value == "write":
                self.output.write(
                    ", ".join(map(lambda x: str(x.value), reversed(args))) + "\n"
                )
                if self.output_callback:
                    self.output_callback()
            elif function_name.value == "read":
                for param in args:
                    if not isinstance(param, VAR):
                        raise RuntimeError(f"Unexpected argument {param} for READ call")
                    param_type = param.type
                    if param_type.type == TYPE.TYPE_TYPE.array:
                        raise RuntimeError(f"Can't store input into array variable")
                    if self.input_callback:
                        self.input_callback()
                    temp = self.input.readline().strip()
                    if param_type.type == TYPE.TYPE_TYPE.int:
                        param.value = int(temp)
                    elif param_type.type == TYPE.TYPE_TYPE.real:
                        param.value = float(temp)
                    elif param_type.type == TYPE.TYPE_TYPE.bool:
                        param.value = True if temp == "true" else False
            else:
                symbol = self.get_symbol(function_name.value)
                if not symbol or symbol.type not in (
                    Symbol.SymbolType.procedure,
                    Symbol.SymbolType.function,
                ):
                    raise RuntimeError(
                        f"Can't find function {function_name.value}! {op}"
                    )
                self.push_scope(symbol.name, self._current_index)
                if isinstance(symbol.value, Procedure):
                    args: List[Union[CONST, VAR]]
                    for index in range(len(symbol.value.params)):
                        param_name = symbol.value.params[index].name
                        param_type = symbol.value.params[index].type
                        if not param_type.check_type(args[index].value):
                            raise RuntimeError(
                                f"Invalid argument {args[index].value!r} for "
                                f"procedure {symbol.name} {param_name}"
                            )
                        new_symbol = Symbol(
                            param_name,
                            Symbol.SymbolType.const,
                            args[index],  # type: ignore
                        )
                        self.push_symbol(new_symbol)
                elif isinstance(symbol.value, Function):
                    for index in range(len(symbol.value.params)):
                        param_name = symbol.value.params[index].name
                        param_type = symbol.value.params[index].type
                        if not param_type.check_type(args[index].value):
                            raise RuntimeError(
                                f"Invalid argument {args[index].value!r} for "
                                f"procedure {symbol.name} {param_name}"
                            )
                        new_symbol = Symbol(
                            param_name,
                            Symbol.SymbolType.const,
                            args[index],  # type: ignore
                        )
                        self.push_symbol(new_symbol)

                    new_symbol = Symbol(
                        symbol.name,
                        Symbol.SymbolType.variable,
                        VAR(symbol.value.return_type),
                    )
                    self.push_symbol(new_symbol)

                self._current_index = symbol.value.block.start_index
        elif op.opcode == OPCODE.opcode_return_function:
            call_name, symbols = self.pop_scope()
            call = self.get_symbol(call_name)
            if call and isinstance(call.value, Function):
                for symbol in symbols:
                    if symbol.name == call_name:
                        self.push_stack(symbol.value)
                        break
                else:
                    raise RuntimeError(f"Function return symbol {call_name} not found")

    def run(self):
        self.reset()
        while not self.finished:
            self.run_operation()


class Operation:
    def __init__(
        self,
        index: int,
        opcode: Union[int, OPCODE],
        arg: Optional[Union[str, CONST, TYPE]],
    ):
        self._index: int = index
        self._opcode: OPCODE = OPCODE(opcode)
        self._arg: Optional[Union[CONST, TYPE]] = (
            self.prepare_arg(arg) if isinstance(arg, str) else arg
        )

    def __str__(self) -> str:
        return f"Operation(index: {self.index}, opcode: {self.opcode.name}, arg: {self.arg})"

    @property
    def index(self) -> int:
        return self._index

    @property
    def opcode(self) -> OPCODE:
        return self._opcode

    @property
    def arg(self) -> Optional[Union[CONST, TYPE]]:
        return self._arg

    def prepare_arg(self, arg: str) -> Optional[Union[CONST, TYPE]]:
        type_str, type_value = arg.split(":", maxsplit=1)
        if type_str == "type":
            return TYPE(type_value)
        elif type_str in CONST.CONST_TYPE.__members__.keys():
            return CONST(CONST.CONST_TYPE[type_str], type_value)
        return None


def convert_line(line: str) -> Operation:
    index_str, opcode_str, arg_str = line.strip("\n").split(",")
    return Operation(int(index_str), int(opcode_str), arg_str)


def convert_lines(lines: List[str]) -> OperationList:
    ops: List[Operation] = []
    for line in lines:
        ops.append(convert_line(line))
    return OperationList(ops)


def convert_file(filename: str, encoding: Optional[str] = None) -> OperationList:
    with open(filename, "r", encoding=encoding) as f:
        op_strs = f.readlines()

    return convert_lines(op_strs)
