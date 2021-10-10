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
from commonfun import*
def findValue(text,signal,filePath,*other):
    texts= splitSpace(text)
    if signal in texts:
        out=EesyStr.removeAll(text,texts[0])
        print(f'{out:<30}')
        return True
    return False

def findsignalInfile(signal,filePath):
    try:
        f=open(filePath,'r')
        print(filePath)
        content=f.readlines()
        for text in content:
            if(findValue(text,signal,filePath)):
                pass
    except:
        pass

findsignalInfile("288","/home/chengxiongzhu/下载/Converted_0828.asc")