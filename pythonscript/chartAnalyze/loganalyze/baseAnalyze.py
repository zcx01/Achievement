from enum import Enum
import os
import re
import typing
import time
import gzip
from threading import Thread
from commonfun import *

# 使用eval()函数创建对象实例
# 使用getattr()获取属性值,获取方法并调用
# 使用setattr()设置属性值

class SearchStatus(Enum):
    NOSTART=1
    START = 2
    STARTING = 3
    FINISH =4
    
class logBase():
    def __init__(self) -> None:
        self.resCallFun = None
        self.currentSearchLine = None
        self.searchStatusChangeFun = None
        self.sendMsgFun = None
        self.searchStatus = SearchStatus.NOSTART
        self.logThread = None
        self.stop = False
        self.tempIndex = -1
        self.keyWordSeries = {}
        self.splitField = 'value'
        self.lineContents={}
        self.totalLineCount = 0
        self.clear()

    def clear(self):
        self.totalLineCount = 0
        self.lineContents.clear()

    def load(self,filePaths):
        filePathIndex = 0
        for filePath in filePaths:
            assert isinstance(filePath,str)
            self.loadLogFile(filePath)
            filePathIndex = filePathIndex + 1
            self.currentSearchLineChanged(filePathIndex,len(self.lineContents))
           

    def searchContentChanged(self,dateStr,value,content,series):
        if self.resCallFun != None:
            self.resCallFun(dateStr,value,content,series)
        else:
            print(dateStr,"    ",value,"    ",content)

    def sendMsg(self,msg):
        if self.sendMsgFun != None:
            self.sendMsgFun(msg)

    def searchStatusChange(self,status):
        self.searchStatus = status
        if self.searchStatusChangeFun != None:
            self.searchStatusChangeFun(self.searchStatus)

    def currentSearchLineChanged(self,lineIndex,count):
        if self.currentSearchLine!= None:
            lineIndex = int(lineIndex / count *100)
            if self.tempIndex != lineIndex:
                self.tempIndex = lineIndex
                self.currentSearchLine(self,lineIndex) 
        else:
            pass

    @typing.overload
    def loadLogFile(self,filePath):
        self.lineContents[filePath] = readFileLines(filePath)
        self.totalLineCount = len(self.lineContents[filePath]) + self.totalLineCount
        return True

    def getLoglineCount(self):
        return self.totalLineCount
    
    def setKeyWords(self,keyWordSeries):
        self.keyWordSeries = keyWordSeries

    def startSearchThread(self,searchkeyFun=None):
        self.searchStatusChange(SearchStatus.NOSTART)
        if self.getLoglineCount() == 0 or len(self.keyWordSeries) == 0: return
        if searchkeyFun == None: searchkeyFun = self.searchkeyWords
        self.logThread = Thread(target=searchkeyFun)
        self.logThread.setDaemon(True)
        self.logThread.start()

    def searchkeyWords(self):
        self.startAnalyze()

    # @typing.overload
    def startAnalyze(self):
        self.searchStatusChange(SearchStatus.START)
        lineContentIndex = 0
        keyConentCount = {}
        keyValueConentCount = {}
        searchCount = 0
        isFirstPrint = True
        for keyWord in self.keyWordSeries:
            keyConentCount[keyWord] = 0
            keyValueConentCount[keyWord] = 0
        for filePath,filelineContents in self.lineContents.items():
            for lineContent in filelineContents:
                if self.stop : return
                assert isinstance(lineContent,str)
                for keyWord,series in self.keyWordSeries.items():
                    if re.search(keyWord,lineContent,re.A):
                        keyConentCount[keyWord] =  keyConentCount[keyWord] +1
                        searchCount = searchCount + 1
                        spaceContent = lineContent.split(" ")
                        dateStr = spaceContent[1] +" "+spaceContent[2]
                        contents = re.findall(e_i,lineContent,re.A)
                        ishasValue = False
                        for contentIndex in range(len(contents)):
                            if self.splitField in contents[contentIndex]:
                                contentNextIndex = contentIndex + 1
                                value = contents[contentNextIndex]
                                self.searchContentChanged(dateStr,value,lineContent,series)
                                keyValueConentCount[keyWord] =  keyValueConentCount[keyWord] +1
                                ishasValue = True

                        if not ishasValue:
                            if isFirstPrint:
                                isFirstPrint = False
                                self.sendMsg(f'不符合规则的解析规则:')
                            self.sendMsg(f'{lineContent}')
                lineContentIndex = lineContentIndex+1
                self.currentSearchLineChanged(lineContentIndex,self.getLoglineCount())
        self.searchStatusChange(SearchStatus.FINISH)
        for keyWord in self.keyWordSeries:
            self.sendMsg(f'搜索 {keyWord} 共 {keyConentCount[keyWord]}')
            self.sendMsg(f'显示 {keyWord} 共 {keyValueConentCount[keyWord]}')
        self.sendMsg(f"搜索完成,共 {searchCount}\n")

class dltLogBase(logBase):
    def __init__(self) -> None:
        super().__init__()
        self.dltExe = None

    def setDltExe(self,dltExe):
        self.dltExe = dltExe

    @staticmethod
    def gunZip(filePath):
        extracted_file_path = filePath.replace('.gz','')
        try:
            # 打开gz文件
            with gzip.open(filePath, 'rb') as gz_file:
                # 读取解压后的文件内容
                extracted_data = gz_file.read()

            # 将解压后的数据写入新文件
            with open(extracted_file_path, 'wb') as extracted_file:
                extracted_file.write(extracted_data)

            return extracted_file_path
        except IOError as e:
            print(f"解压失败：{e}")
        return None
    
    def getConverTxt(self,filePath):
        fileName = os.path.basename(filePath)
        fileName = fileName.replace('.gz','')
        fileName = fileName.replace('.dlt','.txt')
        fileDir = os.path.dirname(filePath)+"/"
        logFile =  fileDir + fileName
        # print(logFile)
        if os.path.exists(logFile):
            return logFile
        return None

    def dltToTxt(self,logPath,filePath,logFile):
        # filePath = os.path.basename(filePath)
        # logFile = os.path.basename(logFile)
        os.system(f'{self.dltExe} -c {filePath} {logFile}')

    def loadLogFile(self,filePath):
        assert isinstance(filePath,str)
        logFileDir = os.path.dirname(filePath)
        logFile = self.getConverTxt(filePath)
        print(self.dltExe,filePath)
        if logFile == None and len(self.dltExe) != 0:
            if getSuffix(filePath) == '.gz':
                filePath = dltLogBase.gunZip(filePath)
                if filePath == None:
                    return False
            logFile = filePath.replace('.dlt','.txt')
            self.dltToTxt(logFileDir,filePath,logFile)
        self.lineContents[filePath] = readFileLines(logFile)
        self.totalLineCount = len(self.lineContents[filePath]) + self.totalLineCount
        return True

class dltLog1(dltLogBase):
    def __init__(self) -> None:
        super().__init__()
    
    def startAnalyze(self):
        self.searchStatusChange(SearchStatus.START)
        lineContentIndex = 0
        searchCount = 0
        for filePath,filelineContents in self.lineContents.items():
            for lineContent in filelineContents:
                if self.stop : return
                assert isinstance(lineContent,str)
                for keyWord,series in self.keyWordSeries.items():
                    if re.search(keyWord,lineContent,re.A):
                        searchCount = searchCount + 1
                        contents = re.split(keyWord,lineContent,re.A)
                        date = contents[0]
                        value = ''
                        if len(contents) > 1 : value = contents[1]
                        self.searchContentChanged(date,value,lineContent,filePath)
                        

                lineContentIndex = lineContentIndex+1
                self.currentSearchLineChanged(lineContentIndex,self.getLoglineCount())
        self.sendMsg(f"搜索完成,共 {searchCount}\n")
        self.searchStatusChange(SearchStatus.FINISH)

if __name__ == '__main__':
    logObj = dltLogBase()
    logObj.setDltExe("D:/Soft/DltViewerSDK/dlt-viewer.exe")
    logObj.load([r"C:/Users/chengxiong.zhu/Downloads/log分析/2023-09-24/ BGS-62018 385DAuserDF04镁佳1553左右手机端打开远程智能泊车CdcRemVideoPwrUpReq发送上高压请求退出远程智能泊车后座舱高压CdcRemVideoPwrUpReq未置为无请求没有下高压解锁座舱高压置为无请求/log_003460_20230922-153505.dlt"])
    # logObj.startSearch("HUD_CDC_5C5")
    while 1 :
        time.sleep(10)