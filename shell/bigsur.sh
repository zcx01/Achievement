#!/bin/bash

if [ $# -lt 1 ]; then
    echo "输入链接地址"
    exit 0
fi
tarFile="qfi_bin"
cd ~/Works/changan_shuaji
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

if [ $1 != "-s" ];then
    rm -r $tarFile

    wget $1 --http-user=chengxiong.zhu --http-password=@Huan2870244352
    file=`basename $1`
    tar -zxvf $file
    echo `date` $file >> version.txt
    rm $file
fi

#qnx 进入fastboot模式
adb_qnx -r

cd $tarFile/common/build/
python3 fastboot_complete.py --pf=8155_la --st=ufs

fastboot reboot
cd ../../../
rm -r $tarFile
exit 0
