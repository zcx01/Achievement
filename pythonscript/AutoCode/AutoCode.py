import os
from posixpath import dirname
from re import T
import sys
import json
from subprocess import Popen
from typing import List
# sys.path.append("..")
from commonfun import *

configFilePath = os.path.abspath(__file__)

def commadEqual(f,t):
    if f == "-"+t or f == "--"+t or f == t:
        return True
    return False

def commadsEqual(inputCmd,cmds):
    if str(type(cmds)).find("list") !=-1:
        for cmd in cmds:
            if(commadEqual(cmd,inputCmd)):
                return True
        return False
    else:
        return commadEqual(inputCmd,cmds)

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

def getFileName(className):
    fileName=""
    index=0
    count = 0
    for c in className:
        if str(c).isupper():
            temp =""
            if index !=0 and count ==0:
                temp = "_"
            count+=1
            if count >= 3:
                count =0
            fileName+=temp + str(c).lower()
        else:
            count=0
            fileName+=c
        index+=1
    return fileName

def getJScontent(dirPath):
    configJson = f'{dirPath}/config.json'
    cr = open(configJson, "r")
    return json.load(cr)

def strRepalce(ori,oriStr,rStr):
    newContent=""
    index=0
    try:
        while index < len(ori):
            beforeIndex=index
            index = ori.index(oriStr,index)
            newContent+=ori[beforeIndex:index]
            nextStr=ori[index:]
            jStr=nextStr[len(oriStr):].strip()
            subtraction="{-s}"
            subtractionEnd="{-e}"
            if jStr.startswith(subtraction):
                temp=jStr.replace(subtraction,"").strip()
                temp=temp.split(subtractionEnd)[0]
                index=ori.index(temp,index)+len(temp)+len(subtractionEnd)
                temp=rStr.replace(temp,"")
                newContent+=temp
            else:
                index+=len(oriStr)
                newContent+=rStr
    except:
        if len(newContent) ==0:
            return ori
        else:
            newContent+=ori[index:]
            return newContent
    return newContent

def getNewContent(ori,oriStr,rStr):
    # newContent = ori.replace(oriStr,rStr)
    # newContent = newContent.replace(oriStr.upper(),rStr.upper())
    # newContent = newContent.replace(oriStr.lower(),rStr.lower())
    newContent =strRepalce(ori,oriStr,rStr)
    newContent =strRepalce(newContent,oriStr.upper(),rStr.upper())
    newContent =strRepalce(newContent,oriStr.lower(),rStr.lower())
    return newContent

def contentRepalce(content,replaceList,className,fileName):
    newContent = getNewContent(content,"{ClassName}",className)
    newContent = getNewContent(newContent,"{fileName}",fileName)
    #参数名和对应参数替换
    index=1
    for replacestr in replaceList:
        newContent = getNewContent(newContent,f'{{{index}}}',replacestr)
        index+=1
    return newContent

def analylineBrackets(content):
    num=0
    for char in content:
        if char == '{':
            num+=1
        elif char == "}":
            num-=1
    return num

def modifyFile(jsConfig,replaceList,className,fileName):

    try:
        modifyDist=jsConfig["M"]
    except:
        return

    for contentValue in modifyDist:
        contents=[]
        text=contentValue["content"]
        if type(text) == str:
            contents.append(text)
        else:
            contents=text
        newContentlist=[]
        for index,content in enumerate(contents):
            newContentlist += contentRepalce(content,replaceList,className,fileName)
            if index != len(contents)-1:
                newContentlist+="\n"

        path=contentValue["path"]
        pos=contentValue["pos"]

        #pos 为空，就在最后添加
        # if len(pos) == 0:
        #     w_in = open(path,"a")
        #     w_in.write("\n")
        #     w_in.writelines(newContentlist)
        #     w_in.close()
        #     continue

        r_in=open(path)
        lineContents=r_in.readlines()
        r_in.close()
        w_in = open(path,"w")
        isStart=False
        isFinish=False
        bracketsNum=-1
        #找到修改的位置
        for lineContent in lineContents:
            #如果没有写入就找位置，已经写入就不找位置
            if not isFinish:
                #找开始的位置
                if not isStart:
                    if pos in lineContent and ";" not in lineContent:
                        isStart = True

                if isStart:
                    #找开始括号的位置
                    #出现括号的位置开始统计左括号的位置
                    if bracketsNum == -1:
                        if "{" in lineContent:
                            bracketsNum=0
                            bracketsNum+=analylineBrackets(lineContent)
                    else:
                        bracketsNum+=analylineBrackets(lineContent)
                    
                    #写入内容
                    if bracketsNum==0:
                        index=lineContent.find("}")
                        w_in.write(lineContent[0:index])
                        w_in.writelines(newContentlist)
                        w_in.write("\n")
                        w_in.write(lineContent[index:])
                        isFinish=True
                        continue

            w_in.write(lineContent)

        #如果没有找到，就在最后添加
        if not isFinish:
            w_in.write("\n")
            w_in.writelines(newContentlist)
        print(f"修改 {path} 完成")
        w_in.close()
                

def createfile(fileName,type,replaceList):
    configDir = getConifgDir(type,configFilePath)
    if not(os.path.isdir(configDir)):
        print("没有此类型！")
        return
    if "_" in fileName:
        className = getClassName(fileName)
    else:
        className=fileName
        fileName=getFileName(className)
    print(f'class {className}')
    for (dirpath,dirnames,filenames) in os.walk(configDir):
        jsConfig = getJScontent(dirpath)

        for oriName in filenames:
            if oriName=="config.json":
                continue
            oriPath = f'{dirpath}/{oriName}'

            #得到目标文件路径
            suffix = os.path.splitext(oriName)[1]
            if(suffix.find("h") !=-1 ):
                print(f'#include "{fileName}{suffix}"')
            if suffix in jsConfig:
                aimPath = jsConfig[suffix]
            else:
                aimPath = os.getcwd()

            #得到文件名
            if  oriName.find("{fileName}") != -1:
                aimPath = f'{aimPath}/{oriName.replace("{fileName}",fileName)}'
            else:
               aimPath = f'{aimPath}/{fileName}{suffix}'

            if os.path.exists(aimPath) :
                print("文件已经存在，是否替换(y/n)？")
                isReplce = input()
                if isReplce == 'n':
                    continue
                
            r = open(oriPath,"r")
            w = open(aimPath,"w")
            contents = r.readlines()
            r.close()

            #进行替换
            for content in contents:
                newContent = contentRepalce(content,replaceList,className,fileName)
                w.write(newContent)
            w.flush()
            w.close()
            if(suffix.find("cpp ") !=-1 ):
                print("python3 filedbc.py "+aimPath)
            else:
                print("生成  "+aimPath+'    文件')

    #通过 config 修改文件
    modifyFile(jsConfig,replaceList,className,fileName)

    printGreen("生成代码完成!")

def showType():
    if len(sys.argv) == 2 :
        commad="t"
        if commadsEqual(sys.argv[1],commad):
            dirPath = os.path.dirname(configFilePath)
            index=1
            for dirname in os.listdir(dirPath):
                typePath = dirPath+'/'+dirname
                if os.path.isdir(typePath):
                    try:
                        js = getJScontent(typePath)
                        if "desc" in js:
                            # print(f'{dirname:<35}')
                            print(f'{str(index):<6}{dirname:<35}'+js["desc"])
                        else:
                            print(f'{str(index):<6}{dirname:<35}')
                    except:
                        pass
                index+=1
            exit()

def getTypeByIndex(currnetType):
    dirPath = os.path.dirname(configFilePath)
    index=1
    for dirname in os.listdir(dirPath):
        typePath = dirPath+'/'+dirname
        if(os.path.isdir(typePath)):
            if(index == currnetType):
                return dirname
        index+=1
    

def userVSCodeOpenType():
    commad=["c","code"]
    if len(sys.argv) >= 2 :
        if commadsEqual(sys.argv[1],commad):
            try:
                type=sys.argv[2]
            except:
                type=""
            configDir = getConifgDir(type,configFilePath)
            if not(os.path.isdir(configDir)):
                print("没有此类型！")
                return
            proc = Popen(
                args=f'code {configDir}',
                shell=True
            )
            exit()

# createfile("vc_test","vehctrl",["CDC_2D2__CdcTotMilg","TOPIC_VEHCTRL_CDC_TOT_MILG","测试","float"])
if __name__ == "__main__":
    if len(sys.argv) == 1 :
        print("请输入:AutoCode 类型 类名，如")
        print("AutoCode vehctrl vc_discharge_soc CDC_2D2__CdcDchaSocLimit TOPIC_VEHCTRL_CDC_DCHA_SOC_LIMIT 交流放电截止SOC设置请求")
        exit()

    showType()
    userVSCodeOpenType()
    if commadEqual(sys.argv[1],"help"):
        print(open( os.path.dirname(configFilePath)+"/README.txt").read())
    
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
    typename=sys.argv[1]

    try:
        if(type(int(sys.argv[1])) == int):
            typename=getTypeByIndex(int(sys.argv[1]))
    except:
        typename=sys.argv[1]
    print(replaceList)
    createfile(sys.argv[2], typename,replaceList)
