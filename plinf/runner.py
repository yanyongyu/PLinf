from enum import Enum
from typing import Any, List, Type, Union, Generic, TypeVar, Optional

from .core import OPCODE


class Symbol:
    pass


class SymbolTable:
    pass


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

    def __init__(self, type: Type[CT], value: str):
        self._type: Type[CT] = type
        self._value: CT = self.convert_value(value)

    def __str__(self) -> str:
        return f"Const(type: {self.type}, value: {self.value})"

    @property
    def type(self) -> Type[CT]:
        return self._type

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


# operation class
class OperationList(List[Optional["Operation"]]):
    def __init__(self, operations: List["Operation"]):
        super(OperationList, self).__init__(self.filter_operations(operations))
        self.reset()

    def reset(self):
        self._current_index = 0

    @property
    def current_operation(self) -> Optional["Operation"]:
        return self[self._current_index]

    @property
    def finished(self) -> bool:
        return self._current_index > len(self)

    @classmethod
    def filter_operations(
        cls, operations: List["Operation"]
    ) -> List[Optional["Operation"]]:
        max_index = max(*operations, key=lambda x: x.index).index
        op_list: List[Optional[Operation]] = [None] * max_index
        for op in operations:
            op_list[op.index] = op
        return op_list

    def run_operation(self):
        # TODO: run one step
        self._current_index += 1

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
