#!/usr/bin/python
import json
import sys
import os
import xlrd
import subprocess
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from commonfun import *
from Analyzedbc import Analyze, DataType

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
            print(f'请输入{msg}类型、前缀(用空格分开):')
            temp=input()
            temps=temp.split(" ")
            type=temps[0]
            suffx=temps[1]
            if len(type) != 0:
                jsConfig[msg]={"filePath":"","type":type,"suffx":suffx}
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
    sheel=book.sheet_by_name("5_Matrix")
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

def getTopic_P(jsContents,desc):
    level=""
    for jsGeneral in jsContents:
        Comments=jsGeneral["Comments"]
        if len(Comments)==0: continue
        lev=jsGeneral["Topic Level 1"]
        if len(lev) != 0: level=lev
        if Comments.find(desc)!=-1 or desc.find(Comments)!=-1:
            levelCount=2
            while(1):
                levelStr="Topic Level "+str(levelCount)
                if len(jsGeneral.get(levelStr,"")) ==0:
                    level=EesyStr.removeAt(level,len(level)-1)
                    return level
                else:
                    level=level+jsGeneral[levelStr]+"/"
                levelCount+=1
    return level

def getTopic(jsConfig,desc,sig,suffx):
    topic=""
    try:
        jsGenerals=getJScontent(getKeyPath("topics_define",jsConfig))
        topic=getTopic_P(jsGenerals,desc)
        if len(topic) !=0:
            return topic
    except:
        pass
    print(f"没有找到{desc},请输入topic?")
    topic=input()
    if len(topic) != 0:
        return topic
    print(f"输入的{desc}为空,是否生成自定义topic(y/n)?")
    cmd=input()
    if "n" in cmd:
        return
    custom_topics_definePath=getKeyPath("topics_define",jsConfig)
    jsCustoms=getJScontent(custom_topics_definePath)
    topic=getTopic_P(jsCustoms,desc)
    if len(topic) !=0:
        return topic
    jsCustom={}
    jsCustom["Topic Level 1"]=suffx
    jsCustom["Topic Level 2"]=sig
    jsCustom["HasSet"]=""
    jsCustom["Comments"]=desc
    jsCustoms.append(jsCustom)
    writeJs(custom_topics_definePath,jsCustoms)
    ex = subprocess.Popen("bash "+getKeyPath("generate_topic",jsConfig),stdout=subprocess.PIPE,shell=True)
    ex.communicate()
    ex.wait()
    return suffx+sig

def getDefine(jsConfig,topic):
    definefile=getKeyPath("definefile",jsConfig)
    texts=readFileLines(definefile)
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
    alreadyText=[]
    for text in content:
        if text.strip().startswith("#") or len(text) == 0 or text in alreadyText or text.strip().startswith("\n"):
            continue
        text=text.replace("\t"," ")
        names=text.split(" ")
        sig=getValueByIndex(names,0)
        sigType = getValueByIndex(names, 1)

        #通过 CAN matrix 表格获取中文描述
        if len(names) < 2 or len(names[2]) == 0 or names[1] == "d":
            desc=getSignalDescInexcel(sig,getKeyPath("canmatrix",jsConfig))
        else:
            desc=getValueByIndex(names,2)

        className=getValueByIndex(names,3,"x")

        # messagesuffix=getValueByIndex(names,3)
        # if len(messagesuffix) != 0:
        #     messagesuffix="."+messagesuffix

        topic=getValueByIndex(names,4)

        message=analy.getMessageBySig(sig)
        if len(message)==0:
            print(f'{sig} {desc} 对应的message不存在')
            continue
        
        messagesig=message+"__"+sig
        #写入 can_parse_whitelist 文件
        can_parse_whitelistPath=getKeyPath("can_parse_whitelist",jsConfig)
        if judgeCommad("-bc",names) or findsignalInfile(f'{messagesig}',can_parse_whitelistPath):
            pass
        else:
            print(f"写入 {can_parse_whitelistPath} 文件")
            can_parse_whitelist=open(can_parse_whitelistPath,"r")
            can_parse_whitelist_content=can_parse_whitelist.read()
            can_parse_whitelist.close()
            can_parse_whitelist=open(can_parse_whitelistPath,"a")
            if not can_parse_whitelist_content.endswith('\n'):
                can_parse_whitelist.write('\n')
            can_parse_whitelist.write(f'{messagesig:<30}       [signal]		[get, change_handle]\n')
            can_parse_whitelist.close()

        # sigType = WriteType(jsConfig, message+messagesuffix)
        # suffx=jsConfig.get(message+messagesuffix,{}).get("suffx","")
        if len(topic)==0 or topic == "x":
            topic = getTopic(jsConfig, desc, sig, "")
        define = getDefine(jsConfig,topic)

        #写入 cpp 文件 #创建 .h .cpp 文件
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
        alreadyText.append(text)
    os.system("Parser")

def xlsToTxt():
    jsConfig=getJScontent(pyFileDir+"config.json")
    book=xlrd.open_workbook(getKeyPath("xlsNewSigPath",jsConfig))
    sheel=book.sheet_by_index(0)
    rowDatas=[]
    newSigFile = open(getKeyPath("newSig", jsConfig), "r")
    oldRowDatas=newSigFile.read().splitlines()
    for oldRowData in oldRowDatas:
        if oldRowData.strip().startswith("#"):
            rowDatas.append(oldRowData)

    for row in range(sheel.nrows):
        if row == 0 :
            continue
        rowDatas.append(" ".join(sheel.row_values(row)))
    wirteFileDicts(getKeyPath("newSig", jsConfig),rowDatas)

if __name__ == "__main__":
    if(judgeCommad("-x","")):
        xlsToTxt()
    dealnewSig()

