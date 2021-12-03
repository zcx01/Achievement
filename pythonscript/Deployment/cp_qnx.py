#!/bin/python
import sys
from key_mouse import *

import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='拷贝qnx文件')
    parser.add_argument('-p','--path',help='文件路径',default='/var/log')
    parser.add_argument('-f','--fileNames',help='文件名',nargs='+',default=['ic_service.core'])  
    parser.add_argument('-t','--time',help='时间间隔',type=int,default=3)
    parser.add_argument('-q','--qnx',help='在qnx中',nargs='*',type=int)
    args = parser.parse_args()
    if '-q' not in sys.argv:
        keyStr('adb shell')
        keyStr("telnet cdc-qnx",1)
        keyStr("root")

    path = args.path
    files = args.fileNames
    timeSpcae = args.time
    print(timeSpcae)
    keyStr(f'cd {path}')
    
    for file in files:
        keyStr(f"cp {file} /var/log/dltlogs/",timeSpcae)
    keyStr('exit')

    for file in files:
        keyStr(f'curl -u root:root "ftp://cdc-qnx/var/log/dltlogs/{file}" -o /sdcard/{file}',timeSpcae)

    keyStr('exit')

    for file in files:
        keyStr(f'adb pull /sdcard/{file} ./')