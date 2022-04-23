#!/usr/bin/python
import os
import string

from commonfun import*
from AnalyzeCan.Analyzedbc import *

def CheckSigName(configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    if down_config == None:
        down_config= getKeyPath("down",jsConfig)
    if up_config == None:
        up_config = getKeyPath('up',jsConfig)
    jsDown = getJScontent(down_config)
    jsUp   = getJScontent(up_config)
    sigNames = []
    for top in jsDown:
        topValue = jsDown[top]
        if type(topValue) == str:
            sigNames.append(topValue)
        else:
            for t in topValue:
                sigNames.append(t)
    
    for s in jsUp:
        sigNames.append(s)


    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)
    for sig in sigNames:
        sigs = re.findall(m_s,sig)
        if len(sigs) >= 3 :
            sig= str(int(sigs[1],16))+sigs[2]
        if not dbc.sigExist(sig):
            printRed(f'{sig:<50} 信号不存在')
    printGreen("分析完成")

if __name__ == "__main__":
    CheckSigName(pyFileDir+"config.json")
    
