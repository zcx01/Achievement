#!/bin/python
import json
import os
import sys
import pyperclip
#sudo pip install pyperclip
#linux 
#sudo apt-get install xsel xclip 
import xlrd
import re
import time
from commonfun import *
from mega_cantools_lib.signal_monitor.signal_monitor import SignalMonitor
from threading import Thread

PC_PWD="123456"
PROJECT_ID='c385ev'
CHANNEL =0
ignore_init_send =False
class useCase(object):
    def __init__(self):
        self.index=0
        self.key=""
        self.signals={}
        self.py=""
        self.sim = SignalMonitor(pwd=PC_PWD, project=PROJECT_ID, channel=CHANNEL, ignore_init_sending=ignore_init_send)

    def Out(self):
        "python3 monitor.py -s BcmPwrStsFb -v 1"
        premise = "python3 monitor.py"
        for signal in self.signals:
            for value in self.signals[signal]:
                premise+=" -s "+signal+" -v "+value
        return premise

    def SendCan(self):
        sendSig={}
        for sigName in self.signals:
            print(f'{sigName}索引')
            index = int(input())
            sendSig[sigName] = self.signals[sigName][index]
        Thread(target=self.sim.begin_sending, args=(sendSig,)).start()
        time.sleep(5)
        print('-s：停止发送')
        print('-h：打印可选的信号')
        print('信号名 值：修改信号值和增加信号值')
        print('输入信号名:停止发送')
        isStop = False
        while(True):
            cmd=input().split(" ")
            if len(cmd) == 0:
                continue
            if '-s' in cmd:
                self.sim.stop()
                return
            elif '-h' in cmd:
                print(sendSig)
            elif len(cmd) == 1:
                self.sim.stop_task(cmd[0])
                isStop = True
            elif len(cmd) == 2:
                if cmd[0] in sendSig and isStop:
                    self.sim.stop()
                    time.sleep(2)
                    modifySendSig = dict(sendSig)
                    modifySendSig[cmd[0]]=cmd[1]
                    isStop=False
                    Thread(target=self.sim.begin_sending, args=(modifySendSig,)).start()
                    time.sleep(5)
                else:
                    self.sim.add_task({cmd[0]:cmd[1]})
    
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
        values=[]
        try:
            sig=signals[index]
            while(re.search(word,signals[index+1],re.A) != None):
                index += 1
                sig = signals[index]
                if re.search(in_i, signals[index+1], re.A) != None:
                    index+=1
                    values.append(signals[index])
                    break
            try:
                while(re.search(in_i,signals[index+1],re.A) != None):
                    index += 1
                    values.append(signals[index])
                    if re.search(word,signals[index+1],re.A) != None:
                        break
            except:
                pass
            case.signals[sig] = []
            for value in values:
                if re.search(word,sig,re.A) != None and re.search(in_i,value,re.A) != None:
                    case.signals[sig].append(str(value).replace("0x",""))
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
                        case.SendCan()
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
