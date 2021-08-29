#!/bin/python
from pykeyboard import *
from pymouse import *
import subprocess
import time
import sys

def keyStr(cmd,t=0.3):
    k.type_string(cmd)
    k.tap_key(k.enter_key)
    time.sleep(t)

k = PyKeyboard()
click = PyMouse
for i in range(3):
    print(i)
    time.sleep(1)
if "-e" not in sys.argv:   
    keyStr("exit")
keyStr("ssh chengxiongzhu@10.25.11.197")
keyStr("123456")
keyStr("cd ~/Works/Repos/changan_c835/prebuilts")
keyStr("rm -rf ic",1)
keyStr("scp -r chengxiongzhu@10.25.11.25:/home/chengxiongzhu/Works/Repos/changan_c835/prebuilts/ic ./")
keyStr("123456")
# 
