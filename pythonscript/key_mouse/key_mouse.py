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

is_ssh = "-s" in sys.argv
if is_ssh:
    keyStr("ssh chengxiongzhu@10.25.11.197")
    keyStr("123456")
