from io import StringIO
import sys
from PyQt5.QtCore import Qt, QTimer

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
    QFrame,
    QTextEdit,
)

from plinf.runner import convert_lines
from plinf.core import get_tree, get_opcode


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


class SubWindow(QWidget):
    def __init__(self, win: "MainWindow"):
        super(SubWindow, self).__init__()
        self.win = win
        self.initUI()

    def initUI(self):
        self.sbTableTitle = QLabel("符号表")
        self.sbTableTitle.setAlignment(Qt.AlignCenter)
        self.sbTableName1 = QLabel("名")
        self.sbTableName1.setFrameShape(QFrame.Box)
        self.sbTableName1.setAlignment(Qt.AlignCenter)
        self.sbTableName2 = QLabel("类")
        self.sbTableName2.setFrameShape(QFrame.Box)
        self.sbTableName2.setAlignment(Qt.AlignCenter)
        self.sbTableName3 = QLabel("值")
        self.sbTableName3.setFrameShape(QFrame.Box)
        self.sbTableName3.setAlignment(Qt.AlignCenter)
        self.sbTableName4 = QLabel("scope")
        self.sbTableName4.setFrameShape(QFrame.Box)
        self.sbTableName4.setAlignment(Qt.AlignCenter)
        self.sbTable = []
        for i in range(16):
            self.sbTable.append(QLabel("1"))
            self.sbTable[i].setFrameShape(QFrame.Box)
            self.sbTable[i].setAlignment(Qt.AlignCenter)

        self.stackTitle = QLabel("堆栈")
        self.stackTitle.setAlignment(Qt.AlignCenter)
        self.stackTable = []
        for i in range(5):
            self.stackTable.append(QLabel("2"))
            self.stackTable[i].setFrameShape(QFrame.Box)
            self.stackTable[i].setAlignment(Qt.AlignCenter)

        self.opTitle = QLabel("当前操作")
        self.opTitle.setAlignment(Qt.AlignCenter)
        self.op1 = QLabel("操作符")
        self.op1.setFrameShape(QFrame.Box)
        self.op1.setAlignment(Qt.AlignCenter)
        self.op2 = QLabel("参数")
        self.op2.setFrameShape(QFrame.Box)
        self.op2.setAlignment(Qt.AlignCenter)
        self.opTable = []
        for i in range(2):
            self.opTable.append(QLabel("3"))
            self.opTable[i].setFrameShape(QFrame.Box)
            self.opTable[i].setAlignment(Qt.AlignCenter)

        self.btn = QPushButton("下一步", self)

        self.opListTitle = QLabel("operation操作列表")
        self.opListTitle.setAlignment(Qt.AlignCenter)
        self.opList = QTextEdit()
        self.opList.setReadOnly(True)

        self.blank = QLabel("")

        grid = QGridLayout()
        grid.setSpacing(0)

        grid.addWidget(self.sbTableTitle, 1, 1, 1, 2)
        grid.addWidget(self.sbTableName1, 2, 0)
        grid.addWidget(self.sbTableName2, 2, 1)
        grid.addWidget(self.sbTableName3, 2, 2)
        grid.addWidget(self.sbTableName4, 2, 3)
        for i in range(16):
            posX = i // 4 + 3
            posY = i % 4
            grid.addWidget(self.sbTable[i], posX, posY)
        grid.addWidget(self.stackTitle, 7, 1, 1, 2)
        for i in range(5):
            grid.addWidget(self.stackTable[i], 8 + i, 1, 1, 2)

        grid.addWidget(self.blank, 13, 1)
        grid.addWidget(self.blank, 1, 4)

        grid.addWidget(self.opTitle, 1, 5, 1, 2)
        grid.addWidget(self.op1, 2, 5)
        grid.addWidget(self.op2, 2, 6)
        for i in range(2):
            grid.addWidget(self.opTable[i], 3, i + 5)
        grid.addWidget(self.btn, 5, 5, 1, 2)

        grid.addWidget(self.blank, 1, 7)

        grid.addWidget(self.opListTitle, 1, 8, 1, 4)
        grid.addWidget(self.opList, 2, 8, 11, 4)

        # self.btn

        self.setLayout(grid)
        self.setWindowTitle("编译")
        self.setGeometry(150, 150, 1080, 720)

    def handle_click(self):
        if not self.isVisible():
            self.show()


def main():
    app = QApplication([])
    win = MainWindow()
    sub = SubWindow(win)
    win.subbtn.clicked.connect(sub.handle_click)
    sub.setWindowModality(Qt.ApplicationModal)
    win.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
