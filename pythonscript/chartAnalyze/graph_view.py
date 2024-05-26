# coding:utf-8
#!/bin/python

'''
参考:
https://blog.csdn.net/zy1620454507/article/details/126378110
'''
import pyqtgraph as pg
from PyQt5.QtCore import QRect,Qt, QDateTime,QObject,QMargins,pyqtSignal,QPointF,QPoint
from PyQt5.QtWidgets import QGraphicsTextItem,QGraphicsScene,QGraphicsView
from loganalyze.baseAnalyze import *
from loganalyze.commonfun import *
from loganalyze.staXls import *

QDATETIMEMSF='yyyy/MM/dd hh:mm:ss.zzz'
QDATEF='yyyy/MM/dd'
QTIMEF='hh:mm:ss'
QDATETIMEMSSPANEF='yyyy/MM/dd\nhh:mm:ss.zzz'
DLTEXEPATH = 'dltExePath'
LableWidth = 60
class DateAxis(pg.AxisItem):
    def __init__(self, orientation, pen=None, textPen=None, tickPen=None, linkView=None, parent=None, maxTickLength=-5, showValues=True, text='', units='', unitPrefix='', **args):
        self.lefLabel = None
        self.rightLabel = None
        super().__init__(orientation, pen, textPen, tickPen, linkView, parent, maxTickLength, showValues, text, units, unitPrefix, **args)
        self.lefLabel = QGraphicsTextItem(self)
        self.rightLabel = QGraphicsTextItem(self)
        self.enableAutoSIPrefix(False)
        self.showLabel()

    def setCustomText(self,textLabel,text):
        centerText = self.labelString()
        pattern = r">.*</span>"
        replacement = f'>{text}</span>'
        textLabel.setHtml(re.sub(pattern, replacement, centerText))

    def setLabelPositon(self,textLabel):
        nudge = 5
        if textLabel is None: # self.label is set to None on close, but resize events can still occur.
            return
        br = textLabel.boundingRect()
        p = QPointF(0, 0)
        if textLabel == self.lefLabel:
            p.setX(0)
        if textLabel == self.rightLabel:
            p.setX(int(self.size().width()-br.width()))
        p.setY(int(self.size().height()-br.height()+nudge))
        textLabel.setPos(p)

    def updateLabelPositon(self):
        self.setLabelPositon(self.lefLabel)
        self.setLabelPositon(self.rightLabel)
         
    def resizeEvent(self, ev=None):
        self.updateLabelPositon()
        return super().resizeEvent(ev)


    def tickStrings(self, values, scale, spacing):
        strns = []
        if not values:
            return pg.AxisItem.tickStrings(self, values, scale, spacing)

        index = 0
        startDate = ""
        endDate = ""
        for x in values:
            try:
                if index == 0:
                    startDate = QDateTime.fromMSecsSinceEpoch(x).toString(QDATEF)
                elif index == len(values) - 1:
                    endDate = QDateTime.fromMSecsSinceEpoch(x).toString(QDATEF)
                strns.append(QDateTime.fromMSecsSinceEpoch(x).toString(QTIMEF))
            except:
                strns.append(x)
            index = index +1

        self.setCustomText(self.lefLabel,startDate)  
        self.setCustomText(self.rightLabel,endDate)    
        return strns


class logSeries(pg.PlotCurveItem):
    def __init__(self,plotItem, parent= None) -> None:
        super().__init__(parent)
        assert isinstance(plotItem,pg.PlotItem)
        self.dataX=[]
        self.dataY=[]
        self.posTextItems = []
        self.setClickable(True)
        self.plotItem = plotItem
        self.plotItem.vb.addItem(self)
        # 创建ScatterPlotItem并设置符号为圆圈
        self.scatter = pg.ScatterPlotItem(symbol='o', pen='w', brush='r')
        # 添加ScatterPlotItem到PlotItem中
        self.plotItem.vb.addItem(self.scatter)
        self.scatter.setData(self.dataX,self.dataY,hoverable=True,tip=self.getToolTip)
        self.plotItem.vb.setYRange(-1,1)
        self.plotItem.vb.sigYRangeChanged.connect(self.yRangeChanged)
        self.isSame = True

    def yRangeChanged(self,obj1,obj2):
        if self.isSame:
            if len(self.dataY) > 0:
                self.plotItem.vb.setYRange(self.dataY[0]-1,self.dataY[0]+1)

    def appendData(self,date,value,content):
        lastSecs = QDateTime.fromString(date[:-3],QDATETIMEMSF).toMSecsSinceEpoch()
        valueIndex = float(value)
        self.dataX.append(lastSecs)
        self.dataY.append(valueIndex)
        text =  pg.TextItem(text=value)
        text.setPos(lastSecs, valueIndex)
        self.posTextItems.append(text)
        self.plotItem.vb.addItem(text)
        self.updateMyData()    
        if self.isSame:
            self.isSame = valueIndex == self.dataY[0]

    def getLineSpaceText(self,space1,space2):
        if space2 < space1:
            tmp = space1
            space1 = space2
            space2 = tmp
        tmpIndexs=[]
        for dataXIndex in range(len(self.dataX)):
            dataX = self.dataX[dataXIndex]
            if space1 <= dataX <= space2:
                tmpIndexs.append(dataXIndex)
        return tmpIndexs

    def getToolTip(self,x,y,data):
        return QDateTime.fromMSecsSinceEpoch(x).toString(QDATETIMEMSF)
        
    def updateMyData(self):
        self.setData(self.dataX,self.dataY)
        # self.scatter.setPointData(tooltip_data)
        self.scatter.setData(self.dataX,self.dataY)
    
    def clearData(self):
        self.dataX.clear()
        self.dataY.clear()
        y_range = self.plotItem.vb.viewRange()[1]
        for posTextItem in self.posTextItems:
            self.plotItem.vb.removeItem(posTextItem)
        self.posTextItems.clear()
        self.updateMyData()
        self.plotItem.vb.setYRange(y_range[0],y_range[1])

class CustomGraphManage(QObject):
    update_data = pyqtSignal(str,str,str,logSeries) 
    update_Progress = pyqtSignal(int) 
    status_changed = pyqtSignal(SearchStatus) 
    send_msg = pyqtSignal(str) 
    def __init__(self,layout, parent=None) -> None:
        super().__init__(parent)
        self.layout = layout
        self.detachView = True
        self.configJson = None
        self.charts = []
        self.pgLayout = None
        self.pgSeries={}
        self.pgFirstPlotItem = None
        self.lines = []
        self.currentline = None
        self.configPath = None
        self.currentlineVisibleCount = 0
        self.initPg()
        self.logAnalyzes = [logBase(),dltLogBase()]
        self.update_data.connect(self.updataSeries)
        self.status_changed.connect(self.statusChanged)
        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.resCallFun = self.analyzesCallBack
            logAnalyze.currentSearchLine = self.updataProgress
            logAnalyze.searchStatusChangeFun = self.status_changed.emit
            logAnalyze.sendMsgFun = self.send_msg.emit

    def statusChanged(self,status):
        if status == SearchStatus.FINISH:
            self.updateLineData(True)
            if self.pgFirstPlotItem != None:
                axis = self.pgFirstPlotItem.getAxis('bottom')
                assert isinstance(axis,DateAxis)
                axis.updateLabelPositon()

    def updataSeries(self,date,value,content,series):
        assert isinstance(series,logSeries)
        series.appendData(date,value,content)

    def updataProgress(self,log,lineContentIndex):
        assert isinstance(log,logBase)
        self.update_Progress.emit(lineContentIndex)
        
    def analyzesCallBack(self,date,value,content,series):
        self.update_data.emit(date,value,content,series)

    def setConfig(self,configPath):
        self.configPath = configPath
        try:
            self.logAnalyzes[1].setDltExe(self.getConfigValue(DLTEXEPATH))
        except:
            return False
        return True

    def setDltExe(self,dltExePath):
        self.modifyConfig(DLTEXEPATH,dltExePath)
        self.setConfig(self.configPath)

    def modifyConfig(self,key,value):
        configConent = getJScontent(self.configPath)
        configConent[key] = value
        writeJs(self.configPath,configConent)

    def getConfigValue(self,key,defaultValue = None):
        configConent = getJScontent(self.configPath)
        if defaultValue == None:
            return configConent[key]
        else:
            if key not in configConent:
                return defaultValue
            else:
                return configConent[key]

    def clearLog(self):
        for serie in self.pgSeries.values():
            assert isinstance(serie,logSeries)
            serie.clearData()

    def loadLog(self,logPaths):
        txtlogs = []
        dltlogs = []
        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.clear()

        for logPath in logPaths:
            if ".dlt" in logPath:
                dltlogs.append(logPath)
            else:
                txtlogs.append(logPath)

        self.logAnalyzes[0].load(txtlogs)
        self.logAnalyzes[1].load(dltlogs)

    def addkeyWords(self,keyWord):
        if keyWord in self.pgSeries:
            self.send_msg.emit(f"{keyWord} 已经存在")
            return False
        self.createPlotItem(keyWord)
        self.updateLogAnalyzekey()
        return True

    def updateLogAnalyzekey(self):
        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.setKeyWords(self.pgSeries)

    def removeKeyWord(self,keyWord):
        if keyWord in self.pgSeries:
            series = self.pgSeries[keyWord]
            assert isinstance(series,logSeries)
            if self.pgFirstPlotItem == series.plotItem:
                nextSeries = None
                for key,sri in self.pgSeries.items():
                    if sri != series:
                        nextSeries = sri
                if nextSeries != None:
                    assert isinstance(nextSeries,logSeries)
                    series.plotItem.removeItem(series.plotItem.getAxis('bottom'))
                    nextSeries.plotItem.removeItem(nextSeries.plotItem.getAxis('bottom'))
                    nextSeries.plotItem.setAxisItems({'bottom':DateAxis(orientation='bottom')})
                    self.pgFirstPlotItem = nextSeries.plotItem
                else:
                    self.pgFirstPlotItem = None
   
            series.plotItem.removeItem(series)
            self.pgLayout.removeItem(series.plotItem)
            del self.pgSeries[keyWord]
        self.updateLogAnalyzekey()

    def searchkeyWords(self):
        for logAnalyze in self.logAnalyzes:
            assert isinstance(logAnalyze,logBase)
            logAnalyze.startSearchThread()

    def initPg(self):
        # 创建视图
        self.pw = pg.GraphicsView()
        self.pw.setWindowTitle('pyqtgraph 标题')
        
        # 创建图形布局
        self.pgLayout = pg.GraphicsLayout()
        # 设置视图中心小部件 为该布局
        self.pw.setCentralWidget(self.pgLayout)
        self.layout.insertWidget(0,self.pw)
        # pw.setBackground("w")
        self.createInfiniteLine()
        self.pw.scene().sigMouseMoved.connect(self.mouseMoved)
        self.pw.scene().sigMouseClicked.connect(self.mouseCliked)

    def createInfiniteLine(self):
        self.lines.append(pg.InfiniteLine(pos=None, angle=90, movable=True,pen = (0, 255, 0),label='',hoverPen=(0, 255, 0)))
        self.lines.append(pg.InfiniteLine(pos=None, angle=90, movable=True,pen = (255, 0, 0),label='',hoverPen=(255, 0, 0)))
        for lineIndex in range(len(self.lines)):
            self.pw.addItem(self.lines[lineIndex])
            self.lines[lineIndex].setVisible(False)
    
    def setCurrentLine(self,valueIndex):
        self.currentline = None
        valueIndex = valueIndex - 1
        if 0 <= valueIndex < len(self.lines):
            self.currentline = self.lines[valueIndex]
            self.currentline.movable = True

    def getCurrentLineIndex(self):
        for lineIndex in range(len(self.lines)):
            if self.lines[lineIndex] == self.currentline:
                return lineIndex
        return -1

    def setLineVisble(self,visible):
        for lineIndex in range(len(self.lines)):
            self.lines[lineIndex].setVisible(visible)
            
    def setLineCount(self,lineCount):
        self.setLineVisble(False)
        for lineIndex in range(lineCount):
            self.lines[lineIndex].setVisible(True)

        self.currentlineVisibleCount = lineCount

    def mouseCliked(self,event):
        if self.currentline != None and event.button() == Qt.LeftButton:
            self.currentline.movable = not self.currentline.movable
            self.updateLineData(False,True)

    def mouseMoved(self,evt):
        if self.currentline != None:
            if self.pgFirstPlotItem != None:
                if  self.currentline.movable:
                    axis = self.pgFirstPlotItem.getAxis('left')
                    assert isinstance(axis,pg.AxisItem)
                    br = axis.label.boundingRect()
                    self.currentline.setPos(max(LableWidth+br.height()/2,evt.x()))  # 根据鼠标的y坐标设置InfiniteLine的
                    pos = self.pgFirstPlotItem.mapToView(evt)
                    startDate = QDateTime.fromMSecsSinceEpoch(pos.x()).toString(QDATETIMEMSSPANEF)
                    self.currentline.label.setText(startDate)
        self.updateLineData(False)

    def updateLineData(self,isUpdateLable,printTextCount=False):
        if self.pgFirstPlotItem != None:
            bottomAxis = self.pgFirstPlotItem.getAxis('bottom')
            timeStampStr = ''
            startPos = QPointF(self.lines[0].value(),0)
            endValue = QPointF(self.lines[1].value(),0)
            startTime = self.pgFirstPlotItem.mapToView(startPos).x()
            endTime = self.pgFirstPlotItem.mapToView(endValue).x()
            if self.currentlineVisibleCount == 2:
                timeStampStr = str(abs(round((startTime -endTime)/1000,3)))
                if printTextCount:
                    for keyWord in self.pgSeries:
                        series = self.pgSeries[keyWord]
                        assert isinstance(series,logSeries)
                        spaceTextIndexs = series.getLineSpaceText(startTime,endTime)
                        self.send_msg.emit(f"{keyWord} 一个{len(spaceTextIndexs)}")
            bottomAxis.setLabel(text=timeStampStr,units='s')

            if isUpdateLable:
                self.lines[0].label.setText(QDateTime.fromMSecsSinceEpoch(startTime).toString(QDATETIMEMSSPANEF))
                self.lines[1].label.setText(QDateTime.fromMSecsSinceEpoch(endTime).toString(QDATETIMEMSSPANEF))

    def createPlotItem(self,keyWord):
        # 视图框，用于存放折线
        p1 = pg.PlotItem()
        
        series = logSeries(p1)
        self.pgSeries[keyWord] = series

        # 向布局添加轴
        self.pgLayout.clear()
        allSeries = list(self.pgSeries.values())
        for pgSerieIndex in range(len(allSeries)):
            self.pgLayout.addItem(allSeries[pgSerieIndex].plotItem, row = len(allSeries) -pgSerieIndex, col = 0,  rowspan=1, colspan=1)

        p1.getAxis("left").setLabel(keyWord)

        # 设置y轴刻度和标签之间的间距为60像素
        p1.getAxis('left').setWidth(LableWidth)
        
        #设置底部的坐标轴
        #创建一个底部方向的时间轴
        if self.pgFirstPlotItem == None:
            axis = DateAxis(orientation='bottom')
            p1.setAxisItems({'bottom':axis})
            self.pgFirstPlotItem = p1
        else:
            bottomAxis = p1.getAxis("bottom")
            assert isinstance(bottomAxis,pg.AxisItem)
            bottomAxis.setTicks([])
            p1.vb.setXLink(self.pgFirstPlotItem.vb)
        
        return series

 
class CustomAnalyzehManage(QObject):
    update_Progress = pyqtSignal(int) 
    send_msg = pyqtSignal(str) 
    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self.logAnalyze = dltLog1()
        self.logAnalyze.resCallFun = self.analyzesCallBack
        self.logAnalyze.currentSearchLine = self.updataProgress
        self.logAnalyze.searchStatusChangeFun = self.statusChanged
        self.logAnalyze.sendMsgFun = self.send_msg.emit
        self.analyzeRes = {}
        self.savePath = r'C:/Users/chengxiong.zhu/Downloads/'

    def setConfig(self,configPath):
        self.configPath = configPath
        try:
            self.logAnalyze.setDltExe(self.getConfigValue(DLTEXEPATH))
        except:
            return False
        return True
    
    def statusChanged(self,status):
        if status == SearchStatus.FINISH:
            coverXls(self.savePath,self.analyzeRes)
            self.send_msg.emit("分析完成")

    def getConfigValue(self,key,defaultValue = None):
        configConent = getJScontent(self.configPath)
        if defaultValue == None:
            return configConent[key]
        else:
            if key not in configConent:
                return defaultValue
            else:
                return configConent[key]
            
    def updataProgress(self,log,lineContentIndex):
        assert isinstance(log,logBase)
        self.update_Progress.emit(lineContentIndex)
        
    def analyzesCallBack(self,date,value,content,filePath):
        if filePath not in self.analyzeRes:
            self.analyzeRes[filePath] = {value:0}
        if value not in self.analyzeRes[filePath]:
            self.analyzeRes[filePath][value] = 0
        self.analyzeRes[filePath][value] = self.analyzeRes[filePath][value] + 1
        

    def loadLog(self,logPaths):
        self.logAnalyze.clear()
        self.logAnalyze.load(logPaths)

    def setkeyWords(self,keyWord):
        pgSeries={keyWord:None}
        self.logAnalyze.setKeyWords(pgSeries)

    def searchkeyWords(self):
        self.analyzeRes.clear()
        self.logAnalyze.startSearchThread(self.logAnalyze.startAnalyze)
