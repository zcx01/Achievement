#!/bin/python
import sys
import time
from execCmd import *
import argparse
import subprocess
from commonfun import *


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='qnx ')

    parser.add_argument('-r','--reset',help='reset',nargs='*')
    parser.add_argument('-m','--subtopic',help='订阅 topic',type=str,default=[])
    parser.add_argument('-p','--pulishtopic',help='发送 topic',type=str,default=[])
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    parser.add_argument('-k','--slay', help='slay process',type=str,nargs='*')
    parser.add_argument('-l','--log', help='查看log',type=str)
    parser.add_argument('-i','--interact', help='interact',default=1,type=int)
    parser.add_argument('-n','--logGrade', help='修改log等级,指的是进程名称',type=str)
    parser.add_argument('-rl','--remvelog', help='清除log', nargs='?',default=1,type=int)
    parser.add_argument('-np','--nextPage', help='下一页', nargs='?')
    parser.add_argument('-v','--value', help='值', nargs='?',default=1,type=int)
    parser.add_argument('-d','--device',help='adb的device',default='',type=str)
    parser.add_argument('-q','--qnxPassword',help='user版本qnx的密码',type=int,nargs='*')
    parser.add_argument('-dlt','--dltlogs',help='拉取dltlogs',nargs='?')
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
    value = args.value

    if "-m" in sys.argv:
        try:
            # keyStr(f"on -T ic_apps_t -u ic_apps mega_ipc_sub -t  \"{args.subtopic}\" ")
            keyStr(subMqtt(args.subtopic))
        except:
            pass

    if "-p" in sys.argv:
        try:
            # keyStr(f"on -T ic_apps_t -u ic_apps mega_ipc_sub -t  \"{args.subtopic}\" ")
            keyStr(sendMqtt(args.pulishtopic,value))
            isExit=True
        except:
            pass
    if "-n" in sys.argv:
        try:
            keyStr(f"echo {args.logGrade}:n:7 >> /var/pps/verbose")
        except:
            pass

    if "-l" in sys.argv:
        try:
            # keyStr(f' tail -f /var/log/syslog | grep \'{args.log}\' ')
             keyStr(f'slog2info -w | grep \'{args.log}\' ')
        except:
            pass
    
    if "-rl" in sys.argv:
        try:
            keyStr(f'rm /var/log/dltlogs/*.dlt*')
            keyStr(f'reset')
            isExit=True
        except:
            pass

    if "-np" in sys.argv:
        try:
            keyStr(r'on -T ic_apps_t -u ic_apps mega_ipc_pub -t "keyinput/event" -m "{\"value\":{\"status\":false, \"longClick\":false,\"keyCode\":14}}"')
            # isExit=True
        except:
            pass
        
    if '-r' in sys.argv:
        # keyStr("mcu_tool -g 2")
        # keyStr("reset -f",0.3,'PON_SOFT_RB_SPARE')
        keyStr("enter_fastoot_mode.sh")
        time.sleep(1)
        isExit=True

    if "-dlt" in sys.argv:
        SetCloseSpawn(True)
        keyStr('rm -rf dltlogs')
        keyStr('adb pull /qlog/dltlogs/ ./')
        isExit=False

    if '-k' in sys.argv:
        slays = args.slay
        assert isinstance(slays,list)
        if len(slays) !=0:
            slay_cmd = f"slay {slays[0]}"
            slay_out = keyStr(slay_cmd)
            while 'slay:' not in slay_out:
                keyStr(slay_cmd)
                # time.sleep(100)
        else:
            keyStr('slay -f slm')
        isExit=True

    if '-e' in sys.argv:
        for cmd in args.excess:
            print(args.excess)
            out = keyStr(cmd)
            print('excess out:\n',out)

    if not isExit:
        interact()
