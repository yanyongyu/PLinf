import unittest
from io import StringIO
from pathlib import Path

from plinf import get_tree, get_opcode, convert_lines


TEST_FILE = Path(__file__).parent / "test.plinf"
TEST_CASE1 = Path(__file__).parent / "PreTest1.pl0"
TEST_CASE2 = Path(__file__).parent / "PreTest2.pl0"
TEST_CASE3 = Path(__file__).parent / "PreTest3.pl0"
TEST_CASE4 = Path(__file__).parent / "PreTest4.pl0"
TEST_CASE5 = Path(__file__).parent / "PreTest5.pl0"
TEST_CASE6 = Path(__file__).parent / "PreTest6.pl0"
TEST_CASE7 = Path(__file__).parent / "PreTest7.pl0"
TEST_CASE8 = Path(__file__).parent / "PreTest8.pl0"
TEST_CASE9 = Path(__file__).parent / "PreTest9.pl0"
TEST_CASE10 = Path(__file__).parent / "PreTest10.pl0"
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

    def test_program(self):
        with TEST_FILE.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)
        assert opcode
        op_list = convert_lines(opcode.splitlines())
        op_list.input = StringIO("1\n")
        op_list.output = StringIO()
        op_list.run()
        self.assertListEqual(
            op_list.output.getvalue().splitlines(),
            ["2", "[[0, 1, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]"],
        )

    def test_case1(self):
        with TEST_CASE1.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case2(self):
        with TEST_CASE2.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case3(self):
        with TEST_CASE3.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case4(self):
        with TEST_CASE4.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case5(self):
        with TEST_CASE5.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case6(self):
        with TEST_CASE6.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNone(opcode)

    def test_case7(self):
        with TEST_CASE7.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)

    def test_case8(self):
        with TEST_CASE8.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)

    def test_case9(self):
        with TEST_CASE9.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)

    def test_case10(self):
        with TEST_CASE10.open("r") as f:
            code = f.read()
        opcode = get_opcode(code)
        self.assertIsNotNone(opcode)


if __name__ == "__main__":
    unittest.main()
