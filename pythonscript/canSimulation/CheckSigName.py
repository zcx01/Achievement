#!/usr/bin/python
import argparse
from nis import cat
from commonfun import*
from AnalyzeCan.Analyzedbc import *
from xlrd.book import Book
from xlrd.sheet import Sheet
import xlrd

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

def CheckSigName(configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    if down_config == None:
        down_config= getKeyPath("down",jsConfig)
    if up_config == None:
        up_config = getKeyPath('up',jsConfig)
    jsDown = getJScontent(down_config)
    jsUp   = getJScontent(up_config)
    sigNames = {}
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)

    for top in jsDown:
        topValue = jsDown[top]
        if type(topValue) == str:
            if topValue != top:
                sigNames[topValue] = 0
        else:
            for t in topValue:
                if t != top:
                    sigNames[t] = 0
    for s in jsUp:
       sigNames[s] = 1

    for sig in sigNames:
        if is_chinese(sig):
            continue
        dbcSigName,Sender,isChanged = configConverdbc(sig,dbc)

        can_parse_whitelistPath = getKeyPath("can_parse_whitelist", jsConfig)
        f=open(can_parse_whitelistPath,'r')
        whitelistPath_content=f.readlines()
        f.close()
        messagesig = dbcSigName.replace("/","__")
        if  not findsignalInfile(f'{messagesig}',whitelistPath_content):
            printRed(f'{messagesig} 不在白名单中')
        
        if Sender == None or not isChanged:
            continue
        if  sigNames[sig] == 1: 
            addConfigDict(jsUp,dbcSigName,sig)       
        if  sigNames[sig] == 0: 
            addConfigDict(jsDown,sig,dbcSigName)
    printGreen("分析完成")

def ToJaveCode(javaPath,configPath,down_config=None,up_config=None):
    pass

def configConverdbc(sig,dbc):
    assert isinstance(dbc,Analyze)
    assert isinstance(sig,str)
    sigs = re.findall(m_s,sig)
    dbcSig = None
    if len(sigs) >= 3 :
        sig16= str(int(sigs[1],16))+"_".join(sigs[2:])
        prefix= f"{sigs[0]}_{sigs[1]}"
        dbcSig = dbc.getSig(sig16)
        if dbcSig == None:
            printRed(f'{sig:<50} {sig16}  没有对应的信号')
        elif dbcSig.getMessage_Name() != prefix:
            # printYellow(f'{sig:<50} {prefix} {dbcSig.getMessage_Name()} message名称错误，即将替换')
            return sig.replace(prefix,dbcSig.getMessage_Name()),dbcSig.Sender,True
    else:
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
                printYellow(f'{key} 是存在的')
                return
            else:
                # y = input("是否替换y/n")
                # if y == 'y':
                js[key] = value
        except:
            js[key] = value
    else:
        js[key] = value
    printGreen(f'{key} 添加完成')

def ToConfigJson(javaPath,configPath,down_config=None,up_config=None):
    jsConfig = getJScontent(configPath)
    contents = readFileLines(javaPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)

    if down_config == None:
        down_config = getKeyPath("down", jsConfig)
    if up_config == None:
        up_config = getKeyPath('up', jsConfig)

    jsDown = getJScontent(down_config)
    jsUp = getJScontent(up_config)
    for content in contents:
        tContents = re.findall(r'topic = ".*"',content)
        if len(tContents) != 0:
            tContent = re.findall(r'".*"',tContents[0])[0]
            assert isinstance(tContent,str)
            tContent=tContent.replace('\"',"")
            dbcSigName,Sender,isChanged = configConverdbc(tContent,dbc)
            if not tContent.endswith('/Set'): down_topic = tContent+"/Set"
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

def addConfigSig(sigs,configPath=None,down_config=None,up_config=None):
    if configPath == None: configPath = pyFileDir+"config.json"
    jsConfig = getJScontent(configPath)
    dbcfile = getKeyPath("dbcfile", jsConfig)
    dbc = Analyze(dbcfile)

    if down_config == None:
        down_config = getKeyPath("down", jsConfig)
    if up_config == None:
        up_config = getKeyPath('up', jsConfig)

    jsDown = getJScontent(down_config)
    jsUp = getJScontent(up_config)
    for sigName in sigs:
        assert isinstance(sigName,str)
        try:
            dbcSigName,Sender,isChanged = configConverdbc(sigName,dbc)
        except:
            printRed(f"{sigName} 信号格式错误")
            continue
        if not sigName.endswith('/Set'): down_topic = sigName+"/Set"
        if Sender == None:
            printRed(f"{sigName} 没有发送者")
            continue
        if Sender not in local_machine_Sender: 
            reConfigDict(jsUp,dbcSigName,sigName)       
            # if down_topic in jsDown :del jsDown[down_topic]   
        if Sender in local_machine_Sender: 
            reConfigDict(jsDown,down_topic,dbcSigName)
            # if dbcSigName in jsUp: del jsUp[dbcSigName]


    writeJs(down_config,jsDown)
    writeJs(up_config,jsUp)

def getCellValue(src, row, col):
    return src.cell_value(row, col)

def addConfigByXls(xlsFileName):
    book = xlrd.open_workbook(xlsFileName)
    assert isinstance(book, Book)
    sheel = book.sheet_by_name(Sig_Matrix)
    sigs = []
    for i in range(sheel.nrows):
        try:
            sigName = getCellValue(sheel,i,XlsCharToInt('C'))
            msgid =  str( getCellValue(sheel,i,XlsCharToInt('E'))).split(".")[0].replace('0x', '')
            Sender= getCellValue(sheel,i,XlsCharToInt('B'))
            msgId_sigName = Sender+"_"+msgid+'/'+sigName
            sigs.append(msgId_sigName)
        except:
            printRed(f'获取 {sigName} 信息失败')
            pass
    addConfigSig(sigs)

    
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        检查配置文件是否正确
        从配置文件生成java代码
        从java生成配置文件
        ''')
    parse.add_argument('-j', '--ToJave', help='生成json代码', nargs='?', type=str)
    parse.add_argument('-c', '--ToConfig', help='从java代码生成配置文件',type=str)
    parse.add_argument('-a', '--addSig', help='把信号添加带配置文件中',nargs='+',type=str)
    parse.add_argument('-s', '--xls', help='把表格中所有的信号都添加配置文件中,-s为表格的路径',type=str)
    arg = parse.parse_args()
    configPath = pyFileDir+"config.json"
    if '-j' in sys.argv:
        ToJaveCode(arg.ToJave,configPath)
    elif '-c' in sys.argv:
        ToConfigJson(arg.ToConfig,configPath)
    elif '-a' in sys.argv:
        addConfigSig(arg.addSig,configPath)
    elif '-s' in sys.argv:
        addConfigByXls(arg.xls)
    else:
        CheckSigName(configPath)
    
