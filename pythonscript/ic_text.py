#!/bin/python3
import os
import sys
import argparse
from commonfun import *
import openpyxl 
from xml.dom.minidom import *
import xlrd
from xlrd.book import Book
from xlrd.sheet import Sheet

SOUCRELANGUAGESUFFIX="zh_CN.ts"
ORILANGUAGESUFFIXS={"en_US.ts":"F","th_TH.ts":"G"} 
SHELLNAME="IC"
class translateConent(object):
    def __init__(self) -> None:
        self.path = ""
        self.sourceKey=""
        self.content=""
        self.exisTranslates=[]
        self.translateContent=""

    def getList(self):
        xlsContent = []
        xlsContent.append(self.path)
        xlsContent.append(self.sourceKey)
        xlsContent.append(self.content)
        for exisTranslate in self.exisTranslates:
            xlsContent.append(exisTranslate)
        return xlsContent
    
def getTextCout(fileName):
    jsContents = getJScontent(fileName)
    count=0
    for top in jsContents:
        for grade in jsContents[top]:
            if isNumber(grade) :
                print(EesyStr.removeAll(jsContents[top][grade],'\n'))
                count+=1

def joint(f,t):
    return f'{f}__{t}'

def translatesByTs(dirpath,oriName,translateConents):
    translatePath_file = f'{dirpath}/{oriName}'
    domTree = parse(translatePath_file)
    assert isinstance(domTree,Document)
    rootNode = domTree.documentElement
    assert isinstance(rootNode,Element)
    contexts = rootNode.getElementsByTagName("context")
    for context in contexts:
        assert isinstance(context,Element)
        contentFile = context.getElementsByTagName("name")[0].childNodes[0].data
        messageNodes = context.getElementsByTagName("message")
        for messageNode in messageNodes:
            assert isinstance(messageNode,Element)
            try:
                source = messageNode.getElementsByTagName("source")[0].childNodes[0].data
            except:
                continue
            try:
                content= messageNode.getElementsByTagName("translation")[0].childNodes[0].data
            except:
                content = source
            xlsContent = translateConent()
            xlsContent.path = joint(oriName,contentFile)
            xlsContent.sourceKey = source
            xlsContent.content = content
            translateConents[source] = xlsContent

def coverXls(translatePath,jsonPath,outPath):
    # 创建一个Excel workbook 对象
    # if os.path.isfile(outPath):
    #     book = openpyxl.load_workbook(outPath)
    #     sh = book['English']
    # else:
    book = openpyxl.Workbook()
    sh = book.active
    sh.title = SHELLNAME
    sh['A1'] = '文件名'
    sh['B1'] = '源key'
    sh['C1'] = '内容'
    count = 3
    exisTranslates = ORILANGUAGESUFFIXS.keys()
    for exisTranslate in exisTranslates:
        sh[f'{XlsIntToChar(count)}1'] = exisTranslate
        count+=1
    sh[f'{XlsIntToChar(count)}1'] = '翻译结果'
    count+=1
    sh[f'{XlsIntToChar(count)}1'] = '备注'

    for (dirpath,dirnames,filenames) in os.walk(translatePath):
        for oriName in filenames:
            if SOUCRELANGUAGESUFFIX in oriName:
                soucreLanguages={}
                translatesByTs(dirpath,oriName,soucreLanguages)
                existranslatelanguages = {}

                for exisTranslate in exisTranslates:
                    existransName = oriName.replace(SOUCRELANGUAGESUFFIX,exisTranslate)
                    existranslatelanguage = {}
                    translatesByTs(dirpath,existransName,existranslatelanguage)
                    existranslatelanguages[exisTranslate] = existranslatelanguage

                count = 0
                for soucreLanguage in soucreLanguages:
                    xlsContent=soucreLanguages[soucreLanguage]
                    assert isinstance(xlsContent,translateConent)
                    for exisTranslate in exisTranslates:
                        try:
                            xlsContent.exisTranslates.append(existranslatelanguages[exisTranslate][xlsContent.sourceKey].content)
                        except:
                            # printYellow(f"{xlsContent.sourceKey} 不存在 {removeSuffix(exisTranslate)}")
                            pass
                    sh.append(xlsContent.getList())
                    count+=1
                print(f"检测 {dirpath}/{oriName} 文件 一共有 {count}")

    try:
        jsContents = getJScontent(jsonPath)
        count=0
        for top in jsContents:
            for grade in jsContents[top]:
                if isNumber(grade) :
                    xlsContent = translateConent()
                    xlsContent.path = os.path.basename(jsonPath)
                    xlsContent.sourceKey = joint(top,grade)          
                    xlsContent.content = jsContents[top][grade][removeSuffix(SOUCRELANGUAGESUFFIX)]
                    for exisTranslate in exisTranslates:
                        try:
                            xlsContent.exisTranslates.append(jsContents[top][grade][removeSuffix(exisTranslate)])
                        except:
                            printYellow(f"{top} 不存在 {removeSuffix(exisTranslate)}")
                    sh.append(xlsContent.getList())
                    count+=1
        print(f"检测 {jsonPath} 文件 一共有{count}")
    except:
        printRed(f"{jsonPath} 异常")
        pass
    book.save(outPath)
    printGreen("检测完成")

def getValue(src, row, col):
    return src.cell_value(row,XlsCharToInt(col))

def removeSuffix(conetnt):
    return conetnt.replace(".ts","")
    
def xlsCover(translatePath,jsonPath,input):
    book = xlrd.open_workbook(input)
    assert isinstance(book, Book)

    sheel = book.sheet_by_name(SHELLNAME)
    assert isinstance(sheel, Sheet)

    for oriLanguageSuffix,oriLanguageSuffixCol in ORILANGUAGESUFFIXS.items():
        tsContent={}
        jsContent={}
        printGreen(f"正在更新 {oriLanguageSuffix} ...")
        for row in range(sheel.nrows):
            xlsContent = translateConent()
            xlsContent.path = getValue(sheel,row,"A")
            xlsContent.sourceKey = getValue(sheel,row,"B")
            xlsContent.content = getValue(sheel,row,"C")
            xlsContent.translateContent = getValue(sheel,row,"D")
            assert isinstance(xlsContent.translateContent,str)
            newTranslateContent = getValue(sheel,row,oriLanguageSuffixCol)
            if len(newTranslateContent)!=0:
                xlsContent.translateContent = newTranslateContent
            if len(xlsContent.translateContent.split('\n')) > 1:
                pass
            else:
                xlsContent.translateContent = xlsContent.translateContent.replace(',',',\n')
            if ".json" in xlsContent.path:
                jsContent[joint(xlsContent.path,xlsContent.sourceKey)] = xlsContent
            else:
                tsContent[joint(xlsContent.path,xlsContent.sourceKey)] = xlsContent
        
        for (dirpath,dirnames,filenames) in os.walk(translatePath):
            for oriName in filenames:
                if SOUCRELANGUAGESUFFIX in oriName:
                    translatePath_file = f'{dirpath}/{oriName}'
                    ori_translatePath_file = translatePath_file.replace(SOUCRELANGUAGESUFFIX,oriLanguageSuffix)
                    if not os.path.isfile(ori_translatePath_file):
                        os.system(f"cp {translatePath_file} {ori_translatePath_file}")
        
        for (dirpath,dirnames,filenames) in os.walk(translatePath):
            for oriName in filenames:
                if oriLanguageSuffix in oriName:
                    print(f"更新 {translatePath_file} 文件")
                    translatePath_file = f'{dirpath}/{oriName}'
                    domTree = parse(translatePath_file)
                    assert isinstance(domTree,Document)
                    rootNode = domTree.documentElement
                    assert isinstance(rootNode,Element)
                    contexts = rootNode.getElementsByTagName("context")
                    for context in contexts:
                        assert isinstance(context,Element)
                        contentFile = context.getElementsByTagName("name")[0].childNodes[0].data
                        messageNodes = context.getElementsByTagName("message")
                        for messageNode in messageNodes:
                            assert isinstance(messageNode,Element)
                            path = joint(oriName.replace(oriLanguageSuffix,SOUCRELANGUAGESUFFIX),contentFile)
                            try:
                                source = messageNode.getElementsByTagName("source")[0].childNodes[0].data
                            except:
                                continue
                            path = joint(path,source)
                            if path in tsContent:
                                if len(messageNode.getElementsByTagName("translation")[0].childNodes) == 0:
                                    phone_text_value = domTree.createTextNode(tsContent[path].translateContent)
                                    messageNode.getElementsByTagName("translation")[0].appendChild(phone_text_value)
                                else:
                                    try:
                                        messageNode.getElementsByTagName("translation")[0].childNodes[0].data = tsContent[path].translateContent
                                    except:
                                        continue
                    with open(translatePath_file, 'w') as f:
                        # 缩进 - 换行 - 编码
                        domTree.writexml(f,encoding='utf-8')

        
        try:
            aimJsContents = getJScontent(jsonPath)
            print(f"更新 {jsonPath} 文件")
            for top in aimJsContents:
                for grade in aimJsContents[top]:
                    if isNumber(grade) :
                        path = os.path.basename(jsonPath)
                        source = joint(top,grade)  
                        path = joint(path,source)
                        if path in jsContent:     
                            aimJsContents[top][grade][removeSuffix(oriLanguageSuffix)] = jsContent[path].translateContent
            writeJs(jsonPath,aimJsContents)
        except:
            pass
    printGreen("更新完成")

def translationText(fileName):
    jsContents = getJScontent(fileName)
    for top in jsContents:
        for grade in jsContents[top]:
            if isNumber(grade) :
                tmp={}
                tmp[removeSuffix(SOUCRELANGUAGESUFFIX)] = jsContents[top][grade]
                jsContents[top][grade] =tmp
    writeJs(fileName,jsContents)
    printGreen("转化完成")

#./ic_text.py -t /home/chengxiongzhu/Works/Repos/changan_c385/qt/ic_qt/resources/translate -j /home/chengxiongzhu/Works/Repos/changan_c385/qt/ic_qt/resources/config/icwarning_config.json -o ic-out.xlsx
if __name__ == "__main__":
    aparse = argparse.ArgumentParser(description='python的脚本模板')
    aparse.add_argument('-t','--translatePath',help='翻译文件所在目录',type=str)
    aparse.add_argument('-j','--json',help='报警文字配置文件',type=str,nargs="?",default="")
    aparse.add_argument('-o','--outPath',help='生成xls文件路径',type=str)
    aparse.add_argument('-i','--input',help='输入xls文件路径',type=str)
    arg = aparse.parse_args()

    if len(sys.argv) == 1:
        getTextCout(arg.fileName)
    elif "-o" in sys.argv:
        coverXls(arg.translatePath,arg.json,arg.outPath)
    elif "-i" in sys.argv:
        xlsCover(arg.translatePath,arg.json,arg.input)
    elif "-j" in sys.argv:
        translationText(arg.json)
