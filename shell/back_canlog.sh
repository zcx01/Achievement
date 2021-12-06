#!/bin/bash

if [ $# -lt 1 ]; then
    echo "输入链接地址,或者文件"
    exit 0
fi
cd ~/Works/Repos/Test/mega_cantools/mega_cantools_lib/mega_cantools_lib/can_log
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

wget $1 --http-user=chengxiong.zhu --http-password=@Huan2870244352
file=`basename $1`
echo $file
# megacanlog --replay $file
rm $file
