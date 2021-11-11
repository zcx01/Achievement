#!/bin/bash

shellPath="/home/chengxiongzhu/Achievement/pythonscript/getgitpath.py"
repoPath="/home/chengxiongzhu/Works/Repos/changan_c835/"
cd $repoPath

if [ $# -lt 1 ]; then
    echo "选择路径:"
    repo status
    # branch=`python3 $shellPath`
    # for f in $branch;
    # do
    #     echo $f
    # done
    exit 0
else
    cd $1
fi

if [ $# -eq 1 ]; then
    git add -A
    git commit -s
    git fetch mega
    git rebase mega/master
    git push mega HEAD:refs/for/master
elif [ $2 == "-c" ];then
    git status
    git add -A
    git rebase --continue
    git push mega HEAD:refs/for/master
elif [ $2 == "-n" ];then
    git add -A
    git commit --amend --no-edit
    git push mega HEAD:refs/for/master
elif [ $2 == "-s" ];then
    repo forall -c "git clean -df" && repo forall -c "git reset --hard; git checkout ." && repo sync --force-sync -j8
elif [ $2 == "-a" ];then
    git add -A
    git commit --amend 
    git push mega HEAD:refs/for/master
fi