from __future__ import print_function

import os.path
import argparse
import sys
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
sys.path.append(os.path.dirname(os.path.abspath(__file__))+"/../")
from topic_def.xslToNewSig import *

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

# The ID and range of a sample spreadsheet.
SAMPLE_SPREADSHEET_ID = '1paIMJgPVcFIohJDAsrnRmFchWjxrkmeNhMOTGEm2F0Y'
SAMPLE_RANGE_NAME = 'A:I'


def getShellValueDrive():
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
    result = sheet.values().get(spreadsheetId=SAMPLE_SPREADSHEET_ID,
                                range=SAMPLE_RANGE_NAME).execute()
    values = result.get('values', [])
    return values


def generateByRemote(startRow, endRow, down, up):
    values = getShellValueDrive()
    generate(values, startRow, endRow, down, up, GoValue, len(values))


def findTopicAndDefine(rows):
    values = getShellValueDrive()
    getTopicAndDefine(values,GoValue,rows)


def GoValue(values, row, col):
    return values[row][col]

if __name__ == '__main__':
    parse = argparse.ArgumentParser(description='这个是通过topic表格生成生成newSig表格')
    parse.add_argument('-d', '--down', help='下行信号的类型', default="vehctrl")
    parse.add_argument('-u', '--up', help='上行信号的类型', default="vehctrl_status")
    parse.add_argument('-s', '--startRow', help='开始的行号', type=int)
    parse.add_argument('-e', '--endRow', help='结束的行号', type=int)
    parse.add_argument('-f', '--findRows',
                       help='生成topic和define的行号列表', type=int, nargs='+')
    arg = parse.parse_args()
    if '-f' in sys.argv:
        findTopicAndDefine(arg.findRows)
    else:
        generateByRemote(arg.startRow, arg.endRow, arg.down, arg.up)
