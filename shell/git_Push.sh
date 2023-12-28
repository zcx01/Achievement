#!/bin/bash

shellPath="/home/chengxiongzhu/Achievement/pythonscript/getgitpath.py"
# repoPath=~/Works/Repos/changan_c385/
# cd $repoPath
#branch="dev_hqx.1.2.1"
branch="master"
prefix="mega"
filterPath=("prebuilts/" "project" "common-prebuilts/" "src/ic_service/tools/auto_gen/" "qt/prebuilt/" "prebuilts/common/")

if [ $# -lt 1 ]; then
    echo "选择路径:"
    project=`repo status -q`
    for f in $project;
    do
        if [[ " ${filterPath[@]} " =~ " $f " ]]; then
            continue
        else
            echo $f
            repo status $f
            repo forall $f -c "git branch -vv" 
        fi

        # if [ $f != "prebuilts/" ] && [ $f != "project" ] && [ $f != "common-prebuilts/" ] && [ $f != "src/ic_service/tools/auto_gen/" ] && [ $f != "qt/prebuilt/" ];then
        #     repo status $f
        #     repo forall $f -c "git branch -vv" 
        # fi
    done
    exit 0
else
    if [ $1 == "-r" ];then
        repo forall -c "git clean -df" && repo forall -c "git reset --hard; git checkout ."
        exit 0
    elif [ $1 == "-rh" ];then
        git reset --soft HEAD^
        exit 0
    else
        cd $1
    fi
fi

if [ $# -ge 3 ]; then
    if [ $2 == "-o" ];then
        branchs=$3
        prefixIndex=`expr index $branchs "/"`
        prefix=${branchs:0:$prefixIndex-1}
        branch=${branchs:$prefixIndex}
    fi
fi

if [ ${!#} == "-c" ];then
    git status
    git add -A
    git rebase --continue
    git push --no-thin $prefix HEAD:refs/for/$branch
elif [ ${!#} == "-n" ];then
    git add -A
    git commit --amend --no-edit
    git push --no-thin $prefix HEAD:refs/for/$branch 
elif [ ${!#} == "-a" ];then
    git add -A
    git commit --amend 
    git push --no-thin $prefix HEAD:refs/for/$branch
else
    git add -A
    git commit -s
    git fetch $prefix
    git rebase $prefix/$branch
    git push --no-thin $prefix HEAD:refs/for/$branch
fi

