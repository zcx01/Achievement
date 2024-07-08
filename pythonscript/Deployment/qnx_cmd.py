#!/bin/python
import sys
import time
from execCmd import *
import argparse
import subprocess
from commonfun import *


APSSUFFIX="aps_i" 
THREADPROPORTION=3
def aps_exist(aps):
    cmd = keyStr('aps')
    cmds = re.findall(e_i,cmd,re.A)
    for apsInfo in cmds:
        if 'aps' in apsInfo:
            if apsInfo == aps:
                return True
    return False

def aps_can_create_num():
    cmd = keyStr('aps')
    cmds = re.findall(e_i,cmd,re.A)
    count = 1
    for apsInfo in cmds:
        if 'aps' in apsInfo:
            count =count+1
    return 32-count

def getApsName(name):
    apsName =  APSSUFFIX+'_'+name
    return apsName[0:15]

def createAps(apsName,proportion):
    keyStr(f'aps create -b {proportion} {apsName}')

def modifyThreadAps(pid,tid,apsName):
    keyStr(f'aps join -p {pid} -t {tid} {apsName}')

def printpPidinSched(apsName):
    keyStr(f'pidin sched | grep {apsName}')

def cpu_aps(processName):
    cmd = keyStr(f'pidin threads | grep {processName}')
    cmdlines = cmd.splitlines()
    yield len(cmdlines)
    for cmdline in cmdlines:
        processInfos = re.findall(r'(?<=\s)\S+(?=\s)',cmdline,re.A)
        if len(processInfos) > 3:
            pid = processInfos[0]
            if isNumber(pid):
                tid = processInfos[1]
                threadName = processInfos[3]
                yield pid,tid,threadName

def process_cpu_aps(processName):
    aps_pr = getApsName(processName)
    if not aps_exist(aps_pr):
        createAps(aps_pr,1)
    apsInfo = cpu_aps(processName)
    next(apsInfo)
    for pid,tid,threadName in apsInfo:
        modifyThreadAps(pid,tid,aps_pr)
    printpPidinSched(aps_pr)

def thread_cpu_aps(processName,tid,extraRutrun,ranged=[]):
    apsInfo = cpu_aps(processName)
    next(apsInfo)
    apsProportion = 0.01
    can_create_num = aps_can_create_num()
    aps_prs=[]
    current_index = 0
    for pid,tid,threadName in apsInfo:
        if len(ranged) != 0 and tid not in ranged:
            continue
        aps_pr = getApsName(threadName)
        if tid:
            aps_pr = getApsName(tid)
        if len(aps_prs) > can_create_num:
            if extraRutrun:
                return
            if not aps_exist(aps_pr):
                if current_index > len(aps_prs):
                    current_index = 0
                aps_pr = aps_prs[current_index]
                current_index = current_index + 1
        elif not aps_exist(aps_pr):
            createAps(aps_pr,apsProportion)
        modifyThreadAps(pid,tid,aps_pr)
        printpPidinSched(aps_pr)
        aps_prs.append(aps_pr)

def statistics_cpu_aps(apsName):

    if apsName == None or len(apsName) == 0:
        apsName = APSSUFFIX
    try:
        keyStr(f'aps show -l -d 1 | grep {apsName} > var/log/aps.txt')
    except:
        pass
    SetCloseSpawn(True)
    keyStr('adb pull /qlog/aps.txt ./')
    interact()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='qnx ')


    parser.add_argument('-i','--interact', help='interact',default=0,type=int)
    parser.add_argument('-d','--device',help='adb的device',default='',type=str)
    parser.add_argument('-q','--qnxPassword',help='user版本qnx的密码',type=int,nargs='*')
    parser.add_argument('-paps','--processAps',help='创建aps查看一个进程的cpu', nargs='?',type=str)
    parser.add_argument('-tnaps','--threadNameAps',help='根据名称创建aps查看一个进程中所有线程的cpu', nargs='?',type=str)
    parser.add_argument('-taps','--threadAps',help='根据tid创建aps查看一个进程中所有线程的cpu', nargs='?',type=str)
    parser.add_argument('-saps','--statisticsAps',help='统计制度的aps,统计的文件在当前目录', nargs='?',type=str,default='')
    args = parser.parse_args()

    device = ""
    rootOut = "#"
    if len(args.device) !=0:
        device = f" -s {args.device}"

    if "-q" in sys.argv:
        rootOut = "Password"

    subprocess.getoutput("adb wait-for-device").split('\n')
        

    setDevice(device)
    keyStr(f'adb{device} root')
    keyStr(f"adb{device} shell")
    keyStr('init.mount_qlog.sh',0,"#")
    keyStr(f"telnet cdc-qnx",0,"login:")
    keyStr(f"root",0,rootOut)
    if rootOut == "Password":
        keyStr(f"*6342@232A#!",0,"#")

    isExit = (args.interact == 0)

    if "-paps" in sys.argv:
        process_cpu_aps(args.processAps)

    if "-taps" in sys.argv:
        thread_cpu_aps(args.threadAps,True)
    
    if "-tnaps" in sys.argv:
        thread_cpu_aps(args.threadNameAps,False)

    if "-saps" in sys.argv:
        statistics_cpu_aps(args.statisticsAps)

    if not isExit:
        interact()
