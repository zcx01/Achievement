#!/usr/bin/python
from os import linesep, sync
import sys
import xlrd
import argparse

from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import*
from Analyzedbc import *
from projectInI import *

def getValue(src, row, col):
    return src.cell_value(row, col)

def getValueKong(src, row, col):
    value = str(src.cell_value(row, col))
    if value == r"/" or len(value) == 0:
        return "\"\""
    return f'\"{value}\"'


def getValueInt(src, row, col, lenght=-1):
    try:
        value = str(src.cell_value(row, col))
        values = value.split(".")
        isallZero = True

        #防止丢失精度
        if len(values) > 1:
            for c in values[1]:
                if c != '0':
                    isallZero =False
                    break

        if not isallZero or 'e' in value:
            return eConverf(float(value))
        return int(values[0])
    except:
        if(lenght == -1):
            return 0
        return pow(2, lenght)

def getSigInfo(sheel, row):
    sig = SigInfo()
    sig.name = str(getValue(sheel, row, 2))
    sig.Sender = str(getValue(sheel, row, 1)).upper()
    sig.messageId = str(getValue(sheel, row, 4)).split(".")[0]
    sig.cycle = getValueInt(sheel, row, 5)
    if sig.cycle == 0 : #没有周期，就解析为0
        sig.sendType = SigSendType.Event

    sig.endBit = getValueInt(sheel, row, 6)
    sig.length = getValueInt(sheel, row, 7)
    sig.factor = getValueInt(sheel, row, 8)
    if sig.factor == float(0):
        print(f'{sig.name}缩放不能为0，此处修改成1')
        sig.factor = 1
    sig.Offset = getValueInt(sheel, row, 9)
    sig.min = getValueInt(sheel, row, 10)
    sig.max = getValueInt(sheel, row, 11, sig.length)
    if getValue(sheel, row, 12) == "Signed":
        sig.dataType = "-"
    sig.Unit = getValueKong(sheel, row, 13)
    sig.enum = str(getValue(sheel, row, 14))
    try:
        if str(getValue(sheel, row, 15)) != 'nan':
            sig.initValue = int(getValue(sheel, row, 15), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, 17)
    sig.Recevier = getValue(sheel, row, 20)
    sig.getStartBit()
    return sig

def getMessageInfo(sheel):
    msgs={}
    assert isinstance(sheel, Sheet)
    for row in range(sheel.nrows):
        try:
            msg=MessageInfo()
            msg.subNet = sheel.cell_value(row,0)
            msg.sender = sheel.cell_value(row,1)
            sendingMode = str(sheel.cell(row,2))
            msg.messageId =  getNoOx16(str(sheel.cell_value(row,4)))
            if 'event' in sendingMode.lower():
                msg.sendType = 8
            msg.cycle =  getValueInt(sheel,row,3)
            if msg.cycle == 0:
                cycleContent =  str(getValue(sheel, row, 3))
                cycleContents = re.findall(e_i,cycleContent,re.A)
                if len(cycleContents) >= 2 :
                    try:
                        msg.cycle = int(cycleContents[0])
                        msg.threeCycle =  int(cycleContents[1])
                    except:
                        pass
            msg.lenght = getValueInt(sheel,row,5)
            msg.Recevier = str(sheel.cell_value(row,6))
            frame = str(sheel.cell_value(row,9))
            if len(frame) ==0 or len(splitSpace(frame)) == 0 or not isNumber(frame):
                frame = SubNet_Frame.get(msg.subNet,0)
            else:
                frame = VFrameFormat.get(frame,0)
            msg.frame = frame
            if msg.messageId not in msgs:
                msgs[msg.messageId] = msg
            else:
                # print(f'{row} {msg.messageId} 已经存在')
                pass
        except:
            if len(msgs) !=0:
                print(f'{row} 是值不合法的')
            pass
    return msgs

def getThreeFrame(jsConfig):
    srcSendType = getKeyPath("srcSendType", jsConfig)
    threeFrames=[]
    if not os.path.isfile(srcSendType):
        print("不存在 srcSendType 文件 " + srcSendType)
        return threeFrames
    typeContents = readFileLines(srcSendType)
    for typeContent in typeContents:
        typeContent = typeContent.strip()
        if typeContent.startswith('.start_bit'):
            try:
                contents = re.findall(e_i,typeContent,re.A)
                threeFrames.append(contents[2])
            except:
                pass
    return threeFrames

def conversion(configPath, wirteSigName, canmatrix=""):
    print(configPath)
    jsConfig = getJScontent(configPath)
    isAllAdd = True
    if len(canmatrix) == 0:
        canmatrix = getKeyPath("canmatrix", jsConfig)
        isAllAdd = False
    print(canmatrix)

    dbcfile = getKeyPath("dbcfile", jsConfig)
    book = xlrd.open_workbook(canmatrix)
    assert isinstance(book,Book)

    sheel = book.sheet_by_name(Sig_Matrix)
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel,Sheet)
    isFind = False

    msgs = getMessageInfo(messageSheel)
    assert isinstance(msgs,dict)

    threeFrames = getThreeFrame(jsConfig)
    for row in range(sheel.nrows):
        sigName = str(getValue(sheel, row, 2))
        if isAllAdd and row == 0:
            continue
        if sigName.strip() == wirteSigName or isAllAdd:
            sig = getSigInfo(sheel, row)
            if sig.name in threeFrames:
                sig.sendType = SigSendType.Three
            # if sig.initValue < sig.min or sig.initValue > sig.max or sig.min == sig.max:
            #     print(f'{sig.name} 写入失败 最大值最小值或者初始值不合理,初始值为{sig.initValue},最小值为{sig.min},最大值为{sig.max}')
            #     return
            # initPy = sig.initValue * sig.factor + sig.Offset
            # if initPy < sig.min or initPy > sig.max:
            #     print(f'{sig.name} 缩放偏移或者初始值物理值不合理,初始值物理值为{sig.initValue},最小值为{sig.min},最大值为{sig.max},缩放为{sig.factor},偏移为{sig.Offset}')
            #     print('是否继续写入(y/n)')
            #     if input() != 'y':
            #         return
            isFind = True
            dbc = Analyze(dbcfile)
            msg = msgs.get(sig.messageId,None)
            if msg == None:
                print(f' {sig.name} 对应的 {sig.messageId} message不存在')
                continue
            dbc.writeSig(sig,msg)
            can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
            if os.path.isfile(can_parse_whitelistPath):
                os.system(f"topic_Parser -w {can_parse_whitelistPath} {sig.getMessage_Id()} {sig.getMessage_Sig()}")
    if not isFind:
        print(f"{wirteSigName} 在CAN矩阵中不存在")

def addHeadEnd(text,name):
    text.insert(0, f'{name}')
    text.append("") 
    return text


def getUseMessage_Sig(jsConfig):
    can_parse_whitelistPath_sig = []
    can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
    can_parse_whitelistPath_contents = readFileLines(can_parse_whitelistPath)
    for text in can_parse_whitelistPath_contents:
        texts = text.split(" ")
        can_parse_whitelistPath_sig.append(texts[0])
    return can_parse_whitelistPath_sig

def filterNoUser(no_use,sig_results,use_sig):
    sig_results_cpoy=[]
    for sig_result in sig_results:
        try:
            message_sig = re.findall(e_i, sig_result, re.A)[0]
            if message_sig == use_sig:
                sig_results_cpoy.append(sig_result)
            else:
                no_use.append(sig_result)
        except:
            sig_results_cpoy.append(sig_result)
    return sig_results_cpoy

def diffCanMatrix(fristMatrix, twoMatrix, configPath, resultPath ,isfilterNoUser):
    jsConfig = getJScontent(configPath)
    if len(fristMatrix) == 0:
        fristMatrix = getKeyPath("canmatrix", jsConfig)
    book1 = xlrd.open_workbook(fristMatrix)
    sheel1 = book1.sheet_by_name(Sig_Matrix)
    book2 = xlrd.open_workbook(twoMatrix)
    sheel2 = book2.sheet_by_name(Sig_Matrix)
    sigInfos = []
    for row in range(sheel1.nrows):
        if row == 0:
            continue
        info =getSigInfo(sheel1, row)
        # info.name = info.name+" "+info.messageId
        sigInfos.append(info)

    results = [] 
    noExit = []
    noExitSigName = []
    for row in range(sheel2.nrows):
        if row == 0:
            continue
        info = getSigInfo(sheel2, row)
        # info.name = info.name+" "+info.messageId
        index = 0
        isSame = CompareResult.No
        for compareSig in sigInfos:
            assert isinstance(compareSig,SigInfo)
            isSame, result = compareSig.compare(info)
            if isSame != CompareResult.No:
                if len(result) !=0:
                    result = addHeadEnd(result,info.getMessage_Sig())
                    results.append('\n'.join(result))
                del sigInfos[index]
                break
            index += 1
        if isSame == CompareResult.No:
            noExit.append(info.getMessage_Sig())
            noExitSigName.append(info.name)
    
    deleteSig=[]
    messageDifSig=[]

    for info in sigInfos:
        assert isinstance(info,SigInfo)
        messageSigStr=''
        while info.name in noExitSigName:
            sigIndex = noExitSigName.index(info.name)
            messageSigStr= messageSigStr +' '+ noExit[sigIndex]
            del noExitSigName[sigIndex]
            del noExit[sigIndex]

        if len(messageSigStr) !=0:
            messageSigStr = messageSigStr + f' 原来 {info.messageId}'
            messageSigStr=messageSigStr.replace(info.getMessage_Sig(),'')
            messageSigStr = info.getMessage_Sig() + messageSigStr
            messageDifSig.append(messageSigStr)
        else:
            deleteSig.append(info.getMessage_Sig())

    no_use=[]
    #过滤掉没有使用信号
    if isfilterNoUser:
        no_use.insert(0,'--------------目前还没有使用的信号--------------')
        use_sig = getUseMessage_Sig(jsConfig)
        results = filterNoUser(no_use,results,use_sig)
        messageDifSig = filterNoUser(no_use,messageDifSig,use_sig)
        noExit = filterNoUser(no_use,noExit,use_sig)
        deleteSig = filterNoUser(no_use,deleteSig,use_sig)


    statistics=[]
    statistics.append('--------------统计--------------')
    statistics.append(f'存在差异的信号有{len(results)}个')
    statistics.append(f'message不同的信号{len(messageDifSig)}个')
    statistics.append(f'在原来的矩阵是不存在的有{len(noExit)}个')
    statistics.append(f'删除信号{len(deleteSig)}个')
    statistics.append("具体如下:")
    statistics.append(" ")

    messageDifSig.insert(0,'---------------不同message的信号----------------')
    deleteSig.insert(0,'---------------删除的信号----------------')
    noExit.insert(0,'--------------不在存在的信号--------------')

    if len(resultPath) != 0:
        print(f"写入{resultPath}文件...")
        wirteFileDicts(resultPath, statistics+results+messageDifSig+noExit+deleteSig+no_use, False)

    print("比较完成!")


def sigNameChanged(configPath,dbcPath,resultPath):
    jsConfig = getJScontent(configPath)
    dbc = Analyze(dbcPath)
    newdbc =Analyze(getKeyPath("dbcfile", jsConfig))
    nameChanged=[]
    resetName=[]
    for sigName in dbc.dbcSigs:
        sig = dbc.dbcSigs[sigName]
        assert isinstance(sig,SigInfo)
        if sigName in newdbc.dbcSigs:
            newsig = newdbc.dbcSigs[sigName]
            assert isinstance(newsig,SigInfo)
            if sig.getMessage_Sig() != newsig.getMessage_Sig():
                nameChanged.append(f'{sig.getMessage_Sig()} : {newsig.getMessage_Sig()}')
        else:
            print(f'{sigName} 被删除或者被重命名')
            resetName.append(sigName)
    if len(resultPath) != 0:
        print(f"写入{resultPath}文件...")
        wirteFileDicts(resultPath,nameChanged+resetName,False)
    
def CopyEnum(configPath,dbcPath):
    jsConfig = getJScontent(configPath)
    dbc = Analyze(dbcPath)
    newdbc = Analyze(getKeyPath("dbcfile", jsConfig))
    for sigName in newdbc.dbcSigs:
        newsig = newdbc.dbcSigs[sigName]
        assert isinstance(newsig, SigInfo)
        if sigName in dbc.dbcSigs:
            sig = dbc.dbcSigs[sigName]
            assert isinstance(sig, SigInfo)
            newsig.enum = sig.enum

    newdbc.repalceSig(newdbc.dbcSigs.values())


def modifyMessageInfo(configPath):
    jsConfig = getJScontent(configPath)
    matrixFilePath = getKeyPath("canmatrix", jsConfig)
    book = xlrd.open_workbook(matrixFilePath)
    assert isinstance(book,Book)
    print(book.sheet_names())
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel,Sheet)
    dbc = Analyze(getKeyPath("dbcfile", jsConfig))
    msgs = getMessageInfo(messageSheel)
    for messageId in dbc.dbcMessage:
        try:
            dbcMsg = dbc.dbcMessage[messageId]
            assert isinstance(dbcMsg,MessageInfo)
            dbcMsg.CopyXls(msgs[messageId])
        except:
            print(f'{dbc.dbcMessage[messageId].messageId} 在CAN矩阵没有找到')

    dbc.repalceMessage(dbc.dbcMessage.values())
    
# conversion(pyFileDir+"config.json","","/home/chengxiongzhu/Works/文档/C样/C385-EVE项目整车通讯协议_V2.2.0_20211203.xlsx")
# conversion(pyFileDir+"config.json",'HU_CurrentLocationLongitude')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='这个脚本是用来通过生成dbc,比较CAN矩阵')

    parse.add_argument('-c', '--config', help='配置文件路径',
                       default=pyFileDir+"config.json")
    parse.add_argument('-a', '--append', help='新增整个can矩阵表格')
    parse.add_argument('-s', '--sigNames', help='信号名称，是一个列表',
                       default=[], nargs='+', type=str)
    parse.add_argument('-f', '--fristMatrix',
                       help='比较dbc矩阵,比较的文件,没有指定就使用配置文件中的路径', default="")
    parse.add_argument('-t', '--twoMatrix', help='比较dbc矩阵,被比较的文件')
    parse.add_argument('-r', '--resultPath', help='比较dbc矩阵结果路径', default='')
    parse.add_argument('-m', '--modifyMessageInfo', help='替换message信息,有m就会替换', default=1,type=int,nargs='*')
    parse.add_argument('-d', '--dbcPath', help='比较新旧两个dbc,输入的是被比较的')
    parse.add_argument('-u', '--isfilterNoUser', help='是否过滤掉没有使用过的信号',nargs='*')
    arg = parse.parse_args()

    if "-a" in sys.argv:
        conversion(arg.config, "", arg.append)
    elif '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config, sigName)
    elif '-m' in sys.argv:
        modifyMessageInfo(arg.config)
    elif '-t' in sys.argv:
        diffCanMatrix(arg.fristMatrix, arg.twoMatrix,arg.config, arg.resultPath,'-u' in sys.argv)
    elif '-d' in sys.argv and '-r' in sys.argv:
        sigNameChanged(arg.config,arg.dbcPath,arg.resultPath)
    elif '-d' in sys.argv:
        CopyEnum(arg.config,arg.dbcPath)
