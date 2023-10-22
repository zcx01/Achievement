#!/usr/bin/python
import os
import sys

import xlrd
import argparse

from xlrd.book import Book
from xlrd.sheet import Sheet
from analyze_dbc.commonfun import*
from analyze_dbc.analyze_dbc import *
from analyze_dbc.projectInI import *

def getValue(src, row, col):
    return src.cell_value(row,XlsCharToInt(col))

def getValueInt(src, row, col, lenght=-1):
    try:
        value = str(getValue(src,row,col))
        value = value.replace('ms','')
        values = value.split(".")
        isallZero = True

        #防止丢失精度
        if len(values) > 1:
            for c in values[1]:
                if c != '0':
                    isallZero = False
                    break

        if not isallZero or 'e' in value.lower():
            return eConverf(float(value))
        return int(values[0])
    except:
        if(lenght == -1):
            return 0
        return pow(2, lenght)-1

def getSigInfo(sheel, row):
    sig = SigInfo()
    sig.subNet = str(getValue(sheel, row, sig_line_subNet)).upper()
    sig.Sender = str(getValue(sheel, row, sig_line_Sender)).upper()
    temp = str(getValue(sheel, row, sig_line_name))
    temps = re.findall(e_i, temp, re.A)
    if "_" in temp:
         sig.name = "".join(temps)
    else:
        sig.name = "_".join(temps)
    sig.chineseName = str(getValue(sheel, row, sig_line_chineseName))
    sig.messageId = str(getValue(sheel, row, sig_line_messageId)).split(".")[0].replace('0x', '')
    sig.cycle = getValueInt(sheel, row, sig_line_cycle)
    if sig.cycle == 0:  # 没有周期，就解析为0
        sig.sendType = SigSendType.Event

    posBit = getStartBit(sheel, row, getValueInt)
    if MSB == True:
        sig.startBit = posBit
    else:
        sig.endBit = posBit
    sig.length = getValueInt(sheel, row, sig_line_length)
    sig.factor = getValueInt(sheel, row, sig_line_factor)
    if sig.factor == float(0) and len(sig.name) != 0:
        printYellow(f'{sig.name} 缩放不能为0，此处修改成1,行号为{row}')
        sig.factor = 1
    sig.Offset = getValueInt(sheel, row, sig_line_Offset)
    sig.min = getValueInt(sheel, row, sig_line_min)
    sig.max = getValueInt(sheel, row, sig_line_max, sig.length)
    if getValue(sheel, row, sig_line_dataType) == "Signed":
        sig.dataType = "-"
    sig.SetUnit(str(getValue(sheel, row, sig_line_unit)))
    if ISUSEDBCENUM: sig.enum = str(getValue(sheel, row, sig_line_enum))
    try:
        if str(getValue(sheel, row, 15)) != 'nan':
            sig.initValue = int(getValue(sheel, row, sig_line_initValue), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, sig_line_invalidValue)
    sig.Recevier = getValue(sheel, row, sig_line_Recevier)
    sig.RecevierRemoveSend()
    if sig.endBit != -1:
        sig.getStartBit()
    else:
        sig.getEndBit()
    return sig

def getMessageInfo(sheel):
    msgs = {}
    assert isinstance(sheel, Sheet)
    for row in range(sheel.nrows):
        try:
            msg = MessageInfo()
            msg.subNet = str(getValue(sheel, row, msg_line_subNet)).upper()
            msg.sender = str(getValue(sheel, row, msg_line_sender)).upper()
            sendingMode = str(getValue(sheel, row, msg_line_sendingMode))
            msg.messageId = getNoOx16(str(getValue(sheel,row, msg_line_messageId)))
            if 'event' in sendingMode.lower():
                msg.sendType = 8
            msg.cycle = getValueInt(sheel, row, msg_line_cycle)
            if msg.cycle == 0:
                cycleContent = str(getValue(sheel, row, msg_line_cycle))
                cycleContents = re.findall(e_i, cycleContent, re.A)
                if len(cycleContents) >= 2:
                    try:
                        msg.cycle = int(cycleContents[0])
                        msg.threeCycle = int(cycleContents[1])
                    except:
                        pass
            msg.lenght = getValueInt(sheel, row, msg_line_lenght)
            msg.Recevier = str(getValue(sheel,row, msg_line_Recevier))
            frame = str(getValue(sheel,row, msg_line_frame))
            try:
                if len(frame) == 0 or len(splitSpace(frame)) == 0:
                    frame = SubNet_Frame.get(msg.subNet, 0)
                else:
                    frame = VFrameFormat.get(frame, int(float(frame)) if isNumber(frame) else SubNet_Frame.get(msg.subNet, 0))
            except:
                frame = SubNet_Frame.get(msg.subNet, 0)

            msg.frame = frame
            if msg.messageId not in msgs:
                msgs[msg.getMessage_SubNet()] = msg
            else:
                # print(f'{row} {msg.messageId} 已经存在')
                pass
        except:
            if len(msgs) != 0:
                print(f'{row} 是值不合法的')
            pass
    return msgs

def getThreeFrame(jsConfig):
    srcSendType = getKeyPath("srcSendType", jsConfig)
    threeFrames = []
    if not os.path.isfile(srcSendType):
        print("不存在 srcSendType 文件 " + srcSendType)
        return threeFrames
    typeContents = readFileLines(srcSendType)
    for typeContent in typeContents:
        typeContent = typeContent.strip()
        if typeContent.startswith('.start_bit'):
            try:
                contents = re.findall(e_i, typeContent, re.A)
                threeFrames.append(contents[2])
            except:
                pass
    return threeFrames

def appoint(sig,wirteSigName, isMsg): #是否是指定添加的信号
    assert isinstance(sig,SigInfo)
    if not isMsg:
        return sig.name.upper() == wirteSigName.upper() or sig.messageId+sig.name.upper() == wirteSigName.upper()
    else:
        return sig.messageId.upper() == wirteSigName.upper()

def appoints(sig,wirteSigNames, isMsg): #是否是指定添加的信号
    assert isinstance(sig,SigInfo)    
    isFind = False
    if not isMsg:
        for wirteSigName in wirteSigNames:
            if sig.name.upper() == wirteSigName.upper() or sig.messageId+sig.name.upper() == wirteSigName.upper():
                isFind = True
                break
    else:
        for wirteSigName in wirteSigNames:
            if sig.messageId.upper() == wirteSigName.upper() or sig.getMessage_Name().upper() == wirteSigName.upper():
                isFind = True
                break
    return isFind

def conversion(configPath, wirteSigName, canmatrix="",isMsg = False):
    jsConfig = getJScontent(configPath)
    isAllAdd = (len(wirteSigName) == 0)
    if len(canmatrix) == 0:
        canmatrix = getKeyPath("canmatrix", jsConfig)
        isAllAdd = False
    print(canmatrix)

    dbcfile = getKeyPath("dbcfile", jsConfig)
    print(dbcfile)
    book = xlrd.open_workbook(canmatrix)
    assert isinstance(book, Book)

    sheel = book.sheet_by_name(Sig_Matrix)
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel, Sheet)
    isFind = False

    msgs = getMessageInfo(messageSheel)
    assert isinstance(msgs, dict)
    if len(msgs) == 0:
        printRed("messaage 不存在或者解析错误")
        return

    threeFrames = getThreeFrame(jsConfig)
    for row in range(sheel.nrows):
        # xf = book.xf_list[getValue(sheel, row, 2).xf_index]
        # print(type(xf))

        if row == 0:
            continue
        sig = getSigInfo(sheel, row)
        if appoint(sig,wirteSigName,isMsg) or isAllAdd:
            if not isWriteSig(sheel,row,getValue):
                print(f"{row} 项目中没有这个信号，无须导入")
                continue
            if sig.name in threeFrames:
                sig.sendType = SigSendType.Three
            # print(type(sig.min),type(sig.max),type(sig.Offset),type(sig.factor))
            realMin = (float(sig.min)-float(sig.Offset)) / float(sig.factor)
            realMax = (float(sig.max)-float(sig.Offset)) / float(sig.factor)
            if realMin < 0 and sig.dataType == "+":
                printRed(f'{sig.name} 极小值小于0,最小值为{sig.min},raw值{realMin}')
                continue
            if realMax > pow(2, sig.length)-1 and sig.max != pow(2, sig.length)-1:
                printYellow(f'{sig.name} 极大值大于长度,最大值为{sig.max},raw值{realMax}，极限值为{pow(2, sig.length)-1} 修改中...')
                sig.max = pow(2, sig.length)-1
            # if sig.min == sig.max:
            #     printRed(f"{sig.name} 最大值和最小值相等最小值为{sig.min},最大值为{sig.max}")
            #     continue

            isFind = True
            dbc = Analyze(dbcfile)
            msg = msgs.get(sig.getMessage_SubNet(), None)
            if msg == None:
                printYellow(f'{row} {sig.name} 对应的 {sig.messageId} message不存在')
                print("可能的原因是:message没有加0x")
                continue
            
            isWriteWhite = False
            writedbcresult = dbc.writeSig(sig, msg)
            if writedbcresult == WriteDBCResult.AlreadyExists:
                if isAllAdd:
                    # printYellow(f'{sig.getMessage_Sig()} 被替换')
                    dbc.repalceSig(sig)
                    isWriteWhite = True
                else:
                    isRepalce = input(f'{sig.getMessage_Sig()} 是否替換 y/n ')
                    if 'y' in isRepalce:
                        dbc.repalceSig(sig)
                        isWriteWhite = True
            if writedbcresult == WriteDBCResult.WriteComplete:
                isWriteWhite = True
            if isWriteWhite and (WRITEWHITE or not isAllAdd):
                can_parse_whitelistPath = getKeyPath(
                    "can_parse_whitelist", jsConfig)
                if os.path.isfile(can_parse_whitelistPath):
                    WriteCan_parse_whitelist(can_parse_whitelistPath,sig.getMessage_Name(),sig.getMessage_Sig(),False)
    if not isFind:
        printRed(f"{wirteSigName} 在CAN矩阵中不存在")

def WriteWhitelistPath(messages=[]):
    jsConfig=getJScontent(pyFileDir+"config.json")
    dbcPath = getKeyPath("dbcfile",jsConfig)
    can_parse_whitelistPath = getKeyPath("can_parse_whitelist",jsConfig)
    dbc = Analyze(dbcPath)
    for sig_dbc in dbc.AnalyzeDictlist:
        assert isinstance(sig_dbc,AnalyzeFile)
        for messageSig in sig_dbc.dbcSigs:
            sig = sig_dbc.getSig(messageSig)
            if appoints(sig,messages,True) or len(messages) == 0:
                WriteCan_parse_whitelist(can_parse_whitelistPath,sig.getMessage_Name(),sig.getMessage_Sig(),False)
    printGreen("写入完成")

def conversionByOtherdbc(configPath, wirteSigNames, dbcfilPath=""):
    assert isinstance(wirteSigNames, list)
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    ori_dbc = AnalyzeFile(dbcfilPath)
    for messageSig in ori_dbc.dbcSigs:
        ori_sig = ori_dbc.getSig(messageSig)
        if ori_sig.name in wirteSigNames:
            msg = ori_dbc.dbcMessage.get(ori_sig.messageId, None)
            if msg == None:
                print(f' {ori_sig.name} 对应的 {ori_sig.messageId} message不存在')
                continue
            dbc = Analyze(dbcfile)
            dbc.writeSig(ori_sig, msg)
            wirteSigNames.pop(wirteSigNames.index(ori_sig.name))

    if len(wirteSigNames):
        print('没有找到的信号-------', wirteSigNames)

def conversionMsgByOtherdbc(configPath,msgIds,dbcfilPaths):
    assert isinstance(msgIds,list)
    jsConfig = getJScontent(configPath)
    ori_dbc = Analyze(getKeyPath("dbcfile", jsConfig))
    modifyMgs={}

    dbc = Analyze(dbcfilPaths)
    dbcMsgInfos = dbc.getAllMessage()
    isReurn = False
    for dbcMsgInfo in dbcMsgInfos:
        if  dbcMsgInfo not in File_SubNet:
            printYellow(f"请在 File_SubNet 变量配置 {dbcMsgInfo} 对应的 SubNet")
            isReurn = True
    if isReurn: return
    for dbcMsgInfo in dbcMsgInfos:
        for dbcMsgId in dbcMsgInfos[dbcMsgInfo]:
            if msgIds == None or len(msgIds) == 0 or dbcMsgId in msgIds:
                msgInfo =dbcMsgInfos[dbcMsgInfo][dbcMsgId]
                assert isinstance(msgInfo,MessageInfo)
                msgInfo.subNet = File_SubNet[dbcMsgInfo]
                modifyMgs[msgInfo.getMessage_SubNet()] = msgInfo

    for msgInfo in list(modifyMgs.values()):
        if msgInfo.messageId == '337':
            print(msgInfo.getMessage_SubNet())
    ori_dbc.repalceMessage(list(modifyMgs.values()))

def RemoveSigs(configPath, sigNames):
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)
    dbc.removeSig(sigNames)

def RemoveMsgs(configPath, msgs,channal):
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)
    dbc.removeMessage(channal,msgs)

def addHeadEnd(text, name):
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

def filterNoUser(no_use, sig_results, use_sig):
    sig_results_cpoy = []
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

def diffCanMatrix(fristMatrix, twoMatrix, configPath, resultPath, isfilterNoUser):
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
        info = getSigInfo(sheel1, row)
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
            assert isinstance(compareSig, SigInfo)
            isSame, result = compareSig.compare(info)
            if isSame != CompareResult.No:
                if len(result) != 0:
                    result = addHeadEnd(result, info.getMessage_Sig())
                    results.append('\n'.join(result))
                del sigInfos[index]
                break
            index += 1
        if isSame == CompareResult.No:
            noExit.append(info.getMessage_Sig())
            noExitSigName.append(info.name)

    deleteSig = []
    messageDifSig = []

    for info in sigInfos:
        assert isinstance(info, SigInfo)
        messageSigStr = ''
        while info.name in noExitSigName:
            sigIndex = noExitSigName.index(info.name)
            messageSigStr = messageSigStr + ' ' + noExit[sigIndex]
            del noExitSigName[sigIndex]
            del noExit[sigIndex]

        if len(messageSigStr) != 0:
            messageSigStr = messageSigStr + f' 原来 {info.messageId}'
            messageSigStr = messageSigStr.replace(info.getMessage_Sig(), '')
            messageSigStr = info.getMessage_Sig() + messageSigStr
            messageDifSig.append(messageSigStr)
        else:
            deleteSig.append(info.getMessage_Sig())

    no_use = []
    #过滤掉没有使用信号
    if isfilterNoUser:
        no_use.insert(0, '--------------目前还没有使用的信号--------------')
        use_sig = getUseMessage_Sig(jsConfig)
        results = filterNoUser(no_use, results, use_sig)
        messageDifSig = filterNoUser(no_use, messageDifSig, use_sig)
        noExit = filterNoUser(no_use, noExit, use_sig)
        deleteSig = filterNoUser(no_use, deleteSig, use_sig)

    statistics = []
    statistics.append('--------------统计--------------')
    statistics.append(f'存在差异的信号有{len(results)}个')
    statistics.append(f'message不同的信号{len(messageDifSig)}个')
    statistics.append(f'在原来的矩阵是不存在的有{len(noExit)}个')
    statistics.append(f'删除信号{len(deleteSig)}个')
    statistics.append("具体如下:")
    statistics.append(" ")

    messageDifSig.insert(0, '---------------不同message的信号----------------')
    deleteSig.insert(0, '---------------删除的信号----------------')
    noExit.insert(0, '--------------不在存在的信号--------------')

    if len(resultPath) != 0:
        print(f"写入{resultPath}文件...")
        wirteFileDicts(resultPath, statistics+results +
                       messageDifSig+noExit+deleteSig+no_use, False)

    print("比较完成!")

def getNameChangedDict(nameChangeds):
    sigNameDict = {}
    for sigName in nameChangeds:
        sigNames = re.findall(e_i, sigName, re.A)
        if len(sigNames) > 1:
            old_SigName = sigNames[0]
            new_SigName = sigNames[1]
            sigNameDict[old_SigName] = new_SigName
    return sigNameDict

def repalceSrcSig(nameChangeds, jsConfig):
    srcPath = getKeyPath("srcPath", jsConfig)
    sigNameDict = getNameChangedDict(nameChangeds)

    for (dirpath, dirnames, filenames) in os.walk(srcPath):
        for fileName in filenames:
            suffix = os.path.splitext(fileName)[1]
            if suffix == '.cpp' or suffix == '.hpp' or suffix == '.h':
                filePath = dirpath+'/'+fileName
                content = readFileAll(filePath)
                sigNames = re.findall(s_i_e, content, re.A)
                sigNames = list(set(sigNames))
                isWrite = False
                for sigName in sigNames:
                    assert isinstance(sigName, str)
                    sigNameSplists = re.findall(m_s, sigName, re.A)
                    mix_sig_lenght = 3
                    if len(sigNameSplists) > mix_sig_lenght:
                        mix_sig_lenght += 1
                        message_Sig = f'{sigNameSplists[1]}_{sigNameSplists[2]}__{sigNameSplists[3]}'
                        # 现在无法处理信号中有'__'的信号
                        while len(sigNameSplists) > mix_sig_lenght and message_Sig not in sigNameDict:
                            message_Sig = message_Sig+'_'+sigNameSplists[4]
                            mix_sig_lenght += 1
                        if message_Sig in sigNameDict:
                            if not isWrite:
                                print(f'正在替换 {filePath} 文件中的信号')
                            print(
                                f"{message_Sig} ---------> {sigNameDict[message_Sig]}")
                            content = content.replace(
                                message_Sig, sigNameDict[message_Sig])
                            isWrite = True
                if isWrite:
                    writeFileAll(filePath, content)

    print('-------修改白名单中的信号-----------')
    can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
    can_parse_whitelistPath_contents = readFileLines(can_parse_whitelistPath)
    for textIndex in range(len(can_parse_whitelistPath_contents)):
        text = can_parse_whitelistPath_contents[textIndex]
        texts = text.split(" ")
        message_Sig = texts[0]
        if message_Sig in sigNameDict:
            can_parse_whitelistPath_contents[textIndex] = text.replace(
                message_Sig, sigNameDict[message_Sig])
    wirteFileDicts(can_parse_whitelistPath,
                   can_parse_whitelistPath_contents, False)
'''
configPath : 配置文件的路径
dbcPath : 原来的dbc目录        
resultPath : 比较的结果的路径 （output）
canMatrix : 原来的CAN矩阵用路径，通过中文来替换
'''
def sigNameChanged(configPath, dbcPath, resultPath, canMatrix):
    jsConfig = getJScontent(configPath)
    dbc = Analyze(dbcPath)
    newdbc = Analyze(getKeyPath("dbcfile", jsConfig))
    nameChanged = []
    resetName = []
    isSame = CompareResult.No
    for messageSigName in dbc.dbcSigs:
        sig = dbc.dbcSigs[messageSigName]
        assert isinstance(sig, SigInfo)

        if not newdbc.sigExist(messageSigName):
            newSig = newdbc.getSig(sig.name)
            if newSig != None:
                assert isinstance(newSig, SigInfo)
                if sig.getMessage_Sig() != newSig.getMessage_Sig():
                    print(newSig.name, '-----------')
                    nameChanged.append(
                        f'{sig.getMessage_Sig()} : {newSig.getMessage_Sig()}')
            else:
                for newMessageSigName in newdbc.dbcSigs:
                    newSig = newdbc.dbcSigs[newMessageSigName]
                    assert isinstance(newSig, SigInfo)
                    isSame, result = sig.compare(newSig)
                    if isSame == CompareResult.Bit:
                        print(newSig.name, '+++++++++++++++++')
                        nameChanged.append(
                            f'{sig.getMessage_Sig()} : {newSig.getMessage_Sig()}')
                        break
                if isSame == CompareResult.No:
                    resetName.append(sig.getMessage_Sig())

    #根据中文备注替换
    if os.path.isfile(canMatrix):
        fristMatrix = getKeyPath("canmatrix", jsConfig)
        book1 = xlrd.open_workbook(fristMatrix)
        sheel1 = book1.sheet_by_name(Sig_Matrix)
        book2 = xlrd.open_workbook(canMatrix)
        sheel2 = book2.sheet_by_name(Sig_Matrix)
        sigInfos = {}
        for row in range(sheel1.nrows):
            if row == 0:
                continue
            info = getSigInfo(sheel1, row)
            sigInfos[info.chineseName] = info
            print(info.getMessage_Sig(), info.chineseName)

        for row in range(sheel2.nrows):
            if row == 0:
                continue
            info = getSigInfo(sheel2, row)
            if info.chineseName in sigInfos and info.getMessage_Sig() in resetName:
                nameChanged.append(
                    f'{info.getMessage_Sig()} : {sigInfos[info.chineseName].getMessage_Sig()}')
                resetName.pop(resetName.index(info.getMessage_Sig()))
    #替换代码相关的
    repalceSrcSig(nameChanged, jsConfig)
    resetName.insert(0, '--------删除或者被重命名 --------')
    if len(resultPath) != 0:
        print(f"写入{resultPath}文件...")
        wirteFileDicts(resultPath, nameChanged+resetName, False)
        printGreen(f"分析完成")

def CopyEnum(configPath, dbcPath, resultPath):
    print('赋值枚举...')
    jsConfig = getJScontent(configPath)
    dbc = Analyze(dbcPath)
    newdbc = Analyze(getKeyPath("dbcfile", jsConfig))
    sigEnums = []
    sigNameDict = {}
    if len(resultPath) != 0:
        nameChangeds = readFileLines(resultPath)
        sigNameDict = getNameChangedDict(nameChangeds)
        sigNameDict = dict(zip(sigNameDict.values(), sigNameDict.keys()))

    for messageSigName in newdbc.dbcSigs:
        newsig = newdbc.dbcSigs[messageSigName]
        assert isinstance(newsig, SigInfo)
        sig = dbc.getSig(newsig.name)
        if sig == None and newsig.getMessage_Sig() in sigNameDict:
            message_Sig = sigNameDict[newsig.getMessage_Sig()]
            sig = dbc.getSig(message_Sig)
        if sig != None:
            assert isinstance(sig, SigInfo)
            newsig.isdbcEnum = sig.isdbcEnum
            newsig.enum = sig.enum
            sigEnums.append(newsig)
    newdbc.repalceSigEnum(sigEnums)

def modifyMessageInfo(configPath,modifyMessages,canmatrix):

    jsConfig = getJScontent(configPath)
    if canmatrix == '' :
        matrixFilePath = getKeyPath("canmatrix", jsConfig)
    else:
        matrixFilePath = canmatrix
    book = xlrd.open_workbook(matrixFilePath)
    assert isinstance(book, Book)
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel, Sheet)
    dbc = Analyze(getKeyPath("dbcfile", jsConfig))
    msgs = getMessageInfo(messageSheel)
    modifyMgs=[]

    for modifyMessage in modifyMessages:
        if modifyMessage in msgs:
            modifyMgs.append(msgs[modifyMessage])
            
    dbc.repalceMessage(modifyMgs)

def findsignalInfile(signal,filePath):
    try:
        f=open(filePath,'r')
        content=f.readlines()
        for text in content:
            texts = text.split(" ")
            try:
                if signal == texts[0]:
                    return True
            except:
                pass
        return False
    except:
        return False

def WriteCan_parse_whitelist(can_parse_whitelistPath,message,messagesig,can_parse_whitelist_return):
    if os.path.isfile(can_parse_whitelistPath):  
        if  findsignalInfile(f'{messagesig}',can_parse_whitelistPath):
            if can_parse_whitelist_return:
                print(f'{can_parse_whitelistPath} 文件存在，跳过')
                return 0
        else:
            # print(f"写入 {can_parse_whitelistPath} 文件")
            can_parse_whitelist_read=open(can_parse_whitelistPath,"r")
            can_parse_whitelist_content_line=readFileLines(can_parse_whitelistPath)

            #写在现有的message后面
            behindStr(can_parse_whitelist_content_line,'message',f'{message:<18}[message]		[all]')

            if not can_parse_whitelist_read.read().endswith('\n'):
                can_parse_whitelist_content_line.append('\n')
            can_parse_whitelist_read.close()
            
            can_parse_whitelist_content_line.append(f'{messagesig:<30}       [signal]		[set, get, change_handle]\n')
            wirteFileDicts(can_parse_whitelistPath,can_parse_whitelist_content_line,False)
            return 2
    return 1

def addCan_parse_whitelist(sigs):
    jsConfig=getJScontent(pyFileDir+"config.json")
    analy=Analyze(getKeyPath("dbcfile",jsConfig))
    for sig in sigs:
        message=analy.getMessage_Id_BySig(sig)
        if len(message)==0:
            print(f'{sig} 对应的message不存在')
            break
        messagesig=analy.getMessage_Id_Sig(sig)
        can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
        WriteCan_parse_whitelist(can_parse_whitelistPath,message,messagesig,False)

'''
获取信号名称对应的中文名称
stype：输入的类型
0   是信号名称
1   是message
2   是文件
'''
def SigNameChinese(configPath, wirteSigNames, canmatrix="",stype = 0):
    jsConfig = getJScontent(configPath)
    if len(canmatrix) == 0:
        canmatrix = getKeyPath("canmatrix", jsConfig)
    print(canmatrix)

    dbcfile = getKeyPath("dbcfile", jsConfig)
    print(dbcfile)
    book = xlrd.open_workbook(canmatrix)
    assert isinstance(book, Book)

    sheel = book.sheet_by_name(Sig_Matrix)
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel, Sheet)

    if stype == 2:
        texts=[]
        for wirteSigName in wirteSigNames:
            text = readFileAll(wirteSigName)
            texts.extend(re.findall(e_i,text,re.A))
        wirteSigNames = texts
    outStrs=[]
    for row in range(sheel.nrows):
        if row == 0:
            continue
        sig = getSigInfo(sheel, row)
        if appoints(sig,wirteSigNames,stype==1):    
            outStr=f'{sig.name:<30}{sig.chineseName}'
            if outStr not in outStrs:
                printGreen(outStr)
                outStrs.append(outStr)


def handleProjectPath(configPath,path):
    jsConfig = getJScontent(configPath)
    if path == None or len(path) == 0:
        print(jsConfig.get("projectPath",""))
    else:
        jsConfig['projectPath'] = path
        writeJs(configPath,jsConfig)
        handleProjectPath(configPath,'')


def updatenIputMsgContent(inputSignalContent,msgInfo):
    print(type(msgInfo))
    bus_id = msgInfo.channel
    msg_id = msgInfo.messageId
    update = msgInfo.sendType != 8
    msg = []
    isExist = False
    if 'msg' in inputSignalContent:
        msg = inputSignalContent['msg']
    
    for inputMsg in msg:
        if  inputMsg["bus_id"] == bus_id and inputMsg["msg_id"] == msg_id:
            inputMsg["update"] = update
            isExist = True
            printGreen(f"更新 bus_id:{bus_id},msg_id:{msg_id}")

    if not isExist:
        inputMsg={}
        inputMsg["bus_id"] = "0x"+bus_id
        inputMsg["msg_id"] = "0x"+msg_id
        inputMsg["priority"] = 0
        inputMsg["update"] = update
        inputMsg["boot_qnx"] = True
        inputMsg["boot_android"] = True
        msg.append(inputMsg)
        printGreen(f"添加 bus_id:{bus_id},msg_id:{msg_id}")
    inputSignalContent['msg'] = msg
'''
添加 input_signal_config.json 文件
https://docs.google.com/document/d/1oNexc9DOYv83p1JLMAdbCcdweU_pKZZ_S8vXjHoEzE4/edit#heading=h.1z8l8k9ig7e7
'''
def addInputMsgConfig(configPath,msgIds):
    jsConfig = getJScontent(configPath)
    inputSignalConfig = getKeyPath("input_signal_config",jsConfig)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    print(dbcfile)

    inputSignalContent = getJScontent(inputSignalConfig)

    dbc = Analyze(dbcfile)
    dbcMsgInfos = dbc.getAllMessage()
    for dbcMsgInfo in dbcMsgInfos:
        for msgInfo in dbcMsgInfos[dbcMsgInfo]:
            if msgIds == None or len(msgIds) == 0 or msgInfo in msgIds:
                updatenIputMsgContent(inputSignalContent,dbcMsgInfos[dbcMsgInfo][msgInfo])

    writeJs(inputSignalConfig,inputSignalContent)
    printGreen("添加完成")
    print(inputSignalConfig)