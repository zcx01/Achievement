#!/usr/bin/python
import os
import sys
import xlrd
import argparse

from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import*
from AnalyzeCan.Analyzedbc import *
from AnalyzeCan.projectInI import *
def getValue(src, row, col):
    return src.cell_value(row, col)

def getValueInt(src, row, col, lenght=-1):
    try:
        value = str(src.cell_value(row, col))
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
    sig.subNet = str(getValue(sheel, row, 0)).upper()
    sig.Sender = str(getValue(sheel, row, 1)).upper()
    temp = str(getValue(sheel, row, 2))
    temps = re.findall(e_i, temp, re.A)
    sig.name = "_".join(temps)
    sig.chineseName = str(getValue(sheel, row, 3))
    sig.messageId = str(getValue(sheel, row, 4)).split(".")[0].replace('0x', '')
    sig.cycle = getValueInt(sheel, row, 5)
    if sig.cycle == 0:  # 没有周期，就解析为0
        sig.sendType = SigSendType.Event

    posBit = getValueInt(sheel, row, 6)
    if MSB == True:
        sig.startBit = posBit
    else:
        sig.endBit = posBit
    sig.length = getValueInt(sheel, row, 7)
    sig.factor = getValueInt(sheel, row, 8)
    if sig.factor == float(0) and len(sig.name) != 0:
        printYellow(f'{sig.name} 缩放不能为0，此处修改成1')
        sig.factor = 1
    sig.Offset = getValueInt(sheel, row, 9)
    sig.min = getValueInt(sheel, row, 10)
    sig.max = getValueInt(sheel, row, 11, sig.length)
    if getValue(sheel, row, 12) == "Signed":
        sig.dataType = "-"
    sig.SetUnit(str(getValue(sheel, row, 13)))
    sig.enum = str(getValue(sheel, row, 14))
    try:
        if str(getValue(sheel, row, 15)) != 'nan':
            sig.initValue = int(getValue(sheel, row, 15), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, 17)
    sig.Recevier = getValue(sheel, row, 20)
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
            msg.subNet = sheel.cell_value(row, 0)
            msg.sender = sheel.cell_value(row, 1)
            sendingMode = str(sheel.cell(row, 2))
            msg.messageId = getNoOx16(str(sheel.cell_value(row, 4)))
            if 'event' in sendingMode.lower():
                msg.sendType = 8
            msg.cycle = getValueInt(sheel, row, 3)
            if msg.cycle == 0:
                cycleContent = str(getValue(sheel, row, 3))
                cycleContents = re.findall(e_i, cycleContent, re.A)
                if len(cycleContents) >= 2:
                    try:
                        msg.cycle = int(cycleContents[0])
                        msg.threeCycle = int(cycleContents[1])
                    except:
                        pass
            msg.lenght = getValueInt(sheel, row, 5)
            msg.Recevier = str(sheel.cell_value(row, 6))
            frame = str(sheel.cell_value(row, 9))
            if len(frame) == 0 or len(splitSpace(frame)) == 0 or not isNumber(frame):
                frame = SubNet_Frame.get(msg.subNet, 0)
            else:
                frame = VFrameFormat.get(frame, 0)
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

def conversion(configPath, wirteSigName, canmatrix=""):
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
        sigName = str(getValue(sheel, row, 2))
        if isAllAdd and row == 0:
            continue
        if sigName.strip() == wirteSigName or isAllAdd:
            sig = getSigInfo(sheel, row)
            if sig.name in threeFrames:
                sig.sendType = SigSendType.Three
            # print(type(sig.min),type(sig.max),type(sig.Offset),type(sig.factor))
            realMin = (float(sig.min)-float(sig.Offset)) / float(sig.factor)
            realMax = (float(sig.max)-float(sig.Offset)) / float(sig.factor)
            if realMin < 0 and sig.dataType == "+":
                printRed(f'{sig.name} 极小值小于0,最小值为{sig.min},raw值{realMin}')
                continue
            if realMax > pow(2, sig.length)-1 and sig.max != pow(2, sig.length)-1:
                printRed(f'{sig.name} 极大值大于长度,最大值为{sig.max},raw值{realMax}')
                continue
            if sig.min == sig.max:
                printRed(f"{sig.name} 最大值和最小值相等最小值为{sig.min},最大值为{sig.max}")
                continue

            isFind = True
            dbc = Analyze(dbcfile)
            msg = msgs.get(sig.getMessage_SubNet(), None)
            if msg == None:
                print(f' {sig.name} 对应的 {sig.messageId} message不存在')
                printYellow("可能的原因是:message没有加0x")
                continue

            writedbcresult = dbc.writeSig(sig, msg)
            if writedbcresult == WriteDBCResult.AlreadyExists:
                dbc.repalceSig(sig)
                # isRepalce = input('是否替換 y/n ')
                # if 'y' in isRepalce:
                #     dbc.repalceSig(sig)

            can_parse_whitelistPath = getKeyPath(
                "can_parse_whitelist", jsConfig)
            if os.path.isfile(can_parse_whitelistPath):
                os.system(
                    f"topic_Parser -w {can_parse_whitelistPath} {sig.getMessage_Id()} {sig.getMessage_Sig()}")
    if not isFind:
        print(f"{wirteSigName} 在CAN矩阵中不存在")

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

def RemoveSigs(configPath, sigNames):
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)
    dbc.removeSig(sigNames)

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

def modifyMessageInfo(configPath):
    jsConfig = getJScontent(configPath)
    matrixFilePath = getKeyPath("canmatrix", jsConfig)
    book = xlrd.open_workbook(matrixFilePath)
    assert isinstance(book, Book)
    print(book.sheet_names())
    messageSheel = book.sheet_by_name(Message_Matrix)
    assert isinstance(messageSheel, Sheet)
    dbc = Analyze(getKeyPath("dbcfile", jsConfig))
    msgs = getMessageInfo(messageSheel)
    for messageId in dbc.dbcMessage:
        try:
            dbcMsg = dbc.dbcMessage[messageId]
            assert isinstance(dbcMsg, MessageInfo)
            dbcMsg = msgs[messageId]
        except:
            print(f'{dbc.dbcMessage[messageId].messageId} 在CAN矩阵没有找到')

    dbc.repalceMessage(dbc.dbcMessage.values())

# conversion(pyFileDir+"config.json","","/home/chengxiongzhu/Achievement/pythonscript/canSimulation/temp.xls")
conversion(pyFileDir+"config.json",'TboxLocalTiYear')
# sigNameChanged(pyFileDir+"config.json",'/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV_V2.1.1_20211009.dbc_old','B_C.txt')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        这个脚本是用来通过生成dbc,比较CAN矩阵,
        d+s:从其他的dbc添加信号,
        d+r+t:信号名称的改变，并且修改配置的中源码的信号名称,
        d+r/d:从指定的dbc复制枚举到新的dbc中 r是输入比较后的结果
        ''')

    parse.add_argument('-c', '--config', help='配置文件路径',
                       default=pyFileDir+"config.json")
    parse.add_argument('-a', '--append', help='新增整个can矩阵表格')
    parse.add_argument('-s', '--sigNames', help='新增信号名，是一个列表',
                       default=[], nargs='+', type=str)
    parse.add_argument('-f', '--fristMatrix',
                       help='比较dbc矩阵,比较的文件,没有指定就使用配置文件中的路径', default="")
    parse.add_argument('-t', '--twoMatrix', help='比较dbc矩阵,被比较的文件,也是旧的一方的文件')
    parse.add_argument('-r', '--resultPath', help='比较dbc矩阵结果路径', default='')
    parse.add_argument('-m', '--modifyMessageInfo',
                       help='替换message信息,有m就会替换', default=1, type=int, nargs='*')
    parse.add_argument('-d', '--dbcPath', help='比较新旧两个dbc,输入的是被比较的')
    parse.add_argument('-rm', '--rmsigs', help='删除信号,是一个集合',nargs='+')
    parse.add_argument('-u', '--isfilterNoUser',
                       help='是否过滤掉没有使用过的信号', nargs='*')
    arg = parse.parse_args()

    if '-d' in sys.argv and '-r' in sys.argv and '-t' in sys.argv:
        sigNameChanged(arg.config, arg.dbcPath, arg.resultPath, arg.twoMatrix)
    elif '-d' in sys.argv and '-s' in sys.argv:
        conversionByOtherdbc(arg.config, arg.sigNames, arg.dbcPath)
    elif '-rm' in sys.argv:
        RemoveSigs(arg.config, arg.rmsigs)
    elif "-a" in sys.argv and '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config,sigName,arg.append)
    elif "-a" in sys.argv:
        conversion(arg.config, "", arg.append)
    elif '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config, sigName)
    elif '-m' in sys.argv:
        modifyMessageInfo(arg.config)
    elif '-t' in sys.argv:
        diffCanMatrix(arg.fristMatrix, arg.twoMatrix, arg.config,arg.resultPath, '-u' in sys.argv)
    elif '-d' in sys.argv:
        CopyEnum(arg.config, arg.dbcPath, arg.resultPath)
