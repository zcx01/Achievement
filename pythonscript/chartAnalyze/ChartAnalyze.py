# coding:utf-8
#!/bin/python

import sys
import os
from PyQt5 import QtCore, QtGui
pyFileDir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(pyFileDir+"/loganalyze")
sys.path.append(pyFileDir+"/dlg")
os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
from chart_view import *
from graph_view import *
from Ui_charMainWiget import *
from PyQt5 import *
from dlg.addTextDlg import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        ui = Ui_MainWindow()
        ui.setupUi(self)
        self.ui = ui
        self.mouseClick = False
        self.startPos = None


        # 创建菜单栏
        menubar = self.menuBar()
        # 创建文件菜单
        set_menu = menubar.addMenu('文件')
        # 创建动作（菜单项）
        new_action = QtWidgets.QAction('dltExe', self)
        # new_action.triggered.connect()
        open_action =QtWidgets.QAction('打开', self)
        save_action = QtWidgets.QAction('保存', self)

        # 将动作添加到文件菜单中
        set_menu.addAction(new_action)
        set_menu.addAction(open_action)
        set_menu.addAction(save_action)


        ui.tableWidget.setColumnCount(1)
        header_labels = ['名称']
        ui.tableWidget.setHorizontalHeaderLabels(header_labels)
        ui.tableWidget.setSelectionMode(QtWidgets.QAbstractItemView.ExtendedSelection)
        ui.tableWidget.itemSelectionChanged.connect(self.tableWidgetSelectChanged)

        ui.progressBar.setVisible(False)
        ui.searchBtn.clicked.connect(self.searchkeyWords)
        ui.testRulerCbx.currentIndexChanged.connect(self.testRulerCbxChanged)
        ui.testRulerBtn.clicked.connect(self.testRulerBtn)
        ui.addKeyBtn.clicked.connect(self.onAddKeyTriggered)
        ui.removeKeyBtn.clicked.connect(self.removekey)
        ui.openFileBtn.clicked.connect(self.openFile)
        self.ui.progressBar.setRange(0,100)


        # 创建一个垂直布局，并将chart控件添加到布局中
        chart_layout = ui.horizontalLayout_3
        self.chartManage = CustomGraphManage(chart_layout)
        self.chartManage.update_Progress.connect(self.updataProgress)
        self.chartManage.send_msg.connect(self.disPlayMsg)

        self.defaultDir = r'C:/Users/chengxiong.zhu/Downloads/log分析/'
        # self.chartManage.loadLog([r"C:/Users/chengxiong.zhu/Downloads/log分析/2023-09-13/log_000268_20230912-095121.dlt"])
        self.add_key("DrivingInfo/PowerStatus")
        self.add_key("DrivingInfo/Speed")


        self.resize(1000,800)
        self.show()
        if not self.chartManage.setConfig(pyFileDir+"/loganalyze/logConfig.json"):
            isTipSetDltExe = self.chartManage.getConfigValue('isTipSetDltExe',True)
            if isTipSetDltExe:
                if self.informationDlg("是否设置dltexe的路径"):
                    file_dialog = QtWidgets.QFileDialog(self,'设置dltexe的路径')
                    if file_dialog.exec_() == QtWidgets.QDialog.Accepted:
                        selected_files = file_dialog.selectedFiles()
                        if len(selected_files) != 0:
                            print(selected_files[0])
                            self.chartManage.setDltExe(selected_files[0])
                else:
                    self.chartManage.modifyConfig('isTipSetDltExe',False)

    def informationDlg(self,content):
        return QtWidgets.QMessageBox.information(self,'提示',content,
                                             QtWidgets.QMessageBox.Ok|QtWidgets.QMessageBox.Cancel) == QtWidgets.QMessageBox.Ok
             
    
    def mousePressEvent(self, a0: QMouseEvent):
        if a0.button() == Qt.LeftButton and self.cursor() == Qt.SplitHCursor:
            self.mouseClick = True
            self.startPos = a0.pos()
        return super().mousePressEvent(a0)
    
    def mouseMoveEvent(self, a0: QMouseEvent):
        # print(a0.pos())
        if self.mouseClick == True:
            delta = a0.pos().x() - self.startPos.x()
            self.ui.lefWidget.setFixedWidth(self.ui.lefWidget.width() + delta)
            self.startPos = a0.pos()
        else:
            leftCursor = self.ui.lefWidget.mapFromGlobal(QCursor.pos())
            if abs(leftCursor.x() - self.ui.lefWidget.width()) < 3:
                self.setCursor(Qt.SplitHCursor)
            elif not self.mouseClick:
                self.setCursor(Qt.ArrowCursor)

        return super().mouseMoveEvent(a0)
    
    def mouseReleaseEvent(self, a0: QMouseEvent):
        if a0.button() == Qt.LeftButton:
            self.mouseClick = False
            self.setCursor(Qt.ArrowCursor)
        return super().mouseReleaseEvent(a0)

    def openFile(self):
        file_dialog = QtWidgets.QFileDialog()
        file_dialog.setDirectory(self.defaultDir)
        file_dialog.setNameFilters(["Text Files (*.txt *.dlt)"])  # 设置文件过滤器
        file_dialog.setFileMode(QtWidgets.QFileDialog.ExistingFiles)  # 设置文件对话框为多选模式
        if file_dialog.exec_() != QtWidgets.QDialog.Accepted: return
        selected_files = file_dialog.selectedFiles()
        if len(selected_files) == 0 : return
        self.ui.textEdit.clear()
        self.chartManage.loadLog(selected_files)
        for selected_file in selected_files:
            self.defaultDir = os.path.dirname(selected_file)
            self.ui.textEdit.append(os.path.basename(selected_file))

    def onAddKeyTriggered(self):
        dlg = addTextDlg()
        dlg.add_text.connect(self.add_key)
        dlg.exec()

    def removekey(self):
        if len(self.ui.tableWidget.selectedItems()) > 1:
            if not self.informationDlg('是否删除选择的关键字'):
                return
            
        selected_rows = []
        for item in self.ui.tableWidget.selectedItems():
            if item.column() == 0:
                text = item.text()
                self.chartManage.removeKeyWord(text)
                selected_rows.append(item.row())

        for row in sorted(selected_rows, reverse=True):
            self.ui.tableWidget.removeRow(row)


    def add_key(self,text):
        if not self.chartManage.addkeyWords(text):
            return
        currentIndex = 0
        self.ui.tableWidget.insertRow(currentIndex)
        item1 = QtWidgets.QTableWidgetItem(text)
        self.ui.tableWidget.setItem(currentIndex,0,item1)

    def testRulerBtn(self):
        if self.ui.testRulerBtn.isCheckable():
            currentLineIndex = self.chartManage.getCurrentLineIndex()
            if self.chartManage.currentlineVisibleCount == 2:
                if currentLineIndex == 0:
                    self.ui.testRulerBtn.setText('测量尺2')
                    self.chartManage.setCurrentLine(2)
                elif currentLineIndex == 1:
                    self.ui.testRulerBtn.setText('测量尺1')
                    self.chartManage.setCurrentLine(1)

    def testRulerCbxChanged(self,index):
        self.chartManage.setLineCount(index)
        if index == 0:
            self.ui.testRulerBtn.setCheckable(False)
            self.ui.testRulerBtn.setText('测量尺数量')
        else:
            if not self.ui.testRulerBtn.isCheckable():
                self.ui.testRulerBtn.setText('测量尺1')
                self.ui.testRulerBtn.setCheckable(True)
                currentLineIndex = self.chartManage.getCurrentLineIndex()
                if currentLineIndex == -1:
                    self.chartManage.setCurrentLine(1)
            
    def searchkeyWords(self):
        self.ui.progressBar.setVisible(True)
        self.chartManage.clearLog()
        self.chartManage.searchkeyWords()

    def tableWidgetSelectChanged(self):
        self.ui.removeKeyBtn.setEnabled(len(self.ui.tableWidget.selectedItems()) > 0)

    def updataProgress(self,currentProgress):
        if currentProgress == 100:
            self.ui.progressBar.setVisible(False)
        self.ui.progressBar.setValue(currentProgress)
        
    def disPlayMsg(self,msg):
        self.ui.textEdit.append(msg)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    app.exec_()

