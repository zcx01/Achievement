#!/bin/python
import os
import sys
import argparse
from commonfun import *

if __name__ == "__main__":
    parse = argparse.ArgumentParser(description='python的脚本模板')
    parse.add_argument('-s','--startRow',help='开始的行号',type=int,default=0)
    arg = parse.parse_args()
