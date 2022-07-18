#!/bin/python
import os
import sys
import argparse
import shutil

def generate(oriDirs,dir):
    filePaths = []
    for resourcesDir in oriDirs:
        for (dirpath,dirnames,filenames) in os.walk(resourcesDir):
            assert isinstance(dirpath,str)
            for fileName in filenames:
                filePath = dirpath+'/'+fileName
                if os.path.isfile(filePath) and dirpath != dir:
                    try:
                        shutil.copy(filePath,dir)
                        filePaths.append(dir+fileName)
                        print(filePath,dir)
                    except:
                        print(f"跳过 {filePath}")
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
