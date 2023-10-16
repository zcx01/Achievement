# coding:utf-8
#!/bin/python

import sys
import os
from PyQt5 import QtCore, QtGui,QtWidgets
from PyQt5 import *
pyFileDir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(pyFileDir+"/Handle")

os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
from Ui_toolMainWindow import *
from Handle.configFile import *
from Handle.tsHanle import *
import threading

class MainWindow(QtWidgets.QMainWindow):
    send_msg = QtCore.pyqtSignal(str) 
    def __init__(self):
        super().__init__()
        self.configPath = pyFileDir+"/Handle/config.json"
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        initUI(self.ui,self.configPath)
        self.ui.openTsBtn.clicked.connect(self.openFile)
        self.ui.saveBtn.clicked.connect(self.saveUI)
        self.ui.trBtn.clicked.connect(self.trHandle)
        self.ui.saveTsBtn.clicked.connect(self.savePath)
        self.ui.trChangeBtn.clicked.connect(self.trChangedHanle)
        self.send_msg.connect(self.disPlayMsg)
        self.disPlayMsg(f"当前进程ID：{os.getpid()}")

        #变量
        self.trChangedFilePath = None

    def openFile(self):
        file_dialog = QtWidgets.QFileDialog()
        file_dialog.setNameFilters(["Text Files (*.xlsx)"])  # 设置文件过滤器
        if file_dialog.exec_() != QtWidgets.QDialog.Accepted: return
        selected_files = file_dialog.selectedFiles()
        if len(selected_files) == 0 : return
        for selected_file in selected_files:
            self.ui.trXlsPath.setText(selected_file)
    
    def savePath(self):
        directory  = QtWidgets.QFileDialog.getExistingDirectory(None, '选择目录')
        if len(directory) == 0 : return
        self.ui.trChangeXlsPath.setText(directory)

    def trHandle(self):
        my_thread = threading.Thread(target=trHanle,args=(self.ui.trXlsPath.text(),self.send_msg.emit,))
        my_thread.setDaemon(True)
        my_thread.start()

    def trChangedHanle(self):
        my_thread = threading.Thread(target=trChangedHanle,args=(self.ui.trChangeXlsPath.text(),self.send_msg.emit,))
        my_thread.setDaemon(True)
        my_thread.start()

    def saveUI(self):
        saveUI(self.ui,self.configPath)
        self.disPlayMsg('保存成功')

    def disPlayMsg(self,msg):
        self.ui.textEdit.append(msg)

    def setTrChangedFilePath(self,path):
        self.trChangedFilePath = path



if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec_()

