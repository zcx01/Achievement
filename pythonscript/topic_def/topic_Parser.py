#!/usr/bin/python
import json
import sys
import os
import xlrd
from Analyzedbc import Analyze, DataType

pyFileDir = os.path.dirname(os.path.abspath(__file__))

def get_upper_case_name(text):
    lst = []
    last_char = ''
    for index, char in enumerate(text):
        if char.isupper() and index != 0 and last_char.islower():
            lst.append("_")
        lst.append(char)
        last_char = char
    result = "".join(lst).upper()
    return result

def getJScontent(configJson):
    with open(configJson, "r") as cr:
        return json.load(cr)

def writeJs(configJson,jsContent):
    cr = open(configJson, "w")
    cr.write(json.dumps(jsContent,ensure_ascii=False,indent=4))
    cr.close()

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
                writeJs(pyFileDir+"/config.json",jsConfig)

def getSigType(jsConfig,msg):
    return jsConfig.get(msg,{}).get("type","")

def getSigSuffx(jsConfig,msg):
    return jsConfig.get(msg,{}).get("suffx","")

def getClassName(sigName):
    print(f'请输入{sigName}的类名：')
    className=""
    while True:
        className=input()
        if len(className) !=0 :
            return className
        else:
            print("类名不能为空！")

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

def dealnewSig():
    jsConfig=getJScontent(pyFileDir+"/config.json")
    analy=Analyze(jsConfig["dbcfile"])

    newSigFile=open(jsConfig["newSig"],"r")
    content=newSigFile.read().splitlines()
    newSigFile.close()
    isContinue = "n"
    for text in content:
        if text.strip().startswith("#") or len(text) == 0:
            continue
        text=text.replace("\t"," ")
        names=text.split(" ")
        sig=names[0]

        #通过 CAN matrix 表格获取中文描述
        if len(names) < 2 or len(names[1]) == 0 or names[1] == "d":
            desc=getSignalDescInexcel(sig,jsConfig["canmatrix"])
        else:
            desc=names[1]

        try:
            className=names[2]
        except:
            className="x"

        messagesuffix="."
        try:
            messagesuffix+=names[3]
        except:
            messagesuffix=""

        message=analy.getMessageBySig(sig)
        if len(message)==0:
            print(f'{sig}对应的message不存在')
            continue
        jsConfigPath=getSigJson(jsConfig,message+messagesuffix,sig)
        jsSig=getJScontent(jsConfigPath)
        if sig in jsSig:
            if isContinue=="y" or isContinue=="n":
                print(f'{sig} 已经存在,是否强执行(y-是，n-否，dy-总是，dn-总否)？')
                isContinue=input()
            if "n" in isContinue:
                continue
            
            #写入 json 文件const
            jsSig[sig]["desc"]=desc
        else:
            jsSig[sig]={"desc":desc}

        print(f'写入 {jsConfigPath} 文件')
        writeJs(jsConfigPath,jsSig)

        #写入 can_parse_whitelist 文件
        can_parse_whitelistPath=jsConfig["can_parse_whitelist"]
        if judgeCommad("-bc",names) or findsignalInfile(f'{message}__{sig}',can_parse_whitelistPath):
            pass
        else:
            print(f"写入 {can_parse_whitelistPath} 文件")
            can_parse_whitelist=open(can_parse_whitelistPath,"a")
            can_parse_whitelist.write(f'{message}__{sig:<30}       [signal]		[get, change_handle]\n')
            can_parse_whitelist.close()

        suffx= getSigSuffx(jsConfig,message+messagesuffix)
        line = 'TOPIC_' + get_upper_case_name(suffx) + '_' + get_upper_case_name(sig)

        #写入 cpp 文件 #创建 .h .cpp 文件
        sigType=getSigType(jsConfig,message+messagesuffix)
        dataType=analy.getSigDataType(sig)
        dataTypeStr="int"
        if dataType == DataType.VFLOAT:
            dataTypeStr="float"
        messagesig=message+"__"+sig
        if judgeCommad("-A",names):
            continue
        elif judgeCommad("-m",names):
            print('\
        //%s\n\
        else if (topicId == %s) \n\
	{\n\
        sig=&CANSIG_%s_g;\n\
	}'% (desc,line,messagesig))
        else:
            desc=addEscape(desc)
            print(f'AutoCode {sigType} {className} {messagesig} {line} {desc} {dataTypeStr}')
            os.system(f'AutoCode {sigType} {className} {messagesig} {line} {desc} {dataTypeStr}')
    os.system("Parser")

if __name__ == "__main__":
    dealnewSig()

