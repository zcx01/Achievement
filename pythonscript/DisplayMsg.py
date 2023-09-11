# coding:utf-8
#!/bin/python

'''
进程间通信参考
https://zhuanlan.zhihu.com/p/541220649
'''
import sys
import os
import argparse
import time
import threading
from PyQt5 import QtGui
from PyQt5.QtWidgets import QApplication, QMainWindow,QTextEdit, QWidget
from PyQt5.QtCore import Qt, QThread, pyqtSignal,QObject
from PyQt5.QtGui import QCloseEvent,QKeyEvent,QResizeEvent
from PyQt5 import QtGui
from PyQt5 import QtCore
from PyQt5 import QtWidgets
import socket

os.environ["QT_QPA_PLATFORM_PLUGIN_PATH"] = ""

PORTMSG = 12345
HOSTMSG = 'LOCALHOST'
CODEMSG = 'utf-8'

def send_msg(msg):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.sendto(msg.encode(CODEMSG), (HOSTMSG, PORTMSG))

def receive_msg(signal):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((HOSTMSG, PORTMSG))
        while True:
            data, addr = s.recvfrom(1024)
            print(f"Received {data.decode(CODEMSG)} from {addr}")
            signal.emit(data.decode(CODEMSG))

#测试 getBugInfo 函数
class UpdateThread(QObject):
    update_data = pyqtSignal(str)
    def start(self) -> None:
        my_thread = threading.Thread(target=receive_msg,args=(self.update_data,))
        my_thread.setDaemon(True)
        my_thread.start()

class MainWindow(QTextEdit):
    def initUI(self):
        self.setWindowFlags(Qt.Window)
        self.subTheard = UpdateThread()
        self.subTheard.update_data.connect(self.updataText)
        self.subTheard.start()

    def updataText(self,text):
        if self.isHidden():
            self.showNormal()
        self.append(text)

    def closeEvent(self, a0: QCloseEvent) -> None:
        a0.ignore()
        self.hide()

    # def resizeEvent(self, a0: QResizeEvent) -> None:
    #     print(a0.size())
    #     self.viewport().resize(a0.size())
    #     return super().resizeEvent(a0)

    def keyPressEvent(self, e: QKeyEvent) -> None:
        modifier = e.modifiers()
        if modifier & Qt.AltModifier:
            if e.key() == Qt.Key_Return:
                cursor = self.textCursor()
                selected_text = self.document().findBlockByLineNumber(cursor.blockNumber()).text()
                #selected_text = str(cursor.selectedText())  # 获取选中的文本
                # selected_text = str(self.textCursor().selectedText())
                # selected_text = selected_text.replace("\n",'')
                cmd = f"explorer {selected_text}"
                os.system(cmd)
        if modifier & Qt.ShiftModifier:
            if e.key() == Qt.Key_C:
                sys.exit()
        return super().keyPressEvent(e)

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
    description='''显示信息''')

    # #这个是要解析 -f 后面的参数
    parser.add_argument('-m', '--MsgSavaPath',help="消息保存的路径",type=str,default='',nargs='?')
    arg=parser.parse_args()

    app = QApplication(sys.argv)
    app.setApplicationName("DisplayMsg")
    textEdit = MainWindow()
    textEdit.initUI()
    textEdit.show()
    app.exec()