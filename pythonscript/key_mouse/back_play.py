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
keyStr("cd ~/Works/Repos/back_play/mega_cantools_lib")
keyStr("python blf_editor.py --replay /home/chengxiongzhu/Works/log/can_log_20211009153412.blf --filter 648")
# 