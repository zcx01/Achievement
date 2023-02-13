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
from AnalyzeCan.Analyzedbc import *
from AnalyzeCan.projectInI import *

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
        useCase.stopSig(self.sendSim)
        useCase.stopSig(self.monitorSim)
    
    @staticmethod
    def stopSig(sim):
        if sim == None:
            return
        sim.stop()
        while True:
            time.sleep(1)
            if sim.stopped:
                break

    def startSig(self,sendSig):
        if self.sendSim == None:
            self.sendSim = SignalMonitor(pwd=PC_PWD, project=PROJECT_ID, channel=CHANNEL, ignore_init_sending=ignore_init_send)
        Thread(target=self.sendSim.begin_sending, args=(sendSig,)).start()
        # while True:
        #     if  self.sim.stopped:
        #         break
        #     time.sleep(1)
        # if not ignore_init_send:
        #     time.sleep(5)
        # else:
        #     time.sleep(1)

    def interactiveSendCanSig(self,sendSig):
        preSigs = list(dict(sendSig).keys())
        preSig = preSigs[len(preSigs)-1]
        while(True):
            cmd=input()
            if len(cmd) == 0:
                continue
            if '-h' in cmd:
                print('-s：停止发送所有的信号')
                print('-r：重新发送')
                print('-e: 退出整个')
                print('信号名 值：修改信号值和增加信号值')
                print('值：修改上一个信号的发送值')
                print('输入信号名:停止发送')
                continue
            cmd = re.findall(e_i,cmd,re.A)
            if isNumber(cmd[0]):
                cmd.insert(0,preSig)
            if '-e' in cmd:
                sys.exit()
            elif '-s' in cmd:
                self.stopAllsig()
                return
            elif '-r' in cmd:
                self.stopAllsig()
                self.startSig(sendSig)
            elif len(cmd) == 1:
                # if  not dbc.sigExist(cmd[0]):
                #     print("输入的信号在dbc不存在")
                #     continue
                self.sendSim.stop_task(cmd[0])
            elif len(cmd) % 2 == 0:
                sigNames = {}
                cmd = re.findall(e_i," ".join(cmd),re.A)
                index = 0
                while(index < len(cmd)):
                    sigName = cmd[index]
                    sigValue = cmd[index+1]

                    if not isNumber(sigValue):
                        print("输入信号值错误")
                    # elif  not dbc.sigExist(sigName):
                    #     print("输入的信号在dbc不存在")
                    else:
                        sigNames[sigName]=sigValue
                        preSig = sigName
                    index+=2
                self.sendSim.add_task(sigNames)

    def SimulationCan(self):
        sendSig={}
        if not ignore_init_send: self.AddPowerSig()
        for sigName in self.sendSignals:
            if len(self.sendSignals[sigName]) > 1:
                print(f'{sigName}:{self.sendSignals[sigName]} 索引')
                index = int(input())
            else:
                index=0
            try:
                sendSig[sigName] = self.sendSignals[sigName][index]
            except:
                printYellow(f'{sigName} 没有合适的值')
        self.startSig(sendSig)
        if len(self.monitorSignals) !=0:
            print(self.monitorSignals)
            self.MonitorSig(self.monitorSignals)
        self.interactiveSendCanSig(sendSig)
    
    def SequenceSendInitValue(self,timeSpace=2):
        self.SendPowerSig()
        temp = []
        for message in dbc.dbcMessage:
            me = dbc.dbcMessage[message]
            assert isinstance(me,MessageInfo)
            task = me.getAllSigInitValue()
            if str(me.messageId) in temp:
                continue
            elif me.sender not in local_machine_Sender and len(task) !=0:
                for p in PowerSig:
                    if p not in task:
                        self.sendSignals[p] = PowerSig[p]
                print(me.messageId,task)
                self.sendSim.add_task(task)
                time.sleep(timeSpace)

    def SendPowerSig(self):
        self.startSig(PowerSig)

    def AddPowerSig(self):
        for p in PowerSig:
            if p not in self.sendSignals:
                self.sendSignals[p] = []
                self.sendSignals[p].append(PowerSig[p])

    def MonitorSig(self,sigName):
        if self.monitorSim == None:
            self.monitorSim = SignalMonitor(pwd=PC_PWD, project=PROJECT_ID, channel=CHANNEL, ignore_init_sending=ignore_init_send)
        Thread(target=self.monitorSim.begin_listening, args=(sigName,)).start()
    
    def find(self,name):
        try:
            if  int(name) == self.index:
                return True
        except:
            if name == self.key:
                return True
        return False

def ReMatchStr(text,case=None):
    if case == None:
        case = useCase()
    signals=re.findall(e_i,text,re.A)
    tempSignals=[]
    preStr=''
    for signal in signals:
        #去除不在dbc中的信号
        if dbc.sigExist(signal) or isNumber(signal):
            if  preStr == '-l':
                case.appendMonitorSignal(signal)
            else:
                tempSignals.append(signal)
        preStr = signal
    signals = tempSignals
    if len(signals)== 0:
        return case
    index=0
    while(index < len(signals)):
        values=[]
        try:
            sig=signals[index]
            #保证开始为信号，而不是数字
            if not isNumber(sig):
                while not isNumber(signals[index+1]):
                    index += 1
                    sig = signals[index]
                    if  isNumber(signals[index+1]):
                        index+=1
                        values.append(signals[index])
                        break
                try:
                     while isNumber(signals[index+1]):
                        index += 1
                        values.append(signals[index])
                        if not isNumber(signals[index+1]):
                            break
                except:
                    pass
                if sig not in case.sendSignals:
                    case.sendSignals[sig] = []
                for value in values:
                    sendValue = str(value)
                    if "0x" in sendValue:
                        sendValue = str(int(value,16))
                    if sendValue not in case.sendSignals[sig]:
                        if dbc.physicalValueVaild(sig,int(sendValue)):
                            case.sendSignals[sig].append(sendValue)
        except:
            pass
        index += 1
    # if len(case.signals) !=0:
    #     print(case.Out())
    return case

def pyperclipCopy(cmd):
    try:
        pass
        # pyperclip.copy(cmd)
    except:
        pass

def displayInfo(usecases):
    tmp=[]
    for case in usecases:
        if case.isVaild():
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
            assert isinstance(case,useCase)
            if case.find(in_s):
                case.SimulationCan()
                pyperclipCopy(case.Out())
                break
            index += 1


def dealTest(dataPath,keyIndex=1,signalIndex=4,isApendPwer=True):
    book=xlrd.open_workbook(dataPath)
    sheel=book.sheet_by_index(0)
    useCases=[]
    for row in range(sheel.nrows):
        case = ReMatchStr(sheel.cell_value(row,signalIndex))
        if len(case.sendSignals) == 0: 
            continue
        case.key = sheel.cell_value(row, keyIndex)
        case.index = row+1
        if(isApendPwer):
            case.AddPowerSig()
        useCases.append(case)
    displayInfo(useCases)

def printSigTypes(sigNames):
    for sigName in sigNames:
        dataTypeStr = dbc.getSigDataType(sigName)
        print(f'{dataTypeStr:<8}{sigName} =0;')

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
    parser.add_argument('-s', '--Send',help="Send CAN",type=str,default='',nargs='?')
    parser.add_argument('-m', '--Monitor',help="Monitor CAN", default=[], nargs='+', type=str)
    parser.add_argument('-p', '--SendPowerSig', help="Send Power Sig", nargs='*', type=int,default=1)
    parser.add_argument('-d', '--dataType',help="get sig data type", default=[], nargs='+', type=str)
    parser.add_argument('-i', '--SequenceSendInitValue',help="按照指定的间隔发送信号初始值",type=int,default=2)

    arg=parser.parse_args()

    use = useCase()
    if "-b" in sys.argv:
        dealTest(arg.bugxlsx,1,26,arg.SendPowerSig)
    elif '-c' in sys.argv:
        dealTest(arg.casexlsx,0,1,arg.SendPowerSig)
    elif '-s' in sys.argv:
        if arg.SendPowerSig==1:
            use.AddPowerSig()
        if arg.Send != None and len(arg.Send) != 0:
            ReMatchStr(str(arg.Send),use)
        use.SimulationCan()
    elif '-m' in sys.argv:
        if arg.SendPowerSig==1:
            use.SendPowerSig()
        use.MonitorSig(arg.Monitor)
    elif '-d' in sys.argv:
        printSigTypes(arg.dataType)  
    elif '-i' in sys.argv:
        use.SequenceSendInitValue(arg.SequenceSendInitValue)
    else:
        dealTest("/home/chengxiongzhu/Works/文档/测试信号.xls")

