import sys
import argparse

from .core import get_tree, get_opcode
from .runner import convert_line, convert_lines, convert_file

parser = argparse.ArgumentParser(description="PL/inf - extends the PL/0")
parser.add_argument("-o", action="store_true", dest="opcode", help="output opcode")
parser.add_argument("-t", action="store_true", dest="tree", help="output tree")
parser.add_argument("-f", action="store_true", dest="run_opcode", help="run opcode")
parser.add_argument("file", help="input file")


def main(args=sys.argv[1:]):
    result = parser.parse_args(args)
    if result.opcode:
        with open(result.file, "r") as f:
            code = f.read()
        opcode = get_opcode(code)
        print(opcode, end="")
    elif result.tree:
        with open(result.file, "r") as f:
            code = f.read()
        tree = get_tree(code)
        print(tree, end="")
    elif result.run_opcode:
        op_list = convert_file(result.file)
        op_list.run()
    else:
        with open(result.file, "r") as f:
            code = f.read()
        opcode = get_opcode(code)
        if opcode:
            op_list = convert_lines(opcode.splitlines())
            op_list.run()
