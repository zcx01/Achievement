#!/usr/bin/expect

# spawn ssh chengxiongzhu@10.25.7.196 \
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

spawn ./delopyvm385.sh -f
expect {
    "*password*" {
        send "qnxuser\r" 
        exp_continue
    }
    "*qnxuser*" {
        send "qnxuser\r" 
        exp_continue
    }
}