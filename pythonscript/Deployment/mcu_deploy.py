#!/bin/python
import sys
import os
from execCmd import *
import argparse

if __name__ == "__main__":
    downHttp = sys.argv[1]
    assert isinstance(downHttp,str)
    fileName = os.path.basename(downHttp)
    keyStr('cd ~/Works/changan_shuaji')
    keyStr(f'rm -rf mcu')
    keyStr(f'mkdir mcu')
    keyStr(f'cd mcu')
    keyStr(f'wget {downHttp} --http-user=chengxiong.zhu --http-password=@Huan2870244352')
    keyStr(f'unzip {fileName}')
    interact()
    mcu_dir = os.path.expanduser("~")+'/Works/changan_shuaji/mcu'
    mcu_bins=[]
    for (dirpath,dirnames,filenames) in os.walk(mcu_dir):
        for mcu_bin in filenames:
            if os.path.splitext(mcu_bin)[1] == '.bin':
                mcu_bins.append( f'{dirpath}/{mcu_bin}')
    mcu_bin = ' '.join(mcu_bins)
    muc_dir = '/ota/android/'
    os.system(f'python3 c385_deploy.py -a {mcu_bin} -e \'flash_mcu.sh p {muc_dir}\' \'flash_mcu.sh c\'')
    

