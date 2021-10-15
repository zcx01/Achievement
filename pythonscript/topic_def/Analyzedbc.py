#!/usr/bin/python
import enum
import os
import sys
import re
from enum import Enum

pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from commonfun import*

class DataType(Enum):
    VINT=1
    VFLOAT=2
class SigInfo(object):
    def __init__(self) :
        self.messageId = ""
        self.name=""
        self.startBit=0
        self.length=0
        self.dataType="+"
        self.factor=0
        self.Offset=0
        self.min=0
        self.max=0
        self.Unit=""
        self.enum=""
        self.initValue=0#十进制
        self.invalidValue=0
        self.Recevier=""
        self.Sender=""
        
        self.cycle=0
    
    def getMId(self):
        return int(self.messageId,16)

    def getSG(self):
        return f' SG_ {self.name} : {self.startBit}|{self.length}@0{self.dataType} ({self.factor},{self.Offset}) [{self.min}|{self.max}] {self.Unit}  {self.Recevier}'
    
    def getEnum(self):
        enumStr=self.enum
        if ":" in self.enum:
            enumStrA=[]
            enumS=self.enum.split(" ")
            for enumM in enumS:
                enumMs=enumM.split(":")
                enumStrA.append(f'{int(enumMs[0],16)} \"{enumMs[1]}\"')
            enumStr=" ".join(enumStrA)
        
        if len(enumStr) == 0 or "~" in enumStr:
            return ""
        return f'VAL_ {self.getMId()} {self.name} {enumStr};'

    def getStartValue(self):
        return f'BA_ \"GenSigStartValue\" SG_  {self.getMId()} {self.name} {self.initValue};'

    def getMessageId(self):
        return f'{self.Sender}_{self.messageId}'

    def getMessage(self):
        return f'BO_  {int(self.messageId,16)} {self.getMessageId()}: 64 {self.Sender}'

    def getMessageCycle(self):
        return f'BA_ \"GenMsgCycleTime\" BO_  {int(self.messageId,16)} {self.cycle};'

    def getMessageVFrameFormat(self):
        return f'BA_ \"VFrameFormat\" BO_ {int(self.messageId,16)} 14;'

    #endBit+(length - length%8)+(8-length)+1=startBit
    def getendBit(self):
        return self.startBit+self.length%8-9

    @staticmethod
    def analySG(text):
        sig=SigInfo()
        e_i=r"\b[a-zA-Z0x0-9]+\b"
        signals=re.findall(e_i,text,re.A)
        if signals== None:
            return sig
        try:
            sig.name=signals[0]
            sig.startBit=int(signals[1])
            sig.length=int(signals[2])
            sig.factor=signals[4]
            sig.Offset=signals[5]
        except:
            pass
        return sig

class dbcSig(object):
    def __init__(self) -> None:
        super().__init__()
        self.message=""
        self.dataType=DataType.VINT
        self.Row=0
        self.startBit=0

class dbcMessage(object):
    def __init__(self) -> None:
        super().__init__()
        self.messgae=""
        self.Row=-1
        self.sigMaxRow=-1

class Analyze(object):
    def __init__(self,dbc_file=None) :
        if len(dbc_file) ==0:
            return
        self.dbcSigs={}
        self.dbcMessage={}
        self.dbcPath=dbc_file
        self.maxSigRow=0
        self.analy()
        
    def analy(self):
        self.dbcSigs={}
        self.dbcMessage={}
        self.maxSigRow=0
        with open(self.dbcPath,"r") as f:
            linelist=f.readlines()
            message=""
            rowIndex=-1
            for text in linelist:
                rowIndex+=1
                text=text.strip()
                if len(text) == 0:
                    continue
                if text.startswith("BO_") :
                    message= self.analyline(text)
                    dm=dbcMessage()
                    dm.messgae=message
                    dm.Row=rowIndex
                    dm.sigMaxRow=dm.Row+1
                    self.dbcMessage[message]=dm
                elif text.startswith("SG_"):
                    sigNams=self.analyline(text)
                    ds=dbcSig()
                    ds.message=message
                    ds.Row=rowIndex
                    ds.dataType=self.analyDataType(text)
                    self.dbcSigs[sigNams] = ds
                    self.maxSigRow = rowIndex
                    try:
                        self.dbcMessage[message].sigMaxRow=rowIndex+1         
                    except:
                        pass

    def getMessageBySig(self,sig):
        return self.dbcSigs.get(sig).message

    def getSigDataType(self,sig):
        return self.dbcSigs.get(sig).dataType

    def analyline(self,msg):
        contents=msg.split(":")
        contents=contents[0].strip().split(" ")
        return contents[len(contents)-1]

    def analyDataType(self,lineContent):
        contents=lineContent.split(" ")
        for text in contents:
            if(text.startswith("(")):
                texts=text.split(",")
                accuracy=texts[0].replace("(","")
                if "." in accuracy:
                    return DataType.VFLOAT
        return DataType.VINT


    def writeSig(self,sig):
        linelist=readFileLines(self.dbcPath)
        # sig=SigInfo(sig)
        if sig.name in self.dbcSigs:
            print("信号已经存在")
            return
        try:
            dm = self.dbcMessage.get(sig.getMessageId())
            startRow=dm.Row+1
            insertRowIndex=-1
            while(startRow <= dm.sigMaxRow):
                lineSig = SigInfo.analySG(linelist[startRow])
                if(lineSig.startBit > sig.startBit):
                    insertRowIndex = startRow
                    break
                startRow+=1
            if insertRowIndex == -1:
                insertRowIndex = dm.sigMaxRow
            linelist.insert(insertRowIndex,sig.getSG())
            linelistSize=len(linelist)
            for row in range(linelistSize):
                if "GenSigStartValue" in str(linelist[linelistSize-1-row]):
                    linelist.insert(linelistSize-row,sig.getStartValue())
                    break
            try:
                enumStr=sig.getEnum()
                if len(enumStr) != 0:
                    linelist.append(enumStr)
            except:
                pass
            wirteFileDicts(self.dbcPath,linelist)
            print(f"{sig.name} 写入完成")
        except:
            print(f'{sig.name} 正在写入message')
            if not self.writeMessage(sig,linelist):
                print(f'{sig.name} 没有message')
                return
            self.analy()
            self.writeSig(sig)

    def writeMessage(self,sig,linelist):
        # linelist=list(linelist)
        # sig=SigInfo(sig)
        if len(sig.messageId) == 0:
            return False
        linelist.insert(self.maxSigRow+1,"\n")
        linelist.insert(self.maxSigRow+2,sig.getMessage())
        linelistSize=len(linelist)
        for row in range(linelistSize):
            if "GenMsgCycleTime" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,sig.getMessageCycle())
                break

        for row in range(linelistSize):
            if "VFrameFormat" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,sig.getMessageVFrameFormat())
                break
        wirteFileDicts(self.dbcPath,linelist)
        return True
         



# a=Analyze("/home/chengxiongzhu/Works/Repos/tool_parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessageBySig("CdcDtc1HiByte"))
