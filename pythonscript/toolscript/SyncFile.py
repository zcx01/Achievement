#!/bin/python
import os
import argparse
import shutil

File_Dict={
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/analyze_dbc_file.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/analyze_dbc/analyze_dbc_file.py",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/analyze_dbc.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/analyze_dbc/analyze_dbc.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/xlsdbcCommand.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/xlsdbcCommand.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/xlsdbc.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/xlsdbc.py",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/config.json":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/analyze_dbc/config.json",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/projectInI.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/analyze_dbc/projectInI.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/checksig.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/checksig.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/sig_google.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/sig_google.py",
    "/home/chengxiongzhu/Achievement/studio/C++/project_Test/tcp":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/src/common/tcp",
    "/home/chengxiongzhu/Achievement/pythonscript/toolscript/SyncQt.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/src/ic_service/tools/xls_transform_dbc_tool/SyncQt.py"
}

def CpFile(file1,file2,cpFilePath):
    cmd = f'cp -rf {file1} {file2}'
    print(cmd)
    if os.path.isfile(file1):
        if os.path.exists(file2):
            os.remove(file2)
        shutil.copy2(file1,file2) #防止拷贝软连接
        cpFilePath.append(file2)
    elif os.path.isdir(file1):
        if os.path.exists(file2):
            shutil.rmtree(file2)
        os.makedirs(file2)
        for (dirpath,dirnames,filenames) in os.walk(file1):
                assert isinstance(dirpath,str)
                for fileName in filenames:
                    filePath = dirpath+'/'+fileName
                    if os.path.isfile(filePath):
                        aimPath = filePath.replace(file1,file2)
                        shutil.copy2(filePath,aimPath) #防止拷贝软连接
                        cpFilePath.append(aimPath)
    
def sync(syncType):
    pushFile=[]
    for file1,file2 in File_Dict.items():
        if syncType == 0:
            CpFile(file2,file1,pushFile)
        else:
            CpFile(file1,file2,pushFile)
    if syncType == 0:
        filePaths = ' '.join(pushFile)
        os.system(f'git add {filePaths}')
        os.system(f'git commit -m \'同步文件\'')
        os.system('git pull')
        os.system('git push')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-s','--sync',help='0是同步，1是反同步',nargs='?',default=0,type=int)
    arg = parser.parse_args()
    sync(arg.sync)