#!/bin/python
import os
import xlrd
from canSimulation.projectInI import *

def findValue(text,signal,filePath,*other):
    if(str(text).find(signal)!=-1):
        print(f'{text:<30}{filePath} {other}')
        return True
    return False

def findsignalInfile(signal,filePath):
    try:
        f=open(filePath,'r')
        print(filePath)
        content=f.readlines()
        for text in content:
            if(findValue(text,signal,filePath)):
                pass
    except:
        pass
    
def findsignalInexcel(signal,filePath):
    book=xlrd.open_workbook(filePath)
    sheel=book.sheet_by_name(Sig_Matrix)
    for row in range(sheel.nrows):
        for col in range(sheel.ncols):
            text=sheel.cell_value(row,col)
            # print(row,col)
            if(findValue(text,signal,filePath,row,col)):
                return

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

findSignal("vehctrl/","/home/chengxiongzhu/11/dltlogs")
# if __name__ == "__main__":
#     if len(sys.argv) == 3 :
#         findSignal(sys.argv[1], sys.argv[2])
