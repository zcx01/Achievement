#ifndef CZDRAW_H
#define CZDRAW_H

#include <QObject>
#include <QSharedPointer>
#include <QGraphicsItem>
#include <QVariantMap>

#define CONFIGFILENAME      "ConfigFileName"    //item配置文件
#define TOOLCLASSNAMES      "toolClassNames"    //配置item的工具的属性

//CManagementItems使用的属性
#define VIEWSIZE            "ViewSize"          //(QString,QString)视图的大小,从返回的的是QSize
#define SCENESIZE           "SceneSize"         //(QString,QString,QString,QString)(场景的大小)从返回的的是QRectF
#define CANZOOM             "CanZoom"           //(bool)设置能够缩放
#define CANTRANSLATE        "CanTranslate"      //(bool)设置能够平移

//CManagementTool使用的属性
//创建Tool的错误类型
#define TOOLEXIST           "tool is already exist"
#define TOOLNONAME          "tools no has toolClassName"
//配置item错误类型
#define TOOLISNULL          "tool is null"
#define TOOLADD             "tool is already add"


//CZBase已经使用的属性
#define BACKGOUNDITEM       "Backgounditem"     //(bool)    背景图元的标识
#define BACKGOUNDINDEX      60
#define IDD                 "Id"                //(QString) 标识
#define ACCEPTDROPS         "AcceptDrops"       //(bool)    是否接收拖拽
#define NOACTIVE            "NoActive"          //(bool)    不活跃
#define NOENABLED           "NoEnabled"         //(bool)    不能生效
#define FLAGS               "Flags"             //(int)     item的标志
#define FOCUS               "Focus"             //(int)     获取焦点的类型
#define CANSETFOCUS         "CanSetFocus"       //(bool)    能否设置焦点的类型
#define NOOPACITY           "NoOpacity"         //(double)  透明度
#define POSX                "Posx"              //(double)  x坐标
#define POSY                "Posy"              //(double)  y坐标
#define ORIGINTYPE          "OriginType"        //(int)     坐标矩阵变换的原点类型 0表示左上角，1表示右上角，2表示左下角，3表示右下角，4表示居中 5表示上居中，6表示下居中，7表示左居中，8表示右居中，其余表示表示左上角
#define ROTATION            "Rotation"          //(double)  旋转的角度
#define SCALE               "Scale"             //(double)  缩放的倍数
#define SELECTED            "Selected"          //(bool)    是否选中
#define TOOLTIP             "ToolTip"           //(QString) 提示
#define NOVISIBLE           "NoVisible"         //(bool)    是否显示
#define ZValue              "ZValue"            //(double)  绘画的顺序
#define BOUNDRECT           "BoundRect"         //(QString) 范围（必设）（在svg(DrawSvg)可以不用设置，如果没有设置者使用默认的，设置了就是用已经设置的）
#define ITEMTYPE            "Itemtype"          //(QString) 类型(如果没有定义，就等于类型)
#define PARENTITEM          "parentitem"        //(QString) 父类图元Id
#define ITEMCLASSNAME       "itemclassname"     //(QString) id的类名，通过类型创建图元的时有用
#define DROPDATA            "DropData"          //(QString) 拖拽的数据
#define EDITEND             "EditEnd"           //(QString) 编辑结束
#define PENS                "Pens"              //(QString) 画笔(依次为线宽[0-1]|颜色[1-4]|风格[4-5];)
#define BRUSHS              "Brushs"            //(QString) 画刷(依次为颜色[1-4]|风格[4-5];)
#define PENINDEX            "PenIndex"          //(int)     当前的画笔索引
#define BRUSHINDEX          "BrushIndex"        //(int)     当前的画刷索引
#define NOCANDELETE         "NoCanDelete"       //(bool)    不能删除
//#define POS                 "Pos"               //(QString) 位置(位置改变发送的标识，不会发送POSX、POSY的标识)

class CZBaseTool;

//一个Item的属性
class DrawItemAttr
{
public:
    QString             id;             //标识(当id = className是，表示工具)
    QVariantMap         attrs;          //属性
    QString             className;      //item的类名
    QString             itmeType;       //图元的类型
    QList<CZBaseTool*>  tool;           //拥有的工具
    QList<QString>      childIds;       //子类的集合
    DrawItemAttr()
    {
    }
    ~DrawItemAttr()
    {

    }
};
typedef QSharedPointer<DrawItemAttr> DrawItemAttrPtr;

namespace CZDRAW
{
enum RotaryAxis     //旋转的轴
{
    XAxis=0x01,     //启用X
    YAxis=0x02,     //启用Y
    ZAxis=0x04,     //启用Z
};

enum EditStatus     //编辑的状态
{
    NoEdit=0,       //没有编辑
    Edit,           //编辑
    NewBulid        //新建
};

Q_DECLARE_FLAGS(RotaryAxiss,RotaryAxis)
}

Q_DECLARE_OPERATORS_FOR_FLAGS(CZDRAW::RotaryAxiss)
#endif // CZDRAW_H
