#!/bin/bash
par=$1
if [ $# != 1 ] ; then
    echo "请输入参数"
    exit 0
fi

if [ $par == "-v" ];then
    scp -r /home/chengxiongzhu/Works/Repos/changan_c835/qt/prebuilt/x86_64/ qnxuser@10.25.11.159:qt
else
    # scp -r  deploy.sh qnxuser@10.25.11.159:
    ssh  qnxuser@10.25.11.159 
fi