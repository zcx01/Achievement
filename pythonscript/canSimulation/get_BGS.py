#!/bin/python
import sys
from commonfun import *
from jira import JIRA
from signalxls import *
        
jira =JIRA("http://jira.i-tetris.com/",basic_auth=("chengxiong.zhu","@Huan2870244352"))
useCases = []
MoniKey="python3"

def getBugInfo(bugId):
    # useCases.clear()
    case=useCase()
    # project =jira.project(str(bugId).split("-")[0])  #获取projet为BGS的信息
    issue=jira.issue(bugId)
    description=str(issue.fields.description).splitlines()
    del description[0]
    if MoniKey in str(issue.fields.description):
        for desc in description:
            if MoniKey in desc:
                print(desc)
                case.py=desc
    else:
        description='\n'.join(description)
        case = ReMatchStr(description)
    useCases.append(case)
        
    index = 1
    for comment in issue.fields.comment.comments:
        if MoniKey in comment.body:
            print(comment.body)
            case.py=comment.body
        else:
            case = ReMatchStr(comment.body)
        case.index = index
        useCases.append(case)
        index+=1
    if len(useCases) == 0:
        return
    pyperclip.copy(useCases[0].Out())
    displayInfo(useCases)

if __name__ == "__main__":
    getBugInfo(sys.argv[1])
    # getBugInfo("BGS-3771")
