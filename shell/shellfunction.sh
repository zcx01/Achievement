#!/bin/bash

function up(){
    OLD_IFS="$IFS"
    IFS="/"
    array=($1)
    IFS="$OLD_IFS"
    num=${#array[@]}   
    aimPath=""
    for ((i=0;i<num-1;i++))
    {
        aimPath+=${array[$i]}"/";
    }
    echo $aimPath
}

function getAbsolute(){
    if [ -f $1 ];then
        fileName=`basename $1`
        path=`up $1`
        path=$(cd $path; pwd)
        path=$path/$fileName
    else
        path=$(cd $path; pwd)
    fi
     echo $path
}

function getLocateIp(){
     echo `ifconfig | grep inet | grep -v inet6 | grep -v 127 |grep -v 172 |awk '{print $2}'|tr -d "addr:"`
}
