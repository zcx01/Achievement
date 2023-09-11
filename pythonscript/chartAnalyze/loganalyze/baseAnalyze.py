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

class logBase():
    def __init__(self) -> None:
        self.resCallFun = None
        self.currentSearchLine = None
        self.logThread = None
        self.clear()

    def clear(self):
        self.filePaths = []
        self.lineContents = []

    def load(self,filePaths):
        self.filePaths.extend(filePaths)
        for filePath in self.filePaths:
            self.loadLogFile(filePath)

    def searchContentChanged(self,dateStr,value,content,series):
        if self.resCallFun != None:
            self.resCallFun(dateStr,value,content,series)
        else:
            print(dateStr,"    ",value,"    ",content)

    def currentSearchLineChanged(self,lineIndex):
        if self.currentSearchLine!= None:
            self.currentSearchLine(lineIndex) 
        else:
            pass
            # print(lineIndex)

    @typing.overload
    def loadLogFile(self,filePath):
        self.lineContents.extend(readFileLines(filePath))
        return True

    def getLoglineCount(self):
        return len(self.lineContents)
    
    def startSearch(self,keyWords,series):
        self.logThread = Thread(target=self.searchkeyWords,args=(keyWords,series,))
        self.logThread.setDaemon(True)
        self.logThread.start()

    def searchkeyWords(self,keyWords,series):
        self.startAnalyze(keyWords,series)

    # @typing.overload
    def startAnalyze(self,keyWords,series):
        lineContentIndex = 0
        for lineContent in self.lineContents:
            if self.stop : return
            assert isinstance(lineContent,str)
            if re.search(keyWords,lineContent,re.A):
                lineContentIndex = lineContentIndex+1
                spaceContent = lineContent.split(" ")
                dateStr = spaceContent[1] +" "+spaceContent[2]
                contents = re.findall(e_i,lineContent,re.A)
                for contentIndex in range(len(contents)):
                    if "value" in contents[contentIndex]:
                        contentNextIndex = contentIndex + 1
                        value = contents[contentNextIndex]
                        self.searchContentChanged(dateStr,value,lineContent,series)
                        self.currentSearchLineChanged(lineContentIndex)


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
        print(logFile)
        if os.path.exists(logFile):
            return logFile
        return None

    def loadLogFile(self,filePath):
        assert isinstance(filePath,str)
        logFile = self.getConverTxt(filePath)
        if logFile == None:
            if getSuffix(filePath) == '.gz':
                filePath = dltLogBase.gunZip(filePath)
                if filePath == None:
                    return False
            print(filePath)
            logFile = filePath.replace('.dlt','.txt')
            os.system(f'{self.dltExe} -c {filePath} {logFile}')
        self.lineContents.extend(readFileLines(logFile))
        return True

if __name__ == '__main__':
    logObj = dltLogBase("D:/Soft/DltViewerSDK/dlt-viewer.exe")
    logObj.load(["C:\\Users\\chengxiong.zhu\\Downloads\\log分析\\2023-07-26\\log_001521_20230724-193751.dlt.gz"])
    logObj.startSearch("HUD_CDC_5C5")
    while 1 :
        time.sleep(10)