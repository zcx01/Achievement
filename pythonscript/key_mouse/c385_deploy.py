#!/bin/python
import time
import sys
from key_mouse import *
import argparse

PrjectDir='changan_c835'

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='部署C385程序')
    
    #这个是要解析 -f 后面的参数
    parser.add_argument('-t','--timeSpace',help="sleep time",default=10)
    parser.add_argument('-c','--customfile',help='adb push custom file list',default=[], nargs='+',type=str)
    parser.add_argument('-k','--slm',help='slay slm',default=1)
    parser.add_argument('-q','--qnx',help='cp for qnx',nargs='*')
    args = parser.parse_args()
    timeSpace = int(args.timeSpace)

    if "-c" in sys.argv:
        proceesNames= args.customfile
        print(proceesNames)
        if len(proceesNames) == 0:
            sys.exit()
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts")

        if is_ssh:
            keyStr("rm -rf ic",1)
            keyStr(f"scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/{PrjectDir}/prebuilts/ic ./")
            keyStr("123456")
            time.sleep(4)
        for proceesName in proceesNames:
            keyStr(f"adb push ic/bin/{proceesName} /sdcard",0)
            
        time.sleep(timeSpace*1.5)
        keyStr("adb shell")
        for proceesName in proceesNames:
            keyStr(f"curl -u root:root \"ftp://192.168.1.1/data/{proceesName}\" -T /sdcard/{proceesName}",0)
        time.sleep(timeSpace)

        keyStr("telnet cdc-qnx",1)
        keyStr("root")
        # if args.slm==1:
        #     keyStr("slay -f slm",2)
        # else:
        #     for proceesName in proceesNames:
        keyStr(f"slay {proceesName}")
        keyStr(f"slay {proceesName}")
        keyStr(f"slay {proceesName}")
        time.sleep(1)

        for proceesName in proceesNames:
            keyStr(f"cp /data/{proceesName} /usr/bin/",0)
            keyStr(f"chmod +x /usr/bin/{proceesName}",0)
        sys.exit()

    if "-q" not in sys.argv:
        keyStr(f"cd ~/Works/Repos/{PrjectDir}/prebuilts")
        if is_ssh:
            keyStr("rm -rf ic",1)
            keyStr(f"scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/{PrjectDir}/prebuilts/ic ./")
            keyStr("123456")
            time.sleep(4)
        keyStr("adb push ic/bin/ic_chime /sdcard",0)
        keyStr("adb push ic/bin/ic_service /sdcard",0)
        keyStr("adb push ic/bin/mcu_service  /sdcard",0)
        keyStr("adb push ic/lib/lib_base.so  /sdcard",0)
        keyStr("adb push ic/lib/lib_mega_ipc.so  /sdcard",0)
        keyStr("adb push ic/qt/bin/ivi_compositor  /sdcard",0)
        keyStr("adb push ic/qt/bin/ic_telltale  /sdcard",0)
        keyStr("adb push ic/qt/qml/MegaIC/libmega_ic_plugin.so  /sdcard",0)
        keyStr("adb push ic/qt/qml/Resources/libresources_plugin.so  /sdcard",0)


        keyStr("adb push ic/qt/config/screen_layout_config.json /sdcard",0)
        keyStr("adb push ic/qt/config/icadas_config.json /sdcard",0)
        keyStr("adb push ic/qt/config/icdriving_config.json /sdcard",0)
        keyStr("adb push ic/qt/config/icscreencast_config.json /sdcard",0)
        keyStr("adb push ic/qt/config/ictelltale_config.json /sdcard",0)
        keyStr("adb push ic/qt/config/icwarning_config.json /sdcard",0)
        time.sleep(timeSpace*1.5)

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
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icdriving_config.json\" -T /sdcard/icdriving_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icscreencast_config.json\" -T /sdcard/icscreencast_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/ictelltale_config.json\" -T /sdcard/ictelltale_config.json",0)
        keyStr("curl -u root:root \"ftp://192.168.1.1/data/icwarning_config.json\" -T /sdcard/icwarning_config.json",0)
        time.sleep(timeSpace)

        keyStr("telnet cdc-qnx",1)
        keyStr("root")
        keyStr("slay -f slm",2)

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
    keyStr("cp /data/icdriving_config.json /opt/qt/config",0)
    keyStr("cp /data/icscreencast_config.json /opt/qt/config",0)
    keyStr("cp /data/ictelltale_config.json /opt/qt/config",0)
    keyStr("cp /data/icwarning_config.json /opt/qt/config",0)
    keyStr("chmod +x /usr/bin/ic_chime",0)
    keyStr("chmod +x /usr/bin/ic_service",0)
    keyStr("chmod +x /usr/bin/mcu_service",0)
    keyStr("chmod +x /usr/bin/ivi_compositor")
    keyStr("chmod +x /usr/bin/ic_telltale")
    # keyStr("reset",0)
