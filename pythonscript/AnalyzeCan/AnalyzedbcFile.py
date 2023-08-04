#!/usr/bin/python
import re
from enum import Enum

from commonfun import *
from projectInI import *
'''
    Motorola格式的dbc中保存的start Bit 是MSB（高字节）
    CANdb++ 显示的是start Bit 是LSB（第字节）
    MSB:表示CAN矩阵是不是高字节存储
    标准CAN:超过8字节
    CAN FD:最大64字节
'''
class DataType(Enum):
    VINT=1
    VFLOAT=2

class WriteDBCResult(Enum):
    AlreadyExists=1     #信号已经存在
    SignalCoverage=2    #信号有覆盖
    WriteComplete=3     #写入完成
    NoMessage=4         #没有message

class CompareResult(Enum):
    No=0            #没有相同的地方
    Bit=1           #字节相同
    Name=2          #名字相同,包括message名称也相同
    SigName=3       #仅仅信号名相同

class SigSendType(Enum):
    Normal = 0      #正常
    Event  = 1      #事件
    Three  = 2      #三帧反转

class SigInfo(object):
    def __init__(self) :
        self.messageId = ""
        self.name=""
        self.startBit=-1
        self.endBit=-1
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
        self.subNet=''
        self.sendType = SigSendType.Normal #发送的类型是事件还是周期 1表示事件 2 表示三帧反转
        #-------message--------
        self.Recevier=""
        self.Sender=""
        self.cycle=0 
        #----------dbc中独有的------------
        self.Row=-1
        self.initRow=-1
        self.enumRow=-1
        self.sendTypeRow = -1
        self.isdbcEnum = False #是否是dbc中的枚举，如果True枚举就是不转化
        self.messgae_Name = ""
        #----------can矩阵独有------------
        self.chineseName=''
    
    def SetUnit(self,value):
        if value == r"/" or len(value) == 0:
            self.Unit = "\"\""
        self.Unit = f'\"{value}\"'

    def getMId(self):
        return int(self.messageId,16)

    def getSG(self):
        return f' SG_ {self.name} : {self.startBit}|{self.length}@0{self.dataType} ({self.factor},{self.Offset}) [{self.min}|{self.max}] {self.Unit}  {self.Recevier}'
    
    def getEnum(self):
        if self.isdbcEnum:
            if len(self.enum) != 0:
                return f'VAL_ {self.getMId()} {self.name} {self.enum}'
        else:
            enumS = self.enum.replace("\n",':')
            enumS = enumS.split(':')
            enumStr = self.getEnumBylist(enumS)
            if len(enumStr) == 0:
                enumS=re.findall(e_i,self.enum,re.A)
                enumStr = self.getEnumBylist(enumS)
            return enumStr
        return ''
        
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

    def getSigSendType(self):
        return f'BA_ \"GenSigSendType\" SG_  {self.getMId()} {self.name} {self.sendType.value};'

    def getMessage_Name(self):
        if len(self.messgae_Name) != 0:
            return self.messgae_Name
        return f'{self.Sender}_{self.messageId}'

    def getMessage_SubNet(self):
         return f'{self.subNet}_{self.messageId}'

    def getMessage_Sig(self):
        return self.getMessage_Name()+"__"+self.name

    #endBit+(length - length%8)+(8-length)+1=startBit
    def getStartBit(self):
        return self.getMotorolaStartBit()

    def getEndBit(self):
        return self.getMotorolaEndBit()

    def getMotorolaStartBit(self):# LSB -> MSB
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

    def getMotorolaEndBit(self):# MSB -> LSB
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
        isSame=CompareResult.No
        link=' --- '
        if self.startBit == other.startBit and self.endBit == other.endBit and self.messageId == other.messageId:
            isSame = CompareResult.Bit
            if self.name.replace(' ','').lower() != other.name.replace(' ','').lower():
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
            if self.sendType != other.sendType:
                result.append(f'类型:{other.sendType}{link}{self.sendType}')
            if self.cycle != other.cycle:
                result.append(f'周期:{other.cycle}{link}{self.cycle}')
            # if len(result) != 0:
            #     result.insert(0,f'{other.name}和原来的{self.name}在同一个message{self.messageId},具体的差别如下:')
        elif self.name+self.messageId == other.name+other.messageId:
            isSame = CompareResult.Name
            # result.append(f"{self.name}名称和message相同,具体的差别如下:")
            if  self.length != other.length:
                result.append(f"长度:{other.length}{link}{self.length}")
            if self.endBit != other.endBit:
                result.append(f"结束位:{other.endBit}{link}{self.endBit}")
            if self.messageId != other.messageId:
                result.append(f"messageId:{other.messageId}{link}{self.messageId}")
        # elif self.name == other.name:
        #     isSame = CompareResult.SigName
        #     result.append(f"name:{self.name},message:{self.messageId} {other.messageId}")
        
        return isSame,result
    
    def RecevierRemoveSend(self):
        if len(self.Recevier)==0 or self.Recevier == None:
            self.Recevier = "Vector__XXX"
        receviers = re.findall(e_i,self.Recevier)
        if self.Sender in receviers:
            receviers.remove(self.Sender)
        if len(receviers) == 0:
            receviers.append("Vector__XXX")
        self.Recevier = ",".join(receviers)

class MessageInfo(object):
    def __init__(self) -> None:
        super().__init__()
        self.messageId = 0 #16进制
        self.sender=''
        self.cycle = 0
        self.threeCycle = 0 #三帧反转的周期
        self.frame=0
        self.subNet=''
        self.Recevier=''
        self.lenght=0
        self.sendType=0
        #---------dbc专有
        self.message_Name=''
        self.sigs=[]
        self.Row=-1
        self.cycleRow=-1
        self.frameRow=-1
        self.sendTypeRow=-1
        self.sigMaxRow=-1
        self.threeCycleRow=-1

    def getMessage_Id(self):
        if len(self.message_Name) !=0:
            return self.message_Name
        return f'{self.sender}_{self.messageId}'

    def getMessage_SubNet(self):
        return f'{self.subNet}_{self.messageId}'

    def getAllSigInitValue(self):
        sig_value={}
        for sig in self.sigs:
            assert isinstance(sig,SigInfo)
            sig_value[sig.name] = sig.min
        return sig_value

    def getMId(self):
        preStr=''
        for i in range(len(self.messageId)):
            if '0' != self.messageId[i]:
                break
            preStr+='0'
        return preStr+str(int(self.messageId,16))

    def getMessageRowContent(self):
        return f'BO_  {self.getMId()} {self.getMessage_Id()}: {self.lenght} {self.sender}'

    def getMessageCycle(self):
        return f'BA_ \"GenMsgCycleTime\" BO_ {self.getMId()} {self.cycle};'

    def getMsgCycleTimeFast(self):
        threeCycle = self.threeCycle
        if threeCycle == 0:
            threeCycle = self.cycle
        if threeCycle !=0:
            return f'BA_ \"GenMsgCycleTimeFast\" BO_ {self.getMId()} {threeCycle};'
        return ''

    def getMessageVFrameFormat(self):
        return f'BA_ \"VFrameFormat\" BO_ {self.getMId()} {self.frame};'

    def getMessageSendType(self):
        return f'BA_ \"GenMsgSendType\" BO_ {self.getMId()} {self.sendType};'

class AnalyzeFile(object):
    def __init__(self,dbc_file=None) :
        if len(dbc_file) ==0:
            return
        self.dbcSigs={} #以 十进制ID+名称 为key
        self.dbcMessage={} # 以 十六进制ID 为key
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
                        self.maxSigRow = rowIndex
                    except:
                        pass
                if not isStart: continue

                if text.startswith("BO_") :
                    dm= AnalyzeFile.analyMessage(text)
                    if dm == None:
                        continue
                    dm.Row=rowIndex
                    dm.sigMaxRow=dm.Row+1
                    self.dbcMessage[dm.messageId]=dm
                    currentdbcMessage =dm
                elif text.startswith("SG_"):
                    ds = AnalyzeFile.analySG(text)
                    ds.Sender = currentdbcMessage.sender
                    ds.messgae_Name = currentdbcMessage.message_Name
                    ds.messageId = currentdbcMessage.messageId
                    ds.Row=rowIndex
                    self.dbcSigs[str(ds.getMId())+ds.name] = ds
                    self.maxSigRow = rowIndex
                    try: 
                        currentdbcMessage.sigMaxRow = rowIndex+1
                        currentdbcMessage.sigs.append(ds)
                    except:
                        pass
                elif "GenSigStartValue" in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageIdS = texts[3]
                        sigName = texts[4]
                        sigValue = int(texts[5])
                        sig = self.dbcSigs[messageIdS+sigName]
                        assert isinstance(sig,SigInfo)
                        sig.initValue = sigValue
                        sig.initRow = rowIndex
                    except:
                        # print(f'初始值 {text} 信号不在定义中')
                        pass
                elif "GenSigSendType" in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageIdS = texts[3]
                        sigName = texts[4]
                        sigValue = int(texts[5])
                        sig = self.dbcSigs[messageIdS+sigName]
                        assert isinstance(sig,SigInfo)
                        sig.sendType = SigSendType(sigValue)
                        sig.sendTypeRow = rowIndex
                    except:
                        # print(f'初始值 {text} 信号不在定义中')
                        pass
                elif "GenMsgCycleTimeFast" in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageId = getNoOx16(texts[3])
                        me = self.dbcMessage[messageId]
                        assert isinstance(me,MessageInfo)
                        me.threeCycle = int(texts[4])
                        me.threeCycleRow = rowIndex
                    except:
                        # print(f'周期 {text} 不在定义中')
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
                elif 'GenMsgSendType' in text:
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageId = getNoOx16(texts[3])
                        me = self.dbcMessage[messageId]
                        assert isinstance(me,MessageInfo)
                        me.sendType = int(texts[4])
                        me.sendTypeRow = rowIndex
                    except:
                        # print(f'frame {text} 不在定义中')
                        pass
                elif text.startswith('VAL_'):
                    try:
                        texts = re.findall(e_i,text,re.A)
                        messageIdS = texts[1]
                        sigName = texts[2]
                        sig = self.dbcSigs[messageIdS+sigName]
                        assert isinstance(sig,SigInfo)
                        try:
                            sig.enum = text.split(sigName)[1].strip()
                            sig.isdbcEnum = True
                        except:
                            pass
                        sig.enumRow = rowIndex
                    except:
                        print(f'枚举值 {sigName} {self.dbcPath} {text} 信号不在定义中')
                        printYellow("可能是大小的写的问题")
                        pass
    
    @staticmethod
    def analyMessage(text):
        messages = re.findall(e_i,text,re.A)
        if len(messages) < 4:
            return None
        ms = MessageInfo()
        ms.messageId =  getNoOx16(messages[1])
        ms.message_Name = messages[2]
        ms.lenght = int(messages[3])
        ms.sender = messages[4]
        return ms

    def getBU(self):
        return f'BU_: {" ".join(self.control)}'
        
    @staticmethod
    def analySG(text):
        sig=SigInfo()
        assert isinstance(text,str)
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
            
            texts = text.split(r'"')
            sig.SetUnit(texts[1])
            sig.Recevier = texts[2].strip()
        except:
            pass
        sig.getEndBit()
        return sig

    @staticmethod
    def appendKey(linelist,key,defalut=-1):
        assert isinstance(linelist,list)
        linelistSize = len(linelist)
        keys = re.findall(e_i,key,re.A)
        for row in range(linelistSize):
            lastStr = str(linelist[linelistSize-1-row])
            if lastStr.startswith(keys[0]+' '):
                lastStrs = re.findall(e_i,lastStr,re.A)
                if len(lastStrs) >1 and lastStrs[1] == keys[1]:
                    linelist.insert(linelistSize-row,key)
                    return linelistSize-row+1
        if defalut != -1:
            linelist.insert(defalut,key)
            return defalut+1
        linelist.append(key)
        return linelistSize+1
    
    def repalceContent(self,linelist,row,content,isTip = True):
        if len(content) != 0 and row > 0:
            linelist[row] = content
        elif(isTip):
            print(f'{content}内容为空, {row} 行号小于等于0')

    def RowContent(self,rowIndexs,row):
        if row > 0:
            rowIndexs.append(row)                       
        
    def writeMessage(self,msg,linelist):
        assert isinstance(linelist,list)
        assert isinstance(msg,MessageInfo)
        if len(msg.messageId) == 0:
            return False
        linelist.insert(self.maxSigRow+1,"\n")
        linelist.insert(self.maxSigRow+2,msg.getMessageRowContent())
        AnalyzeFile.appendKey(linelist,msg.getMessageVFrameFormat())
        AnalyzeFile.appendKey(linelist,msg.getMessageSendType())
        appCycleRow = -1
        if msg.cycle != 0:
            appCycleRow = AnalyzeFile.appendKey(linelist,msg.getMessageCycle())
        msgCycleTimeFast = msg.getMsgCycleTimeFast()
        if len(msgCycleTimeFast) != 0:
            AnalyzeFile.appendKey(linelist,msgCycleTimeFast,appCycleRow)
        wirteFileDicts(self.dbcPath,linelist,False)
        return True

    @staticmethod
    def getValueType(sig,flag):
        assert isinstance(sig,SigInfo)
        return flag in str(sig.min) or flag in str(sig.max) or flag in str(sig.Offset) or flag in str(sig.factor)
    #----------------------------------对外接口-----------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    def getSig(self,sigName):
        if sigName in self.dbcSigs:
            return self.dbcSigs[sigName]
        for messageSig in self.dbcSigs:
            sig = self.dbcSigs[messageSig]
            assert isinstance(sig,SigInfo)
            if sig.name.upper() == sigName.upper() or sig.getMessage_Sig().upper() == sigName.upper():
                return sig
        return None

    def getMessage(self,msgId): #msgId 16进制
        try:
            return self.dbcMessage[msgId]
        except:
            return None

    def getSigsByMessageId(self,msgId):
        sigs=[]
        for messageSig in self.dbcSigs:
            sig = self.dbcSigs[messageSig]
            assert isinstance(sig,SigInfo)
            if sig.messageId == msgId:
                sigs.append(sig)
        return sigs

    def sigExist(self,sigName):
        return self.getSig(sigName) != None

    def sender(self,sigName):
        try:
            sig = self.getSig(sigName)
            assert isinstance(sig,SigInfo)
            return sig.Sender 
        except:
            return ''

    def getMessage_Id_BySig(self,sigName):
        try:
            sig = self.getSig(sigName)
            assert isinstance(sig,SigInfo)
            return sig.getMessage_Name()
        except:
            # print(f'{sig}没有找到message')
            return ""
            # sys.exit()

    def getMessage_Id_Sig(self,sigName):
        try:
            sig = self.getSig(sigName)
            assert isinstance(sig,SigInfo)
            return sig.getMessage_Sig()
        except:
            return ""

    def getSigDataType(self,sigName):
        dataTypeStr=""
        try:
            sig = self.getSig(sigName)
            assert isinstance(sig,SigInfo)
            dayaType = sig.dataType
            if AnalyzeFile.getValueType(sig,'.'):
                dataTypeStr='float'
            elif dayaType == '-' or  AnalyzeFile.getValueType(sig,'-'):
                dataTypeStr="int32_t" 
            else:
                dataTypeStr="uint32_t"
        except:
            pass
        return dataTypeStr

    def writeSig(self,sig,msg):
        assert isinstance(sig,SigInfo)
        assert isinstance(msg,MessageInfo)
        linelist=readFileLines(self.dbcPath)
        linelistSize=len(linelist)
        if str(sig.getMId())+sig.name in self.dbcSigs:
            # print(f"{sig.name}信号已经存在")
            return WriteDBCResult.AlreadyExists
        try:
            dm = self.dbcMessage.get(sig.messageId)
            assert isinstance(dm,MessageInfo)
            #如果大小不一致，取最大的值
            if msg.lenght > dm.lenght:
                linelist[dm.Row] = msg.getMessageRowContent()

            startRow = dm.Row+1
            insertRowIndex=-1
            try:
                userIndex={}
                while(startRow < dm.sigMaxRow):
                    lineSig = AnalyzeFile.analySG(linelist[startRow])
                    userIndex[lineSig.name] = lineSig.useBit
                    if lineSig.startBit > sig.startBit and insertRowIndex == -1:
                        insertRowIndex = startRow 
                    startRow+=1

                if insertRowIndex == -1:
                    insertRowIndex = dm.sigMaxRow
              
                #判断信号是否合理
                sigUsrIndexs=sig.useBit
                cover_count = 0
                user_sigName = []
                for user in userIndex:
                    is_user = False
                    for sigUsrIndex in sigUsrIndexs:
                        if sigUsrIndex in userIndex[user]:
                            cover_count+=1
                            # print(sigUsrIndex,str(userIndex[user]),user,"----------")
                            is_user = True
                    if cover_count == 0:
                        continue
                    if cover_count == len(userIndex[user]) and cover_count == len(sigUsrIndexs) and len(user_sigName) == 0:
                        printYellow(f"{sig.name}: {str(sigUsrIndexs)} 与 {user}: {userIndex[user]} 字节相同+++++  ")
                        return WriteDBCResult.SignalCoverage
                    elif is_user:
                        user_sigName.append(user)
                        
                if cover_count == len(sigUsrIndexs):
                    printYellow(f"{sig.name} 与 {user_sigName} 字节相同")
                    return WriteDBCResult.SignalCoverage
                elif cover_count != 0:
                    if len(user_sigName) ==1:
                        user = user_sigName[0]
                        printRed(f"{sig.name} 信号有覆盖:开始字节 {sig.startBit} ,结束的字节 {sig.endBit} ,占用的字节 {sigUsrIndexs} ,与 {user} 覆盖字节 {userIndex[user]}")
                    else:
                        printYellow(f"{sig.name} 与 {user_sigName} 字节冲突")
                    return WriteDBCResult.SignalCoverage

                linelist.insert(insertRowIndex,sig.getSG())
                msg.message_Name = dm.message_Name
                sig.messgae_Name = dm.message_Name
                insertRow = AnalyzeFile.appendKey(linelist,sig.getStartValue())
                if sig.sendType != SigSendType.Normal:
                    AnalyzeFile.appendKey(linelist,sig.getSigSendType(),insertRow)
 
                #写入BU
                if sig.Sender not in self.control:
                    self.control.append(sig.Sender)
                    for row in range(linelistSize):
                        if linelist[row].startswith("BU_:"):
                            linelist[row]=linelist[row].replace(linelist[row],self.getBU())
                            break
                 
                #写入枚举
                enumStr=sig.getEnum()
                if len(enumStr) != 0:
                    linelist.append(enumStr) 

                wirteFileDicts(self.dbcPath,linelist,False)
                printGreen(f"{sig.name} 写入完成")
            except Exception as e:
                printRed(f"{sig.name} 写入失败:{str(e)}")
        except:
            print(f'{sig.name} 正在写入message')
            if not self.writeMessage(msg,linelist):
                print(f'{sig.name} 没有message')
                return WriteDBCResult.NoMessage
            self.analy()
            self.writeSig(sig,msg)
        return WriteDBCResult.WriteComplete

    def repalceSigEnum(self,sigs):
        linelist = readFileLines(self.dbcPath)
        for sig in sigs:
            assert isinstance(sig,SigInfo)
            ori_sig = self.getSig(str(sig.getMId())+sig.name)
            if ori_sig == None:
                print(f'{sig.name} 不存在')
                continue

            enumStr = sig.getEnum()
            if len(enumStr) !=0:
                if ori_sig.enumRow <= 0:
                    linelist.append(enumStr)
                else:
                    linelist[ori_sig.enumRow] = enumStr
            print(sig.name,'-------',enumStr)
        wirteFileDicts(self.dbcPath, linelist, False)

    def repalceSig(self,sigs):
        linelist = readFileLines(self.dbcPath)
        for sig in sigs:
            assert isinstance(sig,SigInfo)
            ori_sig = self.getSig(str(sig.getMId())+sig.name)
            if ori_sig == None:
                print(f'{sig.name} 不存在')
                continue
            self.repalceContent(linelist,ori_sig.Row, sig.getSG())
            self.repalceContent(linelist,ori_sig.initRow, sig.getStartValue())
            self.repalceContent(linelist,ori_sig.sendTypeRow, sig.getSigSendType(),False)
            enumStr = sig.getEnum()
            if len(enumStr) !=0:
                if ori_sig.enumRow <= 0:
                    linelist.append(enumStr)
                else:
                    linelist[ori_sig.enumRow] = enumStr
        wirteFileDicts(self.dbcPath, linelist, False) 

    def removeSig(self,sigs,isWirte=True):
        removeIndex = []
        for sig in sigs:
            assert isinstance(sig,SigInfo)
            self.RowContent(removeIndex,sig.Row)
            self.RowContent(removeIndex,sig.initRow)
            self.RowContent(removeIndex,sig.sendTypeRow)
            self.RowContent(removeIndex,sig.enumRow)
            printGreen(f"移除{sig.name}信号完成")
        linelist = readFileLines(self.dbcPath)
        linelist=removeListIndexs(linelist,removeIndex)
        if isWirte:
            wirteFileDicts(self.dbcPath, linelist, False)
        return removeIndex

    def removeMessage(self,masgs):
        removeIndex = []
        for msg in masgs:
            assert isinstance(msg,MessageInfo)
            ori_msg = self.dbcMessage.get(msg.messageId,None)
            assert isinstance(ori_msg,MessageInfo)
            if ori_msg == None:
                print(f'{msg.messageId} 不存在')
                continue
            sigs = self.getSigsByMessageId(ori_msg.messageId)
            removeIndex.extend(self.removeSig(sigs,False))
            self.RowContent(removeIndex,ori_msg.Row)
            self.RowContent(removeIndex,ori_msg.frameRow)
            self.RowContent(removeIndex,ori_msg.sendTypeRow)
            self.RowContent(removeIndex,ori_msg.cycleRow)
            self.RowContent(removeIndex,ori_msg.threeCycleRow)
        linelist = readFileLines(self.dbcPath)
        linelist=removeListIndexs(linelist,removeIndex)
        wirteFileDicts(self.dbcPath, linelist, False)
        printGreen("移除message完成")

    def repalceMessage(self,msgs):
        linelist = readFileLines(self.dbcPath)
        deleteRows = []
        for msg in msgs:
            assert isinstance(msg,MessageInfo)
            ori_msg = self.dbcMessage.get(msg.messageId,None)
            assert isinstance(ori_msg,MessageInfo)
            if ori_msg == None:
                print(f'{msg.messageId} 不存在')
                continue
            self.repalceContent(linelist,ori_msg.Row, msg.getMessageRowContent())
            self.repalceContent(linelist,ori_msg.frameRow, msg.getMessageVFrameFormat())
            self.repalceContent(linelist,ori_msg.sendTypeRow, msg.getMessageSendType())

            if msg.cycle != 0:
                self.repalceContent(linelist,ori_msg.cycleRow, msg.getMessageCycle())
            elif ori_msg.cycleRow < 0:
                self.RowContent(deleteRows,ori_msg.cycleRow)

            if msg.threeCycle != 0:
                self.repalceContent(linelist,ori_msg.threeCycleRow, msg.getMsgCycleTimeFast())
            elif ori_msg.threeCycleRow < 0:
                self.RowContent(deleteRows,ori_msg.threeCycleRow)
        
        if len(deleteRows) != 0:
            linelist=removeListIndexs(linelist,deleteRows)
            #print(f'替换 {msg.messageId} {msg.Row} {msg.cycleRow} {msg.frameRow}')
        printGreen(f'替换 {msg.messageId}')
        wirteFileDicts(self.dbcPath, linelist, False)

    #物理值是否有效
    def physicalValueVaild(self,sigName,value):
        sig = self.getSig(sigName)
        if '.' in str(value) and not AnalyzeFile.getValueType(sig,'.'):
            return False
        if float(sig.min) <= float(value) <= float(sig.max):
            return True
        return False

    #是否是本机发送
    def isLocateSend(self,sigName):
        sig = self.getSig(sigName)
        if sig != None:
            return sig.Sender in local_machine_Sender
        return False

    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------



# a=AnalyzeFile("/home/chengxiongzhu/Works/Repos/tool_parser/vendor/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessage_Id_BySig("CdcDtc1HiByte"))
# sig=SigInfo()
# sig.endBit=104
# sig.length=13
# print(sig.getStartBit())
