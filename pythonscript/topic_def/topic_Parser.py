#!/usr/bin/python
import json
import sys
import os
import xlrd
import subprocess
import argparse
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

def getFullPath(path,jsConfig):
    # path=str(path)
    if path.startswith("/"):
        return path
    else:
        projectPath=jsConfig.get("projectPath","")
        return projectPath+path

def getKeyPath(key,jsConfig):
    return getFullPath(jsConfig.get(key,""),jsConfig)

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

#写入 can_parse_whitelist 文件
def WriteCan_parse_whitelist(can_parse_whitelistPath,message,messagesig,can_parse_whitelist_return):
    if os.path.isfile(can_parse_whitelistPath):  
        if  findsignalInfile(f'{messagesig}',can_parse_whitelistPath):
            if can_parse_whitelist_return:
                print(f'{can_parse_whitelistPath} 文件存在，跳过')
                return 0
        else:
            print(f"写入 {can_parse_whitelistPath} 文件")
            can_parse_whitelist_read=open(can_parse_whitelistPath,"r")
            can_parse_whitelist_content_line=readFileLines(can_parse_whitelistPath)

            #写在现有的message后面
            behindStr(can_parse_whitelist_content_line,'message',f'{message:<18}[message]		[all]')

            if not can_parse_whitelist_read.read().endswith('\n'):
                can_parse_whitelist_content_line.append('\n')
            can_parse_whitelist_read.close()
            
            can_parse_whitelist_content_line.append(f'{messagesig:<30}       [signal]		[get, change_handle]\n')
            wirteFileDicts(can_parse_whitelistPath,can_parse_whitelist_content_line,False)
            return 2
    return 1

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
        sigs=getValueByIndex(names,0).split(',')
        for sig in sigs:
            if  not analy.sigExist(sig):
                desc=getValueByIndex(names,2)
                addDbcSigNames[sig] = desc

    print('正在写入dbc...')
    for sig in addDbcSigNames:
        print(f'{sig:<10} {addDbcSigNames[sig]}')
    if len(addDbcSigNames):
        addDbcSigName=' '.join(addDbcSigNames.keys())
        os.system(f'xlsdbc -s {addDbcSigName}')

    successWrite=[]
    failWrite=[]
    analy=Analyze(getKeyPath("dbcfile",jsConfig))
    is_Parser = False
    for text in content:
        if InvalidRow(text,alreadyText):
            continue
        alreadyText.append(text)
        text=text.replace("\t"," ")
        names=text.split(" ")
        sigs=getValueByIndex(names,0).split(",")
        isWriteCanContinue = False
        for sig in sigs:
            message=analy.getMessage_Id_BySig(sig)
            if len(message)==0:
                print(f'{sig} 对应的message不存在')
                failWrite.append(sig)
                isWriteCanContinue = True
                break
            messagesig=analy.getMessage_Id_Sig(sig)
            can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
            WriteCan = WriteCan_parse_whitelist(can_parse_whitelistPath,message,messagesig,can_parse_whitelist_return)
            if WriteCan == 0:
                isWriteCanContinue = True
                break
        
            if WriteCan == 2 and not is_Parser:
                is_Parser = True

        if isWriteCanContinue or judgeCommad("-A",names):
            continue
        
        sig = sigs[0]
        messagesig=analy.getMessage_Id_Sig(sig)
        sigType = getValueByIndex(names, 1)
        desc=getValueByIndex(names,2)
        className=getValueByIndex(names,3,"x")
        define=getValueByIndex(names,4)
        
        if len(define)==0 or define == "x":
            define = getDefine(jsConfig, desc)

        #写入 cpp 文件 #创建 .h .cpp 文件
        dataTypeStr=analy.getSigDataType(sig)
        desc=addEscape(desc)
        print(f'AutoCode {sigType} {className} {messagesig} {define} {desc} {dataTypeStr}')
        os.system(f'AutoCode {sigType} {className} {messagesig} {define} {desc} {dataTypeStr}')
        successWrite.append(sig)
    #     elif judgeCommad("-m",names):
    #         print('\
    #     //%s\n\
    #     else if (topicId == %s) \n\
	# {\n\
    #     sig=&CANSIG_%s_g;\n\
	# }'% (desc,define,messagesig))
    if is_Parser:
        os.system("Parser")
    
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
    parse.add_argument('-r','--CanParseWhitelistReturn', help='在can的白名单中存在就不生成代码',type=int,default=0)
    parse.add_argument('-p','--power',help='是否加入电源信号',default=0,type=int)
    parse.add_argument('-w','--whitelist',nargs='+')
    arg = parse.parse_args()

    if judgeCommad('-w'):
        WriteCan_parse_whitelist(arg.whitelist[0],arg.whitelist[1],arg.whitelist[2],False)
    else:
        isXls = judgeCommad('-s') or not judgeCommad('-t')
        if isXls:
            xlsToTxt(arg.shell)
        dealnewSig(arg.CanParseWhitelistReturn)

        if isXls:
            os.system(f"TestCaseGenerate -s {arg.shell} -p {arg.power}")
