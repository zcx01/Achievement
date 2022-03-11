#!/bin/bash

if [ $1 == "-h" ]; then
    echo "输入链接地址"
    exit 0
fi
tarFile="qfi_bin"
tarDir=~/Works/changan_shuaji

if [ ! -d $tarDir ];then
  mkdir -p $tarDir
fi

cd $tarDir
# for file in `ls` ;do
#     if [ $file == $tarFile ]; then
#         read -p "是否都替换(y/n)?" yesoron
#         if [ $yesoron == "n" ]; then
#             exit 0
#         else
#             break 
#         fi
#     fi
# done
if [ $# -eq 1 ]; then
    rm -r $tarFile

    wget $1 --http-user=chengxiong.zhu --http-password=@Huan2870244352
    file=`basename $1`
    tar -zxvf $file
    echo `date` $file >> version.txt
    rm $file

    #qnx 进入fastboot模式
    # adb_qnx -r
fi

cd $tarFile/common/build/

python3 fastboot_complete.py --pf=8155_la --st=ufs

fastboot reboot
exit 0
