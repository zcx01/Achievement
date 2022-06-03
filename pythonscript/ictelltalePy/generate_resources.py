import os
import sys
import argparse
from pathlib import Path

def generate(resourcesDirs,generateFile):
    generateDirName = os.path.dirname(generateFile)
    qrcFileContent=[]
    qrcFileContent.append("<RCC>")
    qrcFileContent.append("    <qresource prefix=\"/\">")
    
    for resourcesDir in resourcesDirs:
        for (dirpath,dirnames,filenames) in os.walk(resourcesDir):
            assert isinstance(dirpath,str)
            gPath = Path(dirpath)
            dirpath = str(gPath.relative_to(generateDirName))
            for fileName in filenames:
                filePath = dirpath+'/'+fileName
                qrcFileContent.append("        <file>"+filePath+"</file>")

    qrcFileContent.append("    </qresource>")
    qrcFileContent.append("</RCC>")
    cr = open(generateFile, "w")
    cr.writelines('\n'.join(qrcFileContent))
    cr.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='resources')
    parser.add_argument('-d','--dirNames',help='资源目录',nargs='*',default=[])
    parser.add_argument('-g','--generateFileName',help='生成文件名',type=str)
    arg = parser.parse_args()
    generate(arg.dirNames,arg.generateFileName)
