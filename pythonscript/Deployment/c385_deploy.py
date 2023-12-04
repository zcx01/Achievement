#!/bin/python
from os import system
import time
import sys
import subprocess
from execCmd import *
import argparse
from commonfun import *

pyFileDir = os.path.dirname(os.path.abspath(__file__))
qnxConfigDir = pyFileDir+"/qnx_config/"
qnxConfigPath = qnxConfigDir+"config.json"
jsConfig=getJScontent(qnxConfigPath)
androidQnx=AndroidQnx()

def adbPush(proceesNames,excess,argv):
    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    fileDict={}
    if '-a' not in argv:
        for proceesName in proceesNames:
            if proceesName not in jsConfig:
                fileDict[proceesName] = "/usr/bin/"
            else:
                fileDict[proceesName] = getKeyPath(proceesName,jsConfig)
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
        try:
            return out[len(out)-1].split("=")[1]
        except:
            pass
    return ''

def getDevDir():
    # dev = jsConfig.get(getDev(),'') 
    dev=''
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


def zip(absolutePath,user,ssh_ip):
    assert isinstance(absolutePath,str)
    filename = os.path.basename(absolutePath)
    tempdir = os.path.dirname(absolutePath)
    printYellow("如果是长时间等待不退出，就修改结尾符")
    keyStr(f'ssh {user}@{ssh_ip}')
    keyStr(f'cd {tempdir}',0,linux_end)
    # keyStr(f'md5sum {filename}')
    keyStr(f'tar -zcvf  {filename}.tgz {filename}',0,linux_end)
    keyStr('exit',0,'',False)
    SetCloseSpawn(True)
    return f'{absolutePath}.tgz'

def uzip(absolutePath):
    filename = os.path.basename(absolutePath)
    tempdir = os.path.dirname(absolutePath)
    keyStr(f"cd {tempdir}")
    keyStr(f'tar -zxvf {filename}')

def ScpFile(tmpath,user,ssh_ip):
    tmprgz = zip(tmpath,user,ssh_ip)
    tmdir = os.path.dirname(tmpath)
    if not os.path.isdir(tmdir):
        keyStr(f'mkdir -p {tmdir}')
    keyStr(f"rm -rf {tmpath}")
    keyStr(f"scp -r {user}@{ssh_ip}:{tmprgz} {tmdir}/")
    uzip(tmprgz)
    interact()
    keyStr(f'ssh {user}@{ssh_ip}')
    keyStr(f'rm {tmprgz}',0,linux_end)
    keyStr('exit',0,'',False)
    SetCloseSpawn(True)
    interact()

def ScpFileWin(tmpath,tmpathS,user,ssh_ip):
    print('download...')
    keyStr(f"scp -r {user}@{ssh_ip}:{tmpathS} {tmpath}")


def updateConfig(prjectDir,addFileName):
    updateDir = jsConfig['update']
    updateConfig = jsConfig
    for sDir,oDir in updateDir.items():
        sPrjectDir = prjectDir+"/"+sDir
        print(f'添加 {sPrjectDir}')
        for (dirpath,dirnames,filenames) in os.walk(os.path.expanduser(sPrjectDir)):
            for fileName in filenames:
                if addFileName == None or len(addFileName) == 0:
                    printGreen(f'文件 {fileName}')
                elif fileName == addFileName:
                    if fileName not in updateConfig:
                        printGreen(f'添加{fileName}')
                        updateConfig[fileName] = oDir
                        updateConfig["PC"][fileName] = sDir
                    else:
                        printGreen(f"{fileName} 已经在配置文件中")
    writeJs(qnxConfigPath,updateConfig)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='部署C385程序,部署release c385_deploy -c ic_service -d bin -p changan_c385_release -r')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-c','--customfile',help='adb push custom file list',default=[], nargs='+',type=str)
    parser.add_argument('-a','--absolutePath',help='adb push absolute file list',default=[], nargs='+',type=str)
    parser.add_argument('-q','--qnx',help='cp for qnx',nargs='*')
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    parser.add_argument('-r','--not',help='是否重启',nargs='*')
    parser.add_argument('-f','--PcFileName',help="打印自带PC上文件的名称",nargs='*')
    parser.add_argument('-s','--scp',help="从远程复制",nargs='?',default=0,type=int)
    parser.add_argument('-u','--updateConfig',help='添加文件到配置中',default='',type=str,nargs='?')
    parser.add_argument('-p','--PrjectDir',help='prject dir',default='~/Works/Repos/changan_c385/prebuilts/ic',type=str)
    parser.add_argument('-w','--scpWinDir',help='Scp win的目录',default='C:/Users/chengxiong.zhu/Downloads',type=str)
    parser.add_argument('-d','--device',help='adb的device',default='',type=str)
    args = parser.parse_args()
    argv = sys.argv
    if '-f' in argv:
        printPCFile()
        sys.exit()
    
    PrjectDir = args.PrjectDir
    home_dir = os.path.expanduser("~").replace('\\','/')
    PrjectDir = PrjectDir.replace(home_dir,"~")
    print(home_dir)
    printYellow(PrjectDir)
    
    if '-u' in argv:
        updateConfig(PrjectDir,args.updateConfig)
        sys.exit()

    if "-s" in sys.argv:
        user=jsConfig.get("user",)
        ssh_ip = jsConfig.get("ssh_ip","")
        pwd = jsConfig.get("pwd","")
        if '-a' in sys.argv:
            for tmpath in args.absolutePath:
                ScpFile(tmpath,user,ssh_ip)
    
        if '-c' in sys.argv:
            proceesNames= args.customfile
            for proceesName in proceesNames:
                if platform.system() == "Windows":
                    execbin = getExecBin(proceesName,proceesName)
                    tmpathS = f'{PrjectDir}/{execbin}/{proceesName}'
                    print(tmpathS)
                    ScpFileWin(args.scpWinDir,tmpathS,user,ssh_ip)
                else:
                    execbin = getExecBin(proceesName,proceesName)
                    tmpath = f'{PrjectDir}/{execbin}/{proceesName}'
                    ScpFile(tmpath,user,ssh_ip)
        if args.scp == 1:
            sys.exit()

    device = ""
    if len(args.device) !=0:
        device = f" -s {args.device}"

    keyStr(f'adb{device} root')
    androidQnx.setDevice(device)
    main(args,sys.argv)
    if '-a' in argv:
        copAbsolutePath(args.absolutePath)
        interact()
        exit()

    # devDir = getDevDir()
    # print('所在分支-------',devDir)
    # updateStartUp(f'{qnxConfigDir}{devDir}/')
    # if "-r" not in argv :
    #     copyStartfile(f'{qnxConfigDir}{devDir}/not_apps/startup.sh',True)
        
    # keyStr('adb root')
    if "-c" in argv :
        proceesNames= args.customfile
        if len(proceesNames) == 0:
            exit()
        if platform.system() == "Windows":
            keyStr(f"cd {args.scpWinDir}")
        else:
            keyStr(f"cd {PrjectDir}")

        exe_proceesNames=[]
        for proceesName in proceesNames:
            if platform.system() == "Windows":
                execbin = args.scpWinDir
            else:
                execbin = getExecBin(proceesName,proceesName)
            exe_proceesNames.append(f'{execbin}/{proceesName}')
        androidQnx.pc_android_qnx(exe_proceesNames)
        adbPush(proceesNames,args.excess,argv)
        # copyStartfile(f'{qnxConfigDir}{devDir}/startup.sh',False)
        if "-r" in argv : keyStr('reset')
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

    # copyStartfile(f'{qnxConfigDir}{devDir}/startup.sh',False)
    keyStr('reset')
    time.sleep(1)
   

