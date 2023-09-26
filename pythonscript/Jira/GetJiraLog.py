# coding:utf-8
#!/bin/python
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
import socket
from jira import JIRA
import platform
from basic_auth import *

jira =JIRA("http://jira.i-tetris.com/",basic_auth=basic_auth)
LOGDIR=""
TIMEFORMAT="%Y-%m-%d"
TIMEFORMATDATA="%Y-%m"
PORTMSG = 12345
HOSTMSG = 'LOCALHOST'
CODEMSG = 'utf-8'

def printRed(infoStr):
    print('\033[31m'+infoStr+'\033[0m')

def printGreen(infoStr):
    print('\033[32m'+infoStr+'\033[0m')
    
def printYellow(infoStr):
    print('\033[33m'+infoStr+'\033[0m')

def wirteFileDicts(file,data,replace=True):
    cr = open(file, "w")
    if replace:
        for d in data:
            d = d.replace('\xa0', ' ')
            cr.write(str(d).replace("\'","\"")+"\n")
    else:
        cr.writelines('\n'.join(data))
    cr.close()

def send_msg(msg):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.sendto(msg.encode(CODEMSG), (HOSTMSG, PORTMSG))

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

def copySmb(yip,dirlog):
    assert isinstance(yip,str)
    yiplastDir = yip.split("\\")
    yiplastDir = dirlog+"/"+yiplastDir[len(yiplastDir)-1]
    try:
        shutil.rmtree(yiplastDir)
    except:
        pass
    try:
        shutil.copytree(yip,yiplastDir)
    except Exception as e:
        print(e)
        print('进入文件下载模式')
        try:
            print(yiplastDir)
            shutil.copyfile(yip,yiplastDir)
        except Exception as e:
            print(e)
            printRed(f"下载 {yip} 失败")
        pass


def smbToWindow(text,dirlog):
    if "smb:" in text:
        smb = re.findall(r"\bsmb:\S+\b",text,re.A)[0]
        smbNew=smb.replace("smb:","")
        smbNew=smbNew.replace('/','\\')
        text = text.replace(smb,smbNew)
    #     return smb
    ips = re.findall(r'\\\\10.+\S+',text,re.A)
    for yip in ips:
        print("下载 "+yip)
        copySmb(yip,dirlog)
        # os.system(fr'cp -rf {yip} {dirlog}')
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
    oriDir = getOriDir(issue)
    logDir = LOGDIR+issue.key
    return os.path.exists(logDir) or  os.path.exists(oriDir)

def getOriDir(issue):
    summary = re.sub(r'[^\w\-./]', '', issue.fields.summary)
    oriDir = LOGDIR+" "+issue.key+" "+ summary
    return oriDir

def openDir(dirPath):
    if platform.system() == "Windows":
        dirPath = dirPath.replace('/','\\')
    return dirPath
    
def displayIssue(issue,arg,signal,isSearch):
    # dirlog=LOGDIR+issue.key
    dirlog =getOriDir(issue)
    if arg & 1:
        title='标题'
        # print(f'{title:<10}{issue.fields.summary}')
        try:
            if not isSearch:
                createLogDir(dirlog)
                pass
            elif not isExists(issue):
                createLogDir(dirlog)
            else:
                return
        except:
            pass
    printYellow(issue.permalink())
    dirlogTemp = dirlog
    if not signal == None:
        signal(issue.permalink())
        dirlogTemp = openDir(dirlogTemp)
        signal(dirlogTemp)
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
            # if os.path.isExists(path):
            with open(path,'wb') as f:
                f.write(attachment.get())

    if not signal == None:
        signal("下载完成")
        printGreen("下载完成")
        signal("\n")

def getBugInfo(text,isSearch,signal):
    if isSearch:
        #fields = 'comment'不配置就没有备注,默认不存在
        issues = jira.search_issues(text,fields = ['comment','summary','description','attachment'])
        for issue in issues:
            displayIssue(issue,15,signal,isSearch)    
    else:
        issue=jira.issue(text,fields = ['comment','summary','description','attachment'])
        displayIssue(issue,15,signal,isSearch)

def getNoResolvedInfo(signal):
    #fields = 'comment'不配置就没有备注,默认不存在
    isReporting = False
    while 1:
        global LOGDIR
        LOGDIR=ROOTLOGDIR+datetime.datetime.now().strftime(TIMEFORMAT)+"/"
        getBugInfo('issuetype = Bug AND resolution = Unresolved AND assignee in (currentUser()) ORDER BY updated ASC',True,signal)
        time.sleep(10)
        today = datetime.datetime.now()
        if today.hour == 18:
            dateDirs,startDate,endDate,currentDate = getCurrentWeekdDir(None)
            if endDate == today.strftime(TIMEFORMAT) and not isReporting:
                Reporting()
                isReporting = True
    # getBugInfo('BGS-52779')

def get_last_week_thursday_dates(reporData=None):
    if reporData == None or len(reporData) == 0:
        today = datetime.datetime.now()
    else:
        try:
            today= datetime.datetime.strptime(reporData,TIMEFORMAT)
            print(today)
        except:
            printRed(f"输入的日期格式不正确{reporData}")
            pass
    days_to_thursday = (3 - today.weekday()) % 7
    start_of_last_week = today - datetime.timedelta(days=6-days_to_thursday)
    dates = []
    for i in range(7):
        date = start_of_last_week + datetime.timedelta(days=i)
        dates.append(date.strftime(TIMEFORMAT))
    return dates

def getCurrentWeekdDir(reporData=None):
    dates = get_last_week_thursday_dates(reporData)
    dateDirs = []
    for date in dates:
        dateDir = ROOTLOGDIR+date
        if os.path.isdir(dateDir):
            dateDirs.append(dateDir)
    return dateDirs,dates[0],dates[len(dates)-1],dates[3]

def getJiraSolveBugContent(jiraKeys,JiraContent):
    issues=[]
    noSolveBug=[]
    noSolveBugIssues = jira.search_issues("assignee = currentUser() AND resolution = Unresolved order by updated DESC",fields = ['assignee','summary','status'])
    for noSolveBugIssue in noSolveBugIssues:
        noSolveBug.append(noSolveBugIssue.key)
    for jiraKey in jiraKeys:
        try:
            issue = jira.issue(jiraKey,fields = ['assignee','summary','status'])
            if  issue.key not in noSolveBug:
                issues.append(issue)
        except:
            printYellow(f"没有{jiraKey}")
    getIssuesContet(issues,JiraContent)

def getIssuesContet(issues,JiraContent):
    index = 1
    for issue in issues:
        JiraContent.append(f"{index}、{issue.key} {issue.fields.summary}")
        index+=1
   
def Reporting(reporData=None):
    dateDirs,startDate,endDate,currentDate = getCurrentWeekdDir(reporData)
    file_path = ROOTLOGDIR+"Report/"
    if not os.path.isdir(file_path):
        os.makedirs(file_path)
    file_path += endDate+".txt"
    reportContent=[]
    jiraBugKeys=[]
    for dateDir in dateDirs:
        for (dirpath,dirnames,filenames) in os.walk(dateDir):
            if dirpath == dateDir:
                for dirname in dirnames:
                    keys = re.findall(r"-?\b[a-zA-Z_0x0-9.]+\b",dirname,re.A)
                    if len(keys) > 1:
                        jiraBugKey = keys[0]+keys[1]
                        if jiraBugKey not in jiraBugKeys:
                            jiraBugKeys.append(jiraBugKey)
    
    reportContent.append("处理的Bug")
    getJiraSolveBugContent(jiraBugKeys,reportContent)
    reportContent.append("")

    reportContent.append("处理的Task")
    taskSearch = f'issuetype in (Task, Story) AND resolution in (Done, \"Won\'t Do\") AND resolved >= -1w AND assignee in (currentUser()) order by updated DESC' 
    # taskSearch = f'issuetype in (Task, Story) AND resolution in (Done, \"Won\'t Do\") AND resolved >= {startDate} AND resolved <= {endDate} AND assignee in (currentUser()) order by updated DESC'  
    print(taskSearch)
    issues = jira.search_issues(taskSearch,fields = ['assignee','summary','status'])
    getIssuesContet(issues,reportContent)

    wirteFileDicts(file_path,reportContent)
    printGreen(f"{file_path} 生成完成")
    os.system(f'explorer {openDir(file_path)}')

def getLoopJiraIdLog():
    while(True):
        cmd=input()
        if len(cmd) == 0:
            continue
        cmds = re.findall(r"-?\b[a-zA-Z-0x0-9.]+\b",cmd,re.A)
        if '-r' in cmds:
            if len(cmds) > 1 :
                Reporting(cmds[1])
            else:
                Reporting()
        else:
            getJiraIdLog(cmds)

def getJiraIdLog(jiraIds):
    global LOGDIR
    LOGDIR=ROOTLOGDIR+datetime.datetime.now().strftime(TIMEFORMAT)+"/"
    for jiraId in jiraIds:
        getBugInfo(jiraId,False,send_msg)
    
if __name__ == "__main__":

    parser = argparse.ArgumentParser(
    description='''
    获取Jira上的log
    ''')

    # #这个是要解析 -f 后面的参数
    parser.add_argument('-i', '--jiraIds',help="JiraId",type=str,default=[],nargs='+')
    parser.add_argument('-r', '--reporData',help="生成报告的日期，没有默认是今天,格式是Y-m-d",type=str,default='',nargs='?')
    arg=parser.parse_args()

    if not os.path.isdir(ROOTLOGDIR):
        os.makedirs(ROOTLOGDIR)
    if '-i' in sys.argv:
        getJiraIdLog(arg.jiraIds)
    elif '-r' in sys.argv:
        Reporting(arg.reporData)
    else:
        my_thread = threading.Thread(target=getLoopJiraIdLog,args=())
        my_thread.setDaemon(True)
        my_thread.start()
        getNoResolvedInfo(send_msg)