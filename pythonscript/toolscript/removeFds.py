#!/bin/python
import os
import sys
import argparse
import shutil
from commonfun import *
from typing import Set

# 获取脚本执行的目录
script_dir = os.path.dirname(os.path.realpath(__file__))+"/"

# 获取当前目录
current_dir = os.getcwd()

CAN_LIN_KEY_WORDS = ['CANSIG_','LINSIG_','signal->GetValue']


def removeFile(filePath):
    os.remove(filePath)
    printGreen(f"移除{filePath}")

def removeSingleFds(filePath):
    try:
        content = readFileAll(filePath)
    except:
        return False
    for CAN_LIN_KEY_WORD in CAN_LIN_KEY_WORDS:
        if CAN_LIN_KEY_WORD in content:
            removeFile(filePath)
            return True
    return False

def generate(fds):
    if  fds == None:
        fds = []
    if len(fds) == 0:
        fds.append(current_dir)
    print(current_dir)
    cppRemoveFile = []
    for resourcesDir in fds:
        for (dirpath,dirnames,filenames) in os.walk(resourcesDir):
            assert isinstance(dirpath,str)
            for fileName in filenames:
                aimFile = f'{dirpath}/{fileName}'
                if removeSingleFds(aimFile):
                    cppRemoveFile.append(getFileBaseName(fileName))
                elif getFileBaseName(fileName) in cppRemoveFile:
                    removeFile(aimFile)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='删除信号相关的fds')
    parser.add_argument('-f','--fds',help='ic_service的目录',nargs='?',default=[])
    arg = parser.parse_args()
    generate(arg.fds)
