#!/bin/python
import sys
from execCmd import *

import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='拷贝qnx文件')
    parser.add_argument('-p','--path',help='文件路径',default='/var/log')
    parser.add_argument('-f','--fileNames',help='文件名',nargs='+',default=['ic_service.core'])  
    args = parser.parse_args()
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

    is_close_spawn = True
    for file in files:
        keyStr(f'adb pull /sdcard/{file} ./')

    interact()