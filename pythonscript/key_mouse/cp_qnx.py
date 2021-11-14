#!/bin/python
import sys
from key_mouse import *

import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='拷贝qnx文件')
    parser.add_argument('-f','--file',help='文件路径')  
    parser.add_argument('-t','--time',help='时间间隔',type=int,default=3)
    parser.add_argument('-q','--qnx',help='在qnx中',nargs='*',type=int)
    args = parser.parse_args()
    if '-q' not in sys.argv:
        keyStr('adb shell')
        keyStr("telnet cdc-qnx",1)
        keyStr("root")

    filePath = args.file
    path = os.path.dirname(filePath)
    file = os.path.basename(filePath)
    timeSpcae = args.time
    print(timeSpcae)
    keyStr(f'cd {path}')
    keyStr(f"cp {file} /var/log/dltlogs/",timeSpcae)
    keyStr('exit')
    keyStr(f'curl -u root:root "ftp://cdc-qnx/var/log/dltlogs/{file}" -o /sdcard/{file}',timeSpcae)
    keyStr('exit')
    keyStr(f'adb pull /sdcard/{file} ./')