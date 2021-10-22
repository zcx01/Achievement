#!/bin/python
import os
import sys
from commonfun import*

def getSig(text):
    e_i = r"CANSIG_.*_g"
    sigNames = re.findall(e_i, text, re.A)
    sigNames = list(set(sigNames))
    return sigNames

def generateSub(file,variable=''):
    if len(variable) == 0:
        variable = os.path.splitext(os.path.basename(file))[0]
    with open(file, "r") as cr:
        sigNames = getSig(cr.read())
        for sigName in sigNames:
            print(f'{variable}->subscribe((struct veh_signal *)(struct veh_signal *)&{sigName});')

def generateTest(file):
    with open(file, "r") as cr:
        sigNames = getSig(cr.read())
        for sigName in sigNames:
            pass
        
if __name__ == "__main__":
    generateSub(sys.argv[1])
