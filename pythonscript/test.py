# temp=0x1ff
# tmp=0xffffffffffffffff
# uselenght=0
# size=3
# print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-(uselenght+size))))
# uselenght+=size
# size=6
# print(hex(int(temp)>>uselenght & (0xffffffffffffffff>>64-size)))
# print(hex(int("111111",2)))

import os
import sys
from commonfun import*
temp=[999,9,999]
index=0
for t in temp:
    if(t == 9):
        temp.insert(index+1,"dd")
    if(t == "dd"):
        temp.insert(index+1,"ssss")
    index+=1

print(temp)