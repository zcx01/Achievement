#!/usr/bin/python
import os
import sys

import xlrd
import argparse

from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import*
from AnalyzeNet import *
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
        printYellow(f'{sig.name} 缩放不能为0，此处修改成1,行号为{row}')
        sig.factor = 1
    sig.Offset = getValueInt(sheel, row, 9)
    sig.min = getValueInt(sheel, row, 10)
    sig.max = getValueInt(sheel, row, 11, sig.length)
    if getValue(sheel, row, 12) == "Signed":
        sig.dataType = "-"
    sig.SetUnit(str(getValue(sheel, row, 13)))
    if ISUSEDBCENUM: sig.enum = str(getValue(sheel, row, 14))
    try:
        if str(getValue(sheel, row, 15)) != 'nan':
            sig.initValue = int(getValue(sheel, row, 15), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, 17)
    sig.Recevier = getValue(sheel, row, 20)
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
        return sig.messageId == wirteSigName.upper()

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
            if sig.name in threeFrames:
                sig.sendType = SigSendType.Three
            # print(type(sig.min),type(sig.max),type(sig.Offset),type(sig.factor))
            realMin = (float(sig.min)-float(sig.Offset)) / float(sig.factor)
            realMax = (float(sig.max)-float(sig.Offset)) / float(sig.factor)
            if realMin < 0 and sig.dataType == "+":
                printRed(f'{sig.name} 极小值小于0,最小值为{sig.min},raw值{realMin}')
                continue
            if realMax > pow(2, sig.length)-1 and sig.max != pow(2, sig.length)-1:
                printRed(f'{sig.name} 极大值大于长度,最大值为{sig.max},raw值{realMax}，极限值为{pow(2, sig.length)}')
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
                if isAllAdd:
                    dbc.repalceSig(sig)
                else:
                    isRepalce = input(f'{sig.getMessage_Sig()} 是否替換 y/n ')
                    if 'y' in isRepalce:
                        dbc.repalceSig(sig)

    if not isFind:
        print(f"{wirteSigName} 在CAN矩阵中不存在")




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




# conversion(pyFileDir+"config.json","","/home/chengxiongzhu/Achievement/pythonscript/canSimulation/temp.xls")
# conversion(pyFileDir+"config.json",'TboxLocalTiYear')
# sigNameChanged(pyFileDir+"config.json",'/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV_V2.1.1_20211009.dbc_old','B_C.txt')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        这个脚本是用来通过生成dbc,比较CAN矩阵,
        d+s:从其他的dbc添加信号,
        d+r+t:信号名称的改变，并且修改配置的中源码的信号名称,
        d+r/d:从指定的dbc复制枚举到新的dbc中 r是输入比较后的结果
        a+w:把dbc目录下dbc文件中,所有的信号都写入白名单,
        a+s:把指定路径下的CAN矩阵中的指定的信号添加进入dbc
        ''')

    parse.add_argument('-c', '--config', help='配置文件路径',
                       default=pyFileDir+"config.json")
    parse.add_argument('-a', '--append', nargs='?', help='新增整个矩阵表格')
    parse.add_argument('-s', '--sigNames', help='新增信号名，是一个列表',
                       default=[], nargs='+', type=str)
    parse.add_argument('-m', '--messages', help='新增messages，是一个列表',
                       default=[], nargs='+', type=str)
    parse.add_argument('-rs', '--rmsigs', help='删除信号,是一个集合,可以用10进制+信号名称,也可以是信号名',nargs='+')
    parse.add_argument('-rm', '--rmmsgs', help='删除message,是一个集合,是一个16进制',nargs='+')                  
    arg = parse.parse_args()

    canmatrix = arg.append
    if canmatrix == None:
        jsConfig = getJScontent(arg.config)
        canmatrix = getKeyPath("canmatrix", jsConfig)

    if '-rs' in sys.argv:
        RemoveSigs(arg.config, arg.rmsigs)
    elif '-rm' in sys.argv:
        RemoveMsgs(arg.config, arg.rmmsgs,arg.channal)
    elif '-m' in sys.argv:
        for msg in arg.messages:
            conversion(arg.config, msg,canmatrix,True)
    elif "-a" in sys.argv and '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config,sigName,canmatrix)
    elif "-a" in sys.argv:
        conversion(arg.config, "", canmatrix)
    elif '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config, sigName)