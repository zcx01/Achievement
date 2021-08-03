import os
import sys

def getSigName(content):
    srcTexts = content.split(" ")
    srcContent=[]
    for text in srcTexts:
        if len(text) != 0:
            srcContent.append(text)
    return srcContent[2]

def modify(src,aim):
    r_in_src=open(src)
    srcContents=r_in_src.readlines()
    r_in_src.close()
    enum_str={}
    for srcText in srcContents:
        if srcText.startswith("VAL_"):
            enum_str[getSigName(srcText)] = srcText

    r_in_aim=open(aim)
    aimContents=r_in_aim.readlines()
    r_in_aim.close()
    w_in_aim=open(aim,"w")
    for aimText in aimContents:
        if aimText.startswith("VAL_"):
            signame = getSigName(aimText)
            if signame in enum_str:
                w_in_aim.write(enum_str[signame])
                continue
            else:
                print(aimText)
        w_in_aim.write(aimText)
    w_in_aim.close()

#/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dc_
#/home/chengxiongzhu/Works/Repos/changan_c835/src/ic_service/parser/VendorFiles/dbc_files/CAN0_C385EV-E_V2.1.0_20210318.dbc
if __name__ == "__main__":
    if len(sys.argv) == 3 :
        modify(sys.argv[1], sys.argv[2])