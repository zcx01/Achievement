# from typing import List
import json
import re
import sys

w_d=r'[a-zA-Z_]'                #匹配单词
i_i=r"-?[0x0-9]"                #匹配数字
e_i=r"-?\b[a-zA-Z_0x0-9.]+\b"   #匹配单词和数字(包括小数和负数)
d_t=r"\bIPC_\S+\b"              #匹配以IPC开头一句话
s_i = r"CANSIG_.*_g"    
s_i_e = r"CANSIG.\w+"           #匹配CANSIG开头的单词
m_s = r"[a-zA-Z0x0-9]+"         #匹配单词和数字
'''
[a-zA-Z_]+::                    #匹配以::结束的单词
'''

def sendMqtt(topic,value):
    topic=str(topic).replace(r'"','')
    return f'on -T ic_apps_t -u ic_apps mega_ipc_pub -t  \'{topic}\'  -m \''+'{'+f'\"extension\":\"\",\"relative\":false,\"time\":14603935,\"type\":4194304,\"unit\":\"\",\"valid\":true,\"value\":{value}'+'}\''

def subMqtt(topic):
    topic=str(topic).replace(r'"','')
    return f'on -T ic_apps_t -u ic_apps mega_ipc_sub -t \'{topic}\''
    
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

def writeFileAll(file,data):
    cr = open(file, "w")
    cr.write(data)
    cr.close()

def readFileAll(file):
    with open(file, "r") as cr:
        return cr.read()

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
    assert isinstance(path,str)
    if path.startswith("/") or path.startswith("./") or path.startswith("../"):
        return path
    else:
        projectPath=jsConfig.get("projectPath","")
        return projectPath+path

def getKeyPath(key,jsConfig):
    return getFullPath(jsConfig.get(key,""),jsConfig)


def splitSpaceGetValueByIndex(text,index,defaultValue=""):
    return getValueByIndex(splitSpace(text),index,defaultValue)

#判断字符串是否是数字(数字、小数、负数、负小数、0)
def isNumber(text):
    assert isinstance(text,str)
    if '0x' in text:
        text=str(int(text,16))
    if (text.split(".")[0]).isdigit() or text.isdigit() or  (text.split('-')[-1]).split(".")[-1].isdigit():
        if re.search(w_d,text,re.A) == None:
            return True
    return False

"""
检查整个字符串是否包含中文
:param string: 需要检查的字符串
:return: bool
"""
def is_chinese(string):
    for ch in string:
        if u'\u4e00' <= ch <= u'\u9fff':
            return True
    return False
    
#科学技术法转化成数字
def eConverf(value):
    valueStr =str(value)#会把E转化为e
    if 'e' in valueStr:
        valueStrs = valueStr.split('e')
        if valueStrs[1].startswith('-'):
            flootStr = valueStrs[0].split(".")
            digit = 0
            if len(flootStr) > 1:
                digit += len(flootStr[1])
            digit += abs(int(valueStrs[1]))
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

#在指定行后面添加contents
def behindIndex(lines,pos,contents):
    temp=[]
    temp.extend(lines[0:pos])
    temp.extend(contents)
    temp.extend(lines[pos:len(lines)])
    return temp

#
def getNoOx16(text):
    content = str(text)
    if content.startswith('0x'):
        return content.replace('0x', '').upper()
    else:
        preStr=''
        for i in range(len(text)):
            if '0' != text[i]:
                break
            preStr+='0'
        return preStr+str(hex(int(text))).replace('0x','').upper()

#得到关联的类名
def getRelationClassName(text):
    n_i = r'new.*\('
    m_i = r'<.*>'
    className=''
    classNames = re.findall(n_i,text,re.A)
    if len(classNames) == 0:
        classNames = re.findall(m_i,text,re.A)
    if len(classNames) != 0:
        className = classNames[0]
        assert isinstance(className,str)
        className= className.replace('<','')
        className= className.replace('>','')
        if len(re.findall(r"-?\b[a-zA-Z_::0x0-9.]+\b",className,re.A)) != 1:
            className=''
        if "::" in className:
            className = re.findall(e_i,className,re.A)[1]
    return className

#得到本文件的类名
def getSelfClassName(text):
    m_i = r'[a-zA-Z_::]+::'
    classNames = re.findall(m_i,text,re.A)
    className= ''
    if len(classNames) != 0:
        className = classNames[0]
        className.replace(" ",'')
        className = className.split('::')
        className = className[len(className)-2]
    return className

#移除指定行 Indexs:索引集合
def removeListIndexs(linelist,Indexs):
    temp = []
    for index in range(len(linelist)):
        if index not in Indexs:
            temp.append(linelist[index])
    return temp

def printRed(infoStr):
    print('\033[31m'+infoStr+'\033[0m')

def printGreen(infoStr):
    print('\033[32m'+infoStr+'\033[0m')
    
def printYellow(infoStr):
    print('\033[33m'+infoStr+'\033[0m')

def XlsCharToInt(col):
    if type(col) == str:
        return ord(col) - ord('A')
    return col

# print(removeListIndexs([12,23,56],[0,2]))
# def Temp(linelist):
#     linelist.append('ddd')
# linelist=['ww']
# Temp(linelist)
# print(linelist)
