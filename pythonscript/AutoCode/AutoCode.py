import os
from posixpath import dirname
import sys
import json
from subprocess import Popen
from typing import List

configFilePath = os.path.abspath(__file__)

def getConifgDir(type,config):
    cfg = os.path.dirname(config)
    return cfg+"/"+type

def getClassName(fileName):
    className=''
    isUpper = True
    for c in fileName:
        if c == '_':
            isUpper = True
            continue
        if isUpper :
            className += str(c).upper()
            isUpper = False
        else:
            className += c
    return className

def getNewContent(ori,oriStr,rStr):
    newContent = ori.replace(f'{oriStr}',rStr)
    newContent = newContent.replace(f'{oriStr.upper()}',rStr.upper())
    newContent = newContent.replace(f'{oriStr.lower()}',rStr.lower())
    return newContent

def getJScontent(dirPath):
    configJson = f'{dirPath}/config.json'
    cr = open(configJson, "r")
    return json.load(cr)

def createfile(fileName,type,replaceList):
    configDir = getConifgDir(type,configFilePath)
    if not(os.path.isdir(configDir)):
        print("没有此类型！")
        return
    className = getClassName(fileName)
    for (dirpath,dirnames,filenames) in os.walk(configDir):
        aimPaths = getJScontent(dirpath)

        for oriName in filenames:
            if oriName=="config.json":
                continue
            oriPath = f'{dirpath}/{oriName}'

            #得到目标文件路径
            suffix = os.path.splitext(oriName)[1]
            if suffix in aimPaths:
                aimPath = aimPaths[suffix]
            else:
                aimPath = os.getcwd()

            #得到文件名
            if  oriName.find("{fileName}") != -1:
                aimPath = f'{aimPath}/{oriName.replace("{fileName}",fileName)}'
            else:
                aimPath = f'{aimPath}/{fileName}{suffix}'

            r = open(oriPath,"r")
            w = open(aimPath,"w")
            contents = r.readlines()
            r.close()

            #进行替换
            for content in contents:
                newContent = getNewContent(content,"{ClassName}",className)
                newContent = getNewContent(newContent,"{fileName}",fileName)
                #参数名和对应参数替换
                index=0
                for replacestr in replaceList:
                    newContent = getNewContent(newContent,f'{{{index}}}',replacestr)
                    index+=1

                w.write(newContent)

            w.flush()
            w.close()
            print("生成  "+aimPath+'    文件')
    print("生存完成!")

def showType():
    dirPath = os.path.dirname(configFilePath)
    for dirname in os.listdir(dirPath):
        typePath = dirPath+'/'+dirname
        if(os.path.isdir(typePath)):
            js = getJScontent(typePath)
            if "desc" in js:
                print(f'{dirname:<25}'+js["desc"])
            else:
                print(dirname)

def userVSCodeOpenType(type):
    configDir = getConifgDir(type,configFilePath)
    if not(os.path.isdir(configDir)):
        print("没有此类型！")
        return
    proc = Popen(
        args=f'code {configDir}',
        shell=True
    )


if __name__ == "__main__":
    if len(sys.argv) == 2 :
        if sys.argv[1] == "-s" or sys.argv[1] == 's':
            showType()
            exit()
        elif sys.argv[1] == "-c" or sys.argv[1] == 'code':
            userVSCodeOpenType("")
            exit()

    if len(sys.argv) == 3:
        if sys.argv[1] == "code" or sys.argv[1] == "c":
            userVSCodeOpenType(sys.argv[2])
            exit()

    if len(sys.argv) < 2:
        print("请输入文件名称")
        exit()

    if len(sys.argv) < 3:
        print("输入文件类型")
        exit()
    replaceList = list(sys.argv)
    del replaceList[0]
    del replaceList[0]
    del replaceList[0]
    createfile(sys.argv[2], sys.argv[1],replaceList)
