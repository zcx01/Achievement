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

from matplotlib.pyplot import text
from commonfun import *
from jira import JIRA
from signalxls import *
         
jira =JIRA("http://jira.i-tetris.com/",basic_auth=("chengxiong.zhu","@Huan2870244352"))

useCases=[]

def getBugId(bugId):
    bugId = str(bugId)
    if '-' not in bugId:
        if(PROJECT_ID == 'c385ev'):
            bugId = 'BGS-'+bugId
    return bugId

def appendUseCases(case):
    if case.isVaild():
        case.index = len(useCases)
        useCases.append(case)

def sendBugCan(bugId):
    useCases.clear()
    # project =jira.project(str(bugId).split("-")[0])  #获取projet为BGS的信息
    bugId=getBugId(bugId)
    issue=jira.issue(bugId)

    summaryCase = ReMatchStr(issue.fields.summary)

    description=str(issue.fields.description).splitlines()
    del description[0]
    description='\n'.join(description)
    descriptionCase = ReMatchStr(description)

    if not descriptionCase.isSame(summaryCase):
        appendUseCases(summaryCase)

    appendUseCases(descriptionCase)
        
    for comment in issue.fields.comment.comments:
        print(comment.body)
        case = ReMatchStr(comment.body)
        # if descriptionCase.isSame(case):
        #     continue
        appendUseCases(case)
    getLogPath(bugId)
    if len(useCases) == 0:
        printYellow("没有信号的存在")
        return
    pyperclipCopy(useCases[0].Out())
    displayInfo(useCases)


def getLogPath(bugId):
    texts=[]
    bugId=getBugId(bugId)
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

def displayIssue(issue,arg):
    print(f'{issue.key}')
    if arg & 1:
        title='标题'
        print(f'{title:<10}{issue.fields.summary}')
    if arg & 2:
        title='详细'
        print(f'{title:<10}{issue.fields.description}')
    if arg & 4:
        title='备注'
        print(f'---------- {title:} ------------')
        for comment in issue.fields.comment.comments:
            print(comment.body)

def printIssue(issues,in_i_s,arg):
    if len(in_i_s) < 2 :
        print('请输入正确bugid')
        for issue in issues:
            displayIssue(issue,1)
    for issue in issues:
        if issue.key == getBugId(in_i_s[1]):
            displayIssue(issue,arg)

def help():
    print('-h 获取帮助')
    print('bugId 发送CAN报文')
    print("-d bugId 查看问题详细描述")
    print("-c bugId 查看问题备注")
    print("-a bugId 查看问题所有信息")
    print('-e: 退出')

def getBugInfo():
    #fields = 'comment'不配置就没有备注,默认不存在
    issues = jira.search_issues('issuetype = Bug AND resolution = Unresolved AND assignee in (currentUser()) ORDER BY updated ASC'
    ,fields = ['comment','summary','description'])
    for issue in issues:
        displayIssue(issue,1)    
    help()
    while(True):
        in_i = input()
        in_i_s = splitSpace(in_i)
        if '-d' in in_i:
            printIssue(issues,in_i_s,2)
        elif '-c' in in_i:
            printIssue(issues,in_i_s,4)
        elif '-a' in in_i:
            printIssue(issues,in_i_s,7)
        elif '-h' in in_i:
            help()
        elif '-e' in in_i:
                return
        else:
            for issue in issues:
                if getBugId(in_i) == issue.key:
                    sendBugCan(in_i)


if __name__ == "__main__":
    if len(sys.argv) == 2:
        sendBugCan(sys.argv[1])
    else:
        getBugInfo()
    # getBugInfo("BGS-3771")
    # sendBugCan("BGS-4547")
