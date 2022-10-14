#!/bin/python
import os
import sys
import argparse
from commonfun import *
import pyperclip

def toCpp(caseStr):
    assert isinstance(caseStr,str)
    caseStr = caseStr.replace('[','{')
    caseStr = caseStr.replace(']','}')
    print(caseStr)
    # pyperclip.copy(caseStr)

def toLC(caseStr):
    assert isinstance(caseStr,str)
    caseStr = caseStr.replace('{','[')
    caseStr = caseStr.replace('}',']')
    print(caseStr)
    # pyperclip.copy(caseStr)

def transformation(isCode):
    while True:
        cmd=input("请输入: ")
        if len(cmd) == 0:
            continue
        if '-h' in cmd:
            print('-i: 是否转化成C++代码')
            print('-e: 退出整个')
            continue
        try:   
            cmds = re.findall(e_i,cmd,re.A)
            if '-e' in cmd:
                exit()
            elif '-i' in cmds[0]:
                isCode = int(cmds[1])
            else:
                if isCode == 1:
                    toCpp(cmd)
                else:
                    toLC(cmd)
        except:
            pass


if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='转化用例')
    parse.add_argument('-c','--case',help='用例',type=str)
    parse.add_argument('-i','--isCode',help='是否转化成C++代码',type=int,nargs="?",default=1)
    arg = parse.parse_args()
    if "-c" in sys.argv:
        if arg.isCode == 1:
            toCpp(arg.case)
        else:
            toLC(arg.case)
    elif "-i" in sys.argv:
        transformation(arg.isCode)
    

