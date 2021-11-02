#!/bin/bash

shellPath="$(dirname "${BASH_SOURCE[0]}")"

cd $shellPath
commonfun="commonfun.py"
for file_a in ./*
do  
    if [ -d $file_a ]; then
        temp_file=`basename $file_a` 
        rm ./$temp_file/$commonfun
        cd ./$temp_file
        sudo ln -s ../$commonfun ./
        cd ..
    fi
done
