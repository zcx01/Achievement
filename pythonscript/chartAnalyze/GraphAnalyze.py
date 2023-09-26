# coding:utf-8
#!/bin/python

import sys
import os
os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
pyFileDir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(pyFileDir+"/loganalyze")
import pyqtgraph as pg
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QRect

app = QApplication(sys.argv)
# 定义轴 : right 文字的方向
a2 = pg.AxisItem("right")
a3 = pg.AxisItem("right")
a4 = pg.AxisItem("right")
a5 = pg.AxisItem("left")
a6 = pg.AxisItem("left")
 
# 视图框，用于存放折线
p2 = pg.PlotItem()
p3 = pg.PlotItem()
p4 = pg.PlotItem()
p5 = pg.PlotItem()
p6 = pg.PlotItem()

v2 = p2.vb
v3 = p3.vb
v4 = p4.vb
v5 = p5.vb
v6 = p6.vb
 
# 创建视图
pw = pg.GraphicsView()
pw.setWindowTitle('pyqtgraph 标题')
pw.show()
 
# 创建图形布局
l = pg.GraphicsLayout()
# 设置视图中心小部件 为该布局
pw.setCentralWidget(l)
 
# 向布局添加轴
# 注意这里col参数的位置
l.addItem(p2, row = 1, col = 3,  rowspan=1, colspan=1)
l.addItem(p3, row = 2, col = 3,  rowspan=1, colspan=1)
l.addItem(p4, row = 3, col = 3,  rowspan=1, colspan=1)
l.addItem(p5, row = 4, col = 3,  rowspan=1, colspan=1)
l.addItem(p6, row = 5, col = 3,  rowspan=1, colspan=1)
 
# 至少有一个绘图项使用它自己的视图框和左轴。
pI = pg.PlotItem()  # 定义一个绘图项
v1 = pI.vb # 对绘图项的视图框的引用
l.addItem(pI, row = 6, col = 3,  rowspan=1, colspan=1) # 添加绘图框到图形布局
 
# 向绘图框添加视图框
l.scene().addItem(v2)
l.scene().addItem(v3)
l.scene().addItem(v4)
l.scene().addItem(v5)
l.scene().addItem(v6)
 
# 用轴连接 存放折线的视图框
a2.linkToView(v2)
a3.linkToView(v3)
a4.linkToView(v4)
a5.linkToView(v5)
a6.linkToView(v6)
 
# 链接视图框,我也不知道干嘛这样写，但是写上就会在--绘图项的视图框上，整体缩放所有的折线
v2.setXLink(v1)
v3.setXLink(v2)
v4.setXLink(v3)
v5.setXLink(v4)
v6.setXLink(v5)
 
# 轴标签
pI.getAxis("left").setLabel('axis 1 in ViewBox of PlotItem', color='#FFFFFF')
a2.setLabel('axis 2 in Viewbox 2', color='#2E2EFE')
a3.setLabel('axis 3 in Viewbox 3', color='#2EFEF7')
a4.setLabel('axis 4 in Viewbox 4', color='#2EFE2E')
a5.setLabel('axis 5 in Viewbox 5', color='#FFFF00')
a6.setLabel('axis 6 in Viewbox 6', color='#FE2E64')
 
# slot: 插槽：调整大小时更新视图
def updateViews():
    # setGeometry设置几何图形
    # sceneBoundingRect场景边界矩形
    v2.setGeometry(v1.sceneBoundingRect())
    v3.setGeometry(v1.sceneBoundingRect())
    v4.setGeometry(v1.sceneBoundingRect())
    v5.setGeometry(v1.sceneBoundingRect())
    v6.setGeometry(v1.sceneBoundingRect())
    pass
 
# 折线点值 （轴刻度范围自动按最大最小值生成）
x = [1,2,3,4,5,6]
y1 = [0,4,6,8,10,4]
y2 = [0,5,7,9,11,3]
y3 = [0,1,2,3,4,12]
y4 = [0,8,0.3,0.4,2,5]
y5 = [0,1,6,4,2,1]
y6 = [0,0.2,0.3,0.4,0.5,0.6]
 
# 给绘图项的视图框添加折线xy点的值，折线颜色
v1.addItem(pg.PlotCurveItem(x, y1, pen='#FFFFFF'))
v2.addItem(pg.PlotCurveItem(x, y2, pen='#2E2EFE'))
v3.addItem(pg.PlotCurveItem(x, y3, pen='#2EFEF7'))
v4.addItem(pg.PlotCurveItem(x, y4, pen='#2EFE2E'))
v5.addItem(pg.PlotCurveItem(x, y5, pen='#FFFF00'))
v6.addItem(pg.PlotCurveItem(x, y6, pen='#FE2E64'))
#
#  调整大小时更新
v1.sigResized.connect(updateViews)
 
# 开始时自动调整一次以适应视图
# enableAutoRange 启用自动范围
v2.enableAutoRange(axis= pg.ViewBox.XYAxes, enable=True)
v3.enableAutoRange(axis= pg.ViewBox.XYAxes, enable=True)
v4.enableAutoRange(axis= pg.ViewBox.XYAxes, enable=True)
v5.enableAutoRange(axis= pg.ViewBox.XYAxes, enable=True)
v6.enableAutoRange(axis= pg.ViewBox.XYAxes, enable=True)
 
updateViews()
app.exec_()
 

