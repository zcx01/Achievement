#!/bin/bash

# spawn ssh chengxiongzhu@10.25.11.197 \
# "ls\n"\
# "cd Works\n"\
# "ls\n"\
# "adb shell\n"\
# "echo {123456}|ssh chengxiongzhu@10.25.11.6 \n"
# expect {
#     "*password*" {
#         send "123456\r" 
#     }
#     # "Permission*" {send "123456\r"}
# }
# interact

# ssh chengxiongzhu@10.25.11.197 
# <<EOF 
# adb shell 
# EOF

#adb shell telnet cdc-qnx `speed 1` `root`

echo $2
