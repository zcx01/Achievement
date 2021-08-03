#!/bin/bash

if [ $# -lt 1 ]; then
    echo "输入参数 -s:[状态] -c:[空调控制] -v:[模拟信号] -a:[生成车控代码命令] -n:[生成json]"
    exit 0
fi
type=$1

if [ $type == "-s" ]; then
    aim="/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/../config/vehctrl_status_config.json"
    out="vehctrlSts"
    python3  ./topic_def.py $aim $out $type
elif [ $type == "-c" ] || [ $type == "-a" ];then
    aim="/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/../config/vehctrl_config.json"
    out="vehctrl"
    python3  ./topic_def.py $aim $out $type
elif [ $type == "-n" ];then
    aim="/home/chengxiongzhu/Works/newsig.txt"
    python3  ./topic_def.py $aim 
fi