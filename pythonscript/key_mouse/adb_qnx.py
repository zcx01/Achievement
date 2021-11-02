#!/bin/python
from pykeyboard import *
from pymouse import *
import subprocess
import time
import sys
from key_mouse import *

keyStr("adb shell")
keyStr("telnet cdc-qnx")
keyStr("root")

if "-m" in sys.argv:
    keyStr("mosquitto_sub -h cdc-qnx -v -t \"#\" ")
# 