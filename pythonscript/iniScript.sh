#!/bin/bash

shellPath="$(dirname "${BASH_SOURCE[0]}")"

cd $shellPath
commonfun="commonfun.py"
Analyzedbc="Analyzedbc.py"
projectConfig="config.json"
for file_a in ./*
do  
    if [ -d $file_a ]; then
        cd $file_a
        rm $commonfun
        ln -s ../$commonfun ./
        if [ $file_a == "./canSimulation" ];then
            echo "生成"+$file_a+"链接"
            rm $Analyzedbc
            ln -s ../topic_def/$Analyzedbc ./
            ln -s ../topic_def/$projectConfig ./
        fi
        cd ..
    fi
done
