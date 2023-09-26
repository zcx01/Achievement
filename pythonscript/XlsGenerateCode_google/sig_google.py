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

def addConfigByTopicCan(startRow,endRow):
    values = getShellValueDrive("1v4y6DCyc3wnzaY8AdIi51jg4hQnV1Ip8J051WbIGUcc")
    rowRangs = []
    if endRow == -1 : endRow = startRow+1
    print(startRow,endRow)
    for i in range(startRow,endRow):
        rowRangs.append(i)
    addConfigTopicCan(values,len(values),GoValue,rowRangs)

if __name__ == '__main__':
    parse = argparse.ArgumentParser(description='生成配置文件的脚本')
    parse.add_argument('-s','--startRow',help='开始的行号',type=int,default=0)
    parse.add_argument('-e','--endRow',help='结束的行号',type=int,default=-1)
    parse.add_argument('-i', '--ids',help='id', nargs='+')
    parse.add_argument('-tc', '--topicCan', help='通过topic和CAN对应的xls添加配置文件',nargs='?',type=str,default='')
    arg = parse.parse_args()

    if '-i' in sys.argv:
        addConfigs(arg.ids)
    elif '-tc' in sys.argv:
        addConfigByTopicCan(arg.startRow-1,arg.endRow)