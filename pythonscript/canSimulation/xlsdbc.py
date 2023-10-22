#!/usr/bin/python
import sys          
import argparse
from xlsdbcCommand import *

# conversion(pyFileDir+"config.json","","/home/chengxiongzhu/Achievement/pythonscript/canSimulation/temp.xls")
# conversion(pyFileDir+"config.json",'TboxLocalTiYear')
# sigNameChanged(pyFileDir+"config.json",'/home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/parser/vendor/dbc_files/CAN0_C385EV_V2.1.1_20211009.dbc_old','B_C.txt')
if __name__ == "__main__":
    parse = argparse.ArgumentParser(
        description='''
        这个脚本是用来通过生成dbc,比较CAN矩阵,
        d+r+t:信号名称的改变，并且修改配置的中源码的信号名称,
        d+s:从其他的dbc添加信号,
        d+m:从其他的dbc添加msg
        d+r:从指定的dbc复制枚举到新的dbc中 r是输入比较后的结果
        a+w:把dbc目录下dbc文件中,所有的信号都写入白名单,
        a+s:把指定路径下的CAN矩阵中的指定的信号添加进入dbc
        m+w:把msg加入到白名单当中
        ''')

    parse.add_argument('-c', '--config', help='配置文件路径',
                       default=pyFileDir+"config.json")
    parse.add_argument('-a', '--append', nargs='?', help='新增整个can矩阵表格（如果没有指定路径，使用就是配置文件中）、和+w一起使用则是dbc目录')
    parse.add_argument('-s', '--sigNames', help='新增信号名，是一个列表',
                       default=[], nargs='+', type=str)
    parse.add_argument('-m', '--messages', help='新增messages，是一个列表,如 -m 50',
                       default=[], nargs='*', type=str)
    parse.add_argument('-f', '--fristMatrix',
                       help='比较dbc矩阵,比较的文件,没有指定就使用配置文件中的路径', default="")
    parse.add_argument('-t', '--twoMatrix', help='比较dbc矩阵,被比较的文件,也是旧的一方的文件')
    parse.add_argument('-r', '--resultPath', help='比较dbc矩阵结果路径', default='')
    parse.add_argument('-md', '--modifyMessage',
                       help='替换message信息,有m就会替换，使用CAN矩阵的message替换,例如ICAN_50', default='', type=str, nargs='*')
    parse.add_argument('-d', '--dbcPath', help='比较新旧两个dbc,输入的是被比较的')
    parse.add_argument('-rs', '--rmsigs', help='删除信号,是一个集合,可以用10进制+信号名称,也可以是信号名',nargs='+')
    parse.add_argument('-rm', '--rmmsgs', help='删除message,是一个集合,是一个16进制',nargs='+')
    parse.add_argument('-u', '--isfilterNoUser',
                       help='是否过滤掉没有使用过的信号,用于比较can矩阵', nargs='*')
    parse.add_argument('-w', '--WhitelistPath', help='和-a组合是白名单路径，单独是信号名称',default=[], nargs='+', type=str) 
    parse.add_argument('-ch', '--channal', help='删除message指定通道',nargs='?',default="") 
    parse.add_argument('-sc', '--SigNameChinese', help='获取信号的中文描述',default=[], nargs='+') 
    parse.add_argument('-fc', '--fileChinese', help='获取文件中信号的中文描述',default=[], nargs='+')
    parse.add_argument('-p', '--projectPath', help='项目路径',default='', nargs='?',type=str)
    parse.add_argument('-i', '--addInputMsgConfig', help='添加input_signal_config.json文件,参数是16进制的信号名',default=[], nargs='?',type=str)                   
    arg = parse.parse_args()

    initWarnFile()
    canmatrix = arg.append
    if canmatrix == None:
        jsConfig = getJScontent(arg.config)
        canmatrix = getKeyPath("canmatrix", jsConfig)

    if '-d' in sys.argv and '-r' in sys.argv and '-t' in sys.argv:
        sigNameChanged(arg.config, arg.dbcPath, arg.resultPath, arg.twoMatrix)
    elif '-d' in sys.argv and '-s' in sys.argv:
        conversionByOtherdbc(arg.config, arg.sigNames, arg.dbcPath)
    elif '-d' in sys.argv and '-m' in sys.argv:
        conversionMsgByOtherdbc(arg.config, arg.messages, arg.dbcPath)
    elif '-rs' in sys.argv:
        RemoveSigs(arg.config, arg.rmsigs)
    elif '-rm' in sys.argv:
        RemoveMsgs(arg.config, arg.rmmsgs,arg.channal)
    elif "-m" in sys.argv and '-w' in sys.argv:
        WriteWhitelistPath(arg.messages)
    elif '-m' in sys.argv:
        for msg in arg.messages:
            conversion(arg.config, msg,canmatrix,True)
    elif '-md' in sys.argv:
        modifyMessageInfo(arg.config,arg.modifyMessage,canmatrix)
    elif "-a" in sys.argv and '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config,sigName,canmatrix)
    elif "-a" in sys.argv and '-w' in sys.argv:
        WriteWhitelistPath()
    elif "-a" in sys.argv:
        conversion(arg.config, "", canmatrix)
    elif '-s' in sys.argv:
        for sigName in arg.sigNames:
            conversion(arg.config, sigName)
    elif '-w' in sys.argv:
        addCan_parse_whitelist(arg.WhitelistPath)
    elif '-t' in sys.argv:
        diffCanMatrix(arg.fristMatrix, arg.twoMatrix, arg.config,arg.resultPath, '-u' in sys.argv)
    elif '-d' in sys.argv:
        CopyEnum(arg.config, arg.dbcPath, arg.resultPath)
    elif '-sc'in sys.argv:
        SigNameChinese(arg.config,arg.SigNameChinese,canmatrix)
    elif '-fc'in sys.argv:
        SigNameChinese(arg.config,arg.fileChinese,canmatrix,2)
    elif '-p' in sys.argv:
        handleProjectPath(arg.config,arg.projectPath)
    elif '-i' in sys.argv:
        addInputMsgConfig(arg.config,arg.addInputMsgConfig)