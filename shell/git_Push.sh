#!/bin/bash

shellPath="/home/chengxiongzhu/Achievement/pythonscript/getgitpath.py"
# repoPath=~/Works/Repos/changan_c835/
# cd $repoPath
branch="dev_hqx.1.2.1"


if [ $# -lt 1 ]; then
    echo "选择路径:"
    project=`repo status -q`
    for f in $project;
    do
        if [ $f != "prebuilts/" ] && [ $f != "project" ] && [ $f != "common-prebuilts/" ];then
            repo status $f
        fi
    done
    exit 0
else
    if [ $1 == "-r" ];then
        repo forall -c "git clean -df" && repo forall -c "git reset --hard; git checkout ."
        exit 0
    else
        cd $1
    fi
fi

if [ $# -eq 1 ]; then
    git add -A
    git commit -s
    git fetch mega
    git rebase mega/$branch
    git push mega HEAD:refs/for/$branch
elif [ $2 == "-c" ];then
    git status
    git add -A
    git rebase --continue
    git push mega HEAD:refs/for/$branch
elif [ $2 == "-n" ];then
    git add -A
    git commit --amend --no-edit
    git push mega HEAD:refs/for/$branch 
elif [ $2 == "-a" ];then
    git add -A
    git commit --amend 
    git push mega HEAD:refs/for/$branch
fi