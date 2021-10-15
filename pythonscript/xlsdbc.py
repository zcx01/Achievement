#!/usr/bin/python
import os
import sys
import xlrd
from commonfun import*
from topic_def.Analyzedbc import *

def getFullPath(path,jsConfig):
    # path=str(path)
    if path.startswith("/"):
        return path
    else:
        projectPath=jsConfig.get("projectPath","")
        return projectPath+path

def getKeyPath(key,jsConfig):
    return getFullPath(jsConfig.get(key,""),jsConfig)

def getValue(src,row,col):
    return src.cell_value(row,col)

def getValueKong(src,row,col):
    value = str(src.cell_value(row,col))
    if value == r"/" or len(value)==0:
        return "\"\""
    return value

def getValueInt(src,row,col):
    value = str(float(src.cell_value(row,col)))
    values = value.split(".")
    if int(values[1]) != 0:
        return float(value)
    return int(values[0])

def conversion(configPath,wirteSigName):
    print(configPath)
    jsConfig=getJScontent(configPath)
    canmatrix=getKeyPath("canmatrix",jsConfig)
    print(canmatrix)
    dbcfile=getKeyPath("dbcfile",jsConfig)
    dbc=Analyze(dbcfile)
    book = xlrd.open_workbook(canmatrix)
    sheel=book.sheet_by_name("5_Matrix")
    for row in range(sheel.nrows):
        sigName=str(getValue(sheel,row,2))
        if sigName.strip() == wirteSigName:
            sig = SigInfo()
            sig.name = sigName
            sig.Sender = getValue(sheel,row,1)
            sig.messageId = getValue(sheel,row,4)
            sig.cycle =  getValueInt(sheel,row,5)
            sig.startBit = getValueInt(sheel,row,6)
            sig.length = getValueInt(sheel,row,7)
            sig.dataType = "+"
            sig.factor = getValueInt(sheel,row,8)
            sig.Offset = getValueInt(sheel,row,9)
            sig.min = getValueInt(sheel,row,10)
            sig.max = getValueInt(sheel,row,11)
            sig.Unit = getValueKong(sheel,row,13)
            sig.enum = str(getValue(sheel,row,14)).replace("\n"," ")
            sig.initValue = int(getValue(sheel,row,15),16)  # 十进制
            sig.invalidValue = getValue(sheel,row,17)
            sig.Recevier = getValue(sheel,row,20)
            # print(sig.getSG(),sig.initValue)
            dbc.writeSig(sig)
            return
    print("没有找到信号")

if __name__ == "__main__":
    conversion(pyFileDir+"config.json",sys.argv[1])
