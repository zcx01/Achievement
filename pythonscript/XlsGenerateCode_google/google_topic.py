from __future__ import print_function

import os.path
import argparse
import sys
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
sys.path.append(os.path.dirname(os.path.abspath(__file__))+"/../")
from topic_def.xlsToNewSig import *

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

# The ID and range of a sample spreadsheet.
SAMPLE_SPREADSHEET_ID = '1paIMJgPVcFIohJDAsrnRmFchWjxrkmeNhMOTGEm2F0Y'
SAMPLE_RANGE_NAME = 'A:Z'


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


def findTopicAndDefine(findArg):
    if type(findArg[0]) == int:
        findTopicAndDefineByRow(findArg)
    else:
        findTopicAndDefineByDesc(findArg[0])

def findTopicAndDefineByRow(rows):
    values = getShellValueDrive()
    getTopicAndDefineByRow(values,GoValue,rows)

def findTopicAndDefineByDesc(desc):
    values = getShellValueDrive()
    getTopicAndDefineByDesc(values,GoValue,desc, len(values))

def GoValue(values, row, col):
    return values[row][col]

if __name__ == '__main__':
    parse = argparse.ArgumentParser(description='???????????????topic??????????????????newSig??????')
    parse.add_argument('-d', '--down', help='?????????????????????', default="vehctrl")
    parse.add_argument('-u', '--up', help='?????????????????????', default="vehctrl_status")
    parse.add_argument('-s','--startRow',help='???????????????',type=int,default=0)
    parse.add_argument('-e','--endRow',help='???????????????',type=int,default=-1)
    parse.add_argument('-f', '--findArg',
                       help='??????topic???define???????????????', nargs='+')
    arg = parse.parse_args()
    if '-f' in sys.argv:
        findTopicAndDefine(arg.findArg)
    else:
        generateByRemote(arg.startRow, arg.endRow, arg.down, arg.up)
