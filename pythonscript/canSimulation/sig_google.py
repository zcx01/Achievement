#!/usr/bin/python
from __future__ import print_function

'''
参考网站
https://developers.google.com/sheets/api/quickstart/python?hl=zh-cn
'''
import os.path
import argparse
import sys
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
sys.path.append(os.path.dirname(os.path.abspath(__file__))+"./")
from checksig import *
from xlsdbcCommand import *
from analyze_dbc.projectInI import *
# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

# The ID and range of a sample spreadsheet.
# SAMPLE_SPREADSHEET_ID = '1paIMJgPVcFIohJDAsrnRmFchWjxrkmeNhMOTGEm2F0Y'
SAMPLE_RANGE_NAME = 'A:Z'

def getShellValueDrive(sample_spreadsheet_id):
    """Shows basic usage of the Sheets API.
    Prints values from a sample spreadsheet.
    """
    creds = None
    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    service = build('sheets', 'v4', credentials=creds)

    # Call the Sheets API
    sheet = service.spreadsheets()
    result = sheet.values().get(spreadsheetId=sample_spreadsheet_id,
                                range=SAMPLE_RANGE_NAME).execute()
    values = result.get('values', [])
    return values

def GoValue(values, row, col):
    return values[row][XlsCharToInt(col)]

def addConfigs(ids):
    sigs = []
    for id in ids:
        values = getShellValueDrive(id)
        for i in range(len(values)):
            try:
                sigName = GoValue(values,i,'C')
                msgid =  GoValue(values,i,'E')
                Sender= GoValue(values,i,'B')
                msgId_sigName = Sender+"_"+msgid+'/'+sigName
                sigs.append(msgId_sigName)
            except:
                pass
    addConfigSig(sigs)

def addConfigByTopicCan(startRow,endRow,isGetThreeSig):
    if GOOGLESIGTOPICID == '':
        print('表格id是空的')
        return
    values = getShellValueDrive(GOOGLESIGTOPICID)
    rowRangs = []
    if endRow == -1 : endRow = len(values)
    elif endRow == 0 : endRow = startRow+1
    if startRow > 0:
        for i in range(startRow,endRow):
            rowRangs.append(i)
    
    if len(rowRangs) != 1:
         initWarnFile()

    isAll = endRow == len(values) and startRow == 5
    if isGetThreeSig:
        getThreeSig(values,len(values),GoValue,rowRangs)
    else:
        whitelistdbcSigNames = addConfigTopicCan(values,len(values),GoValue,rowRangs,isAll)
        printGreen('写入白名单中...')
        if whitelistdbcSigNames != None and len(whitelistdbcSigNames) != 0:
            addCan_parse_whitelist(whitelistdbcSigNames)
        printGreen('执行完成')

if __name__ == '__main__':
    parse = argparse.ArgumentParser(description='生成配置文件的脚本')
    parse.add_argument('-s','--startRow',help='开始的行号,0表示所有',type=int,default=0)
    parse.add_argument('-e','--endRow',help='结束的行号,-1表到示最后，0表示和startRow相等',type=int,default=-1)
    parse.add_argument('-i', '--ids',help='id', nargs='+')
    parse.add_argument('-t', '--three',help='是否是获取三帧', nargs='?')
    arg = parse.parse_args()

    if '-i' in sys.argv:
        addConfigs(arg.ids)

    startRow = arg.startRow-1
    if startRow < 0 : startRow = 5
    addConfigByTopicCan(startRow,arg.endRow,'-t' in sys.argv)