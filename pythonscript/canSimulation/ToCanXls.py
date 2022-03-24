#!/usr/bin/python
import os
from re import M
import sys
import xlrd
import argparse
import openpyxl 
from xlrd.book import Book
from xlrd.sheet import Sheet
from commonfun import *
from AnalyzeCan.projectInI import *
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"

def getValue(shell,row,col):
    return shell.cell_value(row,XlsCharToInt(col))

def conversion(aimPath,canPath):
    book = openpyxl.Workbook()
    OverView = book.active
    if True:
        OverView.title="4_OverView"
        OverView['A1'] = 'SubNet'
        OverView['B1'] = 'Nodes'
        OverView['C1'] = 'Sending Mode'
        OverView['D1'] = 'Cycle Time(ms)'
        OverView['E1'] = 'Sending ID(hex)'
        OverView['F1'] = 'DLC(byte)'
        OverView['G1'] = 'Involved Nodes'
        OverView['H1'] = '1/通讯速率'
        OverView['I1'] = 'Note'
        OverView['J1'] = 'MessageType 报文格式'

    if True:
        Matrix = book.create_sheet('5_Matrix')
        Matrix['A1'] = "sub-net"
        Matrix['B1'] = "Sender"
        Matrix['C1'] = "Signal Name"
        Matrix['D1'] = "Name In Chinese"
        Matrix['E1'] = "ID"
        Matrix['F1'] = "Cycle Time[ms]"
        Matrix['G1'] = "signal Start bit(0x)"
        Matrix['H1'] = "signal Length(0x)"
        Matrix['I1'] = "Factor"
        Matrix['J1'] = "Offset"
        Matrix['K1'] = "Physical Range Min(dec)"
        Matrix['L1'] = "Physical Range Max (dec)"
        Matrix['M1'] = "Signal Type"
        Matrix['N1'] = "Unit"
        Matrix['O1'] = "Description(hex)"
        Matrix['P1'] = "Initial Value (hex)"
        Matrix['Q1'] = ""
        Matrix['R1'] = "Invalid Value  (hex)"
        Matrix['S1'] = "Route mark"
        Matrix['T1'] = "Note"
        Matrix['U1'] = "Receiver"
        Matrix['V1'] = "SVDC相关"
        Matrix['W1'] = "备注"

    src_book = xlrd.open_workbook(canPath)
    assert isinstance(src_book, Book)

    matrixSheel = src_book.sheet_by_name(Sig_Matrix)
    # messageSheel = src_book.sheet_by_name(Message_Matrix)
    assert isinstance(matrixSheel, Sheet)
    # assert isinstance(messageSheel, Sheet)

    overViewSet=set()
    count_Id=0
    pre_startBit = -1
    for row in range(matrixSheel.nrows):
        try:
            lengthBit=int(getValue(matrixSheel, row, XlsCharToInt("K")))*8
        except:
            continue
        while True:
            sendId="00" + str(count_Id+1)
            pre_startBit= pre_startBit + lengthBit 
            if pre_startBit > 511: # 64 * 8 -1
                pre_startBit = -1
                count_Id+=1
            else:
                break

        startBit = pre_startBit
        if lengthBit > 7:
            startBit -= 7

        receiver = getValue(matrixSheel,row,XlsCharToInt("X"))
        receiver = 'CDC'
        if sendId not in overViewSet:
            printGreen(f"生成 {sendId} 节点")
            overViewInfo =[]
            overViewInfo.append("HCAN")
            overViewInfo.append("ADS")
            overViewInfo.append("cyclic")
            overViewInfo.append(100)
            overViewInfo.append("0x"+sendId)
            overViewInfo.append(64)
            overViewInfo.append(f"ADS,{receiver}")
            overViewInfo.append(500)
            overViewInfo.append("")
            overViewInfo.append("")
            OverView.append(overViewInfo)
            overViewSet.add(sendId)

        matrixInfo=[]
        matrixInfo.append("HCAN")
        matrixInfo.append("ADS")
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("F")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("G")))
        matrixInfo.append(sendId)
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("I")))
        matrixInfo.append(startBit)
        matrixInfo.append(lengthBit)
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("M")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("N")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("O")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("P")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("Q")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("R")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("S")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("T")))
        matrixInfo.append("")
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("U")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("V")))
        matrixInfo.append(getValue(matrixSheel, row, XlsCharToInt("W")))
        matrixInfo.append(receiver)
        matrixInfo.append("")
        matrixInfo.append("")
        Matrix.append(matrixInfo)

    book.save(aimPath)
    printGreen("生成完成")



if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        从其他表格转化成xlsdbc脚本能够识别的脚本
        ''')
    parse.add_argument('-a', '--aimPath', help='生成的CAN矩阵路径',type=str)
    parse.add_argument('-s', '--xls', help='要转化的can矩阵', nargs='?', type=str)
    arg = parse.parse_args()
    conversion(arg.aimPath, arg.xls)
