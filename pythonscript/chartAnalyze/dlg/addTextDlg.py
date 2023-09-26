from Ui_addTextDlg import *

from PyQt5 import QtCore, QtGui, QtWidgets

class addTextDlg(QtWidgets.QDialog):
    add_text =QtCore. pyqtSignal(str)
    def __init__(self):
        super().__init__()
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.setWindowFlags(QtCore.Qt.Dialog | QtCore.Qt.CustomizeWindowHint | QtCore.Qt.WindowStaysOnTopHint)
        self.ui.addbtn.clicked.connect(self.addText)
        self.ui.cancelBtn.clicked.connect(self.cance)

    def getText(self):
        return self.ui.lineEdit.text()
    
    def addText(self):
        if self.getText() == '':
            QtWidgets.QMessageBox.warning(0,"提示","不能为空")
            return
        self.add_text.emit(self.getText())

    def cance(self):
        self.close()