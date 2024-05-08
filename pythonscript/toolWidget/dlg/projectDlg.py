import typing
from PyQt5.QtWidgets import QWidget
from Ui_projectDlg import *

from PyQt5 import QtCore, QtGui, QtWidgets

class projectDlg(QtWidgets.QDialog):
    add_text =QtCore. pyqtSignal(str,str,str,str)
    def __init__(self) -> None:
        super().__init__()
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.setWindowFlags(QtCore.Qt.Dialog|QtCore.Qt.WindowStaysOnTopHint)
        self.ui.addbtn.clicked.connect(self.addText)
        self.ui.cancelBtn.clicked.connect(self.cance)

    def getText(self):
        return self.ui.prjectNameLE.text(),self.ui.projectPathLE.text(),self.ui.tsPathLE.text(),self.ui.wanTextLE.text()
    
    def addText(self):
        if self.getText() == '':
            QtWidgets.QMessageBox.warning(0,"提示","不能为空")
            return
        projectName,projectText,tsText,warnText = self.getText()
        self.add_text.emit(projectName,projectText,tsText,warnText)
        self.accept()

    def cance(self):
        self.reject()