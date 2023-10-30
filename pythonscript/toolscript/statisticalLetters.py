
#!/bin/python
import os
import argparse
import xlrd
import openpyxl
import re

# def getStatistFilePath(dir,file):
#     file_path = os.path.join(dir, file)
#     if os.path
def XlsCharToInt(col):
    if type(col) == str:
        cols = list(col)
        colnum = len(cols) - 1
        return colnum*26 + (ord(cols[colnum]) - ord('A'))
    return col

def XlsIntToChar(col):
    if type(col) == int:
        return chr(col+ord('A')) 
    return col

def getIniCell(Name):
    sh=[]
    sh.append(Name)
    for i in range(26):
        sh.append(0)
    return sh

def readFileLines(file):
    with open(file, "r") as cr:
        return cr.read().splitlines()
  
def StatisticalLetters(directory,filterateFile =''):
    statistDir = directory+"/统计"
    if not os.path.exists(statistDir):
        print(f'创建{statistDir}文件夹')
        os.makedirs(statistDir)
    filterateStr = []
    if len(filterateFile) != 0:
        filterateStr = readFileLines(filterateFile)
    for root, directories, files in os.walk(directory):
        if root != directory: return
        for file in files:
            file_path = os.path.join(root, file)
            # 打开原始Excel文件
            print(f'开始分析{file_path}文件')

            # 打开Excel文件
            workbook = xlrd.open_workbook(file_path)

            # 获取第一个工作表
            sheet = workbook.sheet_by_index(0)

            # 创建新的Excel文件
            new_workbook = openpyxl.Workbook()
            new_sheet = new_workbook.active

            sh=[]
            sh.append('Segmence')
            for i in range(26):
                sh.append(f'{XlsIntToChar(i)} Count')
            new_sheet.append(sh)

            # 获取过滤的列数
            filterateStrCol = []
            for col in  range(sheet.ncols):
                cell_value = str(sheet.cell_value(0, col))
                if cell_value in filterateStr :
                    filterateStrCol.append(col)

            # 遍历原始Excel文件中的所有单元格
            for row  in range(sheet.nrows):
                for col in  range(sheet.ncols):
                    if col in filterateStrCol: continue
                    # 读取单元格的值
                    cell_value = str(sheet.cell_value(row, col))
                    cell_values = re.findall(r'[a-zA-Z]',cell_value,re.A)
                    if len(cell_values) == 0: continue
                    sh = getIniCell(cell_value)
                    for c in cell_values:
                        cIndex = XlsCharToInt(c.upper())+1
                        try:
                            sh[cIndex] = sh[cIndex] + 1
                        except:
                            print(c,cIndex,cell_value)
                            break
                    new_sheet.append(sh)

            print(f'分析{file_path}完成')
            new_file_path = os.path.join(statistDir, file)
            new_workbook.save(new_file_path)
            print(f'生成{new_file_path}完成')


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-d','--dir',help='统计的目录',nargs='?',default='',type=str)
    parser.add_argument('-f','--filterateFile',help='过滤的文件名称',nargs='?',default='',type=str)
    arg = parser.parse_args()
    StatisticalLetters(arg.dir,arg.filterateFile)