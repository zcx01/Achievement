#!/bin/python
import time
import sys
import os
import pexpect
import platform
if platform.system() == "Windows":
    import wexpect


process = None
cmd_Outs={}
new_spawn=[]
shellCmds=[]
linux_end ='$'
is_close_spawn=False

def setDevice(dev):
    global cmd_Outs
    global new_spawn
    cmd_Outs={'telnet':'login','ssh':'password',f'adb{dev} push':'in','curl':'100'}
    new_spawn=['ssh',f'adb{dev} shell']
setDevice("")

def getPexpect(cmd):
    process = None
    if platform.system() == "Windows":
        process = wexpect.spawn('cmd.exe', timeout=300)
        process.expect('>')
        process.sendline(cmd)
    else:
        process = pexpect.spawn(cmd, encoding='utf-8', logfile=sys.stdout, timeout=300)
    return process

def expectPrompt(prompt):
    if platform.system() == "Windows":
        if len(prompt) != 0:
            login_index = process.expect([prompt,wexpect.TIMEOUT])
        else:
            login_index = process.expect(wexpect.EOF)
    else:    
        if len(prompt) != 0:
            login_index = process.expect([prompt, pexpect.EOF, pexpect.TIMEOUT])
        else:
            login_index = process.expect(pexpect.EOF)    
    return login_index

def SetCloseSpawn(s):
    global is_close_spawn
    is_close_spawn = s

def closeSpawn():
    SetCloseSpawn(True)
    global process
    if is_close_spawn and process != None:
        time.sleep(6)
        process.close()
        process=None

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
        process = getPexpect(cmd)
        return ''

    if process == None:
        shellCmds.append(cmd)
        return ''
    if len(out) == 0:
        prompt=cmd_Outs.get(getCommand(cmd,cmd_Outs),'#')
    else:
        prompt=out
    process.sendline(cmd)

    login_index = expectPrompt(prompt)
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
        if platform.system() != "Windows":
            process.interact()
        # else:
        #     process.wait()
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
        self.androidDir = "/sdcard"
        self.android_qnxDir = "/ota"
        self.qnxDir = "/ota/android"
        self.device = ""
        setDevice(self.device)
    
    def setDevice(self,dev):
        self.device = dev
        setDevice(self.device)

    def pc_android_qnx(self,filePaths):
        fileNames=[]
        for path in filePaths:
            keyStr(f'adb{self.device} push {path} {self.androidDir}')
            fileNames .append(os.path.basename(path))

        keyStr(f'adb{self.device} shell')
        keyStr('init.mount_ota.sh',0,"#")
        for fileName in fileNames:
            keyStr(f'cp {self.androidDir}/{fileName} {self.android_qnxDir}',0,"#")

    def qnx_cp(self,fileDict,chmod):
        for file in fileDict:
            if len(fileDict[file]) != 0:
                keyStr(f'md5 {fileDict[file]}{file}')
                keyStr(f"rm {fileDict[file]}{file}")
                keyStr(f"cp {self.qnxDir}/{file} {fileDict[file]}")
                keyStr(f'md5 {fileDict[file]}{file}')
            if chmod:
                keyStr(f'slay {file}')
                keyStr(f"chmod +x {fileDict[file]}/{file}",0)
                keyStr(f"ps -e | grep {file}")