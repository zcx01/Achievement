from commonfun import *
from Ui_toolMainWindow import *
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

def removeGeneratedFiles(disPlayMsg):
    generatedFiles = getGeneratedFiles()
    for generatedFile in generatedFiles:
        try:
            os.remove(generatedFile)
            disPlayMsg(f"删除                                                                                                                                                                                                                                                                                                                                                                                                                                          {generatedFile}")
        except:
            pass
    jsContent['generatedFiles'] = []
    saveConfigKey('generatedFiles')
    disPlayMsg(f"删除完成")

def initUI(ui,configPath,projectBtnLayout,projectBtnFun,projecGroup):
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
    UiKey[ui.trXlsPathW] = 'trXlsPathW'
    UiKey[ui.trXlsPath] = 'trXlsPath'
    UiKey[ui.downLoadPath] = 'downLoadPath'
    UiKey[ui.projectCommonPath] = 'projectCommonPath'
    UiKey[ui.pushFileLE] = 'pushFile'
    for le,keyValue in UiKey.items():
        le.setText(getJsValue(keyValue))
    projectNames = getJsValue('projectNames')
    currentProjectName = getJsValue('currentProjectName')
    tsPaths = getJsValue('tsPaths',{})
    warnTextPaths = getJsValue('warnTextPaths',{})
    for prjectName,projectPath in projectNames.items():
        projectBtn = createProject(projectBtnLayout,projectBtnFun,projecGroup)
        setBtnProject(projectBtn,prjectName,projectPath,tsPaths.get(prjectName,""),warnTextPaths.get(prjectName,""))
        if prjectName == currentProjectName:
            projectBtn.setChecked(True)

def createProject(projectBtnLayout,projectBtnFun,projecGroup):
    global projectUis
    projectBtn = QtWidgets.QRadioButton()
    projectBtn.clicked.connect(projectBtnFun)
    projecGroup.addButton(projectBtn)
    projectBtnLayout.insertWidget(projectBtnLayout.count()-1,projectBtn)
    projectUis.append(projectBtn)
    return projectBtn

def setBtnProject(projectBtn,prjectName,projectPath,ts,warnText):
    assert isinstance(projectBtn,QtWidgets.QRadioButton)
    projectBtn.setText(prjectName)
    projectBtn.setProperty(prjectName,projectPath)
    projectBtn.setProperty("ts",ts)
    projectBtn.setProperty("warnText",warnText)

def getProjectInfo(prjectName):
    for projectBtn in projectUis:
        assert isinstance(projectBtn,QtWidgets.QRadioButton)
        if projectBtn.text() == prjectName:
            return getBtnInfo(projectBtn)
    return None,"",""

def getBtnInfo(projectBtn):
    return projectBtn.property(projectBtn.text()),projectBtn.property("ts"),projectBtn.property("warnText")

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

def getCheckBtn(disPlayMsg):
    for projectUi in projectUis:
        if projectUi.isChecked():
            return projectUi
    disPlayMsg("请选择项目")
    return None

def removePrject(projectBtnLayout,btn):
    index = 0
    for projectUi in projectUis:
        if projectUi == btn:
            projectBtnLayout.removeWidget(btn)
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
    tsPaths = {}
    warnTextPaths ={}
    for prjectUI in projectUis:
        labeText = prjectUI.text()
        projectPath,ts,warnText = getBtnInfo(prjectUI)
        projectNames[labeText] = projectPath
        tsPaths[labeText] = ts
        warnTextPaths[labeText] = warnText

    setJsaValue('projectNames',projectNames)
    setJsaValue('tsPaths',tsPaths)
    setJsaValue('warnTextPaths',warnTextPaths)
    writeJs(configPath,jsContent)

def saveConfigKey(key):
    tmepJsContent = getJScontent(configFilePath)
    tmepJsContent[key] = jsContent[key]
    writeJs(configFilePath,jsContent)