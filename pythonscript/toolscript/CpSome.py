#!/bin/python
import os
import argparse
import subprocess
import sys

# 获取脚本执行的目录
script_dir = os.path.dirname(os.path.realpath(__file__))+"/"

# 获取当前目录
current_dir = os.getcwd()

generateProject = "j90a"
oriProject = "c385"

ignore=[".o"]

def command(cmd):
    print(cmd)
    os.system(cmd)

def getSuffix(fileName):
    suffixs = os.path.splitext(fileName)
    if len(suffixs) > 1 :
        return suffixs[1]    
    return ''


def cpfile(oriPath,aimPath,isCreateDir=False):
    if os.path.exists(aimPath):
        command(f"rm -rf {aimPath}")
    if isCreateDir:
        aimPathDir = os.path.dirname(aimPath)
        if not os.path.exists(aimPathDir):
            os.makedirs(aimPathDir)
    command(f'cp -rf {oriPath} {aimPath}')

def generate(generateDir,cpType):
    if  generateDir == None:
        generateDir = []
    if len(generateDir) == 0:
        generateDir.append(current_dir)

    for resourcesDir in generateDir:
        resourcesDir = os.path.abspath(resourcesDir)
        print(resourcesDir)
        oriPath = resourcesDir.replace(generateProject,oriProject)
        print(oriPath)
        for (dirpath,dirnames,filenames) in os.walk(oriPath):
            assert isinstance(dirpath,str)
            if dirpath == oriPath:
                if cpType & 1:
                    for fileName in filenames:
                        cpfile(f'{oriPath}/{fileName}',f'{resourcesDir}/{fileName}')
                if cpType & 2:
                    for dirname in dirnames:
                        if not dirname.startswith("."):
                            cpfile(f'{oriPath}/{dirname}',f'{resourcesDir}/{dirname}')

def CpSameFile(fileNames,generateDir):
    if len(fileNames) == 0:
        print("文件名是空的")
        return
    for fileName in fileNames:
        shellCmd = f'locate {fileName} | grep changan_{oriProject}'
        outputs = subprocess.check_output(shellCmd, shell=True).decode('utf-8').splitlines()
        for output in outputs:
            if getSuffix(output) not in ignore:
                if len(generateDir) == 0:
                    cpfile(output,output.replace(oriProject,generateProject),True)
                else:
                    cpfile(output,generateDir[0],True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-g','--generateDir',help='生成文件目录',nargs='*',default=[])
    parser.add_argument('-t','--cpType',help='拷贝的类型，1是拷贝文件，2是拷贝目录，3是都拷贝',nargs='?',default=3,type=int)
    parser.add_argument('-f','--cpFileName',help='拷贝的文件名称',nargs='+',default=[],type=str)
    parser.add_argument('-o','--oriProjectName',help='原项目名称',nargs='?',default='c385',type=str)
    parser.add_argument('-p','--projectName',help='当前项目名称',nargs='?',default='j90a',type=str)
    arg = parser.parse_args()
    
    if len(arg.oriProjectName) != 0:
        oriProject = arg.oriProjectName
    if len(arg.projectName) != 0:
        generateProject = arg.projectName
    if '-f' in sys.argv:
        CpSameFile(arg.cpFileName,arg.generateDir)
    else:
        generate(arg.generateDir,arg.cpType)
