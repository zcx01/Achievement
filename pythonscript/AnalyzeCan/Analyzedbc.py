#!/usr/bin/python
import os
from re import S
import sys
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
sys.path.append(pyFileDir)
from commonfun import *
from projectInI import *
from AnalyzedbcFile import *

class Analyze(object):
    def __init__(self,dbc_dir=None) :
        self.AnalyzeDict={}
        self.AnalyzeDictlist=[]
        for (dirpath,dirnames,filenames) in os.walk(dbc_dir):
            for oriName in filenames:
                if ".dbc" in oriName and dirpath == dbc_dir:
                    dbc_file = f'{dirpath}/{oriName}'
                    oriBaseName = oriName.split(".")[0]
                    can_Channel = oriBaseName.split("_")[0]
                    dbc =  AnalyzeFile(dbc_file)
                    self.AnalyzeDict[can_Channel] = dbc
                    if can_Channel == main_can:
                        self.AnalyzeDictlist.insert(0,dbc)
                    else:
                        self.AnalyzeDictlist.append(dbc)

    def getAnalyzeSingleByName(self,sigName):
        for dbc in self.AnalyzeDictlist:
            assert isinstance(dbc,AnalyzeFile)
            if dbc.sigExist(sigName):
                return dbc
        dbc = self.AnalyzeDictlist[0]
        return dbc

    def getAnalyzeSingleBySigInfo(self,sig):
        assert isinstance(sig,SigInfo)
        can_Channel = SubNet_Channel.get(sig.subNet,SubNet_Channel.get("Other"))
        dbc =  self.AnalyzeDict.get(can_Channel,None)
        if dbc == None:
            printYellow(f"{sig.name}没有对应的dbc,can_Channel为{can_Channel} {self.AnalyzeDictlist}")
            dbc = self.AnalyzeDictlist[0]
        else:
            assert isinstance(dbc,AnalyzeFile)
        return dbc

    def GetChannelSig(self,*sigs):
        channelSig={}
        allSigs=[]
        for sig in sigs:
            if type(sig) == tuple:
                for childSig in sig:
                    if type(childSig) == list:
                        allSigs.extend(list(childSig))
                    else:
                        allSigs.append(childSig)
            else:
                allSigs.append(sig)

        for sig in allSigs:
            if type(sig) == SigInfo:
                assert isinstance(sig,SigInfo)
                dbc = self.getAnalyzeSingleBySigInfo(sig)
                sigInfo = sig
            else:
                dbc = self.getAnalyzeSingleByName(sig)
                sigInfo = dbc.getSig(sig)
            if dbc not in channelSig:
                channelSig[dbc] = []
            channelSig[dbc].append(sigInfo)
        return channelSig

    def getAnalyzeSingleByMsgInfo(self,msg):
        assert isinstance(msg,MessageInfo)
        can_Channel = SubNet_Channel.get(msg.subNet,SubNet_Channel.get("Other"))
        dbc =  self.AnalyzeDict.get(can_Channel,None)
        assert isinstance(dbc,AnalyzeFile)
        return dbc

    def GetChannelMsg(self,*msgs):
        channelSig={}
        for msg in msgs:
            assert isinstance(msg,MessageInfo)
            dbc = self.getAnalyzeSingleByMsgInfo(msg)
            if dbc not in channelSig:
                channelSig[dbc] = []
            channelSig[dbc].append(msg)
        return channelSig

    def getSig(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.getSig(sigName)
        return None
    
    def sigExist(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.sigExist(sigName)
        return False

    def sender(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.sender(sigName)
        return ''

    def getMessage_Id_BySig(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.getMessage_Id_BySig(sigName)
        return ''

    def getMessage_Id_Sig(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.getMessage_Id_Sig(sigName)
        return ''

    def getSigDataType(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.getSigDataType(sigName)
        return ''
    
    def physicalValueVaild(self,sigName,value):
        dbc = self.getAnalyzeSingleByName(sigName)
        if  dbc != None:
            return dbc.physicalValueVaild(sigName,value)
        return False
        
    def writeSig(self,sig,msg):
        dbc = self.getAnalyzeSingleBySigInfo(sig)
        if  dbc != None: 
            return dbc.writeSig(sig,msg)
        return WriteDBCResult.NoMessage
    
    def repalceSigEnum(self,*sigs):
        channelSig= self.GetChannelSig(sigs)
        for dbc in channelSig.keys():
            if dbc != None:
                assert isinstance(dbc,AnalyzeFile)
                dbc.repalceSigEnum(channelSig[dbc])
    
    def repalceSig(self,*sigs):
        channelSig= self.GetChannelSig(sigs)
        for dbc in channelSig.keys():
            if dbc != None:
                assert isinstance(dbc,AnalyzeFile)
                dbc.repalceSig(channelSig[dbc])

    def removeSig(self,*sigs):
        channelSig= self.GetChannelSig(sigs)
        for dbc in channelSig.keys():
            if dbc != None:
                assert isinstance(dbc,AnalyzeFile)
                dbc.removeSig(channelSig[dbc])

    def repalceMessage(self,*msgs):
        channelSig= self.GetChannelMsg(msgs)
        for dbc in channelSig.keys():
            if dbc != None:
                assert isinstance(dbc,AnalyzeFile)
                dbc.repalceMessage(channelSig[dbc])

    def isLocateSend(self,sigName):
        dbc = self.getAnalyzeSingleByName(sigName)
        if dbc != None:
            return dbc.isLocateSend(sigName)
        return False