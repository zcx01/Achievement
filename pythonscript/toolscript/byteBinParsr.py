#!/bin/python

import os
import argparse
import sys

def printbinary(binary_string,spaceIndex):
    assert isinstance(binary_string,str)
    binary_string = binary_string.replace(" ",'')
    # 将16进制字符串分割成每两个字符一组
    hex_list = [binary_string[i:i+spaceIndex] for i in range(0, len(binary_string), spaceIndex)]

    # 遍历列表并输出索引和对应的16进制标记
    for index, hex_value in enumerate(hex_list):
        print(f"Index: {index}, bin: {hex_value}")

def printHex(hex_string):
    assert isinstance(hex_string,str)
    if hex_string.startswith("0b"):
        hex_string =  str(hex(int(hex_string,2))).replace('0x','')
    printbinary(hex_string,2)

def printBin(bin_string):
    printbinary(bin_string,8)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-hex','--hex',help='16进制',nargs='?',default='',type=str)
    parser.add_argument('-bin','--bin',help='2进制',nargs='?',default='',type=str)

    arg = parser.parse_args()
    if '-hex' in sys.argv:
        printHex(arg.hex)
    elif '-bin' in sys.argv:
        printBin(arg.bin)