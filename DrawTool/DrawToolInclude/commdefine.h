#ifndef COMMDFINE_H
#define COMMDFINE_H
/*******************************************************
    created     :   2019/12/03
    file base	:   itemtooldefine.h
    author      :   zcx
    purpose     :   工具和画图共有的宏定义、和枚举
*******************************************************/
class Dr
{
public:
    enum EditFoldType       //编辑折线的类型
    {
        NewBuild,           //新建(需要传入所有点的属性)
        ADD,                //添加(需要传入当前的点的索引、坐标)
        Modify,             //修改(需要传入当前的点的索引、新的坐标)
        Delete,             //删除(需要传入当前的点的索引)
        Save,               //保存(不需要其他数据)
        OnlySavePoint,      //仅仅保存点(不需要其他数据)
        GetCurrentIndex,    //得到当前点(需要传入当前的点的坐标)
        Find,               //查找
        Insert,             //插入
    };

    enum GetPosType         //获取节点坐标的类型
    {
        TimeScaleWidth,     //时间刻度的宽度
        GridHeight,         //网格的高度
        SetParentItem,      //设置父图元
    };
};

#define JOIN                ";"                 //大分隔符
#define SJONIN              ","                 //小分隔符

//FoldLine
#define FOLDPOINTS          "FoldPoints"        //折线点集(QString)
#define FOLDCURPOINT        "FoldCurPoint"      //当前的点(QPointF)
#define FOLDCURINDEX        "FoldCurIndex"      //当前点的索引(int)
#define FOLDCURTEXT         "FoldCurText"       //当前点的文本
#define EDITSTATUS          "EditStatus"        //编辑的状态 值为EditFoldType
#define FOLDPOINTRANGE      "FoldPointRange"    //节点上点的范围(int,没有设置默认是10)
#define FOLDDEFAULT         "FoldDefault"       //是否有默认文字

//FlowNodeRelation
#define F_GetPosType        "GetPosType"        //获取节点坐标的类型 值为GetPosType
#define F_FlowName          "FlowName"          //节点所属流程的名字
#define F_PlatformName      "PlatformName"      //节点所属平台名字
#define F_NodeSTime         "NodeSTime"         //节点的开始时间
#define F_NodeETime         "NodeETime"         //节点的结束时间
#define F_NodeX             "NodeX"             //节点的x坐标
#define F_NodeY             "NodeY"             //节点的y坐标
#define F_NodeW             "NodeW"             //节点的宽度
#define F_NodeH             "NodeH"             //节点的高度
#define F_NodePreId         "NodePreId"         //前一个节点的Id
#define F_NodeParent        "NodeParent"        //节点显示范围的Id
#define SizeChanged         "SizeChanged"       //时间刻度大小的改变
#endif // COMMDFINE_H

