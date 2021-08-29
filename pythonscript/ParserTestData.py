import json
import os
# from pythonscript.topic_def.topic_Parser import getJScontent
from commonfun import *


def deal(jsonPath,dataPath):
    js = getJScontent(jsonPath)
    dataJsons=[]
    for j in js:
        for  d in js[j]:
            if d == "desc" or d == "grade":
                continue
            dataJson={}
            dataJson["name"] = j
            dataJson["key"] = int(d)
            dataJson["desc"] = js[j][d]
            dataJson["grade"] = js[j]["grade"]
            dataJsons.append(dataJson)
    wirteFileDicts(dataPath,dataJsons)


if __name__ == "__main__":
    deal("/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/config/icwarning_config.json","/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/test/mqtt_publish/warn.data")