#!/bin/python
from importlib.resources import path
import inspect
from os import system
from traceback import print_exc
import time
import sys
import subprocess
from execCmd import *
import argparse
from commonfun import *

pyFileDir = os.path.dirname(os.path.abspath(__file__))
qnxConfigDir = pyFileDir+"/qnx_config/"
jsConfig=getJScontent(qnxConfigDir+"config.json")
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
    pass
    # SetCloseSpawn(True)
    # copAbsolutePath([path])
    # if isWait:
    #     keyStr("reset")
    #     time.sleep(1)
    #     SetCloseSpawn(True)
    #     time.sleep(5)
    #     for j in range(120):
    #         adb_out = subprocess.getoutput("adb devices").split('\n')
    #         if len(adb_out) >= 3:
    #             if j >=3:
    #                 time.sleep(20)
    #             break
    #         print(f"车机重启中...等待{j+1}秒")
    #         time.sleep(1)

def main(args,argv):
    pass

def getDev():
    out = subprocess.getoutput(f"python3 {pyFileDir}/adb_qnx.py -e \'cat etc/version\' -i 0").splitlines()
    if len(out) != 0:
        return out[len(out)-1].split("=")[1]
    return ''

def getDevDir():
    dev = jsConfig.get(getDev(),'') 
    if len(dev)== 0:
        return jsConfig['Other']
    return dev
    

def updateStartUp(qnxConfig_hqx):
    assert isinstance(qnxConfig_hqx,str)
    os.system(f'python3 {pyFileDir}/cp_qnx.py -p /scripts/ -f startup.sh -a {qnxConfig_hqx}')
    not_appsStartUp=qnxConfig_hqx+'not_apps/startup.sh'
    os.system(f'cp {qnxConfig_hqx}startup.sh {not_appsStartUp}')
    print(f'正在修改{not_appsStartUp}文件')
    content = readFileAll(not_appsStartUp)
    content = content.replace('/bin/slm','# /bin/slm')
    writeFileAll(not_appsStartUp,content)

def getExecBin(defultDir,execName):
    pcDirs = jsConfig.get("PC","")
    tempDir = pcDirs.get(execName,"")
    if len(tempDir) != 0:
        return tempDir
    return defultDir

def printPCFile():
    pcDirs = jsConfig.get("PC","")
    assert isinstance(pcDirs,dict)
    pcFiles = list(pcDirs.keys())
    for pcFile in pcFiles:
        print(pcFile)

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
    parser.add_argument('-f','-PcFileName',help="打印自带PC上文件的名称",nargs='*')
    parser.add_argument('-s','-sship',help="从远程复制",default=jsConfig.get("ssh_ip",""))
    parser.add_argument('-p','--PrjectDir',help='prject dir',default='~/Works/Repos/changan_c835/prebuilts/ic',type=str)
    args = parser.parse_args()
    argv = sys.argv
    if '-f' in argv:
        printPCFile()
        sys.exit()
    PrjectDir = args.PrjectDir

    if "-s" in sys.argv:
        user=jsConfig.get("user",)
        ip = jsConfig.get("ssh_ip","")
        if '-a' in sys.argv:
            tmdir = os.path.dirname(args.absolutePath)
            if not os.path.isdir(tmdir):
                os.system(f'mkdir -p {tmdir}')
            os.system(f"scp -r {user}@{args.ip}:{args.absolutePath} {tmdir}/")
    
        if '-c' in sys.argv:
            if not os.path.isdir(args.customfile):
                os.system(f'mkdir -p {args.customfile}')
            os.system(f"scp -r {user}@{args.ip}:{args.customfile}/* {args.customfile}/")

    keyStr('adb root')
    main(args,sys.argv)
    if '-a' in argv:
        copAbsolutePath(args.absolutePath)
        interact()
        exit()

    devDir = getDevDir()
    print('所在分支-------',devDir)
    updateStartUp(f'{qnxConfigDir}{devDir}/')
    if "-r" not in argv :
        copyStartfile(f'{qnxConfigDir}{devDir}/not_apps/startup.sh',True)
        
    keyStr('adb root')
    if "-c" in argv :
        proceesNames= args.customfile
        if len(proceesNames) == 0:
            exit()
        keyStr(f"cd {PrjectDir}")

        exe_proceesNames=[]
        for proceesName in proceesNames:
            execbin = getExecBin(proceesName,proceesName)
            if len(args.dir) != 0:
                execbin = args.dir
            exe_proceesNames.append(f'{execbin}/{proceesName}')
        androidQnx.pc_android_qnx(exe_proceesNames)
        adbPush(proceesNames,args.excess,argv)
        copyStartfile(f'{qnxConfigDir}{devDir}/startup.sh',False)
        keyStr('reset')
        time.sleep(1)
        exit()

    if "-q" not in argv:
        keyStr(f"cd {PrjectDir}")
        androidQnx.pc_android_qnx([
        "ic_chime/ic_chime",
        "ic_service/ic_service",
        "mcu_service/mcu_service ",
        "lib/lib_base.so",
        "lib/lib_mega_ipc.so",
        "qt/bin/ivi_compositor",
        "qt/qml/MegaIC/libmega_ic_plugin.so",
        "qt/qml/Resources/libresources_plugin.so",

        "qt/config/screen_layout_config.json",
        "qt/config/icadas_config.json",
        "qt/config/icscreencast_config.json",
        "qt/config/ictelltale_config.json",
        "qt/config/icwarning_config.json"])

        keyStr("telnet cdc-qnx")
        keyStr("root")

    fileDict={}
    fileDict['ic_chime']='/usr/bin/'
    fileDict['ic_service']='/usr/bin/'
    fileDict['mcu_service']='/usr/bin/'
    fileDict['ivi_compositor'] = '/usr/bin/'
    androidQnx.qnx_cp(fileDict,True)

    fileDict.clear()
    fileDict['lib_base.so']='/lib64/'
    fileDict['lib_mega_ipc.so']='/lib64/'
    fileDict['libmega_ic_plugin.so']='/opt/qt/qml/MegaIC/libmega_ic_plugin.so'
    fileDict['libresources_plugin.so']='/opt/qt/qml/Resources/libresources_plugin.so'
    fileDict['screen_layout_config.json']='/opt/qt/config'
    fileDict['icadas_config.json']='/opt/qt/config'
    fileDict['icscreencast_config.json']='/opt/qt/config'
    fileDict['ictelltale_config.json']='/opt/qt/config'
    fileDict['icwarning_config.json']='/opt/qt/config'
    androidQnx.qnx_cp(fileDict,False)

    copyStartfile(f'{qnxConfigDir}{devDir}/startup.sh',False)
    keyStr('reset')
    time.sleep(1)
   

