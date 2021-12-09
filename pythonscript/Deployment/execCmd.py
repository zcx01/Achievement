#!/bin/python
import time
import sys
import os
import pexpect


process = None
cmd_Outs={'telnet':'bigsur:/','ssh':'password','adb push':'in','curl':'100'}
new_spawn=['ssh','adb shell']
shellCmds=[]
is_close_spawn=False

def SetCloseSpawn(s):
    global is_close_spawn
    is_close_spawn = s

def keyStr(cmd, t=0.3):
    assert isinstance(cmd,str)
    global process
    global is_close_spawn
    if is_close_spawn and process != None:
        process.close()
        process=None
        is_close_spawn = False

    if  process == None and len(getCommand(cmd,new_spawn)) !=0:
        process = pexpect.spawn(cmd, encoding='utf-8', logfile=sys.stdout, timeout=300)
        return ''

    if process == None:
        shellCmds.append(cmd)
        return ''
    elif len(shellCmds) !=0:
        os.system('&&'.join(shellCmds))
        shellCmds.clear()
    # if cmdStart in new_spawn and currentSpawn != cmdStart:
    #     currentSpawn = cmdStart
    #     if  process != None:
    #         process.close()
    #     try:
    #         process = pexpect.spawn(cmd, encoding='utf-8', logfile=sys.stdout, timeout=300)
    #         return
    #     except:
    #         process = pexpect.spawn("/bin/bash", encoding='utf-8', logfile=sys.stdout, timeout=300)

    prompt=cmd_Outs.get(getCommand(cmd,cmd_Outs),'#')
    process.sendline(cmd)

    if len(prompt) != 0:
        login_index = process.expect([prompt, pexpect.EOF, pexpect.TIMEOUT])
    else:
        login_index = process.expect(pexpect.EOF)
    if login_index != 0:
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

is_ssh = "-s" in sys.argv
if is_ssh:
    keyStr("ssh chengxiongzhu@10.25.11.197")
    keyStr("123456")
