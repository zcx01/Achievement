#!/bin/python
import os
import sys
import argparse
from commonfun import *
import requests

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
from commonfun import *
from jira import JIRA
# from AnalyzeCan.projectInI import *
  
jira =JIRA("http://jira.i-tetris.com/",basic_auth=("chengxiong.zhu","@Huan2870244352"))
useCases=[]

LOGDIR="C:/Users/chengxiong.zhu/Downloads/log分析/"+datetime.datetime.now().strftime("%Y-%m-%d")+"/"

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

def displayIssue(issue,arg):
    dirlog=LOGDIR+issue.key
    print(issue.permalink())
    if arg & 1:
        title='标题'
        print(f'{title:<10}{issue.fields.summary}')
        try:
            createLogDir(dirlog)
        except:
            pass
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

def help():
    print('-h 获取帮助')
    print('bugId 发送CAN报文')
    print("-d bugId 查看问题详细描述")
    print("-c bugId 查看问题备注")
    print("-a bugId 查看问题所有信息")
    print('-e: 退出')


def getBugInfo(text):
    #fields = 'comment'不配置就没有备注,默认不存在
    issues = jira.search_issues(text,fields = ['comment','summary','description','attachment'])
    for issue in issues:
        displayIssue(issue,15)    

    # issue=jira.issue(text)
    # displayIssue(issue,15)

def getNoResolvedInfo():
    #fields = 'comment'不配置就没有备注,默认不存在
    getBugInfo('issuetype = Bug AND resolution = Unresolved AND assignee in (currentUser()) ORDER BY updated ASC')
    # getBugInfo('BGS-52779')

#测试 getBugInfo 函数


if __name__ == "__main__":

    # parser = argparse.ArgumentParser(
    # description='''
    # 获取Jira上的信息，
    # 用来发送信号
    # ''')
    
    # #这个是要解析 -f 后面的参数
    # parser.add_argument('-t', '--toal',help="今天解决的Jira",type=str,default='',nargs='?')
    # arg=parser.parse_args()


    while 1:
        getNoResolvedInfo()
        time.sleep(1000)
    # getBugInfo("BGS-3771")
    # sendBugCan("BGS-4547")
