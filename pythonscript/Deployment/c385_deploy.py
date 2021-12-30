#!/bin/python
from os import system
import time
import sys
import subprocess
from execCmd import *
import argparse
from commonfun import *

# PrjectDir='changan_c835'
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/qnx_config/"
jsConfig=getJScontent(pyFileDir+"config.json")
androidQnx=AndroidQnx()

def adbPush(proceesNames,excess,argv):
    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    fileDict={}
    if '-a' not in argv:
        for proceesName in proceesNames:
            fileDict[proceesName] = "/usr/bin/"
        androidQnx.qnx_cp(fileDict,True)
    else:
        for proceesName in proceesNames:
            fileDict[proceesName] = getKeyPath(proceesName,jsConfig)
        androidQnx.qnx_cp(fileDict,False)
    for cmd in excess:
        keyStr(cmd,0)

def copAbsolutePath(proceesNames):
    if len(proceesNames) == 0:
        exit() 
    androidQnx.pc_android_qnx(proceesNames)
    adbNames=[]
    for proceesName in proceesNames:
        adbNames.append(os.path.basename(proceesName))
    adbPush(adbNames,args.excess,['-a'])

def copyStartfile(path,isWait):
    SetCloseSpawn(True)
    copAbsolutePath([path])
    keyStr("reset")
    SetCloseSpawn(True)
    if isWait:
        time.sleep(5)
        for j in range(120):
            adb_out = subprocess.getoutput("adb devices").split('\n')
            if len(adb_out) >= 3:
                if j >=3:
                    time.sleep(20)
                break
            print(f"车机重启中...等待{j+1}秒")
            time.sleep(1)

def main(args,argv):
    pass
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='部署C385程序,部署release c385_deploy -c ic_service -d bin -p changan_c835_release -r')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-c','--customfile',help='adb push custom file list',default=[], nargs='+',type=str)
    parser.add_argument('-a','--absolutePath',help='adb push absolute file list',default=[], nargs='+',type=str)
    parser.add_argument('-q','--qnx',help='cp for qnx',nargs='*')
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    parser.add_argument('-r','--not',help='excess commad',nargs='*')
    parser.add_argument('-d','--dir',help='exe dir',default='',type=str)
    parser.add_argument('-p','--PrjectDir',help='prject dir',default='changan_c835',type=str)
    args = parser.parse_args()
    argv = sys.argv
    PrjectDir = args.PrjectDir
    keyStr('adb root')
    main(args,sys.argv)
    if '-a' in argv:
        copAbsolutePath(args.absolutePath)
        interact()
        exit()

    if "-r" not in argv :
        copyStartfile(f'{pyFileDir}/dev1.1/not_apps/startup.sh',True)
        
    keyStr('adb root')
    if "-c" in argv :
        proceesNames= args.customfile
        if len(proceesNames) == 0:
            exit()
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts/ic")

        exe_proceesNames=[]
        for proceesName in proceesNames:
            execbin=proceesName
            if len(args.dir) != 0:
                execbin = args.dir
            exe_proceesNames.append(f'{execbin}/{proceesName}')
        androidQnx.pc_android_qnx(exe_proceesNames)
        adbPush(proceesNames,args.excess,argv)
        copyStartfile(f'{pyFileDir}/dev1.1/startup.sh',False)
        exit()

    if "-q" not in argv:
        
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts")
        androidQnx.pc_android_qnx([
        "ic/ic_chime/ic_chime",
        "ic/ic_service/ic_service",
        "ic/mcu_service/mcu_service ",
        "ic/lib/lib_base.so ",
        "ic/lib/lib_mega_ipc.so ",
        "ic/qt/bin/ivi_compositor ",
        "ic/qt/bin/ic_telltale ",
        "ic/qt/qml/MegaIC/libmega_ic_plugin.so ",
        "ic/qt/qml/Resources/libresources_plugin.so ",

        "ic/qt/config/screen_layout_config.json",
        "ic/qt/config/icadas_config.json",
        "ic/qt/config/icscreencast_config.json",
        "ic/qt/config/ictelltale_config.json",
        "ic/qt/config/icwarning_config.json"])

        keyStr("telnet cdc-qnx")
        keyStr("root")

    fileDict={}
    fileDict['ic_chime']='/usr/bin/'
    fileDict['ic_service']='/usr/bin/'
    fileDict['mcu_service']='/usr/bin/'
    fileDict['ivi_compositor'] = '/usr/bin/ivi_compositor'
    fileDict['ic_telltale'] = '/usr/bin/ic_telltale'
    androidQnx.qnx_cp(fileDict,True)

    fileDict.clear()
    fileDict['lib_base.so']='/usr/lib64/'
    fileDict['lib_mega_ipc.so']='/usr/lib64/'
    fileDict['libmega_ic_plugin.so']='/opt/qt/qml/MegaIC/libmega_ic_plugin.so'
    fileDict['libresources_plugin.so']='/opt/qt/qml/Resources/libresources_plugin.so'
    fileDict['screen_layout_config.json']='/opt/qt/config'
    fileDict['icadas_config.json']='/opt/qt/config'
    fileDict['icscreencast_config.json']='/opt/qt/config'
    fileDict['ictelltale_config.json']='/opt/qt/config'
    fileDict['icwarning_config.json']='/opt/qt/config'
    androidQnx.qnx_cp(fileDict,False)

    copyStartfile(f'{pyFileDir}startup.sh',False)
   

