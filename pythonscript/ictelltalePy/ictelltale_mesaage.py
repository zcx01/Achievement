# coding:utf-8
#!/bin/python

import os
import sys
import argparse
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
from commonfun import*

def generateMsg(logMsg):
    topic=""
    valueStr='true'
    if len(logMsg) == 1 : 
        topic = logMsg[0]
        return ""
    elif len(logMsg) >  1 : 
        topic = logMsg[0]
        valueStr = logMsg[1]
    else: 
        return ""
    value = 1 if valueStr == 'true' else 0
    return '{\"%s\": \"Warning/WaterTemperatureHigh\", \"extension\":{\"blinkDuration\":0,\"color\":0,\"dutyCycle\":0, \
\"finalStatus\":-1,\"period\":0},\"relative\":false,\"time\":0,\"valid\":true,\"value\":%i}' % (topic,value)

def generateMsgFile(logFile,generateFile,configPath=''):
    if len(configPath) == 0:
        configPath = pyFileDir+"config.json"
        jsConfig=getJScontent(configPath)
        common=jsConfig["common"]
        configjsonPath=common["configjsonPath"]
    else:
        configjsonPath = configPath
    jsTelltale=getJScontent(configjsonPath,encoding='UTF-8')
    telltaleTopics=[]
    for topic in jsTelltale:
        telltaleTopics.append(topic)
    searchStr = "|".join(telltaleTopics)

    logContents = readFileLines(logFile)
    telltaleMsgs = []
    for logContent in logContents:
        lineContents = re.findall(searchStr,logContent,re.A)
        if len(lineContents) > 0:
            logSearchTopic = f'{lineContents[0]}|false|true'
            logMsg = re.findall(logSearchTopic,logContent,re.A)
            telltaleMsg = generateMsg(logMsg)
            if len(telltaleMsg) != 0:
                print(f'{lineContents[0]:<20}{telltaleMsg}')
                telltaleMsgs.append(telltaleMsg)
    wirteFileDicts(generateFile,telltaleMsgs)
            
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        通过log生成指示灯消息
        ''')
    parse.add_argument('-l', '--logFile', help='log文件',type=str)
    parse.add_argument('-g', '--generateFile', help='生成信息的文件',type=str)
    parse.add_argument('-c', '--configPath', help='生成信息的文件',type=str,default='',nargs='?')
    arg = parse.parse_args()
    if '-l' in sys.argv and '-g' in sys.argv:
        generateMsgFile(arg.logFile,arg.generateFile,arg.configPath)
