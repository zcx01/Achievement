#!/bin/bash

if [ $# -lt 1 ]; then
    echo "输入用户名和ip"
    exit 0
fi

REMOTEHOST=$1
ID_RSA=$HOME/.ssh/id_rsa.pub 
if ! [ -f $ID_RSA ];then
    echo '生成公钥'
    ssh-keygen
fi
scp $ID_RSA $REMOTEHOST:~/tmp.pub
ssh $REMOTEHOST "mkdir -p ~/.ssh && chmod 700 ~/.ssh && cat ~/tmp.pub >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys && rm -f ~/tmp.pub"
