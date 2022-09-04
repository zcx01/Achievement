import sys
import argparse
from commonfun import*
import xlrd
from xlrd.book import Book
from xlrd.sheet import Sheet

class WarnGradeInfo(object):
    def __init__(self) :
        self.timeGrade=""
        self.grade = ""
        self.row = 0

    def printText(self):
        return '等级:'+self.grade+"时间等级:"+self.timeGrade+"行号:"+str(self.row)

def modifyJson(jsPath,modifyTextGrades):
    jsConfig = getJScontent(jsPath)
    copyJsconfig = jsConfig.copy()
    modifyTexts = []
    for topic in jsConfig:
        warnInfos = jsConfig[topic].copy()
        for textGrade in warnInfos:
            if  type(warnInfos[textGrade]) == str and type(textGrade) == str and isNumber(textGrade):
                    # grade = int(textGrade)
                    text = warnInfos[textGrade]
                    for modifyTextGrade in modifyTextGrades:
                        text = removeSeparator(text)
                        if modifyTextGrade == text:
                            try:
                                copyJsconfig[topic]['grade'][textGrade] = modifyTextGrades[modifyTextGrade].grade
                            except:
                                copyJsconfig[topic]['grade'] = modifyTextGrades[modifyTextGrade].grade
                            if 'timeGrade' not in copyJsconfig[topic]:
                                copyJsconfig[topic]['timeGrade'] = dict()
                            copyJsconfig[topic]['timeGrade'][textGrade] = modifyTextGrades[modifyTextGrade].timeGrade
                            printGreen(f"修改{text}报警等级完成")
                            modifyTexts.append(text)

    for modifyText in modifyTexts:
        if modifyText in modifyTextGrades:
            del modifyTextGrades[modifyText]
    
    printRed("以下文本修改失败，请手动修改")
    for modifyTextGrade in modifyTextGrades:
        printYellow(f"{modifyTextGrade} {modifyTextGrades[modifyTextGrade].printText()}")

    writeJs(jsPath,copyJsconfig)

def getCellValue(src, row, col):
    return src.cell_value(row, col)

def removeSeparator(text): #移除分割符
    text = EesyStr.removeAll(text, ",")
    text = EesyStr.removeAll(text,"，")
    text = EesyStr.removeAll(text,"\n")
    text = EesyStr.removeAll(text," ")
    text = EesyStr.removeAll(text,";")
    text = EesyStr.removeAll(text,"；")
    return text

def anyleXls(xlsFileName,jsPath):
    book = xlrd.open_workbook(xlsFileName)
    assert isinstance(book, Book)
    sheel = book.sheet_by_name("自动驾驶文字声音汇总V2.2 ")
    modifyTextGrades = {}
    for i in range(sheel.nrows):
        timeGrade = getCellValue(sheel,i,XlsCharToInt('G'))
        text = getCellValue(sheel,i,XlsCharToInt('I'))
        grade = getCellValue(sheel,i,XlsCharToInt('Q'))
        if grade != "":
            grade = EesyStr.removeAll(grade, "-")
            if "L2" in text:
                assert isinstance(text,str)
                texts = text.split("\n")
                text = ""
                for sTextIndex in range(len(texts)):
                    nextIndex = sTextIndex+1
                    if nextIndex >= len(texts):
                        text+= texts[sTextIndex]
                    else:
                        if 'L2' in texts[nextIndex]:
                            text+= texts[sTextIndex]+"："
                        else:
                            text+= texts[sTextIndex]
                        
                texts = text.split("：")
                for ltext in texts:
                    if 'L2' in ltext:
                        continue
                    ltext = removeSeparator(ltext)
                    gradeInfo = WarnGradeInfo()
                    gradeInfo.timeGrade = timeGrade
                    gradeInfo.grade = grade
                    gradeInfo.row = i
                    modifyTextGrades[ltext] = gradeInfo
            else:
                text =removeSeparator(text)
                gradeInfo = WarnGradeInfo()
                gradeInfo.timeGrade = timeGrade
                gradeInfo.grade = grade
                gradeInfo.row = i
                modifyTextGrades[text] = gradeInfo
    modifyJson(jsPath,modifyTextGrades)


if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        修改文本报警的配置文件
        ''')
    parse.add_argument('-j', '--json', help='文件报警的配置的文件的路径',type=str)
    parse.add_argument('-s', '--xls', help='文件报警的配置的文件的路径',type=str)
    arg = parse.parse_args()
    if '-s' in sys.argv and '-j' in sys.argv:
        anyleXls(arg.xls,arg.json)
