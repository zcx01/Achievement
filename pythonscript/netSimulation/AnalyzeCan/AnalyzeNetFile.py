#!/usr/bin/python
import re
import os
from enum import Enum

from commonfun import *
from projectInI import *
from ccode import *

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

class NetSigInfo(object):
    def __init__(self) :
        self.name=""
        self.start_by_byte=0
        self.length_bits=0
        self.length_byte=0
        self.raw_value=0
        self.phy_value=0
        self.factor=0
        self.offset=0
        self.Offset=0
        self.phy_min=0
        self.phy_max=0
        self.Unit=0
        self.is_timeout=False
        #-------message--------
        self.Recevier=""
        self.Sender=""
        self.cycle=0 
        #----------代码中独有的------------
        self.structRow=-1
        self.externRow=-1
        self.netMsgRow=-1
        #----------can矩阵独有------------
        self.chineseName=''
    
    def getStrcutName(self):
        return 'struct NetSignal Net_{} ='.format(self.name)

    def getExtern(self):
        return 'extern struct NetSignal Net_{};'.format(self.name)

    def getNetMsg(self):
        return 'extern struct NetSignal Net_{};'.format(self.name)

    def getVariableNameAndValue(variable):
        return '.{} = {},'.format(getVariableName(variable)).format(variable)

    def getVariableNameAndBool(variable):
        return '.{}={}'.format(getVariableName(variable)).format(boolToStr(variable))

    def getStrcutCode(self):
        with CBaseBlock(self.getStrcutName()) as block_l0:
            block_l0.add_code_line(self.getVariableNameAndValue(self.start_by_byte),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.length_bits),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.length_byte),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.raw_value),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.phy_value),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.factor),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.offset),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.phy_min),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue(self.phy_max),termination='')
            block_l0.add_code_line(self.getVariableNameAndBool(self.is_timeout),termination='')
        return block_l0.data


class NetMessageInfo(object):
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


class AnalyzeNetParserFile(object):
    def __init__(self,net_parser_Path=None) :
        if len(net_parser_Path) ==0:
            return
        self.netSigs={} #以 name 为key
        self.netMessage={} # 以 十六进制ID 为key
        self.netParserFile=net_parser_Path
        self.maxSigRow=0
        self.analy()
    
    def analy(self):
        self.netSigs={}
        self.netMessage={}
        self.maxSigRow=0
        for (dirpath,dirnames,filenames) in os.walk(self.netParserFile):
            sigInfo = None
            for filename in filenames:
                if getSuffix(filename) != SOURCE: continue
                with open(filename,"r") as f:
                    linelist=f.readlines()
                    rowIndex=-1
                    for text in linelist:
                        rowIndex+=1
                        text=text.strip()
                        if len(text) == 0:
                            continue
                        if text.startswith("struct NetSignal Net_"):
                            try:
                                sigInfo = NetSigInfo()
                                net = r"Net_.\w+"
                                texts = re.findall(net,text,re.A)
                                if len(texts) != 0:
                                    sigInfo.name = texts[0]
                                self.netSigs[sigInfo.name] = sigInfo
                            except:
                                pass
                        variableValue,exist = getVariableText(sigInfo.start_by_byte,text)
                        if exist: sigInfo.start_by_byte = int(variableValue)
                        variableValue,exist = getVariableText(sigInfo.length_bits,text)
                        if exist: sigInfo.length_bits = int(variableValue)
                        variableValue,exist = getVariableText(sigInfo.length_byte,text)
                        if exist: sigInfo.length_byte = int(variableValue)
                        variableValue,exist = getVariableText(sigInfo.raw_value,text)
                        if exist: sigInfo.raw_value = int(variableValue)
                        variableValue,exist = getVariableText(sigInfo.phy_value,text)
                        if exist: sigInfo.phy_value = float(variableValue)
                        variableValue,exist = getVariableText(sigInfo.factor,text)
                        if exist: sigInfo.factor = float(variableValue)
                        variableValue,exist = getVariableText(sigInfo.offset,text)
                        if exist: sigInfo.offset = float(variableValue)
                        variableValue,exist = getVariableText(sigInfo.phy_min,text)
                        if exist: sigInfo.phy_min = float(variableValue)
                        variableValue,exist = getVariableText(sigInfo.phy_max,text)
                        if exist: sigInfo.phy_max = float(variableValue)
                        variableValue,exist = getVariableText(sigInfo.is_timeout,text)
                        if exist: sigInfo.is_timeout = strToBool(variableValue)                                                

    def writeFile(self):
        sigInfos = list(self.netSigs.values())
        sigInfos.sort(key=lambda siginfo: siginfo.start_by_byte)
        for (dirpath,dirnames,filenames) in os.walk(self.netParserFile):
            for filename in filenames:
                suffix = getSuffix(filename)
                if suffix == HEAD:

        pass
    def repalceContent(self,linelist,row,content,isTip = True):
        if len(content) != 0 and row > 0:
            linelist[row] = content
        elif(isTip):
            print(f'{content}内容为空, {row} 行号小于等于0')

    def RowContent(self,rowIndexs,row):
        if row > 0:
            rowIndexs.append(row)                       
        

    #----------------------------------对外接口-----------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    def getSig(self,sigName):
        if sigName in self.netSigs:
            return self.netSigs[sigName]
        for messageSig in self.netSigs:
            sig = self.netSigs[messageSig]
            assert isinstance(sig,NetSigInfo)
            if sig.name.upper() == sigName.upper() or sig.getMessage_Sig().upper() == sigName.upper():
                return sig
        return None

    def getMessage(self,msgId): #msgId 16进制
        try:
            return self.netMessage[msgId]
        except:
            return None

    def sigExist(self,sigName):
        return self.getSig(sigName) != None
        # sys.exit()

    def writeSig(self,sig,msg):
        assert isinstance(sig,NetSigInfo)
        assert isinstance(msg,NetMessageInfo)

    def removeSig(self,sigs,isWirte=True):
        removeIndex = []
        for sig in sigs:
            assert isinstance(sig,NetSigInfo)
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
            assert isinstance(msg,NetMessageInfo)
            ori_msg = self.netMessage.get(msg.messageId,None)
            assert isinstance(ori_msg,NetMessageInfo)
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
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------



# a=AnalyzeNetParserFile("/home/chengxiongzhu/Works/Repos/tool_parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessage_Id_BySig("CdcDtc1HiByte"))
# sig=NetSigInfo()
# sig.endBit=104
# sig.length=13
# print(sig.getStartBit())
