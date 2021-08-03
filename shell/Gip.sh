#!/bin/bash

shellPath="$(dirname "${BASH_SOURCE[0]}")"
. $shellPath/shellfunction.sh

function getIp() {
    path=$1
    if [ $# != 1 ] ; then
        path="-l"
    fi

    if [ $path == "-l" ];then
        echo `getLocateIp`
    elif [ $path == "-o" ]; then
        echo "10.25.11.25"
    fi
}

getIp $@