# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'c:\Users\chengxiong.zhu\Desktop\Achievement\pythonscript\toolWidget\toolMainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1325, 686)
        MainWindow.setMouseTracking(True)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setMouseTracking(True)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setObjectName("tabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.tab)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.groupBox = QtWidgets.QGroupBox(self.tab)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.trXlsPath = QtWidgets.QLineEdit(self.groupBox)
        self.trXlsPath.setInputMask("")
        self.trXlsPath.setObjectName("trXlsPath")
        self.horizontalLayout.addWidget(self.trXlsPath)
        self.openTsBtn = QtWidgets.QPushButton(self.groupBox)
        self.openTsBtn.setObjectName("openTsBtn")
        self.horizontalLayout.addWidget(self.openTsBtn)
        self.trBtn = QtWidgets.QPushButton(self.groupBox)
        self.trBtn.setObjectName("trBtn")
        self.horizontalLayout.addWidget(self.trBtn)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        self.horizontalLayout_9 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_9.setObjectName("horizontalLayout_9")
        self.trChangeXlsPath = QtWidgets.QLineEdit(self.groupBox)
        self.trChangeXlsPath.setInputMask("")
        self.trChangeXlsPath.setCursorPosition(0)
        self.trChangeXlsPath.setObjectName("trChangeXlsPath")
        self.horizontalLayout_9.addWidget(self.trChangeXlsPath)
        self.saveTsBtn = QtWidgets.QPushButton(self.groupBox)
        self.saveTsBtn.setObjectName("saveTsBtn")
        self.horizontalLayout_9.addWidget(self.saveTsBtn)
        self.trChangeBtn = QtWidgets.QPushButton(self.groupBox)
        self.trChangeBtn.setObjectName("trChangeBtn")
        self.horizontalLayout_9.addWidget(self.trChangeBtn)
        self.openTrCBtn = QtWidgets.QPushButton(self.groupBox)
        self.openTrCBtn.setObjectName("openTrCBtn")
        self.horizontalLayout_9.addWidget(self.openTrCBtn)
        self.verticalLayout_2.addLayout(self.horizontalLayout_9)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem)
        self.verticalLayout_5.addWidget(self.groupBox)
        self.tabWidget.addTab(self.tab, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.tab_2)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label = QtWidgets.QLabel(self.tab_2)
        self.label.setMinimumSize(QtCore.QSize(100, 0))
        self.label.setMaximumSize(QtCore.QSize(100, 16777215))
        self.label.setObjectName("label")
        self.horizontalLayout_2.addWidget(self.label)
        self.ipLE = QtWidgets.QLineEdit(self.tab_2)
        self.ipLE.setObjectName("ipLE")
        self.horizontalLayout_2.addWidget(self.ipLE)
        self.verticalLayout_3.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_2 = QtWidgets.QLabel(self.tab_2)
        self.label_2.setMinimumSize(QtCore.QSize(100, 0))
        self.label_2.setMaximumSize(QtCore.QSize(100, 16777215))
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_3.addWidget(self.label_2)
        self.userLE = QtWidgets.QLineEdit(self.tab_2)
        self.userLE.setObjectName("userLE")
        self.horizontalLayout_3.addWidget(self.userLE)
        self.verticalLayout_3.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_3 = QtWidgets.QLabel(self.tab_2)
        self.label_3.setMinimumSize(QtCore.QSize(100, 0))
        self.label_3.setMaximumSize(QtCore.QSize(100, 16777215))
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_4.addWidget(self.label_3)
        self.pwLE = QtWidgets.QLineEdit(self.tab_2)
        self.pwLE.setText("")
        self.pwLE.setEchoMode(QtWidgets.QLineEdit.PasswordEchoOnEdit)
        self.pwLE.setObjectName("pwLE")
        self.horizontalLayout_4.addWidget(self.pwLE)
        self.verticalLayout_3.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.label_4 = QtWidgets.QLabel(self.tab_2)
        self.label_4.setMinimumSize(QtCore.QSize(100, 0))
        self.label_4.setMaximumSize(QtCore.QSize(100, 16777215))
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_7.addWidget(self.label_4)
        self.icTextLE = QtWidgets.QLineEdit(self.tab_2)
        self.icTextLE.setText("")
        self.icTextLE.setEchoMode(QtWidgets.QLineEdit.Normal)
        self.icTextLE.setObjectName("icTextLE")
        self.horizontalLayout_7.addWidget(self.icTextLE)
        self.verticalLayout_3.addLayout(self.horizontalLayout_7)
        self.horizontalLayout_8 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_8.setObjectName("horizontalLayout_8")
        self.label_5 = QtWidgets.QLabel(self.tab_2)
        self.label_5.setMinimumSize(QtCore.QSize(100, 0))
        self.label_5.setMaximumSize(QtCore.QSize(100, 16777215))
        self.label_5.setObjectName("label_5")
        self.horizontalLayout_8.addWidget(self.label_5)
        self.trXlsPathS = QtWidgets.QLineEdit(self.tab_2)
        self.trXlsPathS.setText("")
        self.trXlsPathS.setEchoMode(QtWidgets.QLineEdit.Normal)
        self.trXlsPathS.setObjectName("trXlsPathS")
        self.horizontalLayout_8.addWidget(self.trXlsPathS)
        self.verticalLayout_3.addLayout(self.horizontalLayout_8)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_3.addItem(spacerItem1)
        self.horizontalLayout_6.addLayout(self.verticalLayout_3)
        self.textEdit_2 = QtWidgets.QTextEdit(self.tab_2)
        self.textEdit_2.setReadOnly(True)
        self.textEdit_2.setObjectName("textEdit_2")
        self.horizontalLayout_6.addWidget(self.textEdit_2)
        self.verticalLayout_4.addLayout(self.horizontalLayout_6)
        self.tabWidget.addTab(self.tab_2, "")
        self.verticalLayout.addWidget(self.tabWidget)
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_5.addItem(spacerItem2)
        self.saveBtn = QtWidgets.QPushButton(self.centralwidget)
        self.saveBtn.setObjectName("saveBtn")
        self.horizontalLayout_5.addWidget(self.saveBtn)
        self.verticalLayout.addLayout(self.horizontalLayout_5)
        self.textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit.setObjectName("textEdit")
        self.verticalLayout.addWidget(self.textEdit)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1325, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.groupBox.setTitle(_translate("MainWindow", "翻译操作"))
        self.trXlsPath.setPlaceholderText(_translate("MainWindow", "请输入翻译文件路径,sheet的名称必须是SIC"))
        self.openTsBtn.setText(_translate("MainWindow", "打开文件"))
        self.trBtn.setText(_translate("MainWindow", "翻译"))
        self.trChangeXlsPath.setPlaceholderText(_translate("MainWindow", "请输入文本改变的路径"))
        self.saveTsBtn.setText(_translate("MainWindow", "保存路径"))
        self.trChangeBtn.setText(_translate("MainWindow", "保存"))
        self.openTrCBtn.setText(_translate("MainWindow", "打开文件所在路径"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("MainWindow", "操作"))
        self.label.setText(_translate("MainWindow", "远程ip:"))
        self.label_2.setText(_translate("MainWindow", "用户名"))
        self.label_3.setText(_translate("MainWindow", "密码"))
        self.label_4.setText(_translate("MainWindow", "ic_text的路径:"))
        self.label_5.setText(_translate("MainWindow", "翻译表格远程路径:"))
        self.textEdit_2.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">说明:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">必须远程操作必须设置远程ip、用户名</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">必须安装ssh</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">远程翻译脚本的前置条件:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">必须有ic_text脚本</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">需要配置无密连接</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("MainWindow", "设置"))
        self.saveBtn.setText(_translate("MainWindow", "应用"))