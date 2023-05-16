# coding:utf-8
#!/bin/python


# basic_auth=("chengxiong.zhu","@Huan2870244352")
# if __name__ == "__main__":
#     # parse = argparse.ArgumentParser(description='python的脚本模板')
#     # parse.add_argument('-s','--startRow',help='开始的行号',type=int,default=0)
#     # arg = parse.parse_args()
#     url="http://jira.i-tetris.com/secure/attachment/312417/%E6%97%A5%E5%BF%97.rar"

#     response = requests.get(url,auth=basic_auth)
    
#     with open('C:\\Users\\chengxiong.zhu\\Downloads\\log分析\\test.rar', 'wb') as f:
#         f.write(response.content)
    

'''# 查询issue信息，传入参数issueId
issue = jiraClinet.issue('xxx-679')

# 问题的 key
issue.key

# 问题的 id
issue.id

# 问题的配置域
issue.fields

# 问题标题描述
issue.fields.summary

# 问题详细描述
issue.fields.description

# 问题的类型
issue.fields.issuetype

#问题报告者
issue.fields.reporter '''

import sys
import os
import argparse
import re
import datetime
import shutil
import time
import threading
from PyQt5 import QtGui
from PyQt5.QtWidgets import QApplication, QMainWindow,QTextEdit, QWidget
from jira import JIRA
from PyQt5.QtCore import Qt, QThread, pyqtSignal,QObject
from PyQt5.QtGui import QCloseEvent,QKeyEvent
from commonfun import *
import platform

os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""
  
jira =JIRA("http://jira.i-tetris.com/",basic_auth=("chengxiong.zhu","@Huan2870244352"))
useCases=[]

ROOTLOGDIR="C:/Users/chengxiong.zhu/Downloads/log分析/"
LOGDIR=""
textEdit=None
def appendUseCases(case):
    if case.isVaild():
        case.index = len(useCases)
        useCases.append(case)

def getLogPath(bugId):
    texts=[]
    issue=jira.issue(bugId)
    texts.append(issue.fields.summary)
    texts.append(str(issue.fields.description))
    for comment in issue.fields.comment.comments:
        texts.append(comment.body)
    for text in texts:
        if "smb:" in text:
            smb = re.findall(r"\bsmb:\S+\b",text,re.A)[0]
            smb=smb.replace("smb:","")
            smb=smb.replace('/','\\')
            print(smb)

def smbToWindow(text,dirlog):
    # if "smb:" in text:
    #     smb = re.findall(r"\bsmb:\S+\b",text,re.A)[0]
    #     smb=smb.replace("smb:","")
    #     smb=smb.replace('/','\\')
    #     return smb
    ips = re.findall(r'\\\\10.+\S+\b',text,re.A)
    for yip in ips:
        print("下载 "+yip)
        os.system(f'cp -rf {yip} {dirlog}')
        # try:
        #     shutil.copy2(yip,dirlog)
        # except:
        #     printYellow("下载错误"+yip)
    return ""

def createLogDir(dirlog):
    if os.path.exists(dirlog):
        shutil.rmtree(dirlog)
    os.makedirs(dirlog)

def isExists(issue):
    oriDir = LOGDIR+" "+issue.key+issue.fields.summary
    logDir = LOGDIR+issue.key
    return os.path.exists(logDir) or  os.path.exists(oriDir)
        
def displayIssue(issue,arg,signal):
    dirlog=LOGDIR+issue.key
    if arg & 1:
        title='标题'
        # print(f'{title:<10}{issue.fields.summary}')
        try:
            if not isExists(issue):
                createLogDir(dirlog)
            else:
                return
        except:
            pass
    printYellow(issue.permalink())
    writeFile(issue.key)
    dirlogTemp = dirlog
    if not signal == None:
        signal.emit(issue.permalink())
        if platform.system == "Windows":
            dirlogTemp = dirlogTemp.replace('/','\\')
        signal.emit(dirlogTemp)
    printGreen("下载目录为: "+dirlogTemp)
    if arg & 2:
        title='详细'
        print(f'{title:<10}{issue.fields.description}')
        smbToWindow(str(issue.fields.description),dirlog)
    if arg & 4:
        title='备注'
        print(f'---------- {title:} ------------')
        for comment in issue.fields.comment.comments:
            print(f'{title:<10}{comment.body}')
            smbToWindow(str(comment.body),dirlog)
    if arg & 8:
        title='附件'
        for attachment in issue.fields.attachment:
            print("下载 "+attachment.filename)
            path = dirlog+"/"+attachment.filename
            with open(path,'wb') as f:
                f.write(attachment.get())

    try:
        oriDir =  LOGDIR+" "+issue.key+issue.fields.summary
        if os.path.exists(oriDir):
            shutil.rmtree(oriDir)
        os.rename(dirlog,oriDir)
    except:
        pass
    if not signal == None:
        signal.emit("下载完成")
        printGreen("下载完成")

def help():
    print('-h 获取帮助')
    print('bugId 发送CAN报文')
    print("-d bugId 查看问题详细描述")
    print("-c bugId 查看问题备注")
    print("-a bugId 查看问题所有信息")
    print('-e: 退出')


def getBugInfo(text,isSearch,signal):
    if isSearch:
        #fields = 'comment'不配置就没有备注,默认不存在
        issues = jira.search_issues(text,fields = ['comment','summary','description','attachment'])
        for issue in issues:
            textEdit.append("\n")
            displayIssue(issue,15,signal)    
    else:
        issue=jira.issue(text,fields = ['comment','summary','description','attachment'])
        displayIssue(issue,15,signal)

def getNoResolvedInfo(signal):
    #fields = 'comment'不配置就没有备注,默认不存在
    while 1:
        global LOGDIR
        LOGDIR=ROOTLOGDIR+datetime.datetime.now().strftime("%Y-%m-%d")+"/"
        if not os.path.isdir(LOGDIR):
            writeFile(datetime.datetime.now().strftime("%Y-%m-%d")+'\n')
        getBugInfo('issuetype = Bug AND resolution = Unresolved AND assignee in (currentUser()) ORDER BY updated ASC',True,signal)
        time.sleep(10)
    # getBugInfo('BGS-52779')

def writeFile(text):
    file_path = ROOTLOGDIR+"统计.txt"
    with open(file_path, 'a') as f:
        f.write(text)

#测试 getBugInfo 函数
class UpdateThread(QObject):
    update_data = pyqtSignal(str)
    def start(self) -> None:
        my_thread = threading.Thread(target=getNoResolvedInfo,args=(self.update_data,))
        my_thread.setDaemon(True)
        my_thread.start()


class MainWindow(QTextEdit):
    def initUI(self):
        self.subTheard = UpdateThread()
        self.subTheard.update_data.connect(self.updataText)
        self.subTheard.start()

    def updataText(self,text):
        if self.isHidden():
            self.show()
        self.append(text)

    def closeEvent(self, a0: QCloseEvent) -> None:
        a0.ignore()
        self.hide()
    
    def keyPressEvent(self, e: QKeyEvent) -> None:
        modifier = e.modifiers()
        if modifier & Qt.AltModifier:
            if e.key() == Qt.Key_Return:
                selected_text = str(self.textCursor().selectedText())
                os.system(f"explorer {selected_text}")
        if modifier & Qt.ControlModifier:
            if e.key == Qt.Key_C:
                sys.exit()
        return super().keyPressEvent(e)

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
    description='''
    获取Jira上的log
    ''')

    # #这个是要解析 -f 后面的参数
    parser.add_argument('-i', '--jiraId',help="今天解决的Jira",type=str,default='',nargs='?')
    arg=parser.parse_args()

    if '-i' in sys.argv:
        LOGDIR=ROOTLOGDIR+datetime.datetime.now().strftime("%Y-%m-%d")+"/"
        getBugInfo(arg.jiraId,False,None)
    else:
        try:
            app = QApplication(sys.argv)
            textEdit = MainWindow()
            textEdit.show()
            textEdit.initUI()
            sys.exit(app.exec())
        except KeyboardInterrupt:
            sys.exit()
        # getBugInfo("BGS-3771")
        # sendBugCan("BGS-4547")
