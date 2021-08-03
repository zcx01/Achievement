#!/usr/bin/python
import os
import sys
from enum import Enum

class DataType(Enum):
    VINT=1
    VFLOAT=2

class Analyze(object):
    def __init__(self,dbc_files=None) :
        if len(dbc_files) ==0:
            return
        self.sigForMessage={}
        self.dataType={}
        for dbc_file in dbc_files:
            with open(dbc_file,"r") as f:
                linelist=f.readlines()
                message=""
                for text in linelist:
                    text=text.strip()
                    if len(text) == 0:
                        continue
                    if text.startswith("BO_") :
                        message= self.analyline(text)
                    elif text.startswith("SG_"):
                        sigNams=self.analyline(text)
                        self.sigForMessage[sigNams] = message
                        self.dataType[sigNams]=self.analyDataType(text)                

    def getMessageBySig(self,sig):
        return self.sigForMessage.get(sig,"")

    def getSigDataType(self,sig):
        return self.dataType.get(sig,DataType.VINT)

    def analyline(self,msg):
        contents=msg.split(":")
        contents=contents[0].strip().split(" ")
        return contents[len(contents)-1]

    def analyDataType(self,lineContent):
        contents=lineContent.split(" ")
        for text in contents:
            if(text.startswith("(")):
                texts=text.split(",")
                accuracy=texts[0].replace("(","")
                if "." in accuracy:
                    return DataType.VFLOAT
        return DataType.VINT


# a=Analyze("/home/chengxiongzhu/Works/Repos/tool_parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc")
# print(a.getMessageBySig("CdcDtc1HiByte"))
