#ifndef SERIESDEFINE_H
#define SERIESDEFINE_H



namespace DC
{
enum CharHandleType
{
    ChangedData,
    DeleteData,
};
}

#define D_ZSeriseClassName  "ZSeriseClassName"      //ZSerise类名
#define D_AnimationOptions  "AnimationOptions"      //动画类型
#define D_ChartTitle        "ChartTitle"            //标题

#define SeriesClasName      "SeriesClasName"        //Serise类名
#define D_OnlySerise        "OnlySerise"            //bool,唯一的Chart
#define D_SeriseId          "SeriseId"              //Serise的标识，如果没有就IDD


#define D_ChartHandleType   "ChartHandleType"       //操作

//线图
#define S_LinePointFs       "SerisePointFs"         //点集（1,1|2,3）

//面积图
#define S_AreaPointFfs      "AreaPointFfs"          //上线点集（1,1|2,3）
#define S_AreaPointFts      "AreaPointFts"          //下线点击（1,1|2,3）

//柱状图
#define S_BarTexts          "BarTexts"              //(QString) 柱状图文字(文字1,文字2,...)，值的设置为属性为 文字1 = "1,2,..."
#define S_XCategories       "ACategories"           //(QString) 轴上的文字(文字1,文字2,...)
#define S_ValueShow         "ValueShow"             //值是否在柱状图上显示


//饼状图
#define S_PieTexts          "PieTexts"              //(QString)饼状图的文本 饼状图文字(文字1,文字2,...)，值的设置为属性为 文字1 = "1" 文字2 = "3"
#define S_PieCurIndex       "PieCurIndex"           //(int)饼状图当前的索引
#endif // SERIESDEFINE_H
