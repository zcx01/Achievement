#ifndef ZROTARYTOOL_H
#define ZROTARYTOOL_H

/*******************************************************
    created     :   2019/08/21
    file base	:   ZRotaryTool.h
    author      :   zcx
    purpose     :	旋转工具
*******************************************************/
#include "CZBaseTool.h"
#include <QTime>

class ZRotaryTool :public CZBaseTool
{
public:
    ZRotaryTool(QObject *parnet = NULL);


    // CZBaseTool interface
public:
    virtual QString getClassName();
    virtual void initTool();
    virtual void upDataTool(CZBase *item);

    // CZBaseTool interface
protected:
    virtual void addItem(CZBase *item);
    void removeItem(CZBase *item);
    virtual bool itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    virtual bool itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);
    virtual bool itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem);

private:
    void initData();

    //计算绕点的位置
    void axisPosType(CZBase *item);

    //计算位置
    void posType(CZBase *item);

    //翻转item
    void RotateItem(qreal angle);

    Qt::Axis                m_Axis;         //旋转的轴
    QPointF                 m_AxisPos;      //绕点
    int                     m_AxisPosType;  //绕点类型
    QString                 m_ItemId;       //特定的item的id
    bool                    m_WithChaged;   //跟item的位置改变而改变
    int                     m_PosType;      //位置类型
    QPointF                 m_Distance;     //距离
    CZBase*                 m_RotaryItem;   //旋转的item图片
    CZBase*                 m_Item;         //要旋转的item
    bool                    m_MousePress;   //鼠标是否按下
    QTime                   m_Time;  
};

#endif // ZROTARYTOOL_H
