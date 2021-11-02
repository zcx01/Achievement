#!/bin/python
import os
from re import S
import sys
import openpyxl 
import xlrd
import argparse

from commonfun import*
from xlsdbc import*

def getSig(text):
    e_i = r"CANSIG_.*_g"
    sigNames = re.findall(e_i, text, re.A)
    sigNames = list(set(sigNames))
    sigs=[]
    for sigName in sigNames:
        names = str(sigName).split("_")
        sig = names[len(names)-2]
        sigs.append(sig)
    return sigs

def getSigValue(sig,sheel):
    for row in range(sheel.nrows):
        sigName = str(getValue(sheel, row, 2))
        if  row == 0:
            continue
        if sigName.strip() == sig:
            sig = getSigInfo(sheel,row)
            return sig
    return SigInfo()

def getDefineStr(text):
    e_i = r"\bIPC_\S+\b"
    sigNames = re.findall(e_i, text, re.A)
    sigNames = list(set(sigNames))
    return sigNames

def getTopic(lineContents,define):
    for lineContent in lineContents:
        if splitSpaceGetValueByIndex(lineContent,1) ==  define:
            return splitSpaceGetValueByIndex(lineContent,2)

def sendMqtt(topic,value):
    return f'mosquitto_pub -h cdc-qnx -t  \'{topic}\'  -m \''+'{'+f'\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":{value}'+'}\''

def subMqtt(topic):
    return f'mosquitto_sub -h cdc-qnx -v -t \"{topic}\"'

def lCan(sigNames):
    return f'python monitor.py -l{sigNames}'

def initCombination(value):
    sigCombination=[]
    sigCombination.append(value)
    return sigCombination

def generateTest(cppFile,xlsFileName,jsConfigPath):
    jsConfig = getJScontent(jsConfigPath)

    casePath = getKeyPath("casePath",jsConfig)+"/"+xlsFileName+'.xlsx'
    defineContents = readFileLines(getKeyPath("definefile",jsConfig)) 
    sheel= xlrd.open_workbook(getKeyPath("canmatrix",jsConfig)).sheet_by_name("5_Matrix")

    # 创建一个Excel workbook 对象
    if os.path.isfile(casePath):
        book = openpyxl.load_workbook(casePath)
        sh = book['测试用例1']
    else:
        book = openpyxl.Workbook()
        sh = book.active
        sh.title = '测试用例1'
        sh['A1'] = '用例描述'
        sh['B1'] = '测试消息'
        sh['C1'] = '验证结果命令'
        sh['D1'] = '测试是否通过'
        sh['E1'] = '备注'

    cppFileContets = readFileLines(cppFile) 
    isSendCan = False
    for cppFileContet in cppFileContets:
        if "SignalMsg" in cppFileContet:
            isSendCan = True
            break
    
    with open(cppFile, "r") as cr:
        cppContents = cr.read()
        sigNames = getSig(cppContents)
        expectedResults=[]
        topicDefines = getDefineStr(cppContents)
        if isSendCan:
            sigInfos = []
            for sigName in sigNames:
                sigInfos.append(getSigValue(sigName,sheel))
            
            sigCombinations=[]
            for info in sigInfos:
                minStr = f'{info.name}:{info.min}'
                maxStr = f'{info.name}:{info.max}'
                sigCombinationsSize = len(sigCombinations)

                for index in range(sigCombinationsSize):
                    sigCombinations.append(list(sigCombinations[index]))

                for index in range(sigCombinationsSize):
                    print(index)
                    sigCombinations[index].append(minStr)

                for index in range(sigCombinationsSize):
                    sigCombinations[index+sigCombinationsSize].append(maxStr)

                if len(sigCombinations) == 0:
                    sigCombinations.append(initCombination(minStr))                 
                    sigCombinations.append(initCombination(maxStr))

            for topicDefine in topicDefines:
                topicStr = getTopic(defineContents,topicDefine)
                expectedResults.append(subMqtt(topicStr))
            
            for sigCombination in sigCombinations:
                rowContent=[]
                rowContent.append(cppFile)
                rowContent.append('\n'.join(sigCombination))
                rowContent.append('\n'.join(expectedResults))
                sh.append(rowContent)
        else:
            for topicDefine in topicDefines:
                topicStr = getTopic(defineContents,topicDefine)
                expectedResults.append(sendMqtt(topicStr,0))
                expectedResults.append(sendMqtt(topicStr,1))
            for expectedResult in expectedResults:
                rowContent=[]
                rowContent.append(cppFile)
                rowContent.append(expectedResult)
                rowContent.append(lCan(' '.join(sigNames)))
                sh.append(rowContent)
                
    book.save(casePath)
    print("生成完成")
    os.system("xdg-open "+ casePath)
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='这个脚本是生成测试的case')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-x','--casefile',help="generate case xlsx file name",default="text")
    parser.add_argument('-c','--cppfile',help='cpp file path',default="/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/src/signal_process/src/drive_info/machine_time.cpp")
    args = parser.parse_args()
    generateTest(args.cppfile,args.casefile,pyFileDir+"config.json")