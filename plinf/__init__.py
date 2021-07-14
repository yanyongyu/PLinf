import sys
import argparse

from .gui import main as guimain
from .core import get_tree, get_opcode
from .runner import convert_line, convert_lines, convert_file

parser = argparse.ArgumentParser(description="PL/inf - extends the PL/0")
parser.add_argument("-o", action="store_true", dest="opcode", help="output opcode")
parser.add_argument("-t", action="store_true", dest="tree", help="output tree")
parser.add_argument("-f", action="store_true", dest="run_opcode", help="run opcode")
parser.add_argument("--ui", action="store_true", dest="ui", help="open editor")
parser.add_argument("file", nargs="?", default=None, help="input file")


def main(args=sys.argv[1:]):
    result = parser.parse_args(args)
    if result.opcode:
        assert result.file, "no input file specified"
        with open(result.file, "r") as f:
            code = f.read()
        opcode = get_opcode(code)
        print(opcode, end="")
    elif result.tree:
        assert result.file, "no input file specified"
        with open(result.file, "r") as f:
            code = f.read()
        tree = get_tree(code)
        print(tree, end="")
    elif result.run_opcode:
        assert result.file, "no input file specified"
        op_list = convert_file(result.file)
        op_list.run()
    elif result.ui:
        guimain()
    else:
        assert result.file, "no input file specified"
        with open(result.file, "r") as f:
            code = f.read()
        opcode = get_opcode(code)
        if opcode:
            op_list = convert_lines(opcode.splitlines())
            op_list.run()
