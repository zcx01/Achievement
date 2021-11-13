#!/bin/python
import sys
from key_mouse import *

import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='拷贝qnx文件')
    parser.add_argument('-f','--file',help='文件路径')  
    parser.add_argument('-q','--qnx',help='在qnx中',nargs='*')
    args = parser.parse_args()
    if '-q' not in sys.argv:
        keyStr('adb shell')
        keyStr("telnet cdc-qnx",1)
        keyStr("root")

    file = args.file
    keyStr(f"cp {file} /var/log/dltlogs/")
    keyStr('exit')
    keyStr(f'curl -u root:root "ftp://cdc-qnx/var/log/dltlogs/{file}" -o /sdcard/{file}')
    keyStr('exit')
    keyStr(f'adb pull /sdcard/{file} ./')