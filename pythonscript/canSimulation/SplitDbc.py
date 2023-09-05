#!/usr/bin/python
import os
import sys
import xlrd
import argparse

from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import*
from analyze_dbc.analyze_dbc import *
from xlsdbc import *


def getSheelSig(canDir):
    sigDict={}
    for (dirpath,dirnames,filenames) in os.walk(canDir):
            for oriName in filenames:
                can_file = f'{dirpath}/{oriName}' 
                book = xlrd.open_workbook(can_file)
                assert isinstance(book, Book)
                sheel = book.sheet_by_name(Sig_Matrix)
                for row in range(sheel.nrows):
                    sig = getSigInfo(sheel, row)
                    if sig.getMessage_Sig() not in sigDict:
                        sigDict[sig.getMessage_Sig()] = sig
    return sigDict

def conversionByOtherdbc(configPath):
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    ori_dbc = AnalyzeFile(dbcfile)
    dir =  os.path.dirname(dbcfile)
    sigDict = getSheelSig(dir+"/can")
    adbSig=[]
    for messageSig in ori_dbc.dbcSigs:
        ori_sig = ori_dbc.getSig(messageSig)
        # if ori_sig.messageId == "3AF":
        # if ori_sig.name !="HU_CRCCheck_3AF":
        #    continue  
        can_sig = sigDict.get(ori_sig.getMessage_Sig(),None)
        if can_sig != None:
            ori_sig.subNet = can_sig.subNet
        msg = ori_dbc.dbcMessage.get(ori_sig.messageId, None)
        if msg == None:
            printRed(f' {ori_sig.name} 对应的 {ori_sig.messageId} message不存在')
            continue
        adbSig.append(ori_sig.name)
        dbc_dir = dir+"/dbc"
        dbc = Analyze(dbc_dir)
        dbc.writeSig(ori_sig, msg)

    print(str(" ".join(adbSig)))


if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        这个脚本是用来拆分dbc，分成两路CAN的dbc
        ''')
    conversionByOtherdbc(pyFileDir+"config.json")
    