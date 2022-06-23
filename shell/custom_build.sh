#!/bin/bash
currentPath=$(cd `dirname ./`;pwd)

cd "build"
index=0
if [ $# -lt 1 ]; then
    echo "选择路径:"
    for file_a in ./*
    do  
        index=`expr ${index} + 1`
        temp_file=`basename $file_a`  
        echo $index"-------"$temp_file  
    done

    exit 0
else
    par=$1
    index=0
    expr ${par} + 0 1>/dev/null 2>&1
    if [ $? -eq 0 ]; then
        for file_a in ./*
        do  
            index=`expr ${index} + 1`
            temp_file=`basename $file_a`  
            if [ $index -eq $par ];then
                echo $temp_file 
                cd $temp_file  
            fi
        done
    else
        cd $par
    fi
fi

make -j8
if [ $# -eq 2 ]; then
    ntoaarch64-strip ${par} -g -S -d --strip-debug
fi

make install
cd $currentPath
cd "build_script"
./install_prebuilts.sh
