from commonfun import *
from execCmd import *
from configFile import *
from PyQt5 import *
import datetime

def keyStrCmd(cmd,disPlayMsg,t=0.3,out='$',auto_exit=True):
    disPlayMsg(cmd)
    keyStr(cmd,t,out,auto_exit)

# class handle(QtGui.QObject):
#     send_msg = QtCore.pyqtSignal(str)
#     def __init__(self,disPlayMsg, parent=None) -> None:
#         super().__init__(parent)


def trHanle(xlsPath,disPlayMsg):
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
    keyStrCmd(f'scp {xlsPath} {REMOTEHOST}:{trXlsPathS}',disPlayMsg)
    keyStrCmd(f'ssh {REMOTEHOST}',disPlayMsg)
    # keyStrCmd(f'rm {trXlsPathS}test',disPlayMsg)
    keyStrCmd(f'python3 {icTextLE} -i {trXlsPathS}{xlsPathFileName}',disPlayMsg)
    closeSpawn()
    disPlayMsg('执行完成')

def trChangedHanle(trChangeXlsPath,disPlayMsg):
    if len(trChangeXlsPath) == 0:
        trChangeXlsPath = getJsValue('trChangeXlsPath')
    if len(trChangeXlsPath) == 0:
        disPlayMsg('保存路径不存在')
        return
    ip = getJsValue('ip')
    user = getJsValue('user')
    pw = getJsValue('pw')
    icTextLE = getJsValue('icText')
    if len(icTextLE) == '':
        disPlayMsg('icTextLE脚本路径不存在' )
        return
    REMOTEHOST = f'{user}@{ip}'
    xlsPathFileName = datetime.datetime.now().strftime("%Y_%m_%d_%H_%M_%S") + '_changed.xlsx'
    trXlsPathS = os.path.dirname(icTextLE)+"/"
    keyStrCmd(f'ssh {REMOTEHOST}',disPlayMsg)
    keyStrCmd(f'python3 {icTextLE} -c {trXlsPathS}{xlsPathFileName}',disPlayMsg)
    closeSpawn()
    keyStrCmd(f'scp {REMOTEHOST}:{trXlsPathS}{xlsPathFileName} {trChangeXlsPath}',disPlayMsg)
    keyStrCmd(f'ssh {REMOTEHOST}',disPlayMsg)
    keyStrCmd(f'rm {trXlsPathS}{xlsPathFileName}',disPlayMsg)
    disPlayMsg('执行完成')