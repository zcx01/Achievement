import os
from posixpath import dirname
import re
import sys
from subprocess import Popen
from typing import List
import xlrd
import json

def getJScontent(configJson):
    with open(configJson, "r") as cr:
        return json.load(cr)

def writeJs(configJson,jsContent):
    cr = open(configJson, "w")
    cr.write(json.dumps(jsContent,ensure_ascii=False,indent=4))
    cr.close()

def findValue(text,signal,filePath,*other):
    if(str(text).find(signal)!=-1):
        print(f'{text:<30}{filePath} {other}')
        return True
    return False

def findsignalInfile(signal,filePath):
    try:
        f=open(filePath,'r')
        content=f.readlines()
        for text in content:
            if(findValue(text,signal,filePath)):
                break
    except:
        pass
    
def findsignalInexcel(signal,filePath):
    book=xlrd.open_workbook(filePath)
    sheel=book.sheet_by_index(0)
    for row in range(sheel.nrows):
        isFind = False
        for col in range(sheel.ncols):
            text=sheel.cell_value(row,col)
            if str(text).find(signal)!=-1:
                isFind=True
                break

        if isFind:
            text=str(sheel.cell_value(row,2))
            if text.startswith("ACC"):
                sig=str(text).replace("ACC_","")
                desc=sheel.cell_value(row,3)
                print(sig,"    ",desc)
                configPath="/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/config/icdriving_config.json"
                jsConfig=getJScontent(configPath)
                jsConfig[sig]={"desc":desc}
                writeJs(configPath,jsConfig)
        
def findOneSignal(signal,path):
    for (dirpath,dirnames,filenames) in os.walk(path):
        for oriName in filenames:
            oriPath = f'{dirpath}/{oriName}'
            suffix = os.path.splitext(oriName)[1]
            if(str(suffix).find("xls") !=-1 ):
                findsignalInexcel(signal,oriPath)
            else:
                findsignalInfile(signal,oriPath)

def findSignal(signal,path):
    if os.path.isfile(signal) :
        f=open(signal,'r')
        signals=f.readlines()
        for s in signals:
            findOneSignal(s,path)
    else:
        findOneSignal(signal,path)

findSignal("距离","/home/chengxiongzhu/Works/文档/temp")
# if __name__ == "__main__":
#     if len(sys.argv) == 3 :
#         findSignal(sys.argv[1], sys.argv[2])
