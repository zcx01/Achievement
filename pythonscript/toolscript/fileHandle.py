#!/bin/python
import os
import sys
import argparse
import shutil
from typing import Set

def generate(oriDirs):
    print(oriDirs)
    for resourcesDir in oriDirs:
        for (dirpath,dirnames,filenames) in os.walk(resourcesDir):
            assert isinstance(dirpath,str)
            for fileName in filenames:
               assert isinstance(fileName,str)
               fileName = fileName.split('-')[0].replace('NotoSans','')
               print(fileName)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-d','--dirNames',help='目录',nargs='*',default=[])
    arg = parser.parse_args()
    generate(arg.dirNames)
