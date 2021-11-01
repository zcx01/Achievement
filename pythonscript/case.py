#!/bin/python
from commonfun import*
from signalxls import *
import xlrd
import argparse

def generateCase():
    print("tes")
    pass


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='这个脚本是生成测试的case')
    
    #这个是要解析 -g 后面的参数
    parser.add_argument('-g','--generate',help="generate case xlsx",default=True)
    args = parser.parse_args()

    # if args.generate:
    generateCase()