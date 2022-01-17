#!/bin/python
import sys
import time
from execCmd import *
import argparse
import subprocess


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='qnx ')

    parser.add_argument('-r','--reset',help='reset -f',nargs='*')
    parser.add_argument('-m','--subtopic',help='su btopic',nargs='*',default=[])
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    parser.add_argument('-k','--slay', help='slay process',type=str,nargs='*')
    parser.add_argument('-l','--log', help='taif log',type=str)
    parser.add_argument('-i','--interact', help='interact',default=1,type=int)
    args = parser.parse_args()

    for j in range(120):
        adb_out = subprocess.getoutput("adb devices").split('\n')
        if len(adb_out) >= 3:
            if j >=3:
                time.sleep(20)
            break
        print(f"车机重启中...等待{j+1}秒")
        time.sleep(1)

    keyStr("adb shell")
    keyStr("telnet cdc-qnx")
    keyStr("root")

    isExit = (args.interact == 0)

    if "-m" in sys.argv:
        keyStr("on -T ic_apps_t -u ic_apps mega_ipc_sub -t  \"#\" ")

    if "-l" in sys.argv:
        try:
            keyStr(f' tail -f /var/log/syslog | grep \'{args.log}\' ')
        except:
            pass
        

    if '-r' in sys.argv:
        keyStr("mcu_tool -g 2")
        keyStr("reset -f")
        isExit=True

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
