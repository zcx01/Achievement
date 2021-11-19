#!/usr/bin/python
import os
import re
from enum import Enum
from time import sleep
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/topic_def/"
from commonfun import*

class DataType(Enum):
    VINT=1
    VFLOAT=2

class WriteDBCResult(Enum):
    AlreadyExists=1     #信号已经存在
    SignalCoverage=2    #信号有覆盖
    WriteComplete=3     #写入完成
    NoMessage=4         #没有message

class SigInfo(object):
    def __init__(self,info=None) :
        if info == None:
            self.messageId = ""
            self.name=""
            self.startBit=0
            self.endBit=0
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
            self.useBit=[]
            #----------dbc中独有的-------------
            self.dbcMessage=None
            self.Row=0
        else:
            self.messageId = info.messageId
            self.name=info.name
            self.startBit=info.startBit
            self.endBit=info.endBit
            self.length=info.length
            self.dataType=info.dataType
            self.factor=info.factor
            self.Offset=info.Offset
            self.min=info.min
            self.max=info.max
            self.Unit=info.Unit
            self.enum=info.enum
            self.initValue=info.initValue
            self.invalidValue=info.invalidValue
            self.Recevier=info.Recevier
            self.Sender=info.Sender
            self.cycle=info.cycle
            self.useBit=info.useBit
            self.dbcMessage = info.dbcMessage
            self.Row = info.Row
    
    def getMId(self):
        return int(self.messageId,16)

    def getSG(self):
        return f' SG_ {self.name} : {self.startBit}|{self.length}@0{self.dataType} ({self.factor},{self.Offset}) [{self.min}|{self.max}] {self.Unit}  {self.Recevier}'
    
    def getEnum(self):
        try:
            enumStrA=[]
            enumS=re.findall(e_i,self.enum,re.A)
            enumIndex = 0
            while enumIndex < len(enumS):
                enumStrA.append(f'{int(enumS[enumIndex],16)} \"{enumS[enumIndex+1]}\"')
                enumIndex += 2
            enumStr=" ".join(enumStrA)
            
            if len(enumStr) == 0 or "~" in enumStr:
                return ""
            return f'VAL_ {self.getMId()} {self.name} {enumStr};'
        except:
            return ""

    def getStartValue(self):
        return f'BA_ \"GenSigStartValue\" SG_  {self.getMId()} {self.name} {self.initValue};'

    def getMessage_Id(self):
        return f'{self.Sender}_{self.messageId}'

    def getMessageRowContent(self,size):
        return f'BO_  {self.getMId()} {self.getMessage_Id()}: {size} {self.Sender}'

    def getMessageCycle(self):
        return f'BA_ \"GenMsgCycleTime\" BO_  {self.getMId()} {self.cycle};'

    def getMessageVFrameFormat(self):
        return f'BA_ \"VFrameFormat\" BO_ {self.getMId()} 14;'

    #endBit+(length - length%8)+(8-length)+1=startBit
    def getStartBit(self):
        return self.getMotorolaStartBit()

    def getEndBit(self):
        return self.getMotorolaEndBit()

    def getMotorolaStartBit(self):
        self.useBit.clear()
        startIndex=self.endBit
        self.useBit.append(startIndex)
        leg=1
        while(leg < self.length):
            nextIndex = startIndex+1
            mSb=startIndex//8*8+7
            if nextIndex > mSb:
                startIndex = (startIndex//8*8)-8
            else:
                startIndex=nextIndex
            leg+=1
            self.useBit.append(startIndex)
        self.startBit = startIndex
        return startIndex

    def getMotorolaEndBit(self):
        self.useBit.clear()
        endIndex=self.startBit
        self.useBit.append(endIndex)
        leg=1
        while(leg < self.length):
            nextIndex = endIndex-1
            mSb=endIndex//8*8
            if nextIndex < mSb:
                endIndex = (endIndex//8*8)+15
            else:
                endIndex=nextIndex
            leg+=1
            self.useBit.append(endIndex)
        self.endBit = endIndex
        return endIndex

    def getIntelStartBit(self):
        self.useBit.clear()
        startIndex=self.endBit
        self.useBit.append(startIndex)
        leg=1
        while(leg < self.length):
            nextIndex = startIndex-1
            mSb=startIndex//8*8
            if nextIndex < mSb:
                startIndex = (startIndex//8*8)-8
            else:
                startIndex=nextIndex
            leg+=1
            self.useBit.append(startIndex)
        self.startBit = startIndex
        return startIndex

    def getIntelEndBit(self):
        self.useBit.clear()
        endIndex=self.startBit
        self.useBit.append(endIndex)
        leg=1
        while(leg < self.length):
            nextIndex = endIndex+1
            mSb=endIndex//8*8+7
            if nextIndex > mSb:
                endIndex = (endIndex//8*8)+8
            else:
                endIndex=nextIndex
            leg+=1
            self.useBit.append(endIndex)
        self.endBit = endIndex
        return endIndex

    def compare(self,other):
        other = SigInfo(other)
        result=[]
        isSame=False
        link=' --- '
        if self.startBit == other.startBit and self.endBit == other.endBit and self.messageId == other.messageId:
            isSame = True
            if self.name.replace(' ','') != other.name.replace(' ',''):
                result.append(f"信号名称:{other.name}{link}{self.name}")
            if self.dataType != other.dataType:
                result.append(f'类型:{other.dataType}{link}{self.dataType}')
            if self.factor != other.factor:
                result.append(f'缩放:{other.factor}{link}{self.factor}')
            if self.Offset != other.Offset:
                result.append(f'偏移:{other.Offset}{link}{self.Offset}')
            if self.min != other.min:
                result.append(f'最小值:{other.min}{link}{self.min}')
            if self.max != other.max:
                result.append(f'最大值:{other.max}{link}{self.max}')
            if self.initValue != other.initValue:
                result.append(f'初始值:{other.initValue}{link}{self.initValue}')
            if self.cycle != other.cycle:
                result.append(f'周期:{other.cycle}{link}{self.cycle}')
            # if len(result) != 0:
            #     result.insert(0,f'{other.name}和原来的{self.name}在同一个message{self.messageId},具体的差别如下:')
        elif self.name == other.name:
            isSame = True
            # result.append(f"{self.name}信号名称和message相同,具体的差别如下:")
            if  self.length != other.length:
                result.append(f"长度:{other.length}{link}{self.length}")
            if self.endBit != other.endBit:
                result.append(f"结束位:{other.endBit}{link}{self.endBit}")
            if self.messageId != other.messageId:
                result.append(f"messageId:{other.messageId}{link}{self.messageId}")
            # if len(result) != 0:
            #     result.append(f"{self.name}信号名称相同,具体的差别如下:")
        
        return isSame,result

class dbcMessage(object):
    def __init__(self) -> None:
        super().__init__()
        self.message_Id=''
        self.Row=-1
        self.sigMaxRow=-1
        self.sender=''

class Analyze(object):
    def __init__(self,dbc_file=None) :
        if len(dbc_file) ==0:
            return
        self.dbcSigs={}
        self.dbcMessage={}
        self.dbcPath=dbc_file
        self.maxSigRow=0
        self.control=[]
        self.analy()
        
    def analy(self):
        self.dbcSigs={}
        self.dbcMessage={}
        self.maxSigRow=0
        with open(self.dbcPath,"r") as f:
            linelist=f.readlines()
            currentdbcMessage=None
            rowIndex=-1
            for text in linelist:
                rowIndex+=1
                text=text.strip()
                if len(text) == 0:
                    continue
                if text.startswith("BO_") :
                    dm= Analyze.analyMessage(text)
                    if dm == None:
                        continue
                    dm.Row=rowIndex
                    dm.sigMaxRow=dm.Row+1
                    self.dbcMessage[dm.message_Id]=dm
                    currentdbcMessage =dm
                elif text.startswith("BU_:"):
                    try:
                        self.control = splitSpace(text.split(":")[1])
                    except:
                        pass
                elif text.startswith("SG_"):
                    ds = Analyze.analySG(text)
                    ds.dbcMessage=currentdbcMessage
                    ds.Row=rowIndex
                    self.dbcSigs[ds.name] = ds
                    self.maxSigRow = rowIndex
                    try:
                        self.dbcMessage[currentdbcMessage.message_Id].sigMaxRow=rowIndex+1         
                    except:
                        pass

    def sigExist(self,sig):
        return sig in self.dbcSigs

    def sender(self,sig):
        try:
            return self.dbcSigs[sig].dbcMessage.sender
        except:
            return ''

    def getMessageBySig(self,sig):
        try:
            return self.dbcSigs[sig].dbcMessage.message_Id
        except:
            # print(f'{sig}没有找到message')
            return ""
            # sys.exit()

    def getSigDataType(self,sigName):
        dataTypeStr=""
        try:
            sig = SigInfo(self.dbcSigs.get(sigName))
            dayaType = sig.dataType
            if dayaType == '-':
                dataTypeStr="int32" 
            elif dayaType == '+':
                dataTypeStr="uint32"
            if '.' in str(sig.min) or '.' in str(sig.max):
                dataTypeStr='float'
        except:
            pass
        return dataTypeStr

    def analyline(self,msg):
        contents=msg.split(":")
        contents=contents[0].strip().split(" ")
        return contents[len(contents)-1]

    def getBU(self):
        return f'BU_: {" ".join(self.control)}'

    @staticmethod
    def analyMessage(text):
        messages = re.findall(e_i,text,re.A)
        if len(messages) < 4:
            return None
        ms = dbcMessage()
        ms.message_Id = messages[2]
        ms.sender = messages[4]
        return ms
        
    @staticmethod
    def analySG(text):
        sig=SigInfo()
        signals=re.findall(e_i,text,re.A)
        if signals== None:
            return sig
        try:
            sig.name=signals[1]
            sig.startBit=int(signals[2])
            sig.length=int(signals[3])
            sig.factor=signals[5]
            sig.Offset=signals[6]
            if '0-' in text:
                sig.dataType = '-'
            sig.min=signals[7]
            sig.max=signals[8]
        except:
            pass
        sig.getEndBit()
        return sig

    def writeSig(self,sig):
        sig=SigInfo(sig)
        linelist=readFileLines(self.dbcPath)
        linelistSize=len(linelist)
        if sig.name in self.dbcSigs:
            print(f"{sig.name}信号已经存在")
            return WriteDBCResult.AlreadyExists
        try:
            dm = self.dbcMessage.get(sig.getMessage_Id())
            startRow = dm.Row+1
            insertRowIndex=-1
            try:
                userIndex={}
                while(startRow < dm.sigMaxRow):
                    lineSig = Analyze.analySG(linelist[startRow])
                    userIndex[lineSig.name] = lineSig.useBit
                    if lineSig.startBit > sig.startBit and insertRowIndex == -1:
                        insertRowIndex = startRow 
                    startRow+=1

                if insertRowIndex == -1:
                    insertRowIndex = dm.sigMaxRow
                else:
                    #判断信号是否合理
                    sigUsrIndexs=sig.useBit
                    for user in userIndex:
                        for sigUsrIndex in sigUsrIndexs:
                            if sigUsrIndex in userIndex[user]:
                                print(f"{sig.name} 信号有覆盖:开始字节{sig.startBit},结束的字节{sig.endBit}，占用的字节{sigUsrIndexs},与{user}覆盖字节")
                                return WriteDBCResult.SignalCoverage

                #超出的原来的大小，就扩大
                print(startRow,dm.sigMaxRow,insertRowIndex)
                if insertRowIndex == dm.sigMaxRow and sig.endBit > 63:
                    linelist[dm.Row] = sig.getMessageRowContent(64)

                linelist.insert(insertRowIndex,sig.getSG())
                for row in range(linelistSize):
                    if "GenSigStartValue" in str(linelist[linelistSize-1-row]):
                        linelist.insert(linelistSize-row,sig.getStartValue())
                        break
                #写入枚举
                enumStr=sig.getEnum()
                if len(enumStr) != 0:
                    linelist.append(enumStr) 
 
                #写入BU
                if sig.Sender not in self.control:
                    self.control.append(sig.Sender)
                    for row in range(linelistSize):
                        if linelist[row].startswith("BU_:"):
                            linelist[row]=linelist[row].replace(linelist[row],self.getBU())
                            break
                 
                wirteFileDicts(self.dbcPath,linelist,False)
                print(f"{sig.name} 写入完成")
            except Exception as e:
                print()
                print(f"{sig.name} 写入失败:{str(e)}")
        except:
            print(f'{sig.name} 正在写入message')
            if not self.writeMessage(sig,linelist):
                print(f'{sig.name} 没有message')
                return WriteDBCResult.NoMessage
            self.analy()
            self.writeSig(sig)
        return WriteDBCResult.WriteComplete

    def writeMessage(self,sig,linelist):
        # linelist=list(linelist)
        # sig=SigInfo(sig)
        if len(sig.messageId) == 0:
            return False
        linelist.insert(self.maxSigRow+1,"\n")
        linelist.insert(self.maxSigRow+2,sig.getMessageRowContent(8))
        linelistSize=len(linelist)
        for row in range(linelistSize):
            if "GenMsgCycleTime" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,sig.getMessageCycle())
                break

        for row in range(linelistSize):
            if "VFrameFormat" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,sig.getMessageVFrameFormat())
                break
        wirteFileDicts(self.dbcPath,linelist,False)
        return True
         



# a=Analyze("/home/chengxiongzhu/Works/Repos/tool_parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessageBySig("CdcDtc1HiByte"))
# sig=SigInfo()
# sig.endBit=104
# sig.length=13
# print(sig.getStartBit())
