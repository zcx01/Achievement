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
    parser.add_argument('-k','--slay', help='slay process',default=str,nargs='*')
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

    isExit = False
    if "-m" in sys.argv:
        keyStr("mosquitto_sub -h cdc-qnx -v -t \"#\" ")

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
            keyStr(cmd,0)

    if not isExit:
        interact()
