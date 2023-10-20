from PyQt5 import QtCore, QtGui,QtWidgets
from PyQt5 import *
from Ui_lableLineEdit import *

class lableLineEdit(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.ui = Ui_lableLineEdit()
        self.ui.setupUi(self)
        self.dependentWidget = None
        self.ui.label.textChanged.connect(self.lableTextChanged)

    def setText(self,labeText,lineEeditText):
        self.ui.label.setText(labeText)
        self.ui.lineEdit.setText(lineEeditText)

    def getText(self):
        return self.ui.label.text(),self.ui.lineEdit.text()
    
    def text(self):
        return self.ui.lineEdit.text()
    
    def lableTextChanged(self):
        self.dependentWidget.setText(self.ui.label.text())