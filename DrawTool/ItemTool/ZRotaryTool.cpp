#include "ZRotaryTool.h"
#include "CZStaticFun.h"
#include "ComputeGeometry.h"
#include "hfdefine.h"
#include "../DrawToolInclude/itemtooldefine.h"
#include <QGraphicsSceneMouseEvent>
#include "CManagementItem.h"

ZRotaryTool::ZRotaryTool(QObject *parnet) :CZBaseTool(parnet)
{
    initData();
}

QString ZRotaryTool::getClassName()
{
    return "ZRotaryTool";
}

void ZRotaryTool::initData()
{
    m_Axis = Qt::ZAxis;
    m_WithChaged = true;
    m_AxisPosType = 4;
    m_PosType = 8;
    m_MousePress = false;
    m_Item= NULL;
}

void ZRotaryTool::axisPosType(CZBase *item)
{
    D_ISNULLR(item,);
    m_AxisPos = CZStaticFun::castShowPoint(item->boundingRect(),QRectF(),m_AxisPosType);
    m_AxisPos+=item->pos();
}

void ZRotaryTool::posType(CZBase *item)
{
    D_ISNULLR(item,);
    D_ISNULLR(m_RotaryItem,);
    if(item == m_RotaryItem) return;

    //根据绕点和旋转item中心点位置角度和距离一样来计算，旋转item的位置
    QPointF pos= CZStaticFun::castShowPoint(item->boundingRect(),QRectF(),m_PosType);
    pos+=m_Distance;
    pos+=item->pos();
    m_RotaryItem->setPos(pos);
    QLineF standard(m_AxisPos,m_RotaryItem->mapToScene(m_RotaryItem->boundingRect().center()));
    int length = standard.length();
    QPointF newPos = ComputeGeometry::pointByDistance(m_AxisPos,length,item->rotation());
    m_RotaryItem->setPos(newPos - m_RotaryItem->boundingRect().center());


    //设置选择的角度
    m_RotaryItem->setTransformOriginPoint(m_RotaryItem/*->getThis()*/->boundingRect().center());
    m_RotaryItem->setRotation(item->rotation());
    m_RotaryItem->setZValue(item->zValue());
    m_Item = item;
}

void ZRotaryTool::RotateItem(qreal angle)
{
    //D_ISNULLR(m_ManagmentItem,;);
    CZBase *item  = NULL;
    if(m_ItemId.isEmpty())
    {
        item = m_Item;
    }
    else
    {
        item = m_ManagmentItem->getItemById(m_ItemId);
    }
    D_ISNULLR(item,;);
    QPointF axisPos = m_AxisPos -item->pos();
    item /*->getThis()*/->setTransformOriginPoint(axisPos);
    item->setRotation(angle);
    if(m_WithChaged && m_RotaryItem)
    {
//        m_RotaryItem->getThis()->setTransformOriginPoint(m_RotaryItem->getThis()->boundingRect().center());
//        m_RotaryItem->getThis()->setRotation(angle);
        posType(item);
    }
}

void ZRotaryTool::initTool()
{
    m_RotaryItem = getItemById(ZROTARYTOOLID);
    if(m_RotaryItem)
    {
        QVariantMap pDate = m_RotaryItem->getAttrs();
        m_ItemId = pDate.value(ITEMID).toString();
        m_Axis =(Qt::Axis)pDate.value(AXIS).toInt();
        m_AxisPosType = pDate.value(AXISPOSTYPE).toInt();
        m_WithChaged = pDate.value(WITHCHAGED).toBool();
        m_PosType = pDate.value(POSTYPE).toInt();
        m_Distance = CZStaticFun::QStringToQPointF(pDate.value(DISTANCE).toString());

        if(!m_ItemId.isEmpty())
        {
            CZBase *item = getItemById(m_ItemId);
            axisPosType(item);
            posType(item);
        }
    }
}

void ZRotaryTool::addItem(CZBase *item)
{
    D_ISNULLR(item,);
}

void ZRotaryTool::removeItem(CZBase *item)
{
    if(item == m_RotaryItem) m_RotaryItem =NULL;
    if(item == m_Item) m_Item =NULL;
}
bool ZRotaryTool::itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    if(sourceItem == m_RotaryItem)
    {
        m_MousePress = true;
    }
    else if(m_ItemId.isEmpty())
    {
        CZBase *item = dynamic_cast<CZBase *>(sourceItem);
        D_ISNULLR(item,false);
        //        if(!m_OperationItems.contains(item->getId())) return;
        axisPosType(item);
        posType(item);
    }
    return false;
}

bool ZRotaryTool::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    D_ISNULLR(sourceItem,false);
    if(m_ItemId.isEmpty())
    {
        CZBase *item = dynamic_cast<CZBase *>(sourceItem);
        D_ISNULLR(item,false);
        //if(!m_OperationItems.contains(item->getId())) return;
    }
    if(m_MousePress && sourceItem == m_RotaryItem)
    {
        QLineF line2(m_AxisPos,sourceItem->mapToScene(event->pos()));
        qreal angle =360-line2.angle();
        RotateItem(angle);
        return true;
    }
    return false;
}

bool ZRotaryTool::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    if(sourceItem == m_RotaryItem)
    {
        m_MousePress = false;
        return true;
    }
    return false;
}
MYREGISTER(ZRotaryTool)


void ZRotaryTool::upDataTool(CZBase *item)
{
}
