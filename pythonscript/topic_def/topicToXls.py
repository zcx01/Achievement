#!/usr/bin/python

#
import sys
import os
import xlrd
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir+"..")
from commonfun import *
from Analyzedbc import Analyze, DataType
import openpyxl 
import argparse

def sigExist(sheel,row,col):
    sig = str(sheel.cell_value(row,col))
    return sig,len(sig)>3

def getTopic(deContent,topic):
    for lineContent in deContent:
        if not lineContent.startswith("#define"):
            continue
        topicStr = splitSpaceGetValueByIndex(lineContent,2)
        topicStr = topicStr.replace('\"','')

        #去除第一个
        topicStrS = topicStr.split('/')
        del topicStrS[0]
        topicStr = '/'.join(topicStrS)
        if  topicStr ==  topic:
            return splitSpaceGetValueByIndex(lineContent,1)

    print(f'{topic}没有对应的topic，请重新生成topic')
    return ''

def generate(xlsPath,startRow,endRow):
    startRow+=1
    endRow+=1
    book=xlrd.open_workbook(xlsPath)
    sheel=book.sheet_by_index(0)
    if startRow >= sheel.nrows or endRow >= sheel.nrows or startRow > endRow:
        print('输入的行号不合法')
        return
    jsConfig = getJScontent(pyFileDir+"config.json")
    defineContents = readFileLines(getKeyPath("definefile",jsConfig)) 
    # print(getKeyPath("definefile",jsConfig),defineContents)
    # xlsNewSigPath = getKeyPath("xlsNewSigPath",jsConfig)
    # book = openpyxl.load_workbook(xlsNewSigPath)
    # try:
    #     sh = book[book.sheetnames[0]]
    # except:
    #     print('sheel名称错误')

    while(startRow <= endRow):
        rowContent=[]
        comments =  sheel.cell_value(startRow,5)
        className = sheel.cell_value(startRow,1)+ sheel.cell_value(startRow,2)
        topicStr = sheel.cell_value(startRow,1)
        if len(str(sheel.cell_value(startRow,2))) !=0:
            topicStr+='/'+sheel.cell_value(startRow,2)
        sig,isExist = sigExist(sheel,startRow,7)
        if isExist:
            topicSetStr =topicStr+"/Set"
            topicDefine = getTopic(defineContents,topicSetStr)
            rowContent.append(sig)
            rowContent.append('drive_assist')
            rowContent.append(comments)
            rowContent.append(className)
            rowContent.append(topicDefine)
            rowContent.append('')
            rowContent.append('')
            rowContent.append('n')
            print(rowContent)
            #sh.append(rowContent)
        rowContent.clear()
        sig,isExist = sigExist(sheel,startRow,8)
        if isExist:
            topicDefine = getTopic(defineContents,topicStr)
            rowContent.append(sig)
            rowContent.append('drive_assist_sts')
            rowContent.append(comments+'状态')
            rowContent.append(className+'Status')
            rowContent.append(topicDefine)
            rowContent.append('')
            rowContent.append('')
            rowContent.append('y')
            print(rowContent)
            # sh.append(rowContent)
        startRow+=1

    book.save(xlsNewSigPath)
    print("生成完成")


if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='这个是通过topic表格生成生成newSig表格')
    parse.add_argument('-x','--xlsPath',help='topic表格路径')
    parse.add_argument('-s','--startRow',help='开始的行号',type=int)
    parse.add_argument('-e','--endRow',help='结束的行号',type=int)
    arg = parse.parse_args()
    generate(arg.xlsPath,arg.startRow,arg.endRow)
