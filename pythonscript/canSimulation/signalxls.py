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
from threading import Thread
import argparse
from commonfun import *
from mega_cantools_lib.signal_monitor.signal_monitor import SignalMonitor
from Analyzedbc import *
from projectInI import *


pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/../topic_def/"
jsConfig = getJScontent(pyFileDir+"config.json",)
dbc=Analyze(getKeyPath("dbcfile",jsConfig))

class useCase(object):
    def __init__(self):
        self.index=0
        self.key=""
        self.sendSignals={}
        self.monitorSignals=[]
        self.sendSim = None
        self.monitorSim =None

    def isVaild(self):
        return len(self.sendSignals) !=0 or len(self.monitorSignals) !=0

    def appendMonitorSignal(self,monitorSignal):
        if monitorSignal not in self.monitorSignals:
            self.monitorSignals.append(monitorSignal)

    def Out(self):
        "python3 monitor.py -s BcmPwrStsFb -v 1"
        '''premise = "python3 monitor.py"
        for signal in self.sendSignals:
            for value in self.sendSignals[signal]:
                premise+=" -s "+signal+" -v "+value
        return premise'''
        return str(self.sendSignals)

    def isSame(self,other):
        sameSize = len(self.sendSignals.keys() & other.sendSignals.keys())
        return sameSize == len(self.sendSignals) and sameSize == len(other.sendSignals)

        # return len(self.signals.keys() - other.signals.keys()) ==0

    def stopAllsig(self):
        self.sendSim.stop()
        while True:
            if self.sendSim.stopped:
                break
            time.sleep(1)

    def startSig(self,sendSig):
        Thread(target=self.sendSim.begin_sending, args=(sendSig,)).start()
        # while True:
        #     if  self.sim.stopped:
        #         break
        #     time.sleep(1)
        time.sleep(5)

    def interactiveSendCanSig(self,sendSig):
        print('-s：停止发送')
        print('-h：打印可选的信号')
        print('-r：重新发送')
        print('信号名 值：修改信号值和增加信号值')
        print('输入信号名:停止发送')
        isStop = False
        while(True):
            cmd=input()
            if len(cmd) == 0:
                continue
            cmd=cmd.split(" ")
            if '-s' in cmd:
                self.sendSim.stop()
                return
            elif '-h' in cmd:
                print(self.sendSignals)
            elif '-r' in cmd:
                self.stopAllsig()
                self.startSig(sendSig)
            elif len(cmd) == 1:
                if  not dbc.sigExist(cmd[0]):
                    print("输入的信号在dbc不存在")
                    continue
                self.sendSim.stop_task(cmd[0])
                isStop = True
            elif len(cmd) % 2 == 0:
                sigNames = {}
                cmd = re.findall(e_i," ".join(cmd),re.A)
                if cmd[0] in sendSig and isStop:
                    self.stopAllsig()
                    modifySendSig = dict(sendSig)
                    modifySendSig[cmd[0]]=cmd[1]
                    isStop=False
                    self.startSig(modifySendSig)
                else:
                    index = 0
                    while(index < len(cmd)):
                        sigName = cmd[index]
                        sigValue = cmd[index+1]
                        if  not dbc.sigExist(sigName):
                            print("输入的信号在dbc不存在")
                        elif not isNumber(sigValue):
                            print("输入信号值错误")
                        else:
                            sigNames[sigName]=sigValue
                        index+=2
                    self.sendSim.add_task(sigNames)

    def SimulationCan(self):
        sendSig={}
        for sigName in self.sendSignals:
            if len(self.sendSignals[sigName]) > 1:
                print(f'{sigName}:{self.sendSignals[sigName]} 索引')
                index = int(input())
            else:
                index=0
            sendSig[sigName] = self.sendSignals[sigName][index]
        if self.sendSim == None:
            self.sendSim = SignalMonitor(pwd=PC_PWD, project=PROJECT_ID, channel=CHANNEL, ignore_init_sending=ignore_init_send)
        self.startSig(sendSig)
        if len(self.monitorSignals) !=0:
            print(self.monitorSignals)
            self.MonitorSig(self.monitorSignals)
        self.interactiveSendCanSig(sendSig)
    
    def SendPowerSig(self):
        self.sendSignals[PowerSig]=[]
        self.sendSignals[PowerSig].append("2")
        self.SimulationCan()

    def MonitorSig(self,sigName):
        if self.monitorSim == None:
            self.monitorSim = SignalMonitor(pwd=PC_PWD, project=PROJECT_ID, channel=CHANNEL, ignore_init_sending=ignore_init_send)
        # param = [sigName] #CdcAutoHeadLiSet
        Thread(target=self.monitorSim.begin_listening, args=(sigName,)).start()
    
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
    signals=re.findall(e_i,text,re.A)
    tempSignals=[]
    preStr=''
    for signal in signals:
        #去除不在dbc中的信号
        if dbc.sigExist(signal) or re.search(in_i,signal,re.A) != None:
            if dbc.sender(signal) in local_machine_Sender or preStr == '-l':
                case.appendMonitorSignal(signal)
            else:
                tempSignals.append(signal)
        preStr = signal
    signals = tempSignals
    if signals== None:
        return case
    index=0
    while(index < len(signals)):
        values=[]
        try:
            sig=signals[index]
            #保证开始为信号，而不是数字
            if re.search(word,sig,re.A) != None:
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
                if sig not in case.sendSignals:
                    case.sendSignals[sig] = []
                for value in values:
                    if re.search(word,sig,re.A) != None and re.search(in_i,value,re.A) != None:
                        sendValue = str(value).replace("0x","")
                        if sendValue not in case.sendSignals[sig]:
                            case.sendSignals[sig].append(sendValue)
        except:
            pass
        index += 1
    # if len(case.signals) !=0:
    #     print(case.Out())
    return case

def pyperclipCopy(cmd):
    try:
        pyperclip.copy(cmd)
    except:
        pass

def displayInfo(usecases):
    tmp=[]
    for case in usecases:
        if case.isVaild:
            tmp.append(case)
    useCases=tmp
    isloop = True
    if len(useCases) == 0:
        print('没有发现信号')
        return
    while(isloop):
        if len(useCases) > 1:
            for case in useCases:
                print(f'{case.index:<5}'+f'{case.key:<10}'+case.Out())
            print("请输入索引或者关键字:")
            print('-e: 退出')
            in_s= input()
            if '-e' in in_s:
                return
        else:
            in_s=useCases[0].index
            isloop=False
        index=0
        for case in useCases:
            if case.find(in_s):
                case.SimulationCan()
                pyperclipCopy(case.Out())
                break
            index += 1


def dealTest(dataPath,keyIndex=1,signalIndex=4):
    book=xlrd.open_workbook(dataPath)
    sheel=book.sheet_by_index(0)
    useCases=[]
    for row in range(sheel.nrows):
        case = ReMatchStr(sheel.cell_value(row,signalIndex))
        if len(case.sendSignals) == 0: 
            continue
        case.key = sheel.cell_value(row, keyIndex)
        case.index = row+1
        useCases.append(case)
    displayInfo(useCases)
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
    description='''
    用来发送CAN信号:
    支持jira导出的bug
    支持生成的case
    直接发送CAN信号
    监听CAN信号
    ''')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-b','--bugxlsx',help="jira xlsx file")
    parser.add_argument('-c','--casexlsx',help="generate case xlsx file")
    parser.add_argument('-s', '--Send',help="Send CAN",nargs='*')
    parser.add_argument('-m', '--Monitor',help="Monitor CAN", default=[], nargs='+', type=str)

    arg=parser.parse_args()

    use = useCase()
    if "-b" in sys.argv:
        dealTest(arg.bugxlsx,1,26)
    if '-c' in sys.argv:
        dealTest(arg.casexlsx,0,1)
    elif '-s' in sys.argv:
        use.SendPowerSig()
    elif '-m' in sys.argv:
        use.MonitorSig(arg.Monitor)
    else:
        dealTest("/home/chengxiongzhu/Works/文档/测试信号.xls")

