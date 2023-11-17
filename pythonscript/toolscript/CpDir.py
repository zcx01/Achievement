#!/bin/python
import os
import sys
import argparse
import shutil
from typing import Set

def generate(oriDirs,dir):
    filePaths = []
    repeatPaths={}
    for resourcesDir in oriDirs:
        for (dirpath,dirnames,filenames) in os.walk(resourcesDir):
            assert isinstance(dirpath,str)
            for fileName in filenames:
                filePath = dirpath+'/'+fileName
                if os.path.isfile(filePath) and dirpath != dir:
                    try:
                        if fileName in repeatPaths:
                            cmd = 'y'
                            # cmd = input(f'{fileName}是存在，原来的是{repeatPaths[fileName]},现在是{filePath} 是否替换y/n')
                            if cmd == "n":
                                continue
                        repeatPaths[fileName] = filePath
                        shutil.copy(filePath,dir)
                        filePaths.append(dir+fileName)
                        print(filePath)
                    except Exception as e:
                        print(f"跳过 {str(e)}  {filePath}")
    print("拷贝完成")
    y = input("是否删除y/n")
    if y == 'y':
        for filePath in filePaths:
            if os.path.isfile(filePath):
                os.remove(filePath)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-d','--dirNames',help='资源目录',nargs='*',default=[])
    parser.add_argument('-g','--generateFileName',help='生成文件名',type=str)
    arg = parser.parse_args()
    generate(arg.dirNames,arg.generateFileName)
