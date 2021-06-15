from subprocess import *
import threading
from time import sleep


proc = Popen(
        args='docker exec -it kiara_build_18 bash ',
        shell=True,
        stdin=PIPE
    )
sleep(1)
cmd="cd  ~/Works/Repos/tool_parser;make"
proc.communicate(cmd.encode())