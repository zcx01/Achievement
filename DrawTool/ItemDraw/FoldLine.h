#ifndef FOLDLINE_H
#define FOLDLINE_H

/*******************************************************
    created		:	2019/12/03
    file base   :	FoldLine.h
    author		:	zcx
    purpose		:	画折线
*******************************************************/
#include "../BaseDraw/CZBase.h"
#include "hfdefine.h"
#include <QBrush>
#include <QFont>
#include "../DrawToolPublic/ZGraphicsTextItem.h"

class PointAttr
{
public:
    enum TextItemPos
    {
        Center, //中间
        Border, //两边
    };
    QPointF             pos;        //坐标
    QString             text;
    QBrush              textBrush;
    int                 textWidth;
    QColor              textColor;
    QFont               textFont;
    TextItemPos         textItemPos;
    ZGraphicsTextItem*  textItem;   //文本,第一个点是没有文本的,从第二个点才有文本
    PointAttr*          preAttr;    //前一个属性

    PointAttr();
    virtual ~PointAttr();

    void setPos(QPointF p);

    void setPreAttr(PointAttr *ptr);

    void setTextItemPos(QPointF p);

};
typedef QSharedPointer<PointAttr> PointAttrPtr;

class FoldLine : public CZBase
{
    Q_OBJECT
public:
    enum ArrowsStyle            //箭头的样式
    {
        NoArrow =0x0001,        //没有
        NoSealTriangle =0x0002, //没有封闭的三角形
        SealTriangle = 0x0004,  //封闭的三角形
    };
    Q_DECLARE_FLAGS(ArrowsStyles,ArrowsStyle)

    enum NodeStyle      //节点处的样式
    {
        NoNodeStyle,        //没有
        Ellipse,        //圆
        Rect,           //矩形
    };

    explicit FoldLine(QGraphicsItem *parent = 0);
    ~FoldLine();

    void getAttrUpdate(QVariantMap &pDate);

    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString getClassName();

    QPainterPath shape() const;

private slots:
    void slot_EditFinsh(QGraphicsTextItem *item);

protected:
    void keyPressEvent(QKeyEvent *event);

    void attrUpdate(const QVariantMap &pDate);

    void add();

    bool Asynchronous(QVariant &pData);

    bool isContainPos(QPointF pos);

    //更新范围
    void UpDateBound();

    //添加点
    void addPoint(QPointF pos,const QString &text,int index);

    //修改点
    QPointF ModifyPointPos(int index, QPointF newPos);

    void DeletePoint(int index);

    //保存所有属性
    void saveToAttr(bool NoUseSame);

    //仅仅保存点的坐标
    void OnlySavePoint();

    //得到pos下的索引
    int GetIndexByPoint(QPointF pos);

    //创建一个PointAttrPtr,并且赋默认值(为前一个的值)
    void createPointAttrPtr(PointAttr *attr, int index = -1);

    //给textItem,添加属性
    void setTextItemAttr(ZGraphicsTextItem *textItem, PointAttr *attr);

    QPainterPath                    m_Path;
    QList<PointAttrPtr>             m_PointAttrs;
    int                             m_Range;
    int                             m_ArrowsStyle;
    int                             m_NodeStyle;
    QPen                            m_FoldNodePen;
    QBrush                          m_FoldNodeBrush;
    Q_ENUMS(ArrowsStyle)
    Q_ENUMS(NodeStyle)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(FoldLine::ArrowsStyles)
#endif // FOLDLINE_H
