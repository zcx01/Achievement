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
    return f'\"{value}\"'

def getValueInt(src,row,col,lenght=-1):
    try:
        value = str(float(src.cell_value(row,col)))
        values = value.split(".")
        if int(values[1]) != 0:
            return float(value)
        return int(values[0])
    except:
        if(lenght==-1):
            return 0
        return pow(2,lenght)

def getSigInfo(sheel,row):
    sig = SigInfo()
    isFind = True
    sig.name = str(getValue(sheel,row,2))
    sig.Sender = str(getValue(sheel,row,1)).upper()
    sig.messageId = str(getValue(sheel,row,4)).split(".")[0]
    sig.cycle =  getValueInt(sheel,row,5)
    sig.endBit = getValueInt(sheel,row,6)
    sig.length = getValueInt(sheel,row,7)
    sig.factor = getValueInt(sheel,row,8)
    sig.Offset = getValueInt(sheel,row,9)
    sig.min = getValueInt(sheel,row,10)
    sig.max = getValueInt(sheel,row,11,sig.length)
    if getValue(sheel,row,12) == "Signed":
        sig.dataType = "-"
    sig.Unit = getValueKong(sheel,row,13)
    sig.enum = str(getValue(sheel,row,14)).replace("\n"," ")
    if str(getValue(sheel,row,15)) != 'nan':
        sig.initValue = int(getValue(sheel,row,15),16)  # 十进制
    sig.invalidValue = getValue(sheel,row,17)
    sig.Recevier = getValue(sheel,row,20)
    sig.getStartBit()
    return sig

def conversion(configPath,wirteSigName,canmatrix=""):
    print(configPath)
    jsConfig=getJScontent(configPath)
    isAllAdd = True
    if len(canmatrix) == 0:
        canmatrix = getKeyPath("canmatrix", jsConfig)
        isAllAdd = False
    print(canmatrix)
    dbcfile=getKeyPath("dbcfile",jsConfig)
    book = xlrd.open_workbook(canmatrix)
    sheel=book.sheet_by_name("5_Matrix")
    isFind =False
    for row in range(sheel.nrows):
        sigName=str(getValue(sheel,row,2))
        if isAllAdd and row == 0:
            continue
        if sigName.strip() == wirteSigName or isAllAdd:
            sig = getSigInfo(sheel,row)
            dbc=Analyze(dbcfile)
            dbc.writeSig(sig)

    if not isFind:
        print("没有找到信号")

if __name__ == "__main__":
    sigNames = sys.argv
    if "-a" in sigNames:
        conversion(pyFileDir+"config.json", "",sigNames[2])
    else:
        del sigNames[0]
        for sigName in sigNames:
            conversion(pyFileDir+"config.json", sigName)
    # conversion(pyFileDir+"config.json", "CdcLaneInfo")
