# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'c:\Users\chengxiong.zhu\Desktop\Achievement\pythonscript\chartAnalyze\charMainWiget.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1342, 944)
        MainWindow.setMouseTracking(True)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setMouseTracking(True)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.keyWidget = QtWidgets.QWidget(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.keyWidget.sizePolicy().hasHeightForWidth())
        self.keyWidget.setSizePolicy(sizePolicy)
        self.keyWidget.setMouseTracking(True)
        self.keyWidget.setObjectName("keyWidget")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.keyWidget)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setSpacing(0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.lefWidget = QtWidgets.QWidget(self.keyWidget)
        self.lefWidget.setMinimumSize(QtCore.QSize(0, 0))
        self.lefWidget.setMaximumSize(QtCore.QSize(230, 16777215))
        self.lefWidget.setMouseTracking(True)
        self.lefWidget.setObjectName("lefWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.lefWidget)
        self.verticalLayout.setContentsMargins(0, 0, 3, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.toolWidget = QtWidgets.QWidget(self.lefWidget)
        self.toolWidget.setObjectName("toolWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.toolWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.widget_4 = QtWidgets.QWidget(self.toolWidget)
        self.widget_4.setObjectName("widget_4")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.widget_4)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setSpacing(0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.openFileBtn = QtWidgets.QPushButton(self.widget_4)
        self.openFileBtn.setObjectName("openFileBtn")
        self.verticalLayout_4.addWidget(self.openFileBtn)
        self.searchBtn = QtWidgets.QPushButton(self.widget_4)
        self.searchBtn.setEnabled(True)
        self.searchBtn.setObjectName("searchBtn")
        self.verticalLayout_4.addWidget(self.searchBtn)
        self.horizontalLayout.addWidget(self.widget_4)
        self.widget_5 = QtWidgets.QWidget(self.toolWidget)
        self.widget_5.setObjectName("widget_5")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.widget_5)
        self.verticalLayout_8.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_8.setSpacing(0)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.addKeyBtn = QtWidgets.QPushButton(self.widget_5)
        self.addKeyBtn.setObjectName("addKeyBtn")
        self.verticalLayout_8.addWidget(self.addKeyBtn)
        self.removeKeyBtn = QtWidgets.QPushButton(self.widget_5)
        self.removeKeyBtn.setEnabled(False)
        self.removeKeyBtn.setObjectName("removeKeyBtn")
        self.verticalLayout_8.addWidget(self.removeKeyBtn)
        self.horizontalLayout.addWidget(self.widget_5)
        self.widget_3 = QtWidgets.QWidget(self.toolWidget)
        self.widget_3.setObjectName("widget_3")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.widget_3)
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_3.setSpacing(0)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.testRulerBtn = QtWidgets.QPushButton(self.widget_3)
        self.testRulerBtn.setCheckable(False)
        self.testRulerBtn.setObjectName("testRulerBtn")
        self.verticalLayout_3.addWidget(self.testRulerBtn)
        self.testRulerCbx = QtWidgets.QComboBox(self.widget_3)
        self.testRulerCbx.setObjectName("testRulerCbx")
        self.testRulerCbx.addItem("")
        self.testRulerCbx.addItem("")
        self.testRulerCbx.addItem("")
        self.verticalLayout_3.addWidget(self.testRulerCbx)
        self.horizontalLayout.addWidget(self.widget_3)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout.addWidget(self.toolWidget)
        self.tableWidget = QtWidgets.QTableWidget(self.lefWidget)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)
        self.verticalLayout.addWidget(self.tableWidget)
        self.textEdit = QtWidgets.QTextEdit(self.lefWidget)
        self.textEdit.setObjectName("textEdit")
        self.verticalLayout.addWidget(self.textEdit)
        self.verticalLayout.setStretch(1, 10)
        self.verticalLayout.setStretch(2, 5)
        self.horizontalLayout_2.addWidget(self.lefWidget)
        self.widget = QtWidgets.QWidget(self.keyWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widget.sizePolicy().hasHeightForWidth())
        self.widget.setSizePolicy(sizePolicy)
        self.widget.setMouseTracking(True)
        self.widget.setObjectName("widget")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout_3.setContentsMargins(6, 0, 0, 0)
        self.horizontalLayout_3.setSpacing(0)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.horizontalLayout_2.addWidget(self.widget)
        self.verticalLayout_6.addWidget(self.keyWidget)
        self.widget_2 = QtWidgets.QWidget(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.widget_2.sizePolicy().hasHeightForWidth())
        self.widget_2.setSizePolicy(sizePolicy)
        self.widget_2.setMinimumSize(QtCore.QSize(0, 30))
        self.widget_2.setObjectName("widget_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.widget_2)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.progressBar = QtWidgets.QProgressBar(self.widget_2)
        self.progressBar.setEnabled(True)
        self.progressBar.setProperty("value", 0)
        self.progressBar.setObjectName("progressBar")
        self.verticalLayout_2.addWidget(self.progressBar)
        self.verticalLayout_6.addWidget(self.widget_2)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1342, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.openFileBtn.setText(_translate("MainWindow", "打开"))
        self.searchBtn.setText(_translate("MainWindow", "搜索"))
        self.addKeyBtn.setText(_translate("MainWindow", "添加关键字"))
        self.removeKeyBtn.setText(_translate("MainWindow", "删除关键字"))
        self.testRulerBtn.setText(_translate("MainWindow", "测试尺个数"))
        self.testRulerCbx.setToolTip(_translate("MainWindow", "测试次的个数"))
        self.testRulerCbx.setItemText(0, _translate("MainWindow", "0"))
        self.testRulerCbx.setItemText(1, _translate("MainWindow", "1"))
        self.testRulerCbx.setItemText(2, _translate("MainWindow", "2"))