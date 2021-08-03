#!/bin/bash

shellPath="$(dirname "${BASH_SOURCE[0]}")"
. $shellPath/shellfunction.sh
. $shellPath/Gip.sh

function SupreCp(){
    path=$1
    path=`getAbsolute $path`
    echo $path
    aimPath=$path

    if [ -d $path ];then
        aimPath=`up $path`
        echo $aimPath
    fi
    scp -r $path chengxiongzhu@`getIp -o`:$aimPath 
}

if [ $# -lt 1 ] ; then
    SupreCp $( dirname "./")
    exit 0
fi

for file in $@;do
    SupreCp $file
done
