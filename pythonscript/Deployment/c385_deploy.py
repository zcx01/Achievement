#!/bin/python
from os import system
import time
import sys
from execCmd import *
import argparse

PrjectDir='changan_c835'


def adbPush(proceesNames,excess):
    keyStr("adb shell")
    for proceesName in proceesNames:
        keyStr(f"curl -u root:root \"ftp://192.168.1.1/data/{proceesName}\" -T /sdcard/{proceesName}",0)

    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    if '-a' not in sys.argv:
        for proceesName in proceesNames:
            keyStr(f"cp /data/{proceesName} /usr/bin/",0)
            keyStr(f"chmod +x /usr/bin/{proceesName}",0)
    
    for cmd in excess:
        keyStr(cmd,0)

    interact()
    sys.exit()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='部署C385程序')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-c','--customfile',help='adb push custom file list',default=[], nargs='+',type=str)
    parser.add_argument('-a','--absolutePath',help='adb push absolute file list',default=[], nargs='+',type=str)
    parser.add_argument('-k','--slm',help='slay slm',default=1)
    parser.add_argument('-q','--qnx',help='cp for qnx',nargs='*')
    parser.add_argument('-e','--excess',help='excess commad',nargs='*',default=[])
    args = parser.parse_args()

    if "-c" in sys.argv :
        proceesNames= args.customfile
        if len(proceesNames) == 0:
            sys.exit()
        for proceesName in proceesNames:
            os.system(f'python3 ./adb_qnx.py -k {proceesName}')
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts/ic")

        for proceesName in proceesNames:
            keyStr(f"adb push {proceesName}/{proceesName} /sdcard",0)
        adbPush(proceesNames,args.excess)

    if '-a' in sys.argv:
        proceesNames= args.absolutePath
        if len(proceesNames) == 0:
            sys.exit() 
        adbNames=[]
        for proceesName in proceesNames:
            keyStr(f"adb push {proceesName} /sdcard",0)
            adbNames.append(os.path.basename(proceesName))
        adbPush(adbNames,args.excess)

    if "-q" not in sys.argv:
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts")
        keyStr(f"adb push ic/ic_chime/ic_chime /sdcard",0)
        keyStr(f"adb push ic/ic_service/ic_service /sdcard",0)
        keyStr(f"adb push ic/mcu_service/mcu_service  /sdcard",0)
        keyStr(f"adb push ic/lib/lib_base.so  /sdcard",0)
        keyStr(f"adb push ic/lib/lib_mega_ipc.so  /sdcard",0)
        keyStr(f"adb push ic/qt/bin/ivi_compositor  /sdcard",0)
        keyStr(f"adb push ic/qt/bin/ic_telltale  /sdcard",0)
        keyStr(f"adb push ic/qt/qml/MegaIC/libmega_ic_plugin.so  /sdcard",0)
        keyStr(f"adb push ic/qt/qml/Resources/libresources_plugin.so  /sdcard",0)

        keyStr(f"adb push ic/qt/config/screen_layout_config.json /sdcard",0)
        keyStr(f"adb push ic/qt/config/icadas_config.json /sdcard",0)
        keyStr(f"adb push ic/qt/config/icscreencast_config.json /sdcard",0)
        keyStr(f"adb push ic/qt/config/ictelltale_config.json /sdcard",0)
        keyStr(f"adb push ic/qt/config/icwarning_config.json /sdcard",0)

        keyStr("adb shell")
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_chime\" -T /sdcard/ic_chime",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_service\" -T /sdcard/ic_service",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/mcu_service\" -T /sdcard/mcu_service",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/lib_base.so\" -T /sdcard/lib_base.so",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/lib_mega_ipc.so\" -T /sdcard/lib_mega_ipc.so",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ivi_compositor\" -T /sdcard/ivi_compositor",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_telltale\" -T /sdcard/ic_telltale",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/libmega_ic_plugin.so\" -T /sdcard/libmega_ic_plugin.so",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/libresources_plugin.so\" -T /sdcard/libresources_plugin.so",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/screen_layout_config.json\" -T /sdcard/screen_layout_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icadas_config.json\" -T /sdcard/icadas_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icscreencast_config.json\" -T /sdcard/icscreencast_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ictelltale_config.json\" -T /sdcard/ictelltale_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icwarning_config.json\" -T /sdcard/icwarning_config.json",0)

        keyStr("telnet cdc-qnx",1)
        keyStr("root")
        # keyStr("slay -f slm",2)
        # slay_cmd = f"slay ic_service"
        # slay_out = keyStr(slay_cmd)
        # while 'slay:' not in slay_out:
        #     keyStr(slay_cmd)
        #     time.sleep(100)

    keyStr("cp /data/ic_chime /usr/bin/",0)
    keyStr("cp /data/ic_service /usr/bin/",0)
    keyStr("cp /data/mcu_service /usr/bin/",0)
    keyStr("cp /data/lib_base.so /usr/lib64/",0)
    keyStr("cp /data/lib_mega_ipc.so /usr/lib64/",0)
    keyStr("cp /data/ivi_compositor /usr/bin/ivi_compositor",0)
    keyStr("cp /data/ic_telltale /usr/bin/ic_telltale",0)
    keyStr("cp /data/libmega_ic_plugin.so /opt/qt/qml/MegaIC/libmega_ic_plugin.so",0)
    keyStr("cp /data/libresources_plugin.so /opt/qt/qml/Resources/libresources_plugin.so",0)
    keyStr("cp /data/screen_layout_config.json /opt/qt/config",0)
    keyStr("cp /data/icadas_config.json /opt/qt/config",0)
    keyStr("cp /data/icscreencast_config.json /opt/qt/config",0)
    keyStr("cp /data/ictelltale_config.json /opt/qt/config",0)
    keyStr("cp /data/icwarning_config.json /opt/qt/config",0)
    keyStr("chmod +x /usr/bin/ic_chime",0)
    keyStr("chmod +x /usr/bin/ic_service",0)
    keyStr("chmod +x /usr/bin/mcu_service",0)
    keyStr("chmod +x /usr/bin/ivi_compositor")
    keyStr("chmod +x /usr/bin/ic_telltale")
    interact()
    # keyStr("reset",0)

