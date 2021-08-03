#!/bin/bash
function lnBin(){
    path=$1
    fileName=$(basename $path)
    aimFile=${fileName%\.*}
    suffx=${fileName##*.}
    cmdUp="bash"
    if [ $suffx == "py" ]; then
        cmdUp="python3"
    fi
    echo $cmdUp
    aimFile=~/.bin/$aimFile
    echo $aimFile
    srcFile=$(dirname $path)
    # ln -s $path $aimFile
    cat>$aimFile<<EOF
#!/bin/bash
    # cd $srcFile
    $cmdUp $path \$@
EOF
    chmod 777 $aimFile
}

if [ $# -lt 1 ]; then
    echo "输入文件名:"
    for s in `ls` ;do
        echo "$( cd "$( dirname "./" )" && pwd )"/$s
    done
    exit 0
fi

for file in $@;do
    lnBin $file
done