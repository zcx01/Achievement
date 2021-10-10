import json
import os
import sys
import pyperclip
#sudo pip install pyperclip
#linux 
#sudo apt-get install xsel xclip 
import xlrd
import re
from commonfun import *

class useCase(object):
    def __init__(self):
        self.index=0
        self.key=""
        self.signals={}
        self.py=""

    def Out(self):
        "python3 monitor.py -s BcmPwrStsFb -v 1"
        premise="python3 monitor.py"
        for signal in self.signals:
            premise+=" -s "+signal+" -v "+self.signals[signal]
        return premise
    
    def find(self,name):
        try:
            if  int(name) == self.index:
                return True
        except:
            if name == self.key:
                return True
        return False

def dealBug(dataPath):
    book=xlrd.open_workbook(dataPath)
    sheel=book.sheet_by_index(0)
    for row in range(sheel.nrows):
        for col in range(sheel.ncols):
            text=sheel.cell_value(row,col)

def ReMatchStr(text):
    case = useCase()
    word=r"\b[a-zA-Z]+\b"
    in_i=r"\b[0x0-9]+\b"
    e_i=r"\b[a-zA-Z0x0-9]+\b"
    signals=re.findall(e_i,text,re.A)
    # print(signals)
    if signals== None:
        return case
    index=0
    while(index < len(signals)):
        try:
            sig=signals[index]
            while(re.search(word,signals[index+1],re.A) != None):
                index += 1
                sig = signals[index]
                if re.search(in_i, signals[index+1], re.A) != None:
                    index+=1
                    value=signals[index]
                    break
            try:
                while(re.search(in_i,signals[index+1],re.A) != None):
                    index += 1
                    value = signals[index]
                    if re.search(word,signals[index+1],re.A) != None:
                        break
            except:
                pass
            if re.search(word,sig,re.A) != None and re.search(in_i,value,re.A) != None:
                case.signals[sig]=str(value).replace("0x","")
        except:
            pass
        index += 1
    if len(case.signals) !=0:
        print(case.Out())
    return case

def displayInfo(useCases):
    tmp=[]
    for case in useCases:
        if len(case.signals)!=0 or len(case.py)!=0:
            tmp.append(case)
    print(f"总大小为{len(tmp)}")
    useCases=tmp
    while(True):
        print("请输入索引或者关键字:")
        in_s=input()
        index=0
        for case in useCases:
            try:
                if case.find(in_s) or int(in_s) == index:
                    outString=''
                    if len(case.signals)!=0:
                        outString=case.Out()
                    else:
                        outString=case.py
                    print(outString)
                    pyperclip.copy(outString)
                    break
            except:
                continue
            index += 1

def dealTest(dataPath,keyIndex=1,signalIndex=4):
    book=xlrd.open_workbook(dataPath)
    sheel=book.sheet_by_index(0)
    useCases=[]
    for row in range(sheel.nrows):
        case = ReMatchStr(sheel.cell_value(row,signalIndex))
        if len(case.signals) == 0: 
            continue
        case.key = sheel.cell_value(row, keyIndex)
        case.index = row
        useCases.append(case)
    displayInfo(useCases)
        
if __name__ == "__main__":
    if "-b" in sys.argv:
        dealTest(sys.argv[2],1,26)
    else:
        dealTest("/home/chengxiongzhu/Works/文档/测试信号.xls")
