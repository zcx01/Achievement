#!/bin/python
from pykeyboard import *
from pymouse import *
import subprocess
import time
import sys

def keyStr(cmd):
    k.type_string(cmd)
    k.tap_key(k.enter_key)
    time.sleep(0.3)

k = PyKeyboard()
click = PyMouse
for i in range(3):
    print(i)
    time.sleep(1)
keyStr("ssh chengxiongzhu@10.25.11.197")
keyStr("123456")
keyStr("cd ~/Works/Repos/Test/mega_cantools/mega_cantools_lib/mega_cantools_lib")
# 