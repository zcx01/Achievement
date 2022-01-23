import sys
from execCmd import *
pyFileDir = os.path.dirname(os.path.abspath(__file__))

keyStr(f'cd {pyFileDir}/qnx')
keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /var/log/ -f ic_service.core')
keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /usr/bin/ -f ic_service')
keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /lib64 -f lib_mega_ipc.so')
keyStr('cd ..')
keyStr('cp -f qnx/* ~/Works/Repos/changan_c835/prebuilts/')
keyStr('cd ~/Works/Repos/changan_c835/prebuilts/')
keyStr('ls')
keyStr('ntoaarch64-gdb ic_service ic_service.core')
keyStr('bt')
interact()