# spawn ssh chengxiongzhu@10.25.11.10 \
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

# ssh chengxiongzhu@10.25.11.10 
# <<EOF 
# adb shell 
# EOF

#adb shell telnet cdc-qnx `speed 1` `root`
counter=$1
value=0
while [[ $counter -eq -1 || ($counter -gt 0 && $value -lt $counter) ]]
do
    on -T ic_apps_t -u ic_apps mega_ipc_pub -t 'AC/TemperatureFrontAll/Set' -m '{"extension":null,"relative":false,"time":0,"valid":true,"value":{"CDC_2D2/CdcDrvrTSet":24.0,"CDC_2D2/CdcPassTSet":24.0}}'
    sleep $2
    if [ $counter -ne -1 ]; then
        value=$(($value + 1))
    fi
done