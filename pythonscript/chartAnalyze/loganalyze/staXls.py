from commonfun import *
import openpyxl 
from xml.dom.minidom import *
import xlrd
import datetime
from xlrd.book import Book
from xlrd.sheet import Sheet

def coverXls(savaPath,conents):
    # 创建一个excel文件
    book = openpyxl.Workbook()
    sh = book.active
    sh.title = 'sheel'
    fileIndex = 0
    for filePath in conents.keys():
        sh[f'{XlsIntToChar(fileIndex)}1'] = os.path.basename(filePath)
        fileIndex= fileIndex+1
        sh[f'{XlsIntToChar(fileIndex)}1'] = "个数"
        fileIndex= fileIndex+1

    resConents = list(conents.values())
    for resConentIndex in range(len(resConents)):
        resConent = resConents[resConentIndex]
        for field,count in resConent.items():
            if count == 0:
                continue
            lineContens = []
            for resConentIndexf in range(resConentIndex):
                lineContens.append("")
                lineContens.append("")
            lineContens.append(field)
            lineContens.append(count)
            startIndex = resConentIndex + 1
            while startIndex < len(resConents):
                otherConent = resConents[startIndex]
                if field in otherConent:
                    lineContens.append(field)
                    lineContens.append(otherConent[field])
                    otherConent[field] = 0
                startIndex = startIndex + 1
            sh.append(lineContens)
    xlsPathFileName = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S") + '.xlsx'
    book.save(savaPath+xlsPathFileName)
