#!/usr/bin/python
import os
import sys
import xlrd
import argparse
from commonfun import*
from Analyzedbc import *

def getValue(src, row, col):
    return src.cell_value(row, col)


def getValueKong(src, row, col):
    value = str(src.cell_value(row, col))
    if value == r"/" or len(value) == 0:
        return "\"\""
    return f'\"{value}\"'


def getValueInt(src, row, col, lenght=-1):
    try:
        value = str(float(src.cell_value(row, col)))
        values = value.split(".")
        if int(values[1]) != 0:
            return float(value)
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
    sig.endBit = getValueInt(sheel, row, 6)
    sig.length = getValueInt(sheel, row, 7)
    sig.factor = getValueInt(sheel, row, 8)
    sig.Offset = getValueInt(sheel, row, 9)
    sig.min = getValueInt(sheel, row, 10)
    sig.max = getValueInt(sheel, row, 11, sig.length)
    if getValue(sheel, row, 12) == "Signed":
        sig.dataType = "-"
    sig.Unit = getValueKong(sheel, row, 13)
    sig.enum = str(getValue(sheel, row, 14)).replace("\n", " ")
    try:
        if str(getValue(sheel, row, 15)) != 'nan':
            sig.initValue = int(getValue(sheel, row, 15), 16)  # 十进制
    except:
        pass
    sig.invalidValue = getValue(sheel, row, 17)
    sig.Recevier = getValue(sheel, row, 20)
    sig.getStartBit()
    return sig


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
    sheel = book.sheet_by_name("5_Matrix")
    isFind = False
    for row in range(sheel.nrows):
        sigName = str(getValue(sheel, row, 2))
        if isAllAdd and row == 0:
            continue
        if sigName.strip() == wirteSigName or isAllAdd:
            sig = getSigInfo(sheel, row)
            isFind = True
            dbc = Analyze(dbcfile)
            dbc.writeSig(sig)

    if not isFind:
        print(f"{wirteSigName} 在CAN矩阵中不存在")

def addHeadEnd(text,name):
    text.insert(0, f'-------------- {name} --------------')
    text.append("") 
    return text

def diffCanMatrix(fristMatrix, twoMatrix, configPath, resultPath):
    if len(fristMatrix) == 0:
        jsConfig = getJScontent(configPath)
        fristMatrix = getKeyPath("canmatrix", jsConfig)
    book1 = xlrd.open_workbook(fristMatrix)
    sheel1 = book1.sheet_by_name("5_Matrix")
    book2 = xlrd.open_workbook(twoMatrix)
    sheel2 = book2.sheet_by_name("5_Matrix")
    sigInfos = []
    for row in range(sheel1.nrows):
        if row == 0:
            continue
        info =getSigInfo(sheel1, row)
        info.name = info.name+" "+info.messageId
        sigInfos.append(info)

    results = []
    noExit = []
    for row in range(sheel2.nrows):
        if row == 0:
            continue
        print(f"正在比较{info.name}")
        info = getSigInfo(sheel2, row)
        info.name = info.name+" "+info.messageId
        isSame = False
        index = 0
        for compareSig in sigInfos:
            isSame, result = compareSig.compare(info)
            if isSame:
                if len(result) !=0:
                    result = addHeadEnd(result,info.name)
                    results.append('\n'.join(result))
                del sigInfos[index]
                break
            index += 1
        if not isSame:
            noExit.append(info.name)
    
    statistics=[]
    statistics.append('--------------统计--------------')
    statistics.append(f'存在差异的信号有{len(results)}个')
    statistics.append(f'在原来的矩阵是不存在的有{len(noExit)}个')
    statistics.append("具体如下:")
    statistics.append(" ")

    noExit.insert(0,'--------------不在存在的信号--------------')
    if len(resultPath) != 0:
        print(f"写入{resultPath}文件...")
        wirteFileDicts(resultPath, statistics+results+noExit, False)

    print("比较完成!")


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
    arg = parse.parse_args()

    if "-a" in sys.argv:
        conversion(arg.config, "", arg.append)
    elif '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config, sigName)
    elif '-t' in sys.argv:
        diffCanMatrix(arg.fristMatrix, arg.twoMatrix,
                      arg.config, arg.resultPath)
    # conversion(pyFileDir+"config.json", "CdcLaneInfo")
