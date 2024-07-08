#!/bin/bash

if [ $1 == "-h" ];then
    echo 'can qnx linux'
elif [ $1 == "linux" ];then 
    echo "查看实际使用空间                          df -h"
    echo "ubuntu 查看当前目录下的各文件的大小       sudo du --max-depth=1 -h"
elif [ $1 == "can" ];then
    echo 'cd  /sys/class/net/can0 && echo 4096 > tx_queue_len'
elif [ $1 == "qnx" ]; then
    echo "查看aps_ic里面的线程: pidin sched | grep aps_ic"
    echo "查看线程名称:         pidin threads | grep process_name"
    echo "创建aps_imu区域:      aps create -b 5 aps_imu"
    echo "查看aps_ic使用的CPU:  aps show -l -d 1 | grep aps_ic"
    echo "修改cpu所在区域:      aps join -p 7745574 -t 26 aps_spi"
    echo "设置线程优先级:       slay -P pri -T tid process_name/process_id"
    echo "抓取组播的udp包:      tcpdump -i emac0 -w /log/emac.pcap"
fi