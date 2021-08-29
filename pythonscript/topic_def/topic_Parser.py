#!/usr/bin/python
import json
import sys
import os
import xlrd
from Analyzedbc import Analyze, DataType
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from commonfun import *


def getSigJson(jsConfig,msg,sig):
    filePath=jsConfig.get(msg,{}).get("filePath","")
    while True:
        if os.path.isfile(filePath):
            return filePath
        else:
            print(f'请输入{msg}({sig})对应json配置文件、类型、前缀(用空格分开):')
            temp=input()
            temps=temp.split(" ")
            filePath=temps[0]
            type=temps[1]
            try:
                suffx=temps[2]
            except:
                suffx=type
            if not os.path.isfile(filePath):
                print(f'{filePath}不存在')
            else:
                jsConfig[msg]={"filePath":filePath,"type":type,"suffx":suffx}
                writeJs(pyFileDir+"config.json",jsConfig)

def WriteType(jsConfig,msg):
    type=jsConfig.get(msg,{}).get("type","")
    while True:
        if len(type) != 0:
            return type
        else:
            print(f'请输入{msg}类型')
            type=input()
            if len(type) != 0:
                jsConfig[msg]={"filePath":"","type":type,"suffx":""}
                writeJs(pyFileDir+"config.json",jsConfig)

def addEscape(s):
    temp = str(s).replace("(","\(")
    temp = temp.replace(")","\)")
    return temp

def judgeCommad(cmd,all):
    if cmd in sys.argv or cmd in all:
        return True
    return False

def findsignalInfile(signal,filePath):
    try:
        f=open(filePath,'r')
        content=f.readlines()
        for text in content:
            texts = text.split(" ")
            if signal in texts[0]:
                return True
        return False
    except:
        return False

def getSignalDescInexcel(signal,filePath):
    book=xlrd.open_workbook(filePath)
    sheel=book.sheet_by_index(0)
    for row in range(sheel.nrows):
        text=sheel.cell_value(row,2)
        if str(text).find(signal)!=-1:
            return str(sheel.cell_value(row,3))
    return ""

def getFullPath(path,jsConfig):
    # path=str(path)
    if path.startswith("/"):
        return path
    else:
        projectPath=jsConfig.get("projectPath","")
        return projectPath+path

def getKeyPath(key,jsConfig):
    return getFullPath(jsConfig.get(key,""),jsConfig)

def getTopic(jsConfig,desc,sig):
    try:
        jsGenerals=getJScontent(jsConfig["general_topics_define"])
        level=""
        for jsGeneral in jsGenerals:
            Comments=jsGeneral["Comments"]
            lev=jsGeneral["Topic Level 1"]
            if len(lev) != 0: level=lev
            if Comments.find(desc) or desc.find(Comments):
                return level+jsGeneral["Topic Level 2"]
    except:
        pass
    jsCustoms=getJScontent(jsConfig["custom_topics_define"])
    jsCustom={}
    jsCustom["Topic Level 1"]=""
    jsCustom["Topic Level 2"]=sig
    jsCustom["HasSet"]=""
    jsCustom["Comments"]=desc
    jsCustoms.append(jsCustom)
    return sig

def getDefine(jsConfig,topic):
    definefile=getKeyPath("definefile",jsConfig)
    texts=readFileLine(definefile)
    for text in texts:
        if text.find(topic) != -1:
            return splitSpaceGetValueByIndex(text,1)
    print("没有找到"+topic)
    sys.exit()

def dealnewSig():
    jsConfig=getJScontent(pyFileDir+"config.json")
    analy=Analyze(getKeyPath("dbcfile",jsConfig))

    newSigFile=open(getKeyPath("newSig",jsConfig),"r")
    content=newSigFile.read().splitlines()
    newSigFile.close()
    for text in content:
        if text.strip().startswith("#") or len(text) == 0:
            continue
        text=text.replace("\t"," ")
        names=text.split(" ")
        sig=getValueByIndex(names,0)

        #通过 CAN matrix 表格获取中文描述
        if len(names) < 2 or len(names[1]) == 0 or names[1] == "d":
            desc=getSignalDescInexcel(sig,getKeyPath("canmatrix",jsConfig))
        else:
            desc=getValueByIndex(names,1)

        className=getValueByIndex(names,2,"x")

        messagesuffix=getValueByIndex(names,3)
        if len(message) == 0:
            messagesuffix="."+messagesuffix

        message=analy.getMessageBySig(sig)
        if len(message)==0:
            print(f'{sig}对应的message不存在')
            continue

        topic=getTopic(jsConfig,desc,sig)
        messagesig=message+"__"+sig
        #写入 can_parse_whitelist 文件
        can_parse_whitelistPath=getKeyPath("can_parse_whitelist",jsConfig)
        if judgeCommad("-bc",names) or findsignalInfile(f'{messagesig}',can_parse_whitelistPath):
            pass
        else:
            print(f"写入 {can_parse_whitelistPath} 文件")
            can_parse_whitelist=open(can_parse_whitelistPath,"a")
            can_parse_whitelist.write(f'{messagesig:<30}       [signal]		[get, change_handle]\n')
            can_parse_whitelist.close()

        define = getDefine(jsConfig,topic)

        #写入 cpp 文件 #创建 .h .cpp 文件
        sigType=WriteType(jsConfig,message+messagesuffix)
        dataType=analy.getSigDataType(sig)
        dataTypeStr="int"
        if dataType == DataType.VFLOAT:
            dataTypeStr="float"
        if judgeCommad("-A",names):
            continue
        elif judgeCommad("-m",names):
            print('\
        //%s\n\
        else if (topicId == %s) \n\
	{\n\
        sig=&CANSIG_%s_g;\n\
	}'% (desc,define,messagesig))
        else:
            desc=addEscape(desc)
            print(f'AutoCode {sigType} {className} {messagesig} {define} {desc} {dataTypeStr}')
            os.system(f'AutoCode {sigType} {className} {messagesig} {define} {desc} {dataTypeStr}')
    os.system("Parser")

if __name__ == "__main__":
    dealnewSig()

