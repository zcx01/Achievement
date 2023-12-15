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

MSGHEAD = 'struct NetSignal * '
SIGHEAD = 'struct NetSignal Net_'
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
        self.phy_min=0.0
        self.phy_max=0
        self.Unit=0
        self.is_timeout=False
        #-------message--------
        self.Recevier=''
        self.Sender=''
        self.cycle=0
        self.messagaType = 0x0
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
        return SIGHEAD+self.name+' = {'

    def getExtern(self):
        return f'extern {SIGHEAD}{self.name};'

    def getNetName(self):
        return '	&Net_{},'.format(self.name)
    
    def getExternNetMsg(self):
        return f'extern {MSGHEAD}{NetSigInfo.getNetMsgName(self.messagaType)}[];'

    @staticmethod
    def getNetMsgName(messagaType):
        return f'Net_{messagaType}_Msg'
    
    def getVariableNameAndValue(self,variableName,variable,digit=0):
        if type(variable) == int and digit != 0:
            return '.{} = {}.0,'.format(variableName,variable)
        return '.{} = {},'.format(variableName,variable)

    def getVariableNameAndBool(self,variableName,variable):
        return '.{} = {}'.format(variableName,boolToStr(variable))

    def getStrcutCode(self):
        with CBaseBlock(self.getStrcutName(),block_segmenter=('','};')) as block_l0:
            block_l0.add_code_line(self.getVariableNameAndValue("start_by_byte",self.start_by_byte),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("length_bits",self.length_bits),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("length_byte",self.length_byte),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("raw_value",self.raw_value),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("phy_value",self.phy_value,1),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("factor",self.factor,1),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("offset",self.offset,1),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("phy_min",self.phy_min,1),termination='')
            block_l0.add_code_line(self.getVariableNameAndValue("phy_max",self.phy_max,1),termination='')
            block_l0.add_code_line(self.getVariableNameAndBool("is_timeout",self.is_timeout),termination='')
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

    #得到文本名称，包括msg的id，和信号名称
    @staticmethod
    def getTextName(text):
        net = r"Net_.\w+"
        texts = re.findall(net,text,re.A)
        if len(texts) != 0:
            tmpName = EesyStr.removeAll( texts[0],'Net_')
            return tmpName
        return ''
        
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
                    msgStrs = getTextBlock(linelist,MSGHEAD,'};')
                    msgTypes = {}
                    for msgStr,sigNames in msgStrs.items():
                        msgType = re.findall(i_i,msgStr,re.A)[0]
                        for sigName in sigNames:
                            sigName = AnalyzeNetParserFile.getTextName(sigName)
                            msgTypes[sigName] = msgType

                    for text in linelist:
                        rowIndex+=1
                        text=text.strip()
                        if len(text) == 0:
                            continue
                        if text.startswith(SIGHEAD):
                            try:
                                sigInfo = NetSigInfo()
                                sigInfo.name = AnalyzeNetParserFile.getTextName(text)
                                self.netSigs[sigInfo.name] = sigInfo
                                if sigInfo.name in msgTypes:
                                    sigInfo.messagaType = msgTypes[sigInfo.name]
                                    # print(sigInfo.name,sigInfo.messagaType)
                            except:
                                pass
                            continue
                        if text.startswith("};"):
                            sigInfo = None
                        if sigInfo == None:
                            continue
                        variableValue, exist = getVariableText('start_by_byte', text,True)
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
        if sigInfo.messagaType not in useBtye:
            useBtye[sigInfo.messagaType]=[]
        conflictByte=sigInfo.getUseByte(useBtye[sigInfo.messagaType])
        if len(conflictByte) != 0:
            printRed(f'{sigInfo.name} 字节有冲突，冲突的字节为 {conflictByte}')
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
    
    def clearSig(self):
        self.netSigs.clear()

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
            if str(sigInfo.messagaType) == str(msgId):
                sigInfos.append(sigInfo)
        self.removeSigs(sigInfos)

    @staticmethod
    def getNetMsg(netInfos):
        netSignalStr=[]
        for messagaType,sigNetNames in netInfos.items():
            with CBaseBlock(MSGHEAD+NetSigInfo.getNetMsgName(messagaType)+'[] = {',block_segmenter=('','};')) as block_l0:
                for sigNetName in sigNetNames:
                    block_l0.add_code_line(sigNetName,termination='')
            netSignalStr.extend(block_l0.data)
        return netSignalStr
    
    @staticmethod
    def getMsgParserNet():
        netName = 'NetMsg'
        with CBaseBlock('static bool parser_msg_net'+f'(struct NetSignal* {netName}[],int size,int messagaType,char *data, int length) ',block_segmenter=('{','}')) as block_l0:
            block_l0.add_code_line('bool ret = true;',termination='')
            with CBaseBlock('for (int i = 0; i < size; ++i) {', block_segmenter=('','}'), parent=block_l0) as block_l1:
                block_l1.add_code_line(f'int start_by_byte = {netName}[i]->start_by_byte;',termination='')
                block_l1.add_code_line(f'int signal_length_byte = {netName}[i]->length_byte;',termination='')
                block_l1.add_code_line(f'double factor = {netName}[i]->factor;',termination='')
                block_l1.add_code_line(f'double offset = {netName}[i]->offset;',termination='')
                with CBaseBlock('if (signal_length_byte <= 4) {', block_segmenter=('','}'), parent=block_l1) as block_l2:
                    block_l2.add_code_line(f'uint64_t raw_value = convertEndianToInt64(data+NUM_BYTES_HEAD+start_by_byte,signal_length_byte);',termination='')
                    block_l2.add_code_line(f'double phy_value = raw_value*factor + offset;',termination='')
                    block_l2.add_code_line(f'{netName}[i]->raw_value = raw_value;',termination='')
                    block_l2.add_code_line(f'{netName}[i]->phy_value = phy_value;',termination='')
                with CBaseBlock('else{', block_segmenter=('','}'), parent=block_l1) as block_l3:
                    block_l3.add_code_line(f'ret = false;',termination='')
                with CBaseBlock('if(ret){', block_segmenter=('','}'), parent=block_l1) as block_l4:
                    block_l4.add_code_line(f'if (net_updata_fun != NULL)',termination='')
                    block_l4.add_code_line(f'net_updata_fun(messagaType);',termination='')
            block_l0.add_code_line('return ret;',termination='')
        return block_l0.data  

    @staticmethod
    def getParserNet(messagaTypes):
        with CBaseBlock('',block_segmenter=('','')) as block_l0:
            block_l0.add_code_line(f'PACKET_HEADER head;',termination='')
            block_l0.add_code_line(f'memcpy(&head,data,NUM_BYTES_HEAD);',termination='')
            for messagaType in messagaTypes:
                with CBaseBlock(f'if(head.message_type == 0x{messagaType})', block_segmenter=('{','}'), parent=block_l0) as block_l1:
                    block_l1.add_code_line(f'return parser_msg_net({NetSigInfo.getNetMsgName(messagaType)},head.message_type\
,sizeof({NetSigInfo.getNetMsgName(messagaType)})/sizeof(struct NetSignal*),data,length);',termination='')
            block_l0.add_code_line('return false;',termination='')
        return block_l0.data
        
    def writeFile(self,isCheck=True,isTip=True):
        # if isCheck and not self.checkSigBit(): return WriteResult.SignalCoverage
        sigInfos = list(self.netSigs.values())
        sigInfos.sort(key=lambda siginfo: int(siginfo.start_by_byte) | int(siginfo.messagaType) << 16)
        for (dirpath,dirnames,filenames) in os.walk(self.netParserFile):
            for filename in filenames:
                filename=dirpath+filename
                suffix = getSuffix(filename)
                lineTexts = readFileLines(filename)
                lineTexts,isExistence = RemoveBlock(lineTexts,BUILDINGBLOCKSBEGIN,BUILDINGBLOCKEND)
                if not isExistence: continue
                if suffix == HEADFILNE:
                    tmp = []
                    msgTmp = set()
                    for sigInfo in sigInfos:
                        assert isinstance(sigInfo,NetSigInfo)
                        tmp.append(sigInfo.getExtern())
                        msgTmp.add(sigInfo.getExternNetMsg())
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,tmp,0)
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,list(msgTmp),0)
                    
                
                elif suffix == SOURCE:
                    strcutCode = []
                    netMsg = {}
                    for sigInfo in sigInfos:
                        assert isinstance(sigInfo,NetSigInfo)
                        strcutCodes = sigInfo.getStrcutCode()
                        for scode in strcutCodes:
                            strcutCode.append(scode)
                        if sigInfo.messagaType not in netMsg:
                            netMsg[sigInfo.messagaType] = []
                        netMsg[sigInfo.messagaType].append(sigInfo.getNetName())
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,AnalyzeNetParserFile.getMsgParserNet(),0)
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,AnalyzeNetParserFile.getNetMsg(netMsg),0)
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,strcutCode,0)
                    behindStr(lineTexts,BUILDINGBLOCKSBEGIN,AnalyzeNetParserFile.getParserNet(netMsg.keys()),1)
                wirteFileDicts(filename,lineTexts)
        if isTip : printGreen("写入完成")
        return WriteResult.WriteComplete
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------



# a=AnalyzeNetParserFile("/home/chengxiongzhu/Works/Repos/tool_parser/vendor/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessage_Id_BySig("CdcDtc1HiByte"))
# sig=NetSigInfo()
# sig.endBit=104
# sig.length=13
# print(sig.getStartBit())
