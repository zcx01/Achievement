#!/usr/bin/python
import os
import string
import argparse
from commonfun import*
from AnalyzeCan.Analyzedbc import *

def CheckSigName(configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    if down_config == None:
        down_config= getKeyPath("down",jsConfig)
    if up_config == None:
        up_config = getKeyPath('up',jsConfig)
    jsDown = getJScontent(down_config)
    jsUp   = getJScontent(up_config)
    sigNames = {}
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)

    for top in jsDown:
        topValue = jsDown[top]
        if type(topValue) == str:
            if topValue != top:
                sigNames[topValue] = 0
        else:
            for t in topValue:
                if t != top:
                    sigNames[t] = 0
    for s in jsUp:
       sigNames[s] = 1

    for sig in sigNames:
        if is_chinese(sig):
            continue
        dbcSigName,Sender,isChanged = configConverdbc(sig,dbc)
        if Sender == None or not isChanged:
            continue
        if  sigNames[sig] == 1: 
            addConfigDict(jsUp,dbcSigName,sig)       
        if  sigNames[sig] == 0: 
            addConfigDict(jsDown,sig,dbcSigName)
    printGreen("分析完成")

def ToJaveCode(javaPath,configPath,down_config=None,up_config=None):
    pass

def configConverdbc(sig,dbc):
    assert isinstance(dbc,Analyze)
    assert isinstance(sig,str)
    sigs = re.findall(m_s,sig)
    dbcSig = None
    if len(sigs) >= 3 :
        sig16= str(int(sigs[1],16))+"_".join(sigs[2:])
        prefix= f"{sigs[0]}_{sigs[1]}"
        dbcSig = dbc.getSig(sig16)
        if dbcSig == None:
            printRed(f'{sig:<50}  没有对应的信号')
        elif dbcSig.getMessage_Name() != prefix:
            printYellow(f'{sig:<50} {prefix} {dbcSig.getMessage_Name()} message名称错误，即将替换')
            return sig.replace(prefix,dbcSig.getMessage_Name()),dbcSig.Sender,True
    else:
        dbcSig = dbc.getSig(sig)
        if dbcSig == None:
            printRed(f'{sig:<50}  信号格式错误')
    return sig, None if dbcSig == None else dbcSig.Sender,False

def addConfigDict(js,key,value):
    if value in js: del js[value] 
    js[key] = value

def ToConfigJson(javaPath,configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    contents = readFileLines(javaPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)

    if down_config == None:
        down_config = getKeyPath("down", jsConfig)
    if up_config == None:
        up_config = getKeyPath('up', jsConfig)

    jsDown = getJScontent(down_config)
    jsUp = getJScontent(up_config)
    for content in contents:
        tContents = re.findall(r'topic = ".*"',content)
        if len(tContents) != 0:
            tContent = re.findall(r'".*"',tContents[0])[0]
            assert isinstance(tContent,str)
            tContent=tContent.replace('\"',"")
            dbcSigName,Sender,isChanged = configConverdbc(tContent,dbc)
            down_topic = tContent+"/Set"
            if Sender == None:
                continue
            if Sender not in local_machine_Sender: 
                addConfigDict(jsUp,dbcSigName,tContent)       
                # if down_topic in jsDown :del jsDown[down_topic]   
            if Sender in local_machine_Sender: 
                addConfigDict(jsDown,down_topic,dbcSigName)
                # if dbcSigName in jsUp: del jsUp[dbcSigName]

    writeJs(down_config,jsDown)
    writeJs(up_config,jsUp)

if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        检查配置文件是否正确
        从配置文件生成java代码
        从java生成配置文件
        ''')
    parse.add_argument('-j', '--ToJave', help='生成json代码', nargs='?', type=str)
    parse.add_argument('-c', '--ToConfig', help='从java代码生成配置文件',type=str)
    arg = parse.parse_args()

    if '-j' in sys.argv:
        ToJaveCode(arg.ToJave,pyFileDir+"config.json")
    elif '-c' in sys.argv:
        ToConfigJson(arg.ToConfig,pyFileDir+"config.json")
    else:
        CheckSigName(pyFileDir+"config.json")
    
