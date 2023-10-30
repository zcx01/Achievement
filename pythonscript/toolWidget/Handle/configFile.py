from commonfun import *
from Ui_toolMainWindow import *
from customWidget.lableLineEdit import *
from PyQt5 import *
jsContent = None
UiKey= {}
projectUis= []
configFilePath=''
def getJsValue(key,defaultValue=''):
    if jsContent == None:
        return defaultValue
    return jsContent.get(key,defaultValue)

def setJsaValue(key,value):
    jsContent[key] = value

def getProjectPath(prjectName):
    projectCommonPath = getJsValue('projectCommonPath')
    if projectCommonPath != '':
        assert isinstance(projectCommonPath,str)
        return projectCommonPath.replace('{projectName}',prjectName)
    return ''

def addGeneratedFiles(filePath):
    global jsContent
    if 'generatedFiles' not in jsContent:
        jsContent['generatedFiles'] = []
    jsContent['generatedFiles'].append(filePath)
    saveConfigKey('generatedFiles')

def getGeneratedFiles():
    return getJsValue('generatedFiles',[])

def removeGeneratedFiles():
    generatedFiles = getGeneratedFiles()
    for generatedFile in generatedFiles:
        os.rename(generatedFile)
    jsContent['generatedFiles'] = []
    saveConfigKey('generatedFiles')

def initUI(ui,configPath,projectNameLayout,projectBtnLayout,projectBtnFun,projecGroup):
    assert isinstance(ui,Ui_MainWindow)
    global jsContent
    global UiKey
    global projectUis
    global configFilePath
    configFilePath = configPath
    jsContent = getJScontent(configFilePath)
    UiKey[ui.ipLE] = 'ip'
    UiKey[ui.userLE] = 'user'
    UiKey[ui.pwLE] = 'pw'
    UiKey[ui.icTextLE] = 'icText'
    UiKey[ui.trXlsPathS] = 'trXlsPathS'
    UiKey[ui.trXlsPath] = 'trXlsPath'
    UiKey[ui.downLoadPath] = 'downLoadPath'
    UiKey[ui.projectCommonPath] = 'projectCommonPath'
    UiKey[ui.pushFileLE] = 'pushFile'
    for le,keyValue in UiKey.items():
        le.setText(getJsValue(keyValue))
    projectNames = getJsValue('projectNames')
    currentProjectName = getJsValue('currentProjectName')
    for prjectName,projectPath in projectNames.items():
        leE,projectBtn = createProject(projectNameLayout,projectBtnLayout,projectBtnFun,projecGroup)
        leE.setText(prjectName,projectPath)
        projectBtn.setText(prjectName)
        if prjectName == currentProjectName:
            projectBtn.setChecked(True)

def createProject(projectNameLayout,projectBtnLayout,projectBtnFun,projecGroup):
    leE = lableLineEdit()
    projectNameLayout.insertWidget(projectNameLayout.count()-1,leE)
    projectUis.append(leE)
    projectBtn = QtWidgets.QRadioButton()
    projectBtn.clicked.connect(projectBtnFun)
    projecGroup.addButton(projectBtn)
    projectBtnLayout.insertWidget(projectBtnLayout.count()-1,projectBtn)
    leE.dependentWidget = projectBtn
    return leE,projectBtn

def setCurrentProjectName(projectName):
    setJsaValue('currentProjectName',projectName)

def getCurrentProjectPath():
    projectNames = getJsValue('projectNames')
    currentProjectName = getJsValue('currentProjectName')
    if  projectNames != '':
        if currentProjectName != '':
            return projectNames.get(currentProjectName,'')
        else:
            return projectNames.keys()[0]
    return ''

def getCheckBtn():
    for projectUi in projectUis:
        if projectUi.dependentWidget.isChecked():
            return projectUi.dependentWidget
    return None

def removePrject(projectNameLayout,projectBtnLayout,btn):
    index = 0
    for projectUi in projectUis:
        assert isinstance(projectUi,lableLineEdit)
        assert isinstance(projectNameLayout,QtWidgets.QBoxLayout)
        if projectUi.dependentWidget == btn:
            projectBtnLayout.removeWidget(btn)
            projectNameLayout.removeWidget(projectUi)
            del projectUis[index]
            return
        index = index + 1

def saveUI(ui,configPath):
    if configPath == '':
        configPath = configFilePath
    assert isinstance(ui,Ui_MainWindow)
    for le,keyValue in UiKey.items():
        setJsaValue(keyValue,le.text())
    projectNames = {}
    for prjectUI in projectUis:
        labeText,lineEeditText = prjectUI.getText()
        projectNames[labeText] = lineEeditText
    setJsaValue('projectNames',projectNames)
    writeJs(configPath,jsContent)

def saveConfigKey(key):
    tmepJsContent = getJScontent(configFilePath)
    tmepJsContent[key] = jsContent[key]
    writeJs(configFilePath,jsContent)