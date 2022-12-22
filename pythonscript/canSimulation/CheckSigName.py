#!/usr/bin/python
import argparse
from commonfun import*
from AnalyzeCan.Analyzedbc import *
from xlrd.book import Book
from xlrd.sheet import Sheet
import xlrd

'''
    可以检测的前提条件
    message名称必须是id结尾
'''

def findsignalInfile(signal,content):
    try:
        for text in content:
            texts = re.findall(e_i,text,re.A)
            try:
                if signal == texts[0]:
                    return True
            except:
                pass
        return False
    except:
        return False

def getJsConfig(configPath="",down_config="",up_config="",isPrint = False):
    if configPath == "": configPath = pyFileDir+"config.json"
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)

    if down_config == "":
        down_config = getKeyPath("down", jsConfig)
    if up_config == "":
        up_config = getKeyPath('up', jsConfig)
    
    if isPrint:
        print("down_config:",down_config)
        print("up_config:",up_config)
    dbc = Analyze(dbcfile)
    jsDown = getJScontent(down_config)
    jsUp = getJScontent(up_config)
    return jsDown,jsUp,dbc,jsConfig,down_config,up_config

def CheckSigName(configPath,down_config="",up_config=""):
    jsDown, jsUp, dbc, jsConfig ,down_config,up_config= getJsConfig(configPath,down_config,up_config,True)
    sigNames = {}

    igSigs = []
    checkSigIgnore = getKeyPath("checkSigIgnore",jsConfig)
    if os.path.exists(checkSigIgnore):
        igSigs = getJScontent(checkSigIgnore)
    for top in jsDown:
        topValue = jsDown[top]
        topNoSet = EesyStr.removeAll(top, SETSTR)
        if type(topValue) == str:
            if topValue != top:
                sigNames[topValue] = 0
        else:
            for t in topValue:
                if t != top and t != topNoSet:
                    sigNames[t] = 0
    for s in jsUp:
        isTopc = False
        if type(jsUp[s]) == dict:
            for k in jsUp[s]:
                if k == "bindSigNames":
                    isTopc = True
                    for bindSigName in jsUp[s][k]:
                        sigNames[bindSigName] = s
        if not isTopc: sigNames[s] = 1

    for igSig in igSigs:
        if igSig in sigNames:
            del sigNames[igSig]

    bar= ProgressBar()
    bar.total = len(sigNames)
    igCmd =""
    for sig in sigNames:
        bar.printCurrnt()
        if is_chinese(sig):
            continue
        dbcSigName,Sender,isChanged = configConverdbc(sig,dbc)

        if Sender == None:
            if 'd' not in igCmd:
                igCmd = input("下次检测是否忽略y(是)/n(否)/dy(全是)/dn(全否)")
            if 'y' in igCmd:
                igSigs.append(sig)
            continue
        if  not isChanged:
            continue
        can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
        f=open(can_parse_whitelistPath,'r')
        whitelistPath_content=f.readlines()
        f.close()
        messagesig = dbcSigName.replace("/","__")
        if  not findsignalInfile(f'{messagesig}',whitelistPath_content):
            printRed(f'{messagesig} 不在白名单中')
        
        if  sigNames[sig] == 1: 
            addConfigDict(jsUp,dbcSigName,sig)       
        elif  sigNames[sig] == 0: 
            addConfigDict(jsDown,sig,dbcSigName)
        elif type(sigNames[sig]) == str:
            replaceIndex = jsUp[sigNames[sig]]["bindSigNames"].index(sig)
            jsUp[sigNames[sig]]["bindSigNames"][replaceIndex] = dbcSigName

    writeJs(down_config,jsDown)
    writeJs(up_config,jsUp)
    writeJs(checkSigIgnore,igSigs)
    bar.printCurrnt()
    printGreen("分析完成")

def ToJaveCode(javaPath,configPath,down_config=None,up_config=None):
    pass


def splitSig(sig):
    assert isinstance(sig,str)
    sigs = []
    sigs.append(sig)
    if "__" in sig:
        tempSigs =  sig.split("__")
    elif "/" in sig:
        tempSigs =  sig.split("/")
    else:
        return sigs

    if len(tempSigs) < 2:
        return sigs
    sigs.clear()
    tempMesages = re.findall(m_s,tempSigs[0])
    id = tempMesages.pop()
    sender = "_".join(tempMesages)
    sigs.append(sender)
    sigs.append(id)
    sigs.append(tempSigs[1])
    return sigs
        

def configConverdbc(sig,dbc):
    assert isinstance(dbc,Analyze)
    assert isinstance(sig,str)
    sigs = splitSig(sig)
    dbcSig = None
    if len(sigs) >= 3 :
        try:
            sig16= str(int(sigs[1],16))+"_".join(sigs[2:])
            prefix= f"{sigs[0]}_{sigs[1]}"
            dbcSig = dbc.getSig(sig16,sigs[0])
            if dbcSig != None and dbcSig.getMessage_Name() != prefix:
                printYellow(f' {sig:<50} {prefix} {dbcSig.getMessage_Name()} message名称错误，即将替换')
                return sig.replace(prefix,dbcSig.getMessage_Name()),dbcSig.Sender,True
        except:
            pass
    if dbcSig==None:
        dbcSig = dbc.getSig(sig)
        if dbcSig == None:
            printRed(f'{sig:<50}  信号格式错误')
    return sig if dbcSig == None else dbcSig.getMessage_Name()+'/'+dbcSig.name, None if dbcSig == None else dbcSig.Sender,False

def addConfigDict(js,key,value):
    if value in js: del js[value] 
    js[key] = value

def reConfigDict(js,key,value): # 添加进容器，如果有重复就打印，不添加
    if key in js :
        try:
            if js[key] == value:
                printYellow(f'{value} 是存在的')
                return
            else:
                js[key] = value
        except:
            js[key] = value
    else:
        js[key] = value
    printGreen(f'{value} 添加完成')

def addSet(topic):
    if not topic.endswith(SETSTR): topic = topic+SETSTR
    return topic

def ToConfigJson(javaPath,configPath,down_config="",up_config=""):
    contents = readFileLines(javaPath)
    jsDown, jsUp, dbc, jsConfig,down_config,up_config = getJsConfig(configPath,down_config,up_config)
    for content in contents:
        tContents = re.findall(r'topic = ".*"',content)
        if len(tContents) != 0:
            tContent = re.findall(r'".*"',tContents[0])[0]
            assert isinstance(tContent,str)
            tContent=tContent.replace('\"',"")
            dbcSigName,Sender,isChanged = configConverdbc(tContent,dbc)
            down_topic=addSet(tContent)
            if Sender == None:
                continue
            if Sender not in local_machine_Sender: 
                addConfigDict(jsUp,dbcSigName,tContent)       
                # if down_topic in jsDown :del jsDown[down_topic]   
            if Sender in local_machine_Sender: 
                addConfigDict(jsDown,down_topic,dbcSigName)
                # if dbcSigName in jsUp: del jsUp[dbcSigName]

    writeJs(down_config,jsDown)
    writeJs(up_config,jsUp)

def addConfigSig(sigs,isOriginal,configPath="",down_config="",up_config=""):
    jsDown, jsUp, dbc, jsConfig,down_config,up_config = getJsConfig(configPath,down_config,up_config)
    for sigName in sigs:
        assert isinstance(sigName,str)
        dbcSigName,Sender,isChanged = configConverdbc(sigName,dbc)
        down_topic = sigName if isOriginal else dbcSigName
        down_topic = addSet(sigName)
        if Sender == None:
            printRed(f"{sigName} 没有发送者")
            continue
        if Sender not in local_machine_Sender: 
            reConfigDict(jsUp,dbcSigName,sigName if isOriginal else dbcSigName)       
            # if down_topic in jsDown :del jsDown[down_topic]   
        if Sender in local_machine_Sender: 
            reConfigDict(jsDown,down_topic,dbcSigName)
            # if dbcSigName in jsUp: del jsUp[dbcSigName]


    writeJs(down_config,jsDown)
    writeJs(up_config,jsUp)

def getCellValue(src, row, col):
    return src.cell_value(row, col)

class SigXls():
    def __init__(self) -> None:
        self.sigName =""
        self.msgid = ""
        self.Sender = ""

    def msgId_sigName(self):
        return self.Sender+"_"+self.msgid+'/'+self.sigName

def getSigXls(xlsFileName):
    sigs = []
    book = xlrd.open_workbook(xlsFileName)
    assert isinstance(book, Book)
    sheel = book.sheet_by_name(Sig_Matrix)
    for i in range(sheel.nrows):
        try:
            sigName = getCellValue(sheel,i,XlsCharToInt('C'))
            if len(sigName) == 0:
                printRed(f'{i}行是空的')
                continue
            msgid =  str( getCellValue(sheel,i,XlsCharToInt('E'))).split(".")[0].replace('0x', '')
            Sender= getCellValue(sheel,i,XlsCharToInt('B'))
            sigXls = SigXls()
            sigXls.Sender = Sender
            sigXls.msgid = msgid
            sigXls.sigName = sigName
            sigs.append(sigXls)
        except:
            printRed(f'获取 {sigName} 信息失败')
            pass
    return sigs

def addConfigByXls(xlsFileName):
    sigs = []
    sigXls = getSigXls(xlsFileName)
    for sig in sigXls:
        assert isinstance(sig,SigXls)
        sigs.append(sig.msgId_sigName())
    addConfigSig(sigs,True)

def addMultipleSig(canmatrix,msgIds,topics):
    jsDown, jsUp, dbc, jsConfig,down_config,up_config = getJsConfig()
    if canmatrix =='':
        canmatrix = getKeyPath("canmatrix", jsConfig)
    sigXls = getSigXls(canmatrix)
    sigs = []
    for msgIdIndex in range(len(msgIds)):
        msgId = msgIds[msgIdIndex]
        for sig in sigXls:
            assert isinstance(sig,SigXls)
            if sig.msgid == msgId:
                sigs.append(sig.msgId_sigName())

        if len(topics)!=0:
            bindSigNames=[]
            for sigName in sigs:
                assert isinstance(sigName,str)
                try:
                    dbcSigName,Sender,isChanged = configConverdbc(sigName,dbc)
                except:
                    printRed(f"{sigName} 信号格式错误")
                    continue   
                bindSigNames.append(dbcSigName)

            if Sender not in local_machine_Sender and not topics[msgIdIndex].endswith(SETSTR): 
                jsUp[topics[msgIdIndex]]={}
                jsUp[topics[msgIdIndex]]['bindSigNames'] = bindSigNames
            else:
                jsDown[addSet(topics[msgIdIndex])] = {}
                for bindSigName in bindSigNames:
                    jsDown[addSet(topics[msgIdIndex])][bindSigName]={}
            sigs.clear()

    if len(topics)!=0:    
        writeJs(down_config,jsDown)
        writeJs(up_config,jsUp)     
    else:
        addConfigSig(sigs,True,"",down_config,up_config)

if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        检查配置文件是否正确
        从配置文件生成java代码
        从java生成配置文件
        ''')
    parse.add_argument('-j', '--ToJave', help='生成json代码', nargs='?', type=str)
    parse.add_argument('-c', '--ToConfig', help='从java代码生成配置文件',type=str)
    parse.add_argument('-s', '--addSig', help='把信号添加带配置文件中',nargs='+',type=str)
    parse.add_argument('-a', '--xls', help='把表格中所有的信号都添加配置文件中,-s为表格的路径',type=str,default='')
    parse.add_argument('-d', '--downjson', help='下行文件路径，没有从配置中读取',type=str,default='', nargs='?')
    parse.add_argument('-u', '--upjson', help='上行文件路径，没有从配置中读取',type=str,default='', nargs='?')
    parse.add_argument('-t', '--topic', help='topic是列表和-m参数索引要对应',default=[], nargs='+', type=str)
    parse.add_argument('-m', '--messages', help='新增messages是一个列表',default=[], nargs='+', type=str)
    arg = parse.parse_args()
    configPath = pyFileDir+"config.json"

    if '-m' in sys.argv:
        addMultipleSig(arg.xls,arg.messages,arg.topic)
    elif '-j' in sys.argv:
        ToJaveCode(arg.ToJave,configPath)
    elif '-c' in sys.argv:
        ToConfigJson(arg.ToConfig,configPath)
    elif '-s' in sys.argv:
        addConfigSig(arg.addSig,False,configPath)
    elif '-a' in sys.argv:
        addConfigByXls(arg.xls)
    else:
        CheckSigName(configPath,arg.downjson,arg.upjson)
    
