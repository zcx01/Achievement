#!/bin/python
import os
from re import S
import sys
import openpyxl 
import xlrd
import argparse
from projectInI import *

from commonfun import*
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from xlsdbc import *
configFileDir = os.path.dirname(os.path.abspath(__file__))+"/../topic_def/"


def getSig(text):
    s_i = r"CANSIG_.*_g"
    sigNames = re.findall(s_i, text, re.A)
    sigNames = list(set(sigNames))
    sigs=[]
    for sigName in sigNames:
        names = str(sigName).split("_")
        sigStartIndex = 3
        sig=[]
        while(sigStartIndex < len(names)-1):
            sig.append(names[sigStartIndex])
            sigStartIndex+=1
        sigs.append('_'.join(sig))
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

def getDefine(text):
    t_i = r"\bIPC_\S+\b"
    sigNames = re.findall(t_i, text, re.A)
    sigNames = list(set(sigNames))
    return sigNames

def getTopic(lineContents,define):
    for lineContent in lineContents:
        if splitSpaceGetValueByIndex(lineContent,1) ==  define:
            return splitSpaceGetValueByIndex(lineContent,2)

def getDesc(lineContents,define):
    lineContentsSize = len(lineContents)
    for index in range(lineContentsSize):
        if splitSpaceGetValueByIndex(lineContents[index],1) ==  define:
            return str(lineContents[index-1]).replace("//",'')

def sendMqtt(topic,value):
    topic=str(topic).replace(r'"','')
    return f'mosquitto_pub -h cdc-qnx -t  \'{topic}\'  -m \''+'{'+f'\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":{value}'+'}\''

def subMqtt(topic):
    return f'mosquitto_sub -h cdc-qnx -v -t {topic}'

def lCan(sigNames):
    return f'python monitor.py -l {sigNames}'

def getModuleContent(modulePath,var):
    moduleContents = readFileLines(modulePath)
    isContentStart = False
    contents=[]
    for moduleContent in moduleContents:
        moduleContent = moduleContent.strip()
        if not isContentStart:
            isContentStart =  moduleContent.startswith(var)
        elif isContentStart:
            if 'std::make_shared<' in moduleContent or 'new ' in moduleContent:
                break
            if len(moduleContent) !=0 and not moduleContent.startswith('//'):
                contents.append(moduleContent)
    return contents
            
def initCombination(value):
    sigCombination=[]
    sigCombination.append(value)
    return sigCombination

def Combination(sigCombinations,*value):
    sigCombinationsSize = len(sigCombinations)
    #去重
    value = list(set(value))
    for valueIndex in range(len(value)-1):
        for index in range(sigCombinationsSize):
            sigCombinations.append(list(sigCombinations[index]))

    for valueIndex in range(len(value)):
        for index in range(sigCombinationsSize):
            sigCombinations[index+sigCombinationsSize*valueIndex].append(value[valueIndex])

    if len(sigCombinations) == 0:
        for valueIndex in range(len(value)):
            sigCombinations.append(initCombination(value[valueIndex])) 

def autoCaseGenerate(configPath=pyFileDir+"config.json",shellIndex=0,isAddPowerSig=True):
    jsConfig=getJScontent(configPath)
    book=xlrd.open_workbook(getKeyPath("xlsNewSigPath",jsConfig))
    sheel=book.sheet_by_index(shellIndex)
    xlsFileName=''
    for row in range(sheel.nrows):
        if row == 0 :
            continue
        caseAim=[]
        if isAddPowerSig:
            caseAim.append(f'CANSIG_S_I_{PowerSig}_g')
        caseAim.append(f'CANSIG_S_I_{sheel.cell_value(row,0)}_g')
        caseAim.append(sheel.cell_value(row,4))
        if len(xlsFileName) == 0:
            xlsFileName = sheel.cell_value(row, 2)
        isSendCan = str(sheel.cell_value(row,5)) == 'y'
        generateTest('\n'.join(caseAim),xlsFileName,configPath,'',isSendCan,row == sheel.nrows-1)


def generate(contents,defineContents,isSendCan,canmatrixSheel,sh):
    sigNames = getSig(contents)
    expectedResults=[]
    topicDefines = getDefine(contents)
    desc=''
    if len(topicDefines) > 0:
        desc =getDesc(defineContents,topicDefines[len(topicDefines)-1])
    if isSendCan:
        sigInfos = []
        if len(sigNames) == 0:
            print('没有检测到信号')
            return
        for sigName in sigNames:
            info = getSigValue(sigName,canmatrixSheel)
            if len(info.name) == 0:
                print(f' canmatrix 中没有 {sigName}信号')
                continue
            sigInfos.append(info)
        
        sigCombinations=[]
        for info in sigInfos:
            minStr = f'{info.name}:{info.min}'
            maxStr = f'{info.name}:{info.max}'
            # mid = (info.min + info.max) // 2
            # midStr = f'{info.name}:{mid}'
            Combination(sigCombinations,minStr,maxStr)

        for topicDefine in topicDefines:
            topicStr = getTopic(defineContents,topicDefine)
            expectedResults.append(subMqtt(topicStr))
        
        for sigCombination in sigCombinations:
            print(sigCombinations)
            rowContent=[]
            rowContent.append(desc)
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
            rowContent.append(desc)
            rowContent.append(expectedResult)
            rowContent.append(lCan(' -l '.join(sigNames)))
            sh.append(rowContent)

def generateTest(caseAim,xlsFileName,jsConfigPath,variable,isSendCan=False,isOPenCase=True):
    jsConfig = getJScontent(jsConfigPath)
    casePath = getKeyPath("casePath",jsConfig)+"/"+xlsFileName+'.xlsx'
    defineContents = readFileLines(getKeyPath("definefile",jsConfig)) 
    canmatrixSheel= xlrd.open_workbook(getKeyPath("canmatrix",jsConfig)).sheet_by_name("5_Matrix")

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
        sh['D1'] = '验证结果'
        sh['E1'] = '备注'
    
    if os.path.isfile(caseAim):
        if len(variable)==0:
            cppFileContets = readFileLines(caseAim) 
            for cppFileContet in cppFileContets:
                if "SignalMsg" in cppFileContet:
                    isSendCan = True
                    break
            generate('\n'.join(cppFileContet),defineContents,isSendCan,canmatrixSheel,sh)
        else:
            moduleContents = getModuleContent(caseAim,variable)
            print(moduleContents)
            for moduleContent in moduleContents:
                if len(getSig(moduleContent)) !=0:
                    isSendCan = True
            generate('\n'.join(moduleContents),defineContents,isSendCan,canmatrixSheel,sh)
    else:
        generate(caseAim,defineContents,isSendCan,canmatrixSheel,sh)

    book.save(casePath)
    print("生成完成")
    if isOPenCase:
        path = str(casePath).replace('(','\(')
        path = str(path).replace(')','\)')
        os.system("xdg-open "+ path)
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='这个脚本是生成测试的case')

    parser.add_argument('-x','--casefile',help="指定生成的case路径",default="text")
    parser.add_argument('-a','--aimfile',help='被自测的文件名',default="/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/src/signal_process/src/drive_info/machine_time.cpp")
    parser.add_argument('-v','--variable',help='moudle中的变量名',default='')
    parser.add_argument('-p','--power',help='是否加入电源信号',default=0,type=int)
    parser.add_argument('-s', '--shellIndex', help='shell的索引', default=0, type=int)
    args = parser.parse_args()
    if '-a' in sys.argv:
        generateTest(args.aimfile,args.casefile,configFileDir+"config.json",args.variable)
    else:
        autoCaseGenerate(configFileDir+"config.json",args.shellIndex,args.power)
