#!/bin/python
import os
import argparse

# 获取脚本执行的目录
script_dir = os.path.dirname(os.path.realpath(__file__))+"/"

# 获取当前目录
current_dir = os.getcwd()

generateProject = "j90a"
oriProject = "c385"

def command(cmd):
    print(cmd)
    os.system(cmd)


def cpfile(oriPath,aimPath):
    if os.path.exists(aimPath):
        command(f"rm -rf {aimPath}")
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


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-g','--generateDir',help='生成文件目录',nargs='*',default=[])
    parser.add_argument('-t','--cpType',help='拷贝的类型，1是拷贝目录，2是拷贝目录，3是都拷贝',nargs='?',default=3,type=int)
    arg = parser.parse_args()
    generate(arg.generateDir,arg.cpType)
