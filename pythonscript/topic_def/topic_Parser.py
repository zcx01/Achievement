#!/usr/bin/python
import json
import sys
import os
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
        if sig not in jsSig:
            jsSig[sig]={"desc":desc}
            print(f'写入 {jsConfigPath} 文件')
            writeJs(jsConfigPath,jsSig)
        else:
            if isContinue=="y" or isContinue=="n":
                print(f'{sig} 已经存在,是否强执行(y-是，n-否，dy-总是，dn-总否)？')
                isContinue=input()
            if "n" in isContinue:
                continue

        #写入 can_parse_whitelist 文件
        can_parse_whitelistPath=jsConfig["can_parse_whitelist"]
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
        print(f'AutoCode {sigType} {className} {message}__{sig} {line} {desc} {dataTypeStr}')
        if len(sys.argv) >1 and sys.argv[1] == "-A":
            continue
        desc=addEscape(desc)
        os.system(f'AutoCode {sigType} {className} {message}__{sig} {line} {desc} {dataTypeStr}')
    os.system("Parser")

if __name__ == "__main__":
    dealnewSig()

