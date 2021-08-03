#!/usr/bin/python
import json
import sys
import os
from Analyzedbc import Analyze

def get_upper_case_name(text):
    lst = []
    last_char = ''
    for index, char in enumerate(text):
        if char.isupper() and index != 0 and last_char.islower():
            lst.append("_")
        lst.append(char)
        last_char = char
    result = "".join(lst).upper()
    return result

def getConfig(signame,desc):
    return str('''
    "%s":{
        "desc": "%s" 
    },''' % (signame,desc))

def getJScontent(configJson):
    cr = open(configJson, "r")
    return json.load(cr)

def writeJs(configJson,jsContent):
    cr = open(configJson, "w")
    cr.write(json.dumps(jsContent,ensure_ascii=False,indent=4))

def getSigJson(sigName):
    filePath=jsConfig.get(sigName,"")
    while True:
        if os.path.isfile(filePath):
            return filePath
        else:
            print(f'请输入{sigName}对应json配置文件:')
            filePath=input()
            if not os.path.isfile(filePath):
                print(f'{filePath}不存在')
            else:
                jsConfig[sigName]=filePath
                writeJs("./config.json",jsConfig)
    
if __name__ == "__main__":
    jsConfig=getJScontent("./config.json")
    analy=Analyze(jsConfig["dbcfile"])
    if len(sys.argv) ==2:
        newSigFile=open(jsConfig["newSig"],"r")
        content=newSigFile.readlines()
        messageGroup={}
        messageNames={}
        for text in content:
            if text.strip().startswith("#"):
                continue
            names=text.split("\t")
            if len(names) == 1:
                names=text.split(" ")
            sig=names[0].strip()
            desc=names[1]
            desc=names[1].strip()
            message=analy.getMessageBySig(sig)
            if len(message)==0:
                print(f'{sig}对应的message不存在')
                continue

            messageNames[message]=messageNames.get(message,"")+f'{message}__{sig:<30}       [signal]		[get, change_handle]\n'
            messageGroup[message]=messageGroup.get(message,"")+getConfig(sig,desc)
            jsSig=getJScontent(getSigJson(message))
            if sig not in jsSig:
                jsSig[sig]={"desc":desc}
                writeJs(getSigJson(message),jsSig)
        for msg in messageGroup.keys():
            print(f'{msg}'+"--------------")
            print(messageNames[message])
            print(messageGroup[message])

        newSigFile.close()
        exit()

    if len(sys.argv) < 4:
        print('Error: input json file(*.json) or out file(*.h) not specified')
        sys.exit()
    f_in = open(sys.argv[1], 'r')
    type= sys.argv[3]
    if len(type) == 0:
        print("输入类型")
        exit()

    content = json.loads(f_in.read())
    # content["test"]={"desc":"测试"}
    # w_in = open(sys.argv[1],"w")
    # w_in.write(json.dumps(content,ensure_ascii=False,indent=4))
    sorted(content)

    for item in content:
        print('//' + content[item]['desc'])
        line = 'TOPIC_' + get_upper_case_name(sys.argv[2]) + '_' + get_upper_case_name(item)
        if(type == "-v"):
            print(f'python monitor.py -s  BcmPwrStsFb  -v 3 -s {item} -v 10')
        elif(type == "-s"):
            print(f'vehctrl_status_int->addSignalAndTop((struct veh_signal *)&CANSIG_GW_352__{item}_g, {line});'+ '\n')
        elif(type == "-a"):
            desc=content[item]['desc']
            print(f'AutoCode vehctrl classname CDC_2D2__{item} {line} {desc}')
        elif(type == "-c"):
            print('\
        else if (topicId == %s) {\n\
\n\
        /*value not change*/\n\
        send_can_frame(&CANSIG_CDC_2D2__%s_g, info.value, signal_value_type::eSigValType_uint32_t);\n\
\n\
        /*send value back to UI*/\n\
        publish_status(%s, info.value);\n\
\n\
    }' % ( line,item,line))
        #/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/../config/vehctrl_status_config.json /home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/topic_def/vehctrlSts_topic_def.h
        #/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/../config/vehctrl_config.json /home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/scripts/topic_def/vehctrl_topic_def.h


