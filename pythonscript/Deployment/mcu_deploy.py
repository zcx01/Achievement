#!/bin/python
import sys
import os
from execCmd import *
import argparse

pyFileDir = os.path.dirname(os.path.abspath(__file__))
if __name__ == "__main__":
    downHttp = sys.argv[1]
    assert isinstance(downHttp,str)
    fileName = os.path.basename(downHttp)
    keyStr('cd ~/Works/changan_shuaji')
    keyStr(f'rm -rf mcu')

    keyStr(f'mkdir mcu')
    keyStr(f'cd mcu')
    keyStr(f'wget {downHttp} --http-user=chengxiong.zhu --http-password=@Huan2870244352')
    # keyStr(f'unzip {fileName}')
    interact()
    mcu_dir = os.path.expanduser("~")+'/Works/changan_shuaji/mcu'
    # mcu_bins=[]
    mcu_bin=''
    for (dirpath,dirnames,filenames) in os.walk(mcu_dir):
        for mcu_bin in filenames:
            if os.path.splitext(mcu_bin)[1] == '.tgz':
                # mcu_bins.append( f'{dirpath}/{mcu_bin}')
                mcu_bin = f'{dirpath}/{mcu_bin}'
                break
    # mcu_bin = ' '.join(mcu_bins)
    # muc_dir = f'/ota/android/'
    os.system(f'python3 {pyFileDir}/c385_deploy.py -a {mcu_bin} -e \'flash_mcu.sh -u 1 {os.path.basename(mcu_bin)}\' \'flash_mcu.sh -a 1\' \'flash_mcu.sh -r 1\'')
    