from commonfun import *
from execCmd import *
from configFile import *
from PyQt5 import *
import datetime
import subprocess
from enum import Enum


disPlayMsg = None
def keyStrCmd(cmd,t=0.3,out='$',auto_exit=True):
    if disPlayMsg != None:
        disPlayMsg(cmd)
    keyStr(cmd,t,out,auto_exit)
       

def setDisPlayMsg(disPlayMsgFun):
    global disPlayMsg
    disPlayMsg = disPlayMsgFun
# class handle(QtGui.QObject):
#     send_msg = QtCore.pyqtSignal(str)
#     def __init__(self,disPlayMsg, parent=None) -> None:
#         super().__init__(parent)

def sshIp():
    ip = getJsValue('ip')
    user = getJsValue('user')
    REMOTEHOST = f'{user}@{ip}'
    keyStrCmd(f'ssh {REMOTEHOST}')
    return REMOTEHOST

def closeIp():
    keyStrCmd(f'exit',t=0.3,out='closed.')
    closeSpawn()

def trHanle(xlsPath):
    if len(xlsPath) == 0:
        xlsPath = getJsValue('xlsPath')
    if len(xlsPath) == 0:
        disPlayMsg('翻译文件不存在')
        return
    ip = getJsValue('ip')
    user = getJsValue('user')
    pw = getJsValue('pw')
    icTextLE = getJsValue('icText')
    trXlsPathS = getJsValue('trXlsPathS')
    if len(trXlsPathS) == '':
        disPlayMsg('目标路径不存在' )
        return
    if len(icTextLE) == '':
        disPlayMsg('icTextLE脚本路径不存在' )
        return
    REMOTEHOST = f'{user}@{ip}'
    xlsPathFileName = os.path.basename(xlsPath)
    translate = getCurrentProjectPath()+'/qt/ic_qt/resources/translate'
    icwarning_config = getCurrentProjectPath()+'/qt/ic_qt/resources/config/icwarning_config.json'
    keyStrCmd(f'scp {xlsPath} {REMOTEHOST}:{trXlsPathS}')
    sshIp()
    keyStrCmd(f'rm {trXlsPathS}test',disPlayMsg)
    keyStrCmd(f'python3 {icTextLE} -t {translate} -j {icwarning_config} -i {trXlsPathS}{xlsPathFileName}')
    closeIp()
    disPlayMsg('执行完成')

def trChangedHanle(downLoadPath,setTrChangedFilePath):
    if len(downLoadPath) == 0:
        downLoadPath = getJsValue('downLoadPath')
    if len(downLoadPath) == 0:
        disPlayMsg('保存路径不存在')
        return
    icTextLE = getJsValue('icText')
    if len(icTextLE) == '':
        disPlayMsg('icTextLE脚本路径不存在' )
        return
    xlsPathFileName = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S") + '_changed.xlsx'
    trXlsPathS = os.path.dirname(icTextLE)+"/"
    translate = getCurrentProjectPath()+'/qt/ic_qt/resources/translate'
    icwarning_config = getCurrentProjectPath()+'/qt/ic_qt/resources/config/icwarning_config.json'
    REMOTEHOST = sshIp()
    keyStrCmd(f'python3 {icTextLE} -t {translate} -j {icwarning_config} -c {trXlsPathS}{xlsPathFileName}')
    closeIp()
    keyStrCmd(f'scp {REMOTEHOST}:{trXlsPathS}{xlsPathFileName} {downLoadPath}')
    time.sleep(6)
    sshIp()
    keyStrCmd(f'rm {trXlsPathS}{xlsPathFileName}')
    closeIp()
    disPlayMsg('执行完成')
    trChangedFilePath = f'{downLoadPath}/{xlsPathFileName}'
    addGeneratedFiles(trChangedFilePath)
    setTrChangedFilePath(trChangedFilePath)

class CanHanleType(Enum):
    UpdateXls = 1
    AddSig = 2
    AddWSig = 3

def canHanle(handleType,texts):
    assert isinstance(handleType,CanHanleType)
    xls_can_path =  getCurrentProjectPath()+'/xls_transform_dbc_tool/'
    REMOTEHOST = sshIp()
    keyStrCmd(f'cd {xls_can_path}',)
    if handleType ==  CanHanleType.UpdateXls:
        keyStrCmd(f'python3 sig_google.py')
        closeIp()
        downLoadPath = getJsValue('downLoadPath')
        keyStrCmd(f'scp {REMOTEHOST}:{xls_can_path}errSig.xls {downLoadPath}')
        errSig = f'{downLoadPath}/errSig.xls'
        openFileUseDefault(errSig)
        addGeneratedFiles(errSig)
    
    if texts == None or len(texts) == '':
        disPlayMsg('请添加信号名')
        return
    
    if handleType == CanHanleType.AddSig:
        keyStrCmd(f'python3 xlsdbc.py -s {texts}')
        closeIp()
    elif handleType == CanHanleType.AddWSig:
        keyStrCmd(f'python3 xlsdbc.py -w {texts}')
        closeIp()
    disPlayMsg('执行完成')
    return ''

def getPushFiles():
    pushFile = getJsValue('pushFile')
    if pushFile == '':
        return []
    cmd = subprocess.Popen(f"python {pushFile} -f" ,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE,
                       shell=True)
    (output, err) = cmd.communicate()
    return output.decode('utf-8').splitlines()

def pushFileHanle(fileName,isScp):
    if fileName == None or fileName == '':
        disPlayMsg("请选择文件")
        return
    projectPath =  getCurrentProjectPath()+'/prebuilts/ic'
    pushFile = getJsValue('pushFile')
    downLoadPath = getJsValue('downLoadPath')
    ScpCmd =''
    if isScp : ScpCmd = ' -s'
    cmdStr = f'python {pushFile} -p {projectPath} -w {downLoadPath} -c {fileName}{ScpCmd}'
    disPlayMsg(cmdStr)
    p = subprocess.Popen(cmdStr,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.STDOUT,
                       shell=True)

    for line in iter(p.stdout.readline, b''):
        disPlayMsg(line.rstrip().decode('utf8'))
    disPlayMsg('执行完成')