#!/bin/bash
#此脚本用来初始化本工程的脚本

shellPath="$(dirname "${BASH_SOURCE[0]}")"

cd $shellPath
commonfun="commonfun.py"
Analyzedbc="analyze_dbc"
basic_auth="basic_auth.py"
for file_a in ./*
do  
    if [ -d $file_a ]; then
        cd $file_a
        rm $commonfun
        ln -s ../$commonfun ./
        if [ $file_a == "./canSimulation" ] || [ $file_a == "./topic_def" ];then
            echo "生成"+$file_a+"链接"
            rm $Analyzedbc
            ln -s ../$Analyzedbc ./
            ln -s ../$Analyzedbc ./
        fi
        if [ $file_a == "./Gerrit" ] || [ $file_a == "./Jira" ];then
            echo "生成"+$file_a+"链接"
            rm $basic_auth
            ln -s ../$basic_auth ./
            ln -s ../$basic_auth ./
        fi
        cd ..
    fi
done
