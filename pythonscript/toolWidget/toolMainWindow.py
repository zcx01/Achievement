# coding:utf-8
#!/bin/python

import sys
import os
from PyQt5 import QtCore, QtGui,QtWidgets
from PyQt5 import *
pyFileDir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(pyFileDir+"/Handle")
sys.path.append(pyFileDir+"/customWidget")
sys.path.append(pyFileDir+"/dlg")

os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
from Ui_toolMainWindow import *
from Handle.configFile import *
from Handle.handle import *
from dlg.addTextDlg import *
from customWidget.lableLineEdit import *
import threading

class MainWindow(QtWidgets.QMainWindow):
    send_msg = QtCore.pyqtSignal(str) 
    def __init__(self):
        super().__init__()
        self.configPath = pyFileDir+"/Handle/config.json"
        self.projecGroup = QtWidgets.QButtonGroup()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        initUI(self.ui,self.configPath,self.ui.verticalLayout_7,self.ui.horizontalLayout_12,self.selecteProject,self.projecGroup)
        defFileName=['ic_service','ic_chime']
        self.ui.pushCbx.addItems(defFileName)
        self.ui.pushCbx.addItems(getPushFiles())

        setDisPlayMsg(self.send_msg.emit)
        self.ui.openTsBtn.clicked.connect(self.openFile)
        self.ui.saveBtn.clicked.connect(self.saveUI)
        self.ui.trBtn.clicked.connect(self.trHandle)
        self.ui.saveTsBtn.clicked.connect(self.savePath)
        self.ui.trChangeBtn.clicked.connect(self.trChangedHanle)
        self.ui.openTrCBtn.clicked.connect(self.openTrChangedFile)
        self.ui.openTrCPathBtn.clicked.connect(self.openTrChangedPath)
        self.ui.addProjectBtn.clicked.connect(self.addPrjectBtn)
        self.ui.removePrjectBtn.clicked.connect(self.removePrject)
        self.ui.updateXlsBtn.clicked.connect(self.canHanleBtn)
        self.ui.addSigBtn.clicked.connect(self.canHanleBtn)
        self.ui.addWSigBtn.clicked.connect(self.canHanleBtn)
        self.ui.pushFileBtn.clicked.connect(self.pushFileHanleBtn)
        self.ui.pushFileEdit.textChanged.connect(self.pushFileEditChanged)
        self.send_msg.connect(self.disPlayMsg)
        self.disPlayMsg(f"当前进程ID：{os.getpid()}")

        #ui状态
        self.ui.groupBox.setEnabled(getJsValue('icText') != 0)

        #变量
        self.trChangedFilePaths = []

    def informationDlg(self,content):
        return QtWidgets.QMessageBox.information(self,'提示',content,
                                             QtWidgets.QMessageBox.Ok|QtWidgets.QMessageBox.Cancel) == QtWidgets.QMessageBox.Ok
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
        self.ui.downLoadPath.setText(directory)

    def trHandle(self):
        my_thread = threading.Thread(target=trHanle,args=(self.ui.trXlsPath.text(),))
        my_thread.setDaemon(True)
        my_thread.start()

    def trChangedHanle(self):
        my_thread = threading.Thread(target=trChangedHanle,args=(self.ui.downLoadPath.text(),self.setTrChangedFilePath,))
        my_thread.setDaemon(True)
        my_thread.start()
    
    def saveUI(self):
        saveUI(self.ui,self.configPath)
        self.disPlayMsg('保存成功')

    def disPlayMsg(self,msg):
        self.ui.textEdit.append(msg)

    def setTrChangedFilePath(self,path):
        self.trChangedFilePaths.append(path)

    def openTrChangedFile(self):
        if len(self.trChangedFilePaths) != 0:
            openFileUseDefault(self.trChangedFilePaths[len(self.trChangedFilePaths) -1])
        else:
            self.disPlayMsg('没有生成翻译文件')

    def openTrChangedPath(self):
        openFileUseDefault(self.ui.downLoadPath.text())

    def selecteProject(self):
        btn = self.sender()
        setCurrentProjectName(btn.text())
        self.disPlayMsg(f'当前路径: {getCurrentProjectPath()}')

    def addPrjectBtn(self):
        dlg = addTextDlg()
        dlg.add_text.connect(self.addPrject)
        dlg.exec()
        
    def addPrject(self,text):
        leE,projectBtn = createProject(self.ui.verticalLayout_7,self.ui.horizontalLayout_12,self.selecteProject,self.projecGroup)
        leE.setText(text,getProjectPath(text))


    def removePrject(self):
        btn = getCheckBtn()
        if btn == None:
            self.disPlayMsg('请选中项目')
            return
        if not self.informationDlg(f'是否删除{btn.text()}项目'):
            return
        removePrject(self.ui.verticalLayout_7,self.ui.horizontalLayout_12,btn)
        setCurrentProjectName('')
    
    def getSelectLineText(self,textEdit):
        assert isinstance(textEdit,QtWidgets.QTextEdit)
        cursor = textEdit.textCursor()
        return textEdit.document().findBlockByLineNumber(cursor.blockNumber()).text()
    
    def canHanleBtn(self):
        btn = self.sender()
        canHandleType = None
        if btn == self.ui.updateXlsBtn:
            canHandleType = CanHanleType.UpdateXls
        elif btn == self.ui.addSigBtn:
            canHandleType = CanHanleType.AddSig
        elif btn == self.ui.addWSigBtn:
            canHandleType = CanHanleType.AddWSig
        else:
            return
        text = self.getSelectLineText(self.ui.canTextEdit)
        my_thread = threading.Thread(target=canHanle,args=(canHandleType,text,))
        my_thread.setDaemon(True)
        my_thread.start()

    def pushFileHanleBtn(self):
        fileName = self.ui.pushCbx.currentText()
        my_thread = threading.Thread(target=pushFileHanle,args=(fileName,self.ui.scpFileBtn.isChecked(),))
        my_thread.setDaemon(True)
        my_thread.start()

    def pushFileEditChanged(self):
        text = self.ui.pushFileEdit.text()
        for index in range(self.ui.pushCbx.count()):
            cbxText = self.ui.pushCbx.itemText(index)
            if text in cbxText:
                self.ui.pushCbx.setCurrentIndex(index)
                return
            
if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec_()

