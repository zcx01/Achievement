#!/bin/python
import sys
from execCmd import *

import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='拷贝qnx文件')
    parser.add_argument('-p','--path',help='文件路径',default='')
    parser.add_argument('-f','--fileNames',help='文件名',nargs='+',default=['ic_service.core.gz'])  
    parser.add_argument('-a','--aimDir',help='目标目录',default='./',type=str)  
    args = parser.parse_args()
    keyStr('adb root')
    keyStr('adb shell')
    keyStr("telnet cdc-qnx",1)
    keyStr("root")

    path = args.path
    files = args.fileNames
    if path != "":
        keyStr(f'cd {path}')
    
    print(files)
    for file in files:
        keyStr(f"cp {file} /var/log/dltlogs/",0)

    SetCloseSpawn(True)
    for file in files:
        keyStr(f'adb pull /qlog/dltlogs/{os.path.basename(file)} {args.aimDir}')

    interact()