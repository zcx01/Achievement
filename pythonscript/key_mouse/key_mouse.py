#!/bin/python
import time
import sys
import os
import subprocess
'''from pykeyboard import *
from pymouse import *


def keyStr(cmd,t=0.3):
    k.type_string(cmd)
    k.tap_key(k.enter_key)
    time.sleep(t)

k = PyKeyboard()
click = PyMouse
for i in range(3):
    print(i)
    time.sleep(1)'''

def execCmd(cmd):
    ex = subprocess.Popen(cmd,stdout=subprocess.PIPE,stdin=subprocess.PIPE,shell=True)
    # ex.communicate()
    # ex.wait()

def keyStr(cmd,t=0.3):
    cmd = str(cmd)
    os.system(cmd+'\n')

is_ssh = "-s" in sys.argv
if is_ssh:
    keyStr("ssh chengxiongzhu@10.25.11.197")
    keyStr("123456")
