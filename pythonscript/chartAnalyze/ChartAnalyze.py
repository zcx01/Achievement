# coding:utf-8
#!/bin/python

import sys
import os
pyFileDir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(pyFileDir+"/loganalyze")
os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
from chart_view import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
         # 创建一个QWidget作为主窗口的中心部件
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        mainLayout = QHBoxLayout(central_widget)
        mainLayout.setContentsMargins(0,0,0,0)

         # 创建一个垂直布局，并将chart控件添加到布局中
        chart_layout = QVBoxLayout()
        chart_layout.setSpacing(0)
        chart_layout.setContentsMargins(0,0,0,0)
        self.chartManage = CustomChartManage(chart_layout)
        self.chartManage.setConfig(pyFileDir+"/loganalyze/logConfig.json")
        mainLayout.addLayout(chart_layout)

        self.chartManage.loadLog(["C:\\Users\\chengxiong.zhu\\Downloads\\log分析\\2023-07-26\\log_001521_20230724-193751.dlt.gz"])
        self.chartManage.searchkeyWords("HUD_CDC_5C5")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.resize(1000,800)
    window.show()
    app.exec_()

