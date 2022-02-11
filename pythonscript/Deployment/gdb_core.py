import sys
from execCmd import *
import argparse
pyFileDir = os.path.dirname(os.path.abspath(__file__))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='分析core文件')
    parser.add_argument('-c','--core', help='core文件',default="ic_service",type=str)
    parser.add_argument('-n','--noCopy', help='不从qnx上拷贝直接分析',nargs="*")
    parser.add_argument('-p','--prebuilts', help='prebuilts目录',default='~/Works/Repos/changan_c835/prebuilts/',)
    args = parser.parse_args()

    core = args.core
    prebuilts = args.prebuilts
    if '-n' not in sys.argv:
        keyStr(f'cd {pyFileDir}/qnx')
        keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /var/log/ -f {core}.core')
        keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /usr/bin/ -f {core}')
        keyStr(f'python3 {pyFileDir}/cp_qnx.py -p /lib64 -f lib_mega_ipc.so')
        keyStr('cd ..')
        keyStr(f'cp -f qnx/* {prebuilts}')
    keyStr(f'cd {prebuilts}')
    keyStr('ls')
    keyStr(f'ntoaarch64-gdb {core} {core}.core')
    keyStr('bt')
    interact()