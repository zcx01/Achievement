#!/usr/bin/python
import json
import sys
import os
import xlrd
import subprocess
import argparse
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from commonfun import *
from Analyzedbc import *

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

def judgeCommad(cmd,all=[]):
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
    execCmd("bash "+getKeyPath("generate_topic",jsConfig))
    return suffx+sig

def execCmd(cmd):
    ex = subprocess.Popen(cmd,stdout=subprocess.PIPE,shell=True)
    ex.communicate()
    ex.wait()

def getDefine(jsConfig,topic):
    definefile=getKeyPath("definefile",jsConfig)
    texts=readFileLines(definefile)
    for text in texts:
        if text.find(topic) != -1:
            return splitSpaceGetValueByIndex(text,1)
    print("没有找到"+topic)
    sys.exit()

def InvalidRow(text,alreadyText):
    return text.strip().startswith("#") or len(text) == 0 or text in alreadyText or text.strip().startswith("\n") or len(text.replace(' ',''))==0

def dealnewSig(can_parse_whitelist_return=False):
    jsConfig=getJScontent(pyFileDir+"config.json")
    newSigFile=open(getKeyPath("newSig",jsConfig),"r")
    content=newSigFile.read().splitlines()
    newSigFile.close()
    alreadyText=[]
    analy=Analyze(getKeyPath("dbcfile",jsConfig))

    #通过CAN添加dbc文件
    addDbcSigNames={}
    for text in content:
        if InvalidRow(text,alreadyText):
            continue
        text=text.replace("\t"," ")
        names=text.split(" ")
        sig=getValueByIndex(names,0)
        if  not analy.sigExist(sig):
            desc=getValueByIndex(names,2)
            addDbcSigNames[sig] = desc

    print('正在写入dbc...')
    for sig in addDbcSigNames:
        print(f'{sig:<10} {addDbcSigNames[sig]}')
    addDbcSigName=' '.join(addDbcSigNames.keys())
    os.system(f'xlsdbc -s {addDbcSigName}')

    analy=Analyze(getKeyPath("dbcfile",jsConfig))
    for text in content:
        if InvalidRow(text,alreadyText):
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
            if can_parse_whitelist_return:
                print(f'{can_parse_whitelistPath} 文件存在，跳过')
                continue
        else:
            print(f"写入 {can_parse_whitelistPath} 文件")
            # can_parse_whitelist=open(can_parse_whitelistPath,"r")
            can_parse_whitelist_content_line=readFileLines(can_parse_whitelistPath)
  
            #写在现有的message后面
            behindStr(can_parse_whitelist_content_line,'message',f'{message:<18}[message]		[all]')

            if not can_parse_whitelist_content_line[len(can_parse_whitelist_content_line)-1].endswith('\n'):
                can_parse_whitelist_content_line.append('\n')

            can_parse_whitelist_content_line.append(f'{messagesig:<30}       [signal]		[get, change_handle]\n')
            wirteFileDicts(can_parse_whitelistPath,can_parse_whitelist_content_line,False)
            

        # sigType = WriteType(jsConfig, message+messagesuffix)
        # suffx=jsConfig.get(message+messagesuffix,{}).get("suffx","")
        if len(topic)==0 or topic == "x":
            topic = getTopic(jsConfig, desc, sig, "")
        define = getDefine(jsConfig,topic)

        #写入 cpp 文件 #创建 .h .cpp 文件
        dataTypeStr=analy.getSigDataType(sig)
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
    

def xlsToTxt(shellIndex=0):
    jsConfig=getJScontent(pyFileDir+"config.json")
    book=xlrd.open_workbook(getKeyPath("xlsNewSigPath",jsConfig))
    sheel=book.sheet_by_index(shellIndex)
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
    parse = argparse.ArgumentParser(description='可以通过文本或者表格生成代码的脚本')
    parse.add_argument('-s','--shell',help='shell的索引',type=int,default=0)
    parse.add_argument('-t','--text',help='文本生成')
    parse.add_argument('-r', '--CanParseWhitelistReturn', help='在can的白名单中存在就不生成代码',type=int,default=0)
    parse.add_argument('-p','--power',help='是否加入电源信号',default=1,type=int)

    arg = parse.parse_args()

    isShell = not judgeCommad("-t") or judgeCommad('-s')
    if isShell:
        xlsToTxt(arg.shell)
    dealnewSig(arg.CanParseWhitelistReturn)

    if isShell:
        os.system(f"TestCaseGenerate -s {arg.shell} -p {arg.power}")
    os.system("Parser")
