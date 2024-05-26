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

import argparse
from commonfun import *
from jira import JIRA
# from analyze_dbc.projectInI import *
         
jira =JIRA("http://jira.i-tetris.com/",basic_auth=("chengxiong.zhu","@Huan2870244352"))
useCases=[]



def getBugInfo(issue_key,target_key):

    relation_type = "related to" # 关联类型为“Related To”

    commmet = f"同{target_key}"
    #fields = 'comment'不配置就没有备注,默认不存在
    source_issue = jira.issue(issue_key)

    target_issue = jira.issue(target_key)
    jira.add_comment(source_issue, commmet)

    target_issue = jira.issue(target_key)
    
    # 添加关联
    # jira.create_issue_link('', source_issue.id, target_issue.id, relation_type)

    # 设置解决结果为"已修复"
    # Duplicate 为重复提交
    resolution = {'name': 'Fixed'}

    # source_issue.update(fields={'resolution': {'name': 'Fixed'}})


    # 设置新的resolution值
    new_resolution = "Fixed"
    source_issue.fields.resolution = new_resolution
    
    # 更新issue
    jira.edit_issue(source_issue, fields={'resolution': {'name': new_resolution}})

    # source_issue.update(fields={"resolution": {"id": f"{target_issue.id}"}})
    # jira.transition_issue(source_issue, transition={'resolution': resolution})
    #jira.transition_issue(source_issue, '5', assignee=("chengxiong.zhu","@Huan2870244352"), resolution={'id': f'{target_issue}'})

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
    description='''
    获取Jira上的信息，
    用来发送信号
    ''')
    
    # #这个是要解析 -f 后面的参数
    parser.add_argument('-s', '--src_key',help="源bug",type=str,default=[],nargs='+')
    parser.add_argument('-t', '--target_key',help="连接的bug",type=str,default='',nargs='?')
    arg=parser.parse_args()

    for srcKey in arg.src_key:
        getBugInfo(srcKey,arg.target_key)
