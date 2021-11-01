#!/bin/python
import os
import sys
from commonfun import*


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

fileName = "/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210713.dbc"
lines = readFileLines(fileName)
wirteFileDicts(fileName,lines,False)

if __name__ == "__main__":
    pass