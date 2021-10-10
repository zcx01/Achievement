import sys
from commonfun import *

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
