#!/bin/bash

if [ $# -lt 1 ]; then
    echo "输入链接地址"
    exit 0
fi
tarFile="qfi_bin"
tarBeFile="bigsur_hqx"
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

rm -r $tarFile

wget $1 --http-user=chengxiong.zhu --http-password=@Huan2870244352
for file in `ls` ;do
    if [ $file == *$tarBeFile* ]; then
        tar -zxvf $file
        echo `date` $file >> version.txt
        rm $file
        break
    fi
done

cd $tarFile/common/build/
python3 fastboot_complete.py --pf=8155_la --st=ufs

fastboot reboot
rm -r $tarFile
exit 0
