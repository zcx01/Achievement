# coding:utf-8
#!/bin/python

import sys
import os
import typing
from PyQt5 import QtCore, QtWidgets 
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget,QGraphicsItem,QHBoxLayout
from PyQt5.QtChart import QChart, QChartView, QLineSeries, QDateTimeAxis,QValueAxis,QXYSeries
from PyQt5.QtCore import Qt, QDateTime,QObject,QMargins,pyqtSignal
from PyQt5.QtGui import QPainter,QCursor
from PyQt5.QtGui import QWheelEvent,QMouseEvent
from loganalyze.baseAnalyze import *
from loganalyze.commonfun import *

class CustomChartView(QChartView):
    def __init__(self,chart,chars):
        super().__init__(chart)
        self.setRenderHint(QPainter.Antialiasing)
        self.setRubberBand(QChartView.RectangleRubberBand)
        self.setDragMode(QChartView.ScrollHandDrag)
        self.setContentsMargins(0, 0, 0, 0)
        self.setMouseTracking(True)
        self.drag_start_pos = None
        self.chart = chart
        self.charts = chars

    def viewChanged(self):
        for chart in self.charts: 
            chart.chartViewChanged()
        
    def wheelEvent(self, event: QWheelEvent):
        delta = event.angleDelta().y() / 120
        # 鼠标在横坐标上滚动，调整横坐标范围
        if event.pos().x() > self.height() - event.pos().y():
            factor = 1.1 if delta < 0 else 0.9
            for chart in self.charts:
                axis = chart.axisX()
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
        self.viewChanged()

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drag_start_pos = event.pos()

    def mouseMoveEvent(self, event: QMouseEvent):
        if self.drag_start_pos is not None:
            delta = self.drag_start_pos - event.pos()
            self.chart.scroll(delta.x(), -delta.y())
            for chart in self.charts:
                if chart != self.chart:
                    chart.scroll(delta.x(),0)
            self.drag_start_pos = event.pos()
            self.viewChanged()

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drag_start_pos = None    

class logSeries(QLineSeries):
    def __init__(self, parent= None) -> None:
        super().__init__(parent)
        
        # self.setPointLabelsVisible(False)
        self.setPointLabelsFormat("@yPoint")
        self.setPointsVisible(True)
        self.setName("测试")
        self.chart = None
        self.pointConent={}
        self.start = True

    #要在数据之后调用
    def setChar(self,chart,yAxis = None):
        assert isinstance(chart,QChart)
        if self.chart != None:
            self.chart.removeSeries(self)
        self.chart = chart
        self.chart.addSeries(self) # 这一步要在 attachAxis 前面
        # 将线系列与轴绑定
        self.attachAxis(self.chart.axisX())
        if yAxis == None:
            self.attachAxis(self.chart.axisY())
        else:
            self.attachAxis(yAxis)

    def appendData(self,date,value,content):
        lastSecs = QDateTime.fromString(date[:-3],'yyyy/MM/dd hh:mm:ss.zzz').toMSecsSinceEpoch()
        self.append(lastSecs, int(value))
        self.chart.update()

class CustomChart(QChart):
    def __init__(self,charts) -> None:
        super().__init__()

        self.setMargins(QMargins(0,0,0,0))

        self.chart_view = CustomChartView(self,charts)
        
        # 创建一个时间轴
        self.axis_x = QDateTimeAxis()
        self.axis_x.setTitleText("时间")
        self.axis_x.setFormat("yyyy/MM/dd hh:mm:ss")

        self.addAxis(self.axis_x, Qt.AlignBottom)

        # 创建一个数值轴
        self.axis_y = QValueAxis()
        self.addAxis(self.axis_y, Qt.AlignLeft)

        self.legend().setAlignment(Qt.AlignLeft)
        self.logSeries =[]
       
    def chartViewChanged(self):
        displayCount = 0
        for logSerie in self.logSeries:
            displayCount = max(self.getSerieVisiblePoints(logSerie),displayCount)
        self.axis_x.setTickCount(displayCount)

    def getSerieVisiblePoints(self,series):

        # 获取绘图区域的矩形
        plot_area_rect = self.chart_view.rect()

        # 获取绘图区域的左上角和右下角坐标
        top_left = self.mapToScene(plot_area_rect.topLeft())
        bottom_right = self.mapToScene(plot_area_rect.bottomRight())

        # 将左上角和右下角坐标映射到数据坐标
        top_left_value = self.mapToValue(top_left)
        bottom_right_value = self.mapToValue(bottom_right)

        # 计算在屏幕上绘制的点数
        num_points = len(series.pointsVector())
        visible_points = 0
        for i in range(num_points):
            point = series.at(i)
            if top_left_value.x() <= point.x() <= bottom_right_value.x() and top_left_value.y() >= point.y() >= bottom_right_value.y():
                visible_points += 1

        return visible_points

    def createSeries(self):
        # 创建一个线系列
        series = logSeries() 
        series.setChar(self)
        self.logSeries.append(series)
        self.chartViewChanged()

        # # 添加数据到线系列
        # lastSecs=0
        
        # # 生成示例数据
        # xData = ['2023/07/11 10:37:30', '2023/07/11 10:37:40', '2023/07/11 10:37:45', '2023/07/11 10:37:50', '2023/07/11 10:37:56']  # 时间
        # yDate = [10, 20, 15, 25, 30]  # 数值
        # for p in range(10):
        #     for i in range(len(xData)):
        #         if p == 0:
        #             lastSecs = QDateTime.fromString(xData[i],'yyyy/MM/dd hh:mm:ss').toMSecsSinceEpoch()
        #             series.append(lastSecs, yDate[i])
        #         else:
        #             lastSecs= lastSecs+60000*(i+1)
        #             series.append(lastSecs, yDate[i])
        return series

class CustomChartManage(QObject):
    update_data = pyqtSignal(str,str,str,logSeries) #date value content series
    def __init__(self,layout, parent=None) -> None:
        super().__init__(parent)
        self.layout = layout
        self.detachView = True
        self.configJson = None
        self.charts = []
        self.logAnalyzes = [logBase(),dltLogBase()]
        self.update_data.connect(self.updataSeries)
        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.resCallFun = self.analyzesCallBack


    def updataSeries(self,date,value,content,series):
        assert isinstance(series,logSeries)
        series.appendData(date,value,content)

    def analyzesCallBack(self,date,value,content,series):
        self.update_data.emit(date,value,content,series)

    def setConfig(self,configPath):
        self.configPath = getJScontent(configPath)
        self.logAnalyzes[1].setDltExe(self.configPath["dltExePath"])

    def clearLog(self):
        for chart in self.charts:
            assert isinstance(chart,QChart)
            chart.removeAllSeries()
            del chart
        self.charts.clear()

        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.clear()
        
    def loadLog(self,logPaths):
        txtlogs = []
        dltlogs = []
        for logPath in logPaths:
            if ".dlt" in logPath:
                dltlogs.append(logPath)
            else:
                txtlogs.append(logPath)

        self.logAnalyzes[0].load(txtlogs)
        self.logAnalyzes[1].load(dltlogs)

    def searchkeyWords(self,keyWords):
        if self.detachView or len(self.charts) == 0:
            chart = self.createChar()
        else:
            chart = self.charts[0]

        series = chart.createSeries()

        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.startSearch(keyWords,series)

    def createChar(self):
        chart = CustomChart(self.charts)
        if len(self.charts) != 0:
            chart.axis_x.setTitleText("")
            chart.axis_x.setLabelsVisible(False)
        self.layout.insertWidget(0,chart.chart_view)
        self.charts.append(chart)
        return chart