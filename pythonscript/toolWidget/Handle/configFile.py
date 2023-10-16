from commonfun import *
from Ui_toolMainWindow import *

jsContent = None
UiKey= {}
def getJsValue(key):
    if jsContent == None:
        return ""
    return jsContent.get(key,"")

def setJsaValue(key,value):
    jsContent[key] = value

def initUI(ui,configPath):
    assert isinstance(ui,Ui_MainWindow)
    global jsContent
    global UiKey
    jsContent = getJScontent(configPath)
    UiKey[ui.ipLE] = 'ip'
    UiKey[ui.userLE] = 'user'
    UiKey[ui.pwLE] = 'pw'
    UiKey[ui.icTextLE] = 'icText'
    UiKey[ui.trXlsPathS] = 'trXlsPathS'
    UiKey[ui.trXlsPath] = 'trXlsPath'
    UiKey[ui.trChangeXlsPath] = 'trChangeXlsPath'
    for le,keyValue in UiKey.items():
        le.setText(getJsValue(keyValue))

def saveUI(ui,configPath):
    assert isinstance(ui,Ui_MainWindow)
    for le,keyValue in UiKey.items():
        setJsaValue(keyValue,le.text())
    writeJs(configPath,jsContent)