#ifndef ITEMFOLDREGARD_H
#define ITEMFOLDREGARD_H

/*******************************************************
    created		:   2019/12/05
    file base   :   ItemFoldRegard.h
    author		:	zcx
    purpose		:   图元之间的折线关系
--------------------折线的移动（确定图元之间的折线关系，即创建关系）---------------------
                    图上的关系确认流程:
                    1.移动折线上的点，在移动的过程中，找到与之碰撞的图元
                    2.判断该图元是否有该工具,画出该图元可以连线的点
                    3.当松开鼠标的时,判断该折线头与尾距离该图元连线的点的远近
                    4.把这两个相连，折线的其他点不动
                    数据上关系的确认流程:
                    5.当图上关系确认完成后,在图元属性中保留
                    该折线的ID、该折线点的索引、与之相应点在该图元的位置的索引

-------------------图元移动(折线随之移动)---------------------------------------
                   1.图元移动时(要去除折线),通过属性的Id找到该图元的折线
                   2.在通过属性找到折线点的索引、与之相应点在该图元的位置
                   3.修改折线该点的位置
*******************************************************/
#include "../BaseDraw/CZBaseTool.h"

class ItemFoldRegard : public CZBaseTool
{
    Q_OBJECT
public:
    explicit ItemFoldRegard(QObject *parent = 0);

    // CZBaseTool interface
    QString getClassName();
    void upDataTool(CZBase *item);

    void setEditItem(CZDRAW::EditStatus state, CZBase *item);

protected:
    void removeItem(CZBase *item);
    void addItem(CZBase *item);
signals:

public slots:

    void slot_MoveFoldLine(QString id,QString attrKey);
    // CZBaseTool interface
protected:
    bool itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    QVariant dealData(CZBase *item, void *pData);
private:
    //得到衔接的点集
    QList<QPointF> getJoinPoints(QVariantMap attr, QPainterPath path);

    //移动点
    void moveFoldPoint(CZBase *item,int index,QPointF pos, bool isSave = true);

    //移除旧的绑定
    void removeOldBind(CZBase *item,QString key,int foldIndex = -1);

    //移动折线
    void moveFoldLine(CZBase *item);

    CZBase*         m_CurCollItem;  //当前与折线碰撞的图元
    QList<QPointF>  m_JoinPoints;   //碰撞图元衔接的点集
    int             m_CurrentIndex; //当前的点
    bool            m_LeftPress;    //是否是右键按下
};

#endif // ITEMFOLDREGARD_H
