# from typing import List
import json
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
        try:
            temp.remove(r)
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

def wirteFileDicts(file,data):
    cr = open(file, "w")
    for d in data:
        cr.write(str(d).replace("\'","\"")+"\n")
    cr.close()

def readFileLine(file):
    with open(file, "r") as cr:
        return cr.readline()

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

def splitSpaceGetValueByIndex(text,index,defaultValue=""):
    return getValueByIndex(splitSpace(text),index,defaultValue)