#!/bin/python
import subprocess
import os
try:
    from analyze_dbc.projectInI import *
except:
    gitStoreInfos={
        "~/Works/Repos/changan_j90a/qt/ic_apps/ic_dashboard/":
        ['content_Dark_j90a','content_Light_j90a']
    }
    gitnore=['ui.qml']

def printRed(infoStr):
    print('\033[31m'+infoStr+'\033[0m')

def printGreen(infoStr):
    print('\033[32m'+infoStr+'\033[0m')
    
def printYellow(infoStr):
    print('\033[33m'+infoStr+'\033[0m')

def execCmd(cmd):
    print(cmd)
    os.system(cmd)

def getChangedFileInfo(fileInfo):
    assert isinstance(fileInfo,str)
    changeFiles  = fileInfo.split(" ")
    return changeFiles[0]," ".join(changeFiles[1:])

def getSuffix(filePath):
    fileName =  os.path.basename(filePath)
    fileNames = fileName.split(".")
    if len(fileNames) <= 1:
        return filePath
    return ".".join(fileNames[1:])


def getChangeFileDir(changeFile):
    changeFileDir = os.path.dirname(changeFile)
    changeFileDirs = changeFileDir.split("/")
    if len(changeFileDirs) <= 1:
        return  changeFileDir,''
    return changeFileDirs[0],'/'.join(changeFileDirs[1:])
    
def Sync(gitStore,SyncDirs):
    cmdStr = f'cd {gitStore} && git status -s'
    p = subprocess.Popen(cmdStr,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.STDOUT,
                        shell=True)
    changeFiles=[]
    for line in iter(p.stdout.readline, b''):
        changeFiles.append(line.rstrip().decode('utf8').strip())

    changeTypeInfos={}
    ischangeTypeInfosTip=False
    for fileInfo in changeFiles:
        changeType,changeFile = getChangedFileInfo(fileInfo)
        if changeType == "??":changeType='A'
        if getSuffix(changeFile) in gitnore:
            printYellow(f'{fileInfo} 在忽略文件中，跳过...')
            continue

        changeFileDir,childFileDir = getChangeFileDir(changeFile)
        changeFileName = os.path.basename(changeFile)
        if changeType not in changeTypeInfos:
            changeTypeInfos[changeType] = set()
        if changeType=='M':
            cmdStr = f'cd {gitStore} && git diff {changeFile}> {gitStore}tmp.patch'
            execCmd(cmdStr)
            # print(changeFileDir)
            for SyncDir in SyncDirs:
                if SyncDir != changeFileDir:
                    sysFileName = fileInfo.replace(changeFileDir,SyncDir)
                    # print(sysFileName)
                    if sysFileName in changeFiles:
                        printYellow(f'{sysFileName} 文件有修改，跳过...')
                        continue
                    cmdStr = f'cd {gitStore}{SyncDir}/{childFileDir} && patch < {gitStore}tmp.patch'
                    execCmd(cmdStr)
            cmdStr = f'rm {gitStore}tmp.patch'
            execCmd(cmdStr)
        elif  changeType=='A':
            for SyncDir in SyncDirs:
                if SyncDir != changeFileDir:
                    addFilePath = changeFile.replace(changeFileDir,SyncDir)
                    if not os.path.exists(gitStore+addFilePath):
                        cmdStr = f'cp {gitStore}{changeFile} {gitStore}{SyncDir}'
                        execCmd(cmdStr)
                    changeTypeInfos['A'].add(addFilePath)
                    ischangeTypeInfosTip =True
        elif changeType=='D':
            for SyncDir in SyncDirs:
                if SyncDir != changeFileDir:
                    remveFilePath = changeFile.replace(changeFileDir,SyncDir)
                    if os.path.exists(gitStore+remveFilePath):
                        cmdStr = f'rm {gitStore}{remveFilePath}'
                        exec(cmdStr)
                    changeTypeInfos[changeType].add(remveFilePath)
                    ischangeTypeInfosTip =True

    if ischangeTypeInfosTip:
        printRed('有文件的增加和删除，请修改对应的qrc文件')
        for changeType,fileNames in changeTypeInfos.items():
            if len(fileNames) == 0:
                continue
            if changeType == 'A':
                print('增加的文件有:')
            elif changeType == 'D':
                print('删除的文件有:')
            print('\n'.join(fileNames))

if __name__ == "__main__":
    for gitStore,SyncDirs in gitStoreInfos.items():
        Sync(os.path.abspath(gitStore)+'/',SyncDirs)