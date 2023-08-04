# coding:utf-8
#!/bin/python

import sys
import os
os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
from chart_view import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
         # 创建一个QWidget作为主窗口的中心部件
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
         # 创建一个垂直布局，并将chart控件添加到布局中
        layout = QVBoxLayout(central_widget)
        self.chartManage = CustomChartManage(layout)
        self.chartManage.createChar()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.resize(1000,800)
    window.show()
    app.exec_()

