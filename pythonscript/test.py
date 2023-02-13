#!/bin/python
import os
import sys
import pexpect
import subprocess


# temp=0x1ff
# tmp=0xffffffffffffffff
# uselenght=0
# size=3
# print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-(uselenght+size))))
# uselenght+=size
# size=6
# print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-size)))
# print(hex(int("111111",2)))

def getFileName(className):
    fileName=""
    index=0
    for c in className:
        if str(c).isupper():
            temp =""
            if index !=0:
                temp = "_"
            fileName+=temp + str(c).lower()
        else:
            fileName+=c
        index+=1
    return fileName

fileName = "/home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210713.dbc"

if __name__ == "__main__":
    p = pexpect.spawn("adb shell", encoding='utf-8', logfile=sys.stdout, timeout=300)
    p.sendline("telnet 192.168.1.1")
    login_index = p.expect(["login:", pexpect.EOF, pexpect.TIMEOUT])
    if login_index != 0:
        print("telnet qunx失败！")
        exit(1)

    print("telnet至qunx成功！")
    p.sendline("root")
    root_index = p.expect(["#", pexpect.EOF, pexpect.TIMEOUT])
    if root_index != 0:
        print("切换至root失败！")
        exit(1)
