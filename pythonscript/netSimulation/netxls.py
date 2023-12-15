#!/usr/bin/python
import os
import sys

import xlrd
import argparse
import copy
from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import*
from AnalyzenNet.AnalyzeNetFile import *
from AnalyzenNet.projectInI import *

def getValue(src, row, col):
    return src.cell_value(row, XlsCharToInt(col))

def getValueInt(src, row, col, lenght=-1):
    try:
        value = str(getValue(src,row, col))
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
    sig = NetSigInfo()
    sig.subNet = str(getValue(sheel, row, sig_line_subNet)).upper()
    sig.Sender = str(getValue(sheel, row, sig_line_Sender)).upper()
    temp = str(getValue(sheel, row, sig_line_name))
    temps = re.findall(e_i, temp, re.A)
    sig.name = "_".join(temps)
    sig.chineseName = str(getValue(sheel, row, sig_line_chineseName))
    sig.messagaType = str(getValue(sheel, row, sig_line_messageId)).split(".")[0].replace('0x', '')
    sig.cycle = getValueInt(sheel, row, sig_line_cycle)
    sig.start_by_byte = getValueInt(sheel, row, sig_line_start_by_byte)
    sig.length_byte = getValueInt(sheel, row, sig_line_length_byte)
    if len(sig_line_length_bits) !=0:
        sig.length_bits = getValueInt(sheel, row, sig_line_length_bits)
    else:
        sig.length_bits = 8 * sig.length_byte
    sig.factor = getValueInt(sheel, row, sig_line_factor)
    if sig.factor == float(0) and len(sig.name) != 0:
        printYellow(f'{sig.name} 缩放不能为0，此处修改成1,行号为{row}')
        sig.factor = 1
    sig.offset = getValueInt(sheel, row, sig_line_Offset)
    sig.phy_min = getValueInt(sheel, row, sig_line_min)
    sig.phy_max = getValueInt(sheel, row, sig_line_max, sig.length_bits)
    if getValue(sheel, row, sig_line_dataType) == "Signed":
        sig.dataType = "-"
    sig.SetUnit(str(getValue(sheel, row,sig_line_unit)))
    if ISUSEDBCENUM: sig.enum = str(getValue(sheel, row, 14))
    try:
        if str(getValue(sheel, row, sig_line_initValue)) != 'nan':
            sig.initValue = int(getValue(sheel, row, 15), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, sig_line_invalidValue)
    sig.Recevier = getValue(sheel, row, sig_line_Recevier)
    return sig

def appoint(sig,wirteSigName, isMsg): #是否是指定添加的信号
    assert isinstance(sig,NetSigInfo)
    if not isMsg:
        return sig.name.upper() == wirteSigName.upper() or sig.messagaType+sig.name.upper() == wirteSigName.upper()
    else:
        return sig.messagaType == wirteSigName.upper()


def addSig(sig,wirteSigName,isMsg,isAllAdd,net):
    assert isinstance(sig,NetSigInfo)
    assert isinstance(net,AnalyzeNetParserFile)
    if appoint(sig,wirteSigName,isMsg) or isAllAdd:
        realMin = (float(sig.phy_min)-float(sig.offset)) / float(sig.factor)
        realMax = (float(sig.phy_max)-float(sig.offset)) / float(sig.factor)
        if realMin < 0 and sig.dataType == "+":
            phy_min =  float(sig.offset)
            printRed(f'{sig.name} 极小值小于0,表中最小物理值值为{sig.phy_min},能达到的最小物理值为{phy_min}')
            return
        if realMax > pow(2, sig.length_bits)-1 and sig.phy_max != pow(2, sig.length_bits)-1:
            phy_max = (pow(2, sig.length_bits)-1) * float(sig.factor) + float(sig.offset)
            printRed(f'{sig.name} 极大值大于长度,表中最大物理值为{sig.phy_max}，能达到的最大物理值为{phy_max}')
            return
        if sig.phy_min == sig.phy_max:
            printRed(f"{sig.name} 最大值和最小值相等值为{sig.phy_max}")
            return

        isFind = True
        writedbcresult = net.addSig(sig)
        if writedbcresult == WriteResult.AlreadyExists:
            if isAllAdd:
                net.repalceSig(sig)
            else:
                isRepalce = input(f'{sig.name()} 是否替換 y/n ')
                if 'y' in isRepalce:
                    net.repalceSig(sig)
    return isFind


'''
sig:信号名称
sigSheelName:sheet的中的名称
space:信号的间隔，比如XYXY,就是2，XYZXYZ就是3
'''
def getExpandSig(sig,sigSheelName,space):
    assert isinstance(sig,NetSigInfo)
    expandSigs=[]
    match = re.search(r'\((.*?)\)', sigSheelName)
    if match:  
        substring = match.group(1)
        rangeIndex = re.findall(i_i,substring,re.A)
        expandSigName = sigSheelName.replace('('+substring+')','')
        startIndex = int(rangeIndex[0])
        endIndex = int(rangeIndex[1])
        start_by_byte = sig.start_by_byte
        for index in range(startIndex,endIndex+1):
            expandSig = copy.deepcopy(sig)
            expandSig.name = expandSigName.replace(expand_flag,str(index))
            expandSig.start_by_byte = start_by_byte
            start_by_byte = start_by_byte + sig.length_byte * space 
            expandSigs.append(expandSig)
        return expandSigs

def conversion(configPath, wirteSigName, canmatrix="",isMsg = False):
    jsConfig = getJScontent(configPath)
    isAllAdd = (len(wirteSigName) == 0)
    if len(canmatrix) == 0:
        canmatrix = getKeyPath("canmatrix", jsConfig)
        isAllAdd = False
    print(canmatrix)

    netfile = getKeyPath("netParser", jsConfig)
    print(netfile)
    book = xlrd.open_workbook(canmatrix)
    assert isinstance(book, Book)

    sheel = book.sheet_by_name(Sig_Matrix)
    isFind = False

    net = AnalyzeNetParserFile(netfile)
    if isAllAdd:
        net.clearSig()
    
    expandSigs={}
    for row in range(sheel.nrows):
        if row == 0:
            continue
        sig = getSigInfo(sheel, row)
        if sig.name == None or len(sig.name) ==0:
            continue
        isExpand = False
        for expand_field in expand_fields:
            if expand_field in sig.chineseName:
                sig.name = str(getValue(sheel, row, sig_line_name))
                if sig.messagaType not in expandSigs:
                    expandSigs[sig.messagaType]=[]
                expandSigs[sig.messagaType].append(sig)
                isExpand = True
                break
        if isExpand: continue
        if addSig(sig,wirteSigName,isMsg,isAllAdd,net):
            isFind = True

    for messagaType,expandSigList in expandSigs.items():
        for sig in expandSigList:
            siglist = getExpandSig(sig,sig.name,len(expandSigList))
            for expandSig in siglist:
                if addSig(expandSig,wirteSigName,isMsg,isAllAdd,net):
                    isFind = True
    
    if not isFind:
        print(f"{wirteSigName} 在矩阵中不存在")
    else:
        net.writeFile()

def RemoveSigs(configPath, sigNames):
    jsConfig = getJScontent(configPath)
    netfile = getKeyPath("netParser", jsConfig)
    net = AnalyzeNetParserFile(netfile)
    net.removeSigByNames(sigNames)

def RemoveMsgs(configPath, msgs,channal):
    jsConfig = getJScontent(configPath)
    netfile = getKeyPath("netParser", jsConfig)
    net = AnalyzeNetParserFile(netfile)
    net.removeMessage(channal,msgs)

def addHeadEnd(text, name):
    text.insert(0, f'{name}')
    text.append("")
    return text




# conversion(pyFileDir+"config.json","","/home/chengxiongzhu/Achievement/pythonscript/netSimulation/NID3.0（HMI）与CDC的以太网通讯协议V1.2_202201021.xlsx")
# conversion(pyFileDir+"config.json",'TboxLocalTiYear')
# sigNameChanged(pyFileDir+"config.json",'/home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/parser/vendor/dbc_files/CAN0_C385EV_V2.1.1_20211009.dbc_old','B_C.txt')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
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