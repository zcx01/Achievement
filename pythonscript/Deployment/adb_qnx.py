#!/bin/python
import sys
import time
from execCmd import *
import argparse



if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='qnx ')

    parser.add_argument('-r','--reset',help='reset -f',nargs='*')
    parser.add_argument('-m','--subtopic',help='su btopic',nargs='*',default=[])
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    args = parser.parse_args()

    keyStr("adb shell")
    keyStr("telnet cdc-qnx")
    keyStr("root")

    if "-m" in sys.argv:
        keyStr("mosquitto_sub -h cdc-qnx -v -t \"#\" ")

    if '-r' in sys.argv:
        keyStr("mcu_tool -g 2")
        keyStr("reset -f")
        exit(1)
    if '-e' in sys.argv:
        for cmd in args.excess:
            keyStr(cmd,0)
    interact()