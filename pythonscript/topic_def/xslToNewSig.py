#!/usr/bin/python
import sys
import os
import xlrd
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
from commonfun import *
import openpyxl 
import argparse

def sigExist(sheel,row,col,CallFun):
    sig = str(getValue(CallFun,sheel,row,col))
    relation=''
    if ',' in sig:
        sigs = sig.split(',')
        sig = sigs[0]
        del sigs[0]
        relation = ','.join(sigs)
    exist = len(sig)>3 and sig!='None'
    if not exist:
        print(row+1,chr(col+65),'信号不存在')
    return sig,exist,relation
 
def getDefineByFile(deContent,topic):
    for lineContent in deContent:
        if not lineContent.startswith("#define"):
            continue
        topicStr = splitSpaceGetValueByIndex(lineContent,2)
        topicStr = topicStr.replace('\"','')
        if  topicStr ==  topic:
            return splitSpaceGetValueByIndex(lineContent,1)
    print(f'{topic}没有对应的topic，请重新生成topic')
    return ''

def getDefineBySelf(topic):
    topic = topic.replace('/','')
    define = ''
    for t in topic:
        t = str(t)
        if t.isupper():
            define+='_'+t
        else:
            define+=t.upper()
    return 'IPC'+ define

def generateByXls(xlsPath,startRow,endRow,down,up):
    book=xlrd.open_workbook(xlsPath)
    sheel=book.sheet_by_index(0)
    generate(sheel,startRow,endRow,down,up,xlsVaule,sheel.nrows)

def xlsVaule(sheel,row,col):
    return sheel.cell_value(row,col)

def getValue(CallFun,sheel,row,col):
    try:
        return CallFun(sheel,row,col)
    except:
        # print(row+1,chr(col+65),'值不存在')
        return

def  getTopicByXls(CallFun,sheel,row):
    topics = []
    try:
        col=0
        findRow = row
        COLNUM=3
        while col < COLNUM:
            topic = CallFun(sheel,findRow,col)
            if col == COLNUM-1 and len(topic) == 0:
                break
            if len(topic) != 0:
                #去除第一个topic中的/
                if len(topics) == 0:
                    topic = EesyStr.removeAt(topic,len(topic)-1)
                topics.append(topic)
                findRow = row
                col+=1
            else:
                findRow-=1
    except:
        if len(topics):
            print(row+1,'值不存在')
    topic = '/'.join(topics)
    return topic+'/Set',topic

def getComments(CallFun,sheel,startRow):
    comment = getValue(CallFun,sheel,startRow,5)
    statusStr='状态'
    commentStatus=comment
    if statusStr not in comment:
        commentStatus=comment+statusStr
    return comment,commentStatus

def getTopicAndDefineByRow(sheel,CallFun,rows):
    pubTopic=[]
    subTopic=[]
    descs=[]
    for row in rows:
        row-=1
        commentSet, comment = getComments(CallFun, sheel, row)
        topicStrSet, topicStr = getTopicByXls(CallFun, sheel, row)
        defineStrSet = getDefineBySelf(topicStrSet)
        defineStr = getDefineBySelf(topicStr)
        print(f'{row:<5}{topicStr:<50}{defineStr:<50}{comment}')
        print(f'{row:<5}{topicStrSet:<50}{defineStrSet:<50}{commentSet:}')
        subTopic.append(topicStr)
        pubTopic.append(topicStrSet)
        descs.append(comment)
    
    try:
        while True:
            m = input('是否生成消息(y/n/h)')
            if  m == 'n':
                return
            if  m == 'h':
                for row in range(len(subTopic)):
                    print(f'{row:<5}{subTopic[row]:<50}{descs[row]}')
            rowIndex = input('输入索引')
            for row in range(len(subTopic)):
                if row == int(rowIndex):
                    print(subMqtt(f'\'{subTopic[row]}\''))
                    print(sendMqtt(f'{pubTopic[row]}',1))
    except:
        pass


def getTopicAndDefineByDesc(sheel,CallFun,desc,rows):
    findRows=[]
    for row in range(rows):
        try:
            commentSet, comment = getComments(CallFun, sheel, row)
            if desc in commentSet or desc in comment:
                findRows.append(row+1)
        except:
            pass
    getTopicAndDefineByRow(sheel,CallFun,findRows)

def generate(sheel,startRow,endRow,down,up,CallFun,rows):
    startRow-=1
    endRow-=1
    if startRow >= rows or endRow >= rows or startRow > endRow:
        print('输入的行号不合法')
        return
    jsConfig = getJScontent(pyFileDir+"config.json")
    defineContents = readFileLines(getKeyPath("definefile",jsConfig)) 
    xlsNewSigPath = getKeyPath("xlsNewSigPath",jsConfig)
    book = openpyxl.Workbook()
    sh = book.active
    rowContent=[]

    while(startRow <= endRow):
        commentSet,comment =  getComments(CallFun,sheel,startRow)
        topicStrSet, topicStr = getTopicByXls(CallFun, sheel, startRow)
        className = getValue(CallFun,sheel,startRow,1)+ getValue(CallFun,sheel,startRow,2)
        sig,isExist,relation = sigExist(sheel,startRow,7,CallFun)
        if isExist:
            rowContent=[]
            topicDefine = getDefineByFile(defineContents,topicStrSet)
            rowContent.append(sig)
            rowContent.append(down)
            rowContent.append(commentSet)
            rowContent.append(className)
            rowContent.append(topicDefine)
            rowContent.append('n')
            rowContent.append(relation)
            print(rowContent)
            sh.append(rowContent)

        sig,isExist,relation = sigExist(sheel,startRow,8,CallFun)
        if isExist:
            rowContent=[]
            topicDefine = getDefineByFile(defineContents,topicStr)
            rowContent.append(sig)
            rowContent.append(up)
            rowContent.append(comment)
            rowContent.append(className+'Status')
            rowContent.append(topicDefine)
            rowContent.append('y')
            rowContent.append(relation)
            print(rowContent)
            sh.append(rowContent)
        startRow+=1

    saveFileName=xlsNewSigPath+'.xlsx'
    book.save(saveFileName)
    book.close()
    print("生成完成")
    os.system(f'xdg-open {saveFileName}')
 
if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='这个是通过topic表格生成生成newSig表格')
    parse.add_argument('-d','--down',help='下行信号的类型',default="vehctrl")
    parse.add_argument('-u','--up',help='上行信号的类型',default="vehctrl_status")
    parse.add_argument('-x','--xlsPath',help='topic表格路径')
    parse.add_argument('-s','--startRow',help='开始的行号',type=int)
    parse.add_argument('-e','--endRow',help='结束的行号',type=int)
    arg = parse.parse_args()
    generateByXls(arg.xlsPath,arg.startRow,arg.endRow,arg.down,arg.up)
