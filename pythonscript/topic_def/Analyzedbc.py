#!/usr/bin/python
import sys
import os
import re
from enum import Enum
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
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
    def __init__(self) :
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
        self.useBit=[]
        #-------message--------
        self.Recevier=""
        self.Sender=""
        self.cycle=0
        #----------dbc中独有的------------
        self.Row=0
        self.initRow=0
        self.enumRow=0
    
    def getMId(self):
        return int(self.messageId,16)

    def getSG(self):
        return f' SG_ {self.name} : {self.startBit}|{self.length}@0{self.dataType} ({self.factor},{self.Offset}) [{self.min}|{self.max}] {self.Unit}  {self.Recevier}'
    
    def getEnum(self):
        enumS = self.enum.replace("\n",':')
        enumS = enumS.split(':')
        enumStr = self.getEnumBylist(enumS)
        if len(enumStr) == 0:
            enumS=re.findall(e_i,self.enum,re.A)
            enumStr = self.getEnumBylist(enumS)
        return enumStr

    def getEnumBylist(self,enumS):
        try:
            enumStrA=[]
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

    def getMessage_Sig(self):
        return self.getMessage_Id()+"__"+self.name

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
        assert isinstance(other,SigInfo)
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

class MessageInfo(object):
    def __init__(self) -> None:
        super().__init__()
        self.messageId = 0
        self.sender=''
        self.cycle = 0
        self.frame=0
        self.subNet=''
        self.Recevier=''
        self.lenght=0
        #---------dbc专有
        self.message_Id=''
        self.sigs=[]
        self.Row=-1
        self.cycleRow=0
        self.frameRow=0
        self.sigMaxRow=-1

    def getMessage_Id(self):
        if len(self.message_Id) !=0:
            return self.message_Id
        return f'{self.sender}_{self.messageId}'

    def getAllSigInitValue(self):
        sig_value={}
        for sig in self.sigs:
            assert isinstance(sig,SigInfo)
            sig_value[sig.name] = sig.min
        return sig_value

    def getMId(self):
        return int(self.messageId,16)

    def getMessageRowContent(self):
        return f'BO_  {self.getMId()} {self.getMessage_Id()}: {self.lenght} {self.sender}'

    def getMessageCycle(self):
        return f'BA_ \"GenMsgCycleTime\" BO_ {self.getMId()} {self.cycle};'

    def getMessageVFrameFormat(self):
        return f'BA_ \"VFrameFormat\" BO_ {self.getMId()} {self.frame};'

    def CopyXls(self,other):
        assert isinstance(other,MessageInfo)
        self.messageId = other.messageId
        self.sender= other.sender
        self.cycle =  other.cycle
        self.frame=  other.frame
        self.subNet= other.subNet
        self.Recevier= other.Recevier
        self.lenght= other.lenght
        

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
        isStart = False
        with open(self.dbcPath,"r") as f:
            linelist=f.readlines()
            currentdbcMessage=None
            rowIndex=-1
            for text in linelist:
                rowIndex+=1
                text=text.strip()
                if len(text) == 0:
                    continue
                if text.startswith("BU_:"):
                    if not isStart: isStart = True
                    try:
                        self.control = splitSpace(text.split(":")[1])
                    except:
                        pass
                if not isStart: continue

                if text.startswith("BO_") :
                    dm= Analyze.analyMessage(text)
                    if dm == None:
                        continue
                    dm.Row=rowIndex
                    dm.sigMaxRow=dm.Row+1
                    self.dbcMessage[dm.messageId]=dm
                    currentdbcMessage =dm
                elif text.startswith("SG_"):
                    ds = Analyze.analySG(text)
                    ds.Sender = currentdbcMessage.sender
                    ds.messageId = currentdbcMessage.messageId
                    ds.Row=rowIndex
                    self.dbcSigs[ds.name] = ds
                    self.maxSigRow = rowIndex
                    try: 
                        currentdbcMessage.sigMaxRow = rowIndex+1
                        currentdbcMessage.sigs.append(ds)
                    except:
                        pass
                elif "GenSigStartValue" in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        sigName = texts[4]
                        sigValue = int(texts[5])
                        sig = self.dbcSigs[sigName]
                        assert isinstance(sig,SigInfo)
                        sig.initValue = sigValue
                        sig.initRow = rowIndex
                    except:
                        # print(f'初始值 {text} 信号不在定义中')
                        pass
                elif "GenMsgCycleTime" in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageId = getNoOx16(texts[3])
                        me = self.dbcMessage[messageId]
                        assert isinstance(me,MessageInfo)
                        me.cycle = int(texts[4])
                        me.cycleRow = rowIndex
                    except:
                        # print(f'周期 {text} 不在定义中')
                        pass
                elif 'VFrameFormat' in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageId = getNoOx16(texts[3])
                        me = self.dbcMessage[messageId]
                        assert isinstance(me,MessageInfo)
                        me.frame = int(texts[4])
                        me.frameRow = rowIndex
                    except:
                        # print(f'frame {text} 不在定义中')
                        pass
                elif text.startswith('VAL_'):
                    try:
                        texts = re.findall(e_i,text,re.A)
                        sigName = texts[2]
                        sig = self.dbcSigs[sigName]
                        assert isinstance(sig,SigInfo)
                        try:
                            sig.enum = text.split(sigName)[1].strip()
                        except:
                            pass
                        sig.enumRow = rowIndex
                    except:
                        print(f'枚举值 {text} 信号不在定义中')
                        pass

    def sigExist(self,sigName):
        return sigName in self.dbcSigs

    def sender(self,sigName):
        try:
            sig = self.dbcSigs[sigName]
            assert isinstance(sig,SigInfo)
            return sig.Sender 
        except:
            return ''

    def getMessage_Id_BySig(self,sigName):
        try:
            sig = self.dbcSigs[sigName]
            assert isinstance(sig,SigInfo)
            return sig.getMessage_Id()
        except:
            # print(f'{sig}没有找到message')
            return ""
            # sys.exit()

    def getMessage_Id_Sig(self,sigName):
        try:
            sig = self.dbcSigs[sigName]
            assert isinstance(sig,SigInfo)
            return sig.getMessage_Sig()
        except:
            return ""

    def getSigDataType(self,sigName):
        dataTypeStr=""
        try:
            sig = self.dbcSigs.get(sigName)
            assert isinstance(sig,SigInfo)
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
        ms = MessageInfo()
        ms.messageId =  getNoOx16(messages[1])
        ms.message_Id = messages[2]
        ms.lenght = messages[3]
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

    def writeSig(self,sig,msg):
        assert isinstance(sig,SigInfo)
        assert isinstance(msg,MessageInfo)
        linelist=readFileLines(self.dbcPath)
        linelistSize=len(linelist)
        if sig.name in self.dbcSigs:
            print(f"{sig.name}信号已经存在")
            return WriteDBCResult.AlreadyExists
        try:
            dm = self.dbcMessage.get(sig.messageId)
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
            if not self.writeMessage(msg,linelist):
                print(f'{sig.name} 没有message')
                return WriteDBCResult.NoMessage
            self.analy()
            self.writeSig(sig,msg)
        return WriteDBCResult.WriteComplete

    def writeMessage(self,msg,linelist):
        assert isinstance(linelist,list)
        assert isinstance(msg,MessageInfo)
        if len(msg.messageId) == 0:
            return False
        linelist.insert(self.maxSigRow+1,"\n")
        linelist.insert(self.maxSigRow+2,msg.getMessageRowContent())
        linelistSize=len(linelist)
        for row in range(linelistSize):
            if "GenMsgCycleTime" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,msg.getMessageCycle())
                break

        for row in range(linelistSize):
            if "VFrameFormat" in str(linelist[linelistSize-1-row]):
                linelist.insert(linelistSize-row,msg.getMessageVFrameFormat())
                break
        wirteFileDicts(self.dbcPath,linelist,False)
        return True
         
    def repalceMessage(self,msgs):
        linelist = readFileLines(self.dbcPath)
        for msg in msgs:
            assert isinstance(msg,MessageInfo)
            linelist[msg.Row] = msg.getMessageRowContent()
            linelist[msg.cycleRow] = msg.getMessageCycle()
            linelist[msg.frameRow] =  msg.getMessageVFrameFormat()
            # print(f'替换 {msg.messageId} {msg.Row} {msg.cycleRow} {msg.frameRow}')
        wirteFileDicts(self.dbcPath, linelist, False)



# a=Analyze("/home/chengxiongzhu/Works/Repos/tool_parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessage_Id_BySig("CdcDtc1HiByte"))
# sig=SigInfo()
# sig.endBit=104
# sig.length=13
# print(sig.getStartBit())