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
    keyStr('adb root')
    keyStr('adb shell')
    keyStr("telnet cdc-qnx",1)
    keyStr("root")

    path = args.path
    files = args.fileNames
    keyStr(f'cd {path}')
    
    print(files)
    for file in files:
        keyStr(f"cp {file} /var/log/dltlogs/",0)
        keyStr(f"chmod 777 /var/log/dltlogs/{file}",0)

    SetCloseSpawn(True)
    for file in files:
        keyStr(f'adb pull /qlog/dltlogs/{file} ./')

    interact()