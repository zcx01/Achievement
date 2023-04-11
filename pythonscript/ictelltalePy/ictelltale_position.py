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
        print(f"\"{topic}\",")
        for pro in jsTelltale[topic]:
            if len(pic) != 0 and pic in str(jsTelltale[topic][pro]):
                print(pic,"---------",topic,lef)
                jsTelltale[topic]["left"]=lef
                jsTelltale[topic]["top"]=top
                return topic
    sys.exit()
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
    # writeJs(configjsonPath,jsTelltale)
            
def getPosition(configPath):
    jsConfig=getJScontent(configPath)
    common=jsConfig["common"]
    space=common["space"]
    configjsonPath=common["configjsonPath"]
    imageWith=common["imageWith"]
    groupTopic={}
    jsTelltale=getJScontent(configjsonPath)
    for topic in jsTelltale:
        y = jsTelltale[topic]["top"]
        if y not in groupTopic:
            groupTopic[y] = []
        groupTopic[y].append(jsTelltale[topic])
    
    for y in groupTopic:
        tmp = groupTopic[y]
        assert isinstance(tmp, list)
        groupTopic[y] = sorted(tmp,key=lambda x : x["left"])

    groupTopics=[]
    for y in groupTopic:
        currentGroup=[]
        pre_value = 0
        for tmp in groupTopic[y]:
            x = tmp['left']
            pic = tmp['pic']
            startPos = {}
            if len(currentGroup) == 0 :
                startPos['x'] = x
                startPos['y'] = y
                currentGroup.append(startPos)
                currentGroup.append(pic)
            elif x - pre_value < space-2 :
                last_index = len(currentGroup) -1
                last_pic = currentGroup[last_index]
                if type(last_pic) == str:
                    last_pic = last_pic + "," + pic
                    currentGroup[last_index] = last_pic
            elif x - pre_value > space + imageWith + 10:
                groupTopics.append(currentGroup.copy())
                currentGroup.clear()
                startPos['x'] = x
                startPos['y'] = y
                currentGroup.append(startPos)
                currentGroup.append(pic)
            else:
                currentGroup.append(pic)
            pre_value = x
        groupTopics.append(currentGroup.copy())
    print(groupTopics)
    jsConfig["position"] = groupTopics
    writeJs(configPath,jsConfig)
    pass

if __name__ == "__main__":
    if len(sys.argv) >=2:
        position(sys.argv[1])
    else:
        getPosition(pyFileDir+"config.json")
