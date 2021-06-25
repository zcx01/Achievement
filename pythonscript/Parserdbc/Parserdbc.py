from subprocess import *
import threading
import os
from time import sleep

proc = Popen(
        args='ssh chengxiongzhu@10.25.7.196',
        stdin=PIPE,
        stdout=PIPE,
        shell=True,
        universal_newlines = True
    )
# proc.wait()
# proc.stdin.write("ls")

# print(proc.stdin.readable())
#proc.stdin.write(("print('subp_popen.stdin.write3'+1)").encode())
#proc.stdin.close()
