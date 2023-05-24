#!/bin/python
import os
import sys
import argparse
from commonfun import *
import openpyxl
from xml.dom.minidom import *
from openpyxl.worksheet.worksheet import Worksheet


def getContent(xmlFile):
    megacontent = {}
    megaoscontent = {}
    domTree = parse(xmlFile)
    assert isinstance(domTree,Document)
    rootNode = domTree.documentElement
    assert isinstance(rootNode,Element)
    contexts = rootNode.getElementsByTagName("project")
    for context in contexts:
        assert isinstance(context,Element)
        name = context.getAttribute("name")
        path = context.getAttribute("path")
        if context.hasAttribute("remote"):
            remote = context.getAttribute("remote")
            if remote == "megaOS":
                megaoscontent[path] = name
                continue
        megacontent[path] = name
    return megacontent,megaoscontent

def diffContent(fContent,tContent):
    SomeContent = []
    DifferentContent = []
    for path, name in fContent.items():
        if path in tContent:
            if fContent[path] == tContent[path]:
                SomeContent.append(name)
            else:
                DifferentContentTmp={}
                if path in tContent:
                    DifferentContentTmp[name] = tContent[path]
                else:
                    DifferentContentTmp[name] = ""
                DifferentContent.append(DifferentContentTmp)
            
            if path in tContent:
                del tContent[path]
    
    for path, name in tContent.items(): 
        ContentTmp={}
        ContentTmp[""] =name
        DifferentContent.append(ContentTmp)
    return SomeContent, DifferentContent
    
def writeShell(wshell,SomeContent,DifferentContentTmp):
    wshell.append(["相同的仓库"])
    for content in SomeContent:
        wshell.append([content])

    wshell.append(["不相同的仓库"])
    wshell.append(["C385","C673"])
    for contents in DifferentContentTmp:
        tmp=[]
        for content in contents:
            tmp.append(content)
            tmp.append(contents[content])
        wshell.append(tmp)


def getDiff(fxml,txml,xlsFileName):
    fMegaContent,fMegaOsContent = getContent(fxml)
    tMegaContent,tMegaOsContent = getContent(txml)

    book = openpyxl.Workbook()
    wshell = book.active
    assert isinstance(wshell,Worksheet)
    wshell.append(["mega"])
    SomeContent, fDifferentContent = diffContent(fMegaContent, tMegaContent)
    writeShell(wshell,SomeContent, fDifferentContent)
    wshell.append([])
    wshell.append(["megaos"])
    SomeContent, fDifferentContent = diffContent(fMegaOsContent, tMegaOsContent)
    writeShell(wshell,SomeContent, fDifferentContent)

    book.save(xlsFileName)
    print("比较完成")
    


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='python的脚本模板')
    parser.add_argument('-f','--fxml',help='第一个xml',type=str)
    parser.add_argument('-t','--txml',help='第二个xml',type=str)
    parser.add_argument('-x','--xlsx',help='结果输出',type=str)
    arg = parser.parse_args()
    getDiff(arg.fxml,arg.txml,arg.xlsx)