# coding:utf-8
#!/bin/python

import sys
import os
import typing
from PyQt5 import QtCore, QtWidgets 
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget,QGraphicsItem
from PyQt5.QtChart import QChart, QChartView, QLineSeries, QDateTimeAxis,QValueAxis,QXYSeries
from PyQt5.QtCore import Qt, QDateTime,QObject
from PyQt5.QtGui import QPainter,QCursor
from PyQt5.QtGui import QWheelEvent,QMouseEvent

class CustomChartView(QChartView):
    def __init__(self, chart):
        super().__init__(chart)
        self.setRenderHint(QPainter.Antialiasing)
        self.setRubberBand(QChartView.RectangleRubberBand)
        self.setDragMode(QChartView.ScrollHandDrag)
        self.setMouseTracking(True)
        self.drag_start_pos = None
        self.chart = chart
        
    def wheelEvent(self, event: QWheelEvent):
        delta = event.angleDelta().y() / 120
            # 鼠标在横坐标上滚动，调整横坐标范围
        
        if event.pos().x() > self.height() - event.pos().y():
            factor = 1.1 if delta < 0 else 0.9
            axis = self.chart.axisX()
            range_start = axis.min().toMSecsSinceEpoch()
            range_end = axis.max().toMSecsSinceEpoch()
            range_length = range_end - range_start
            range_center = (range_start + range_end) / 2
            new_range_length = range_length * factor
            new_range_start = int(range_center - new_range_length / 2)
            new_range_end = int(range_center + new_range_length / 2)
            axis.setRange(QDateTime.fromMSecsSinceEpoch(new_range_start), 
                            QDateTime.fromMSecsSinceEpoch(new_range_end))
        else:
            # 鼠标在纵坐标上滚动，调整纵坐标范围
            y_axis = self.chart.axisY()
            # 鼠标在纵坐标轴上滚动
            new_min = y_axis.min() + delta
            new_max = y_axis.max() - delta
            y_axis.setRange(new_min,new_max)
        super().wheelEvent(event)

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drag_start_pos = event.pos()

    def mouseMoveEvent(self, event: QMouseEvent):
        if self.drag_start_pos is not None:
            delta = self.drag_start_pos - event.pos()
            self.chart.scroll(delta.x(), -delta.y())
            self.drag_start_pos = event.pos()

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drag_start_pos = None    

class logSeries(QLineSeries):
    def __init__(self, parent= None) -> None:
        super().__init__(parent)
        
        # self.setPointLabelsVisible(True)
        self.setPointLabelsFormat("@yPoint")
        self.setPointsVisible(True)
        self.setName("测试")
        self.chart = None

    #要在数据之后调用
    def setChar(self,chart):
        assert isinstance(chart,QChart)
        self.chart = chart
        self.chart.addSeries(self) # 这一步要在 attachAxis 前面
        # 将线系列与轴绑定
        self.attachAxis(self.chart.axisX())
        self.attachAxis(self.chart.axisY())

class CustomChart(QChart):
    def __init__(self) -> None:
        super().__init__()

        self.chart_view = CustomChartView(self)
        # 创建一个时间轴
        self.axis_x = QDateTimeAxis()
        self.axis_x.setTitleText("时间")
        self.axis_x.setFormat("yyyy/MM/dd hh:mm:ss")
         # 创建一个数值轴
        self.axis_y = QValueAxis()

        self.addAxis(self.axis_x, Qt.AlignBottom)
        self.addAxis(self.axis_y, Qt.AlignLeft)


         # 生成示例数据
        x = ['2023/07/11 10:37:30', '2023/07/11 10:37:40', '2023/07/11 10:37:45', '2023/07/11 10:37:50', '2023/07/11 10:37:56']  # 时间
        y = [10, 20, 15, 25, 30]  # 数值

        # 创建一个线系列
        series = logSeries() 
        # 添加数据到线系列

        lastSecs=0
        for p in range(10):
            for i in range(len(x)):
                if p == 0:
                    lastSecs = QDateTime.fromString(x[i],'yyyy/MM/dd hh:mm:ss').toMSecsSinceEpoch()
                    series.append(lastSecs, y[i])
                else:
                    lastSecs= lastSecs+60000*(i+1)
                    series.append(lastSecs, y[i])


        # series1 = logSeries() 
        #  # 添加数据到线系列
        # for i in range(len(x)):
        #     series1.append(QDateTime.fromString(x[i],'yyyy/MM/dd hh:mm:ss').toMSecsSinceEpoch(), y[i]+1)
        # series1.setChar(self.chart)
        series.setChar(self)

class CustomChartManage():
    def __init__(self,layout) -> None:
        self.layout = layout
        self.charts = []

    def createChar(self):
        chart = CustomChart()
        self.layout.addWidget(chart.chart_view)

