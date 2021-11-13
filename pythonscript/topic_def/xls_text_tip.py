from os import replace
import xlrd
import json

def analyze(xlsPath,jsonPath):
    book=xlrd.open_workbook(xlsPath)
    sheel=book.sheet_by_index(0)
    cr = open(jsonPath, "r")
    jsContent = json.load(cr)
    for row in range(sheel.nrows) :
        desc=str(sheel.cell_value(row,0))
        try:
            topic =str(sheel.cell_value(row,1))
            value = int(sheel.cell_value(row,2),16)
            sig=str(sheel.cell_value(row,1))
        except:
            continue
        t_content={}
        
        descs=desc.split(":")
        desc=descs[0]
        grade=descs[1]
        if len(jsContent) != 0 and topic in jsContent:
            jsContent[topic][str(value)] = desc
        else:
            t_content["grade"] =grade
            t_content[str(value)] = desc
            jsContent[topic] = t_content
            print(topic+" "+"d"+" "+"x"+" "+"tx")
        
    cr = open(jsonPath, "w")
    cr.write(json.dumps(jsContent,ensure_ascii=False,indent=4))
    cr.close()

if __name__ == "__main__":
    analyze("/home/chengxiongzhu/Works/文档/B样/文字提示.xls","/home/chengxiongzhu/Works/Repos/changan_c835/qt/ic_qt/resources/config/icwarning_config.json")