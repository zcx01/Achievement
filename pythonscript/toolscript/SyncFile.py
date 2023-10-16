#!/bin/python
import os
import argparse

File_Dict={
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/analyze_dbc_file.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/xls_transform_dbc_tool/analyze_dbc/analyze_dbc_file.py",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/analyze_dbc.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/xls_transform_dbc_tool/analyze_dbc/analyze_dbc.py",
    "/home/chengxiongzhu/Achievement/pythonscript/commonfun.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/xls_transform_dbc_tool/analyze_dbc/commonfun.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/xlsdbcCommand.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/xls_transform_dbc_tool/xlsdbcCommand.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/xlsdbc.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/xls_transform_dbc_tool/xlsdbc.py",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/config.json":
    "/home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/config/can_matrix_config.json",
    "/home/chengxiongzhu/Achievement/pythonscript/analyze_dbc/projectInI.py":
    "/home/chengxiongzhu/Works/Repos/changan_c385/src/ic_service/config/can_matrix_projectInI.py",
    "/home/chengxiongzhu/Achievement/pythonscript/canSimulation/checksig.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/xls_transform_dbc_tool/checksig.py",
    "/home/chengxiongzhu/Achievement/pythonscript/XlsGenerateCode_google/sig_google.py":
    "/home/chengxiongzhu/Works/Repos/changan_j90a/xls_transform_dbc_tool/sig_google.py"
}

def CpFile(file1,file2):
    cmd = f'cp -rf {file1} {file2}'
    os.system(cmd)
    print(cmd)

def sync(type):
    for file1,file2 in File_Dict.items():
        if type == 0:
            CpFile(file2,file1)
        else:
            CpFile(file1,file2)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-s','--sync',help='0是同步，1是反同步',nargs='?',default=0,type=int)
    arg = parser.parse_args()
    sync(arg.sync)