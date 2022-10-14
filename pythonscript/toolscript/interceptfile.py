import sys
from commonfun import *
#此脚本用来截取文件的从开始行到结束行之间的文本
def deal(dataPath,outPath,startIndex,endIndex):
    contentes=readFileLines(dataPath)
    index = startIndex
    intercept=[]
    while index <= endIndex:
        if(index > len(contentes)):
            break
        intercept.append(contentes[index])
        index+=1
    wirteFileDicts(outPath,intercept)
    print("finish")

        
if __name__ == "__main__":
    deal("/home/chengxiongzhu/Works/log/dltlogs/log.6.dlt","/home/chengxiongzhu/Works/log/out.txt",int(sys.argv[1]),int(sys.argv[2]))
