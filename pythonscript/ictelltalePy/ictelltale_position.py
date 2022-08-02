import os
import sys
pyFileDir = os.path.dirname(os.path.abspath(__file__))+"/"
from commonfun import*

def otherTelltale(jsTelltale,modifytopic,imageWith,space):
    x=72
    y=80+56
    index = 0
    for topic in jsTelltale:
        if topic not in modifytopic:
            left = x+(imageWith+space)*index
            top = y
            jsTelltale[topic]["left"]=left
            jsTelltale[topic]["top"]=top
            print(jsTelltale[topic]["desc"],jsTelltale[topic]["pic"])
            index += 1
            if index == 11:
                index=0
                y+=56

def modifyTelltale(pic,jsTelltale,lef,top):
    for topic in jsTelltale:
        for pro in jsTelltale[topic]:
            if len(pic) != 0 and pic in str(jsTelltale[topic][pro]):
                print(pic,"---------",topic,lef)
                jsTelltale[topic]["left"]=lef
                jsTelltale[topic]["top"]=top
                return topic
    return ""

def position(configPath):
    jsConfig=getJScontent(configPath)
    common=jsConfig["common"]
    space=common["space"]
    configjsonPath=common["configjsonPath"]
    imageWith=common["imageWith"]
    positions=jsConfig["position"]
    modifytopic=[]
    jsTelltale=getJScontent(configjsonPath)
    for position in positions:
        x=0
        y=0
        index=0
        for pos in position:
            if type(pos) is dict:
                x=pos["x"]
                y=pos["y"]
                continue
            left=x+(imageWith+space)*index
            top=y
            imageNames=str(pos).split(",")
            for imageName in imageNames:
                modifytopic.append(modifyTelltale(imageName, jsTelltale, left, top))
            index += 1
    otherTelltale(jsTelltale, modifytopic, imageWith, space)
    writeJs(configjsonPath,jsTelltale)
            
def getPosition():
    pass

if __name__ == "__main__":
    if len(sys.argv) >=2:
        position(sys.argv[1])
    else:
        position(pyFileDir+"config.json")
