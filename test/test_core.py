import unittest
from pathlib import Path

from plinf.core import get_tree, get_opcode


TEST_FILE = Path(__file__).parent / "test.plinf"
TREE_OUTPUT_FILE = Path(__file__).parent.parent / "temp" / "tree_output.txt"
OPCODE_OUTPUT_FILE = Path(__file__).parent.parent / "temp" / "opcode_output.txt"


class TestOutput(unittest.TestCase):
    def test_tree_output(self):
        with TEST_FILE.open("r") as f:
            code = f.read()
        tree = get_tree(code)
        self.assertIsNotNone(tree)
        assert tree
        with TREE_OUTPUT_FILE.open("w") as f:
            f.write(tree)

    def test_opcode_output(self):
        with TEST_FILE.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)
        assert opcode
        with OPCODE_OUTPUT_FILE.open("w") as f:
            f.write(opcode)


if __name__ == "__main__":
    unittest.main()
