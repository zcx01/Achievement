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
    sigNames = []
    for top in jsDown:
        topValue = jsDown[top]
        if type(topValue) == str:
            if topValue != top:
                sigNames.append(topValue)
        else:
            for t in topValue:
                if t != top:
                    sigNames.append(t)
    for s in jsUp:
       sigNames.append(s)

    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)
    for sig in sigNames:
        if is_chinese(sig):
            continue
        # printGreen(sig)
        sigs = re.findall(m_s,sig)
        if len(sigs) >= 3 :
            sig16= str(int(sigs[1],16))+"_".join(sigs[2:])
        if not dbc.sigExist(sig16):
            printRed(f'{sig:<50} 信号不存在')
    printGreen("分析完成")

def ToJaveCode(javaPath,configPath,down_config=None,up_config=None):
    pass

def ToConfigJson(javaPath,configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    contents = readFileLines(javaPath)
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
            if "/Set" in tContent:
                if tContent not in jsDown:
                    jsDown[tContent] = ""
            else:
                if tContent not in jsUp:
                    jsUp[tContent] = ""
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
    
