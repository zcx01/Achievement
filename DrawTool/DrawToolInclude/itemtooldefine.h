#ifndef ITEMTOOLDEFINE_H
#define ITEMTOOLDEFINE_H
/*******************************************************
    created     :   2019/08/08
    file base	:   itemtooldefine.h
    author      :   zcx
    purpose     :	属性宏定义
*******************************************************/
//BrokenLineTool
#define CHILDID				"childId"			//子item的id
#define HEIGHTSCALE			"HeighScale"		//高度比例

//Attachment
#define ATTACHMENTID        "attachmentId"      //相连item的ID

//ZRotaryTool
#define ZROTARYTOOLID       "ZRotaryTool"       //旋转工具item的id,即id为ZRotaryTool，及时旋转的图元

//CRotaryTool
#define AXIS                "Axis"              //旋转的轴
#define AXISPOSTYPE         "AxisPosType"       //绕点类型
#define WITHCHAGED          "WithChaged"        //跟item的位置改变而改变
#define POSTYPE             "PosType"           //位置类型
#define DISTANCE            "Distance"          //距离
#define ITEMID              "ItemId"            //特定的item的id(如果不配置，就旋转所有工具的item)

//Adsorb
#define ADSORBID            "Adsorb"            //吸附工具的Id
#define ADSORBRECT          "AdsorbRect"        //吸附工具的的范围

//DisPlayName
#define ITEMNAME            "ItemName"          //图元的名字
#define NAMEPOS             "NamePos"           //名字出现的位置
#define NAMEFONT            "NameFont"          //字体(依次为大小,加粗,斜体,下划线,上划线,文字的间距)
#define NAMEPEN             "NamePen"           //画笔(依次为线宽[0-1];颜色[1-4];风格[4-5])
#define NAMEBRUSH           "NameBrush"         //画笔(颜色1-4)
#define ISITEMIN            "IsItemIn"          //是否在图元内
#define NAMEDIS             "NameDistance"      //距离
#define EBLEEDIT            "EbleEdit"          //是否可以编辑

//ItemFoldRegard
#define FOLDID              0                   //第0位置储存的折线的ID
#define FOLDINDEX           1                   //第1位置储存的折线的对应的索引
#define FOLDJOININDEX       2                   //绑定图元上对应FOLDINDEX上的位置的索引
#define JOINPOINTS          "JoinPoints"        //碰撞图元上设置的自定义的衔接点(0,0;1,1),如果是特殊的点，请使用()
#define BINDFOLD            "BindFold"          //与碰撞图元绑定所有折线的属性
#define BEGPOINTID          "BegPointID"        //与头点绑定的图元的Id(QString)
#define ENDPOINTID          "EndPointID"        //与尾点绑定的图元的Id(QString)

//BoundChanged
#define VASSISTLINE         "VAssistLine"       //垂直辅助线的ID
#define HASSISTLINE         "HAssistLine"       //水平复制线的ID

#endif // ITEMTOOLDEFINE_H
