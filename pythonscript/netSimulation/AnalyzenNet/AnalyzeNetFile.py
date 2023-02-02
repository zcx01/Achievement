#!/usr/bin/python
import re
import os
from enum import Enum
from commonfun import *
from AnalyzenNet.projectInI import *
from AnalyzenNet.ccode import *
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"

class DataType(Enum):
    VINT=1
    VFLOAT=2

class WriteResult(Enum):
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
        self.Recevier=''
        self.Sender=''
        self.cycle=0
        self.messageId ='' 
        #----------代码中独有的------------
        self.structRow=-1
        self.externRow=-1
        self.netMsgRow=-1
        #----------can矩阵独有------------
        self.chineseName=''
        self.subNet=''
        self.dataType = ''
        self.enum=''
        self.initValue=''
        self.invalidValue=''
        self.Unit=''

    def SetUnit(self,value):
        if value == r"/" or len(value) == 0:
            self.Unit = "\"\""
        self.Unit = f'\"{value}\"'

    def getStrcutName(self):
        return 'struct NetSignal Net_{} ='.format(self.name)

    def getExtern(self):
        return 'extern struct NetSignal Net_{};'.format(self.name)

    def getNetMsg(self):
        return '	&Net_{},\n'.format(self.name)

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
            block_l0.add_blank_line()
        return block_l0.data

    #得到使用的字节,如果返回的数组有数据标识有冲突
    def getUseByte(self,useByte):
        conflictByte=[]
        conflict= False
        assert isinstance(useByte,list)
        for byte in range(self.length_byte):
            currentByte=self.start_by_byte+byte
            if currentByte in useByte:
                conflict = True
            if conflict:
                conflictByte.append(currentByte)
            else:
                useByte.append(currentByte)
        return conflictByte
class AnalyzeNetParserFile(object):
    def __init__(self,net_parser_Path=None) :
        if len(net_parser_Path) ==0:
            return
        self.netSigs={} #以 name 为key
        self.netParserFile=net_parser_Path
        self.maxSigRow=0
        self.analy()

    
    def analy(self):
        self.netSigs={}
        self.maxSigRow=0
        for (dirpath,dirnames,filenames) in os.walk(self.netParserFile):
            sigInfo = None
            for filename in filenames:
                filename=dirpath+filename
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
                                if texts[0] == "Net_ACC_LaneEquationC2":
                                    print("dd")
                                self.netSigs[sigInfo.name] = sigInfo
                            except:
                                pass
                            continue
                        if sigInfo == None:
                            continue
                        variableValue, exist = getVariableText('start_by_byte', text)
                        if exist:
                            sigInfo.start_by_byte = int(variableValue)
                            continue
                        variableValue, exist = getVariableText('length_bits', text)
                        if exist:
                            sigInfo.length_bits = int(variableValue)
                            continue
                        variableValue, exist = getVariableText('length_byte', text)
                        if exist:
                            sigInfo.length_byte = int(variableValue)
                            continue
                        variableValue, exist = getVariableText('raw_value', text)
                        if exist:
                            sigInfo.raw_value = int(variableValue)
                            continue
                        variableValue, exist = getVariableText('phy_value', text,True)
                        if exist:
                            sigInfo.phy_value = float(variableValue)
                            continue
                        variableValue, exist = getVariableText('factor', text,True)
                        if exist:
                            sigInfo.factor = float(variableValue)
                            continue
                        variableValue, exist = getVariableText('offset', text,True)
                        if exist:
                            sigInfo.offset = float(variableValue)
                            continue
                        variableValue, exist = getVariableText('phy_min', text,True)
                        if exist:
                            sigInfo.phy_min = float(variableValue)
                            continue
                        variableValue, exist = getVariableText('phy_max', text,True)
                        if exist:
                            sigInfo.phy_max = float(variableValue)
                            continue
                        variableValue, exist = getVariableText('is_timeout', text)
                        if exist:
                            sigInfo.is_timeout = strToBool(variableValue)

    @staticmethod
    def RemoveOldbBock(lineTexts,beginStr,endStr):
        assert isinstance(lineTexts,list)
        tmp=[]
        isRemove = False
        for lineText in lineTexts:
            if BUILDINGBLOCKSBEGIN in lineText:
                tmp.append(lineText)
                isRemove = True
            elif BUILDINGBLOCKEND in lineText:
                tmp.append(lineText)
                isRemove = True
            if not isRemove:
                tmp.append(lineText)
        return tmp
                
    def repalceContent(self,linelist,row,content,isTip = True):
        if len(content) != 0 and row > 0:
            linelist[row] = content
        elif(isTip):
            print(f'{content}内容为空, {row} 行号小于等于0')

    def RowContent(self,rowIndexs,row):
        if row > 0:
            rowIndexs.append(row) 

    def checkOneSigBit(self,sigInfo,useBtye):
        assert isinstance(sigInfo,NetSigInfo)
        if sigInfo.messageId not in useBtye:
            useBtye[sigInfo.messageId]=[]
        conflictByte=sigInfo.getUseByte(useBtye[sigInfo.messageId])
        if len(conflictByte) != 0:
            printRed(f'{sigInfo.name}字节有冲突，冲突的字节为{conflictByte}')
            return False
        return True

    def checkSigBit(self,sig=None):
        useBtye={}
        if sig==None:
            passCheck = True
            sigInfos = list(self.netSigs.values())
            for sigInfo in sigInfos:
                if not self.checkOneSigBit(sigInfo,useBtye):
                    passCheck = False
            return passCheck
        else:
            return self.checkOneSigBit(sig,useBtye)

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
        return None

    def sigExist(self,sigName):
        return self.getSig(sigName) != None
        # sys.exit()

    def addSig(self,sigInfo):
        assert isinstance(sigInfo,NetSigInfo)
        if self.sigExist(sigInfo.name):
            return WriteResult.AlreadyExists
        elif not self.checkSigBit(sigInfo):
            return WriteResult.SignalCoverage
        self.netSigs[sigInfo.name] = sigInfo
        return WriteResult.WriteComplete

    def repalceSig(self,sigInfo):
        assert isinstance(sigInfo,NetSigInfo)
        self.netSigs[sigInfo.name] = sigInfo

    def removeSigs(self,sigInfos):
        for sigInfo in sigInfos:
            assert isinstance(sigInfo,NetSigInfo)
            if  sigInfo.name in self.netSigs:
                del self.netSigs[sigInfo.name]
                printGreen(f'{sigInfo.name}删除成功')
            printGreen(f'{sigInfo.name}不存在')
        self.writeFile(False,False)

    def removeSigByNames(self,sigNames):
        sigInfos=[]
        for sigName in sigNames:
            if sigName in self.netSigs:
                sigInfos.append(self.netSigs[sigName])
        self.removeSigs(sigInfos)

    def removeMessage(self,msgId):
        allsigInfos = list(self.netSigs.values())
        sigInfos=[]
        for sigInfo in allsigInfos:
            assert isinstance(sigInfo,NetSigInfo)
            if str(sigInfo.messageId) == str(msgId):
                sigInfos.append(sigInfo)
        self.removeSigs(sigInfos)


    def writeFile(self,isCheck=True,isTip=True):
        if isCheck and not self.checkSigBit(): return WriteResult.SignalCoverage
        sigInfos = list(self.netSigs.values())
        sigInfos.sort(key=lambda siginfo: siginfo.start_by_byte)
        for (dirpath,dirnames,filenames) in os.walk(self.netParserFile):
            for filename in filenames:
                filename=dirpath+filename
                suffix = getSuffix(filename)
                lineTexts = readFileLines(filename)
                lineTexts = RemoveBlock(lineTexts,BUILDINGBLOCKSBEGIN,BUILDINGBLOCKEND)
                if suffix == HEADFILNE:
                    tmp = []
                    for sigInfo in sigInfos:
                        assert isinstance(sigInfo,NetSigInfo)
                        tmp.append(sigInfo.getExtern())
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,tmp,0)
                
                elif suffix == SOURCE:
                    strcutCode = []
                    netMsg = []
                    for sigInfo in sigInfos:
                        assert isinstance(sigInfo,NetSigInfo)
                        strcutCode.append(sigInfo.getStrcutCode())
                        strcutCode.append("\n")
                        netMsg.append(sigInfo.getStrcutCode())
                        netMsg.append("\n")
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,strcutCode,0)
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,netMsg,1)
                wirteFileDicts(filename,lineTexts,False)
        if isTip : printGreen("写入完成")
        return WriteResult.WriteComplete
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
