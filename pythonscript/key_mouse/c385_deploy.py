#!/bin/python
from pykeyboard import *
from pymouse import *
import subprocess
import time
import sys

def keyStr(cmd,t=0.3):
    k.type_string(cmd)
    # if(t != 0):
    #     k.tap_key(k.enter_key)
    # else:
    k.tap_key(k.enter_key)
    time.sleep(t)

k = PyKeyboard()
click = PyMouse
for i in range(3):
    print(i)
    time.sleep(1)
if "-s" not in sys.argv:
    keyStr("ssh chengxiongzhu@10.25.11.197")
    keyStr("123456")

if "-i" in sys.argv:
    keyStr("cd ~/Works/Repos/changan_c835/prebuilts")
    keyStr("rm -rf ic",1)
    keyStr("scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/changan_c835/prebuilts/ic ./")
    keyStr("123456")
    time.sleep(2.5)
    keyStr("adb push ic/bin/ic_service /sdcard",2)
    keyStr("adb shell")
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_service\" -T /sdcard/ic_service",1)
    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    keyStr("slay -f slm",2)
    keyStr("cp /data/ic_service /usr/bin/",1)
    keyStr("chmod +x /usr/bin/ic_service",1)
    sys.exit()

if "-c" in sys.argv:
    proceesNames= sys.argv
    del proceesNames[0]
    del proceesNames[0]
    if len(proceesNames) == 0:
        sys.exit()
    keyStr("cd ~/Works/Repos/changan_c835/prebuilts")
    keyStr("rm -rf ic",1)
    keyStr("scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/changan_c835/prebuilts/ic ./")
    keyStr("123456")
    time.sleep(2.5)
    for proceesName in proceesNames:
        keyStr(f"adb push ic/bin/{proceesName} /sdcard",0)
        
    time.sleep(2)
    keyStr("adb shell")
    for proceesName in proceesNames:
        keyStr(f"curl -u root:root \"ftp://192.168.1.1/data/{proceesName}\" -T /sdcard/{proceesName}",0)
    time.sleep(2)

    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    for proceesName in proceesNames:
        keyStr(f"slay {proceesName}")
        keyStr(f"slay {proceesName}")
        keyStr(f"slay {proceesName}")
    time.sleep(1)

    for proceesName in proceesNames:
        keyStr(f"cp /data/{proceesName} /usr/bin/",0)
        keyStr(f"chmod +x /usr/bin/{proceesName}",0)
    sys.exit()

if "-q" not in sys.argv:
    keyStr("cd ~/Works/Repos/changan_c835/prebuilts")
    keyStr("rm -rf ic",1)
    keyStr("scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/changan_c835/prebuilts/ic ./")
    keyStr("123456")
    time.sleep(2.5)
    keyStr("adb push ic/bin/ic_chime /sdcard",0)
    keyStr("adb push ic/bin/ic_service /sdcard",0)
    keyStr("adb push ic/bin/mcu_service  /sdcard",0)
    keyStr("adb push ic/lib/lib_base.so  /sdcard",0)
    keyStr("adb push ic/lib/lib_mega_ipc.so  /sdcard",0)
    keyStr("adb push ic/qt/bin/ivi_compositor  /sdcard",0)
    keyStr("adb push ic/qt/qml/MegaIC/libmega_ic_plugin.so  /sdcard",0)
    keyStr("adb push ic/qt/qml/Resources/libresources_plugin.so  /sdcard",0)

    keyStr("adb push ic/qt/config/screen_layout_config.json /sdcard",0)
    keyStr("adb push ic/qt/config/icadas_config.json /sdcard",0)
    keyStr("adb push ic/qt/config/icdriving_config.json /sdcard",0)
    keyStr("adb push ic/qt/config/icscreencast_config.json /sdcard",0)
    keyStr("adb push ic/qt/config/ictelltale_config.json /sdcard",0)
    keyStr("adb push ic/qt/config/icwarning_config.json /sdcard",0)
    time.sleep(10)

    keyStr("adb shell")
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_chime\" -T /sdcard/ic_chime",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/ic_service\" -T /sdcard/ic_service",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/mcu_service\" -T /sdcard/mcu_service",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/lib_base.so\" -T /sdcard/lib_base.so",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/lib_mega_ipc.so\" -T /sdcard/lib_mega_ipc.so",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/ivi_compositor\" -T /sdcard/ivi_compositor",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/libmega_ic_plugin.so\" -T /sdcard/libmega_ic_plugin.so",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/libresources_plugin.so\" -T /sdcard/libresources_plugin.so",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/screen_layout_config.json\" -T /sdcard/screen_layout_config.json",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/icadas_config.json\" -T /sdcard/icadas_config.json",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/icdriving_config.json\" -T /sdcard/icdriving_config.json",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/icscreencast_config.json\" -T /sdcard/icscreencast_config.json",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/ictelltale_config.json\" -T /sdcard/ictelltale_config.json",0)
    keyStr("curl -u root:root \"ftp://192.168.1.1/data/icwarning_config.json\" -T /sdcard/icwarning_config.json",0)
    time.sleep(10)

    keyStr("telnet cdc-qnx",1)
    keyStr("root")
    keyStr("slay -f slm",2)

keyStr("cp /data/ic_chime /usr/bin/",0)
keyStr("cp /data/ic_service /usr/bin/",0)
keyStr("cp /data/mcu_service /usr/bin/",0)
keyStr("cp /data/lib_base.so /usr/lib64/",0)
keyStr("cp /data/lib_mega_ipc.so /usr/lib64/",0)
keyStr("cp /data/ivi_compositor /usr/bin/ivi_compositor",0)
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
# keyStr("reset",0)
