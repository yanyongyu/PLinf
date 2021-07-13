from enum import Enum, IntEnum, auto
from typing import Any, List, Type, Union, Tuple, Generic, TypeVar, Optional

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
        for i in range(-1, -len(self.scope), -1):
            current_scope = self.scope[i]
            for symbol in current_scope:
                if symbol.name == symbol_name:
                    return symbol
        return None


# stack accept type
class StackType:
    pass


CT = TypeVar("CT", int, float, bool, str)


class CONST(StackType, Generic[CT]):
    class CONST_TYPE(Enum):
        int = int
        real = float
        bool = bool
        str = str

    def __init__(self, type: CONST_TYPE, value: str):
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

    def convert_value(self, value: str) -> CT:
        return self.type(value)


class BLOCK(StackType):
    pass


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
        self._value = None

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


# operation class
class OperationList(List[Optional["Operation"]]):
    def __init__(self, operations: List["Operation"]):
        super(OperationList, self).__init__(self.filter_operations(operations))
        self.reset()

    def reset(self):
        self._current_index = 0
        self._function_call_stack = []
        self._stack: List[StackType] = []
        self._symbol_table = SymbolTable()

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
        op_list: List[Optional[Operation]] = [None] * max_index
        for op in operations:
            op_list[op.index] = op
        return op_list

    def pop_stack(self, num: int) -> Tuple[StackType, ...]:
        result = tuple(self._stack[-num:])
        del self._stack[-num:]
        return result

    def push_symbol(self, symbol: Symbol):
        self._symbol_table.push_symbol(symbol)

    def push_scope(self):
        self._function_call_stack.append(self._current_index)
        self._symbol_table.push_scope()

    def pop_scope(self) -> List[Symbol]:
        self._current_index = self._function_call_stack.pop()
        return self._symbol_table.pop_scope()

    def run_operation(self):
        # TODO: run one step
        op = self.current_operation
        self._current_index += 1
        if op is None:
            return
        if op.opcode == OPCODE.op_nop:
            pass
        elif op.opcode == OPCODE.op_const_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, CONST) or value.type is str:
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            var = VAR(TYPE(value.type_name))
            symbol = Symbol(name.value, Symbol.SymbolType.const, var)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.op_type_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, TYPE):
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            symbol = Symbol(name.value, Symbol.SymbolType.type, value)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.op_var_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not str:
                raise RuntimeError(f"{op} with unexpected argument type")
            name: CONST[str] = op.arg
            value, *_ = self.pop_stack(1)
            if not isinstance(value, TYPE):
                raise RuntimeError(f"{op} failed because unexpected TOS {value}")

            var = VAR(value)
            symbol = Symbol(name.value, Symbol.SymbolType.variable, var)
            self.push_symbol(symbol)
        elif op.opcode == OPCODE.op_procedure_declare:
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
        elif op.opcode == OPCODE.op_function_declare:
            if not isinstance(op.arg, CONST) or op.arg.type is not int:
                raise RuntimeError(f"{op} with unexpected argument type")
            param_count: CONST[int] = op.arg
            function_name, return_type, *params, block = self.pop_stack(
                param_count.value + 2
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
        return f"Operation(index: {self.index}, opcode: {self.opcode}, arg: {self.arg})"

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
            return CONST(CONST.CONST_TYPE(type_str).value, type_value)
        return None


def convert_line(line: str) -> Operation:
    index_str, opcode_str, arg_str = line.split(",")
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
