#!/usr/bin/python
import sys
import os
import xlrd
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
from commonfun import *
import openpyxl 
import argparse

SETSTR='/Set'

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
 
#返回 define topic desc
def analyDefine(deContent,contents,spaceIndex):
    desc=''
    defines=[]
    topics=[]
    descs=[]
    for lineContent in deContent:
        if not lineContent.startswith("#define"):
            desc=lineContent
            continue
        spaceStr = splitSpaceGetValueByIndex(lineContent,spaceIndex)
        spaceStr = spaceStr.replace('\"','')
        if  spaceStr in  contents:
            define=splitSpaceGetValueByIndex(lineContent, 1)
            topic = splitSpaceGetValueByIndex(lineContent, 2)
            if len(contents) == 0:
                return define , topic , desc
            else:
                defines.append(define)
                topics.append(topic)
                descs.append(desc)
    if len(define) == 0:
        print(f'没有找到 {contents} ')
    return defines,topics,descs

def getDefineByFile(deContent,topic):
    topiclist=[]
    topiclist.append(topic)
    define,topic,dec = analyDefine(deContent,topiclist,2)
    return define[0]

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

def getTopicByXls(CallFun,sheel,row):
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
    return topic+SETSTR,topic

def getComments(CallFun,sheel,startRow):
    comment = getValue(CallFun,sheel,startRow,5)
    statusStr='状态'
    commentStatus=comment
    if statusStr not in comment:
        commentStatus=comment+statusStr
    return comment,commentStatus

def getTopicAndDefineByRow(sheel,CallFun,rows):
    subTopic=[]
    pubTopic=[]
    descs=[]
    for row in rows:
        row-=1
        commentSet, comment = getComments(CallFun, sheel, row)
        topicStrSet, topicStr = getTopicByXls(CallFun, sheel, row)
        defineStrSet = getDefineBySelf(topicStrSet)
        defineStr = getDefineBySelf(topicStr)
        print(f'{row:<5}{topicStr:<50}{defineStr:<70}{comment}')
        print(f'{row:<5}{topicStrSet:<50}{defineStrSet:<70}{commentSet:}')
        subTopic.append(topicStr)
        pubTopic.append(topicStrSet)
        descs.append(comment)

    interactiveTopic(subTopic,pubTopic,descs)

def interactiveTopic(subTopic,pubTopic,descs,isTip=True):
    try:
        for row in range(len(subTopic)):
            print(f'{row:<5}{subTopic[row]:<50}{descs[row]}')
        rowIndex = -1
        while True:
            if isTip:
                m = input('是否生成消息(y/n/h)')
                if  m == 'n':return
                rowIndex = input('输入索引')
            for row in range(len(subTopic)):
                if row == int(rowIndex) or rowIndex == -1:
                    if subTopic[row].endswith(SETSTR):
                        print(sendMqtt(f'{pubTopic[row]}',1))
                    else:
                        print(subMqtt(f'\'{subTopic[row]}\''))
                    if row < len(pubTopic):
                        print(sendMqtt(f'{pubTopic[row]}',1))
            if not isTip:return
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


def getDefineByContent(defineSets,content):
    defines =  re.findall(d_t, content, re.A)
    for define in defines:
        assert isinstance(define,str)
        defineSets.add(define)
        return defineSets

def getDefineBySig(sigName,srcPath):
    defineSets=set()
    className = ''
    for (dirpath,dirnames,filenames) in os.walk(srcPath):
        for fileName in filenames:
            if os.path.splitext(fileName)[1] == '.cpp': 
                filePath = dirpath+'/'+fileName
                contents = readFileLines(filePath)
                for content in contents:
                    classNames = getClassNames(content)
                    if len(classNames) != 0:
                        className = classNames[0]
                    if sigName in content:
                        getDefineByContent(defineSets,content)
                        if len(defineSets) != 0:
                            return defineSets
   
                with open(filePath, "r") as cr:
                    content = cr.read()
                    if sigName in content:
                        getDefineByContent(defineSets,content)

    if len(defineSets) == 0 and len(className) !=0:
        for (dirpath,dirnames,filenames) in os.walk(srcPath):
            for fileName in filenames:
                if os.path.splitext(fileName)[1] == '.cpp': 
                    filePath = dirpath+'/'+fileName
                    contents = readFileLines(filePath)
                    for contentIndex in range(len(contents)):
                        classNames = getClassNames(contents[contentIndex])
                        if len(classNames) != 0:
                            if classNames[0] == className:
                                while contentIndex < len(content):
                                    getDefineByContent(defineSets,contents[contentIndex])
                                    contentIndex+=1
                                    classNames = getClassNames(contents[contentIndex])
                                    if len(classNames) != 0:
                                         return defineSets
                        contentIndex+=1

    return defineSets

def getTopicAndDefineBySig(sigName):
    jsConfig = getJScontent(pyFileDir+"config.json")
    defineContents = readFileLines(getKeyPath("definefile",jsConfig)) 
    srcPath = getKeyPath("srcPath",jsConfig)
    topics=[]
    defineSets=getDefineBySig(sigName,srcPath)
    if len(defineSets) ==0:
        print(f'没有找到')
        return
    defines,topics,decs = analyDefine(defineContents,defineSets,1)     
    interactiveTopic(topics,[],decs,False)


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

# getTopicAndDefineBySig('ItmsAutoDefrstDefogFctSts')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='这个是通过topic表格生成生成newSig表格')
    parse.add_argument('-d','--down',help='下行信号的类型',default="vehctrl")
    parse.add_argument('-u','--up',help='上行信号的类型',default="vehctrl_status")
    parse.add_argument('-x','--xlsPath',help='topic表格路径')
    parse.add_argument('-s','--startRow',help='开始的行号',type=int)
    parse.add_argument('-e','--endRow',help='结束的行号',type=int)
    parse.add_argument('-f','--findSigName',help='信号名称',type=str)
    arg = parse.parse_args()
    if '-f' in sys.argv:
        getTopicAndDefineBySig(arg.findSigName)
    else:
        generateByXls(arg.xlsPath,arg.startRow,arg.endRow,arg.down,arg.up)
