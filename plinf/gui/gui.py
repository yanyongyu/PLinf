import os
import sys
from io import StringIO

from PyQt5.QtCore import QUrl, Qt, QFileInfo, QObject, pyqtSlot
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWidgets import (
    QFileDialog,
    QGridLayout,
    QInputDialog,
    QLabel,
    QLineEdit,
    QMessageBox,
    QPushButton,
    QTextEdit,
    QWidget,
    QApplication,
    QMainWindow,
)

from plinf.core import get_tree, get_opcode
from plinf.runner import convert_lines, Symbol, CONST, TYPE


CURRENT_DIR = os.path.dirname(__file__)
HTML_FILE = os.path.join(CURRENT_DIR, "index.html")


class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.initUI()

    def initUI(self):
        self.opbtn = QPushButton("打开文件", self)
        self.opbtn.setToolTip("打开需编译的文件")
        self.clearbtn = QPushButton("清除内容", self)
        self.clearbtn.setToolTip("清除编译结果区内容")
        self.subbtn = QPushButton("单步调试", self)
        self.subbtn.setEnabled(False)

        self.texttitle = QLabel("文件内容")
        self.text = QTextEdit()
        self.savebtn = QPushButton("保存文件", self)
        self.savebtn.setEnabled(False)

        self.resulttitle = QLabel("结果")
        self.result = QTextEdit()
        self.result.setLineWrapMode(QTextEdit.NoWrap)
        self.result.setReadOnly(True)
        self.resultbtn = QPushButton("编译", self)
        self.opcodebtn = QPushButton("生成中间代码", self)
        self.astbtn = QPushButton("生成语法树", self)
        self.resultbtn.setEnabled(False)
        self.opcodebtn.setEnabled(False)
        self.astbtn.setEnabled(False)

        grid = QGridLayout()
        grid.setSpacing(10)

        grid.addWidget(self.opbtn, 2, 0)
        grid.addWidget(self.clearbtn, 3, 0)
        grid.addWidget(self.subbtn, 4, 0)
        grid.addWidget(self.texttitle, 1, 1)
        grid.addWidget(self.text, 2, 1, 15, 3)
        grid.addWidget(self.savebtn, 17, 1, 1, 3)
        grid.addWidget(self.resulttitle, 1, 4)
        grid.addWidget(self.result, 2, 4, 15, 3)
        grid.addWidget(self.resultbtn, 17, 4)
        grid.addWidget(self.opcodebtn, 17, 5)
        grid.addWidget(self.astbtn, 17, 6)

        self.opbtn.clicked.connect(self.opbtn_Clicked)
        self.clearbtn.clicked.connect(self.clearbtn_Clicked)
        self.savebtn.clicked.connect(self.savebtn_Clicked)
        self.resultbtn.clicked.connect(self.resultbtn_Clicked)
        self.opcodebtn.clicked.connect(self.opcodebtn_Clicked)
        self.astbtn.clicked.connect(self.astbtn_CLicked)

        self.setLayout(grid)
        self.setWindowTitle("编译")
        self.setGeometry(70, 70, 1080, 720)

    def opbtn_Clicked(self):
        self.openfile_name = QFileDialog.getOpenFileName(self, "选择文件", "", "所有文件(*.*)")
        if not self.openfile_name[0]:
            return
        self.path = self.openfile_name[0]
        f = open(self.path, encoding="utf-8")
        self.content = f.read()
        self.text.setPlainText(self.content)
        f.close()
        self.savebtn.setEnabled(True)
        self.resultbtn.setEnabled(True)
        self.opcodebtn.setEnabled(True)
        self.astbtn.setEnabled(True)
        self.subbtn.setEnabled(True)

    def clearbtn_Clicked(self):
        self.text.setPlainText("")
        self.result.setPlainText("")
        self.savebtn.setEnabled(False)
        self.resultbtn.setEnabled(False)
        self.opcodebtn.setEnabled(False)
        self.astbtn.setEnabled(False)
        self.subbtn.setEnabled(False)

    def savebtn_Clicked(self):
        reply = QMessageBox.question(
            self, "提示", "是否确认保存？", QMessageBox.Yes | QMessageBox.No, QMessageBox.No
        )

        if reply == QMessageBox.Yes:
            self.content = self.text.toPlainText()
            f = open(self.path, "w", encoding="utf-8")
            f.write(self.content)
            f.close
            QMessageBox.about(self, "成功", "保存成功！")
        else:
            pass

    def resultbtn_Clicked(self):
        opcode = get_opcode(self.content)
        if opcode is None:
            QMessageBox.warning(self, "错误", "语法错误！")
        else:
            self.result.setPlainText("")
            self.op_list = convert_lines(opcode.splitlines())
            self.op_list.input = StringIO()
            self.op_list.output = StringIO()
            self.op_list.on_input(self.user_input)
            self.op_list.on_output(self.user_output)
            try:
                self.op_list.run()
            except Exception as e:
                QMessageBox.warning(self, "错误", f"运行错误！{e!r}")

    def user_input(self):
        value, _ = QInputDialog.getText(self, "请输入", "请输入：", QLineEdit.Normal, "")
        self.op_list.input.truncate(0)
        self.op_list.input.seek(0)
        self.op_list.input.write(value + "\n")
        self.op_list.input.seek(0)

    def user_output(self):
        self.result.setPlainText(self.op_list.output.getvalue())  # type: ignore

    def opcodebtn_Clicked(self):
        opcode = get_opcode(self.content)
        if opcode is None:
            QMessageBox.warning(self, "错误", "语法错误！")
        else:
            self.result.setPlainText(opcode)

    def astbtn_CLicked(self):
        tree = get_tree(self.content)
        if tree is None:
            QMessageBox.warning(self, "错误", "语法错误！")
        else:
            self.result.setPlainText(tree)


class Myshared(QObject):
    def __init__(self, win: MainWindow, sub: "SubWindow"):
        super().__init__()
        self.win = win
        self.sub = sub

    @pyqtSlot()
    def do_execute(self):
        self.sub.run_code()

    @pyqtSlot()
    def reset(self):
        self.sub.reset()


class SubWindow(QMainWindow):
    def __init__(self, win: MainWindow):
        super(SubWindow, self).__init__()
        self.win = win
        self.setWindowTitle("编译")
        self.setGeometry(150, 150, 1440, 810)
        self.browser = QWebEngineView()
        self.browser.load(QUrl(f"file://{QFileInfo(HTML_FILE).absoluteFilePath()}"))
        self.setCentralWidget(self.browser)

    def user_input(self):
        value, _ = QInputDialog.getText(self, "请输入", "请输入：", QLineEdit.Normal, "")
        self.op_list.input.truncate(0)
        self.op_list.input.seek(0)
        self.op_list.input.write(value + "\n")
        self.op_list.input.seek(0)

    def handle_click(self):
        opcode = get_opcode(self.win.content)
        if opcode is None:
            QMessageBox.warning(self, "错误", "语法错误！")
            return
        else:
            self.win.result.setPlainText("")
            self.op_list = convert_lines(opcode.splitlines())
            self.op_list.input = StringIO()
            self.op_list.output = StringIO()
            self.op_list.on_input(self.user_input)
            self.op_list.on_output(self.refresh_page)
            self.init_page()

        if not self.isVisible():
            self.show()

    def init_page(self):
        op_list = self.op_list
        operations = []
        for index, op in enumerate(op_list):
            if not op:
                operations.append([str(index), "null", "null", "null"])
            else:
                if not op.arg:
                    arg_type = "null"
                    arg_value = "null"
                elif isinstance(op.arg, CONST):
                    arg_type = op.arg.type_name
                    arg_value = op.arg.to_string()
                else:
                    arg_type = "type"
                    arg_value = op.arg.to_string()
                operations.append([str(index), op.opcode.name, arg_type, arg_value])

        code = self.win.content
        tree = get_tree(code)
        jscode = (
            f"init_code({code!r});\n"
            f"init_opcode({operations!r});\n"
            f"init_tree({tree!r});"
        )
        self.browser.page().runJavaScript(jscode)
        self.refresh_page()

    def refresh_page(self):
        op_list = self.op_list
        output = op_list.output.getvalue()
        index = op_list._current_index
        finished = op_list.finished

        symbols = []
        for i, scope in enumerate(op_list._symbol_table.scope):
            for symbol in scope:
                if symbol.type in (Symbol.SymbolType.const, Symbol.SymbolType.variable):
                    value = symbol.value.value
                else:
                    value = symbol.value
                symbols.append([symbol.name, symbol.type.name, str(value), str(i)])

        stack = []
        for stack_content in op_list._stack:
            stack.insert(
                0, [type(stack_content).__name__.lower(), stack_content.to_string()]
            )

        jscode = (
            f"refresh_symbol({symbols!r});\n"
            f"refresh_stack({stack!r});\n"
            f"refresh_output({output!r});\n"
        )
        if finished:
            jscode += f"finished({index});"
        else:
            jscode += f"refresh_opcode({index});"
        self.browser.page().runJavaScript(jscode)

    def run_code(self):
        self.op_list.run_operation()
        self.refresh_page()

    def reset(self):
        self.op_list.reset()
        self.refresh_page()


def main():
    app = QApplication([])
    win = MainWindow()
    sub = SubWindow(win)

    channel = QWebChannel()
    shared = Myshared(win, sub)
    channel.registerObject("con", shared)
    sub.browser.page().setWebChannel(channel)

    win.subbtn.clicked.connect(sub.handle_click)
    sub.setWindowModality(Qt.ApplicationModal)
    win.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
