#!/bin/python
import sys
from execCmd import *

keyStr("adb shell")
keyStr("telnet cdc-qnx")
keyStr("root")

if "-m" in sys.argv:
    keyStr("mosquitto_sub -h cdc-qnx -v -t \"#\" ")

interact()