# from typing import List
import json
import re
class EesyStr():
    @staticmethod
    def removeAt(s,index):
        temp=list(s)
        try:
            temp.pop(index)
        except:
            print("移除失败，索引超出范围")
        return "".join(temp)

    @staticmethod
    def removeOne(s,r):
        temp=list(s)
        tempr=list(r)
        try:
            temp.remove(tempr)
        except:
            print("移除失败")
        return "".join(temp)

    @staticmethod
    def removeAll(s,r):
        return s.replace(r,"")

    @staticmethod
    def chop(s):
        temp=list(s)
        try:
            temp.pop()
        except:
            print("删除失败，字符串为空")
        return "".join(temp)


def getJScontent(configJson):
    with open(configJson, "r") as cr:
        return json.load(cr)

def writeJs(configJson,jsContent):
    cr = open(configJson, "w")
    cr.write(json.dumps(jsContent,ensure_ascii=False,indent=4))
    cr.close()

def wirteFileDicts(file,data,replace=True):
    cr = open(file, "w")
    if replace:
        for d in data:
            cr.write(str(d).replace("\'","\"")+"\n")
    else:
        cr.writelines('\n'.join(data))
    cr.close()

def readFileLines(file):
    with open(file, "r") as cr:
        return cr.read().splitlines()

def getValueByIndex(names,index,defaultValue=""):
    try:
        return names[index]
    except:
        return defaultValue

def splitSpace(text):
    # text=str(text)
    texts=text.split(" ")
    contents=[]
    for t in texts:
        if len(t) != 0:
            contents.append(t)
    return contents

def getFullPath(path,jsConfig):
    # path=str(path)
    if path.startswith("/"):
        return path
    else:
        projectPath=jsConfig.get("projectPath","")
        return projectPath+path

def getKeyPath(key,jsConfig):
    return getFullPath(jsConfig.get(key,""),jsConfig)


def splitSpaceGetValueByIndex(text,index,defaultValue=""):
    return getValueByIndex(splitSpace(text),index,defaultValue)

def getWordAndNum(text):
    e_i = r"\b[a-zA-Z0x0-9]+\b"
    return re.findall(e_i, text, re.A)

def getWord(text):
    e_i = r"\b[a-zA-Z]+\b"
    return re.findall(e_i, text, re.A)

def getNum(text):
    e_i = r"\b[0-9]+\b"
    return re.findall(e_i, text, re.A)

#判断字符串是否是数字(数字、小数、负数、负小数、0)
def isNumber(text):
    if (text.split(".")[0]).isdigit() or text.isdigit() or  (text.split('-')[-1]).split(".")[-1].isdigit():
        return True
    else:
        return False

#科学技术法转化成数字
def eConverf(value):
    valueStr =str(value)#会把E转化为e
    if 'e' in valueStr:
        valueStrs = valueStr.split('e')
        if valueStrs[1].startswith('-'):
            digit = abs(int(valueStrs[1]))
            digit += len(valueStrs[0])-2
            head='{:.%df}' % digit
            return head.format(value)
    return value

#在lines关键字behind后面添加content
def behindStr(lines,behind,content):
    index = 0
    behinds=[]
    row=0
    while index < len(lines):
        if behind in lines[index]:
            behinds.append(lines[index])
            row = index+1
        index+=1
    if content not in behinds:
        lines.insert(row,content)