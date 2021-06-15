import os
import sys

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

def createfile(fileName,type):
    configDir = getConifgDir(type,configFilePath)
    if not(os.path.isdir(configDir)):
        print("没有此类型！")
        return
    className = getClassName(fileName)
    for (dirpath,dirnames,filenames) in os.walk(configDir):
        for oriName in filenames:
            oriPath = f'{dirpath}/{oriName}'
            aimPath = f'{os.getcwd()}/{fileName}{os.path.splitext(oriName)[1]}'
            r = open(oriPath,"r")
            w = open(aimPath,"w")
            contents = r.readlines()
            r.close()
            for content in contents:
                newContent = getNewContent(content,"{ClassName}",className)
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
            print(dirname)

if __name__== "__main__":
    if len(sys.argv) == 2  and (sys.argv[1] == "-s" or sys.argv[1]=='s'):
        showType()
        exit()
    if len(sys.argv) < 2:
        print("请输入文件名称")
    if len(sys.argv) < 3:
        print("输入文件类型")
    createfile(sys.argv[1],sys.argv[2])
