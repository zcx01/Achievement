#!/bin/python
import time
import sys
import os
from typing import Dict
import pexpect


process = None
cmd_Outs={'telnet':'login','ssh':'password','adb push':'in','curl':'100'}
new_spawn=['ssh','adb shell']
shellCmds=[]
is_close_spawn=False

def SetCloseSpawn(s):
    global is_close_spawn
    is_close_spawn = s

def keyStr(cmd, t=0.3,out='',auto_exit=True):
    assert isinstance(cmd,str)
    global process
    global is_close_spawn
    if is_close_spawn and process != None:
        process.close()
        process=None
    is_close_spawn = False

    if  process == None and len(getCommand(cmd,new_spawn)) !=0:
        if len(shellCmds) !=0:
            os.system('&&'.join(shellCmds))
            shellCmds.clear()
        process = pexpect.spawn(cmd, encoding='utf-8', logfile=sys.stdout, timeout=300)
        return ''

    if process == None:
        shellCmds.append(cmd)
        return ''
    if len(out) == 0:
        prompt=cmd_Outs.get(getCommand(cmd,cmd_Outs),'#')
    else:
        prompt=out
    process.sendline(cmd)

    if len(prompt) != 0:
        login_index = process.expect([prompt, pexpect.EOF, pexpect.TIMEOUT])
    else:
        login_index = process.expect(pexpect.EOF)
    if auto_exit and login_index != 0:
        print(f'执行{cmd}失败')
        exit(1)
    if  process != None:
        return process.before.strip()
    else:
        return ''


def interact():
    global process
    if  process != None:
        process.logfile = None #在调用 interact() 之前, 要确保控制台日志输出为空,否则会出现异常   write() argument must be str, not bytes
        process.interact()
    elif len(shellCmds) !=0:
        os.system('&&'.join(shellCmds))
        shellCmds.clear()

def getCommand(cmd,arrys):
    for arry in arrys:
        if cmd.startswith(arry):
            return arry
    return ''

class AndroidQnx(object):
    def __init__(self):
        super().__init__()
        self.androidDir = "/data"
        self.android_qnxDir = "/ota"
        self.qnxDir = "/ota/android"
    
    def pc_android_qnx(self,filePaths):
        fileNames=[]
        for path in filePaths:
            keyStr(f'adb push {path} {self.androidDir}')
            fileNames .append(os.path.basename(path))

        keyStr('adb shell')
        for fileName in fileNames:
            keyStr(f'cp {self.androidDir}/{fileName} {self.android_qnxDir}',0,"#")

    def qnx_cp(self,fileDict,chmod):
        for file in fileDict:
            if len(fileDict[file]) != 0:
                keyStr(f"rm {fileDict[file]}{file}")
                keyStr(f"cp {self.qnxDir}/{file} {fileDict[file]}")
            if chmod:
                keyStr(f"chmod +x {fileDict[file]}/{file}",0)