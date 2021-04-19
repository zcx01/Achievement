#include "ItemFoldRegard.h"
#include "../DrawToolInclude/commdefine.h"
#include "CZStaticFun.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "../DrawToolInclude/itemtooldefine.h"
#include "hfdefine.h"
#include "CManagementItem.h"


ItemFoldRegard::ItemFoldRegard(QObject *parent) : CZBaseTool(parent)
{
    m_CurCollItem = NULL;
    m_CurrentIndex = -1;
    m_LeftPress = false;
}


QString ItemFoldRegard::getClassName()
{
    return "ItemFoldRegard";
}

void ItemFoldRegard::upDataTool(CZBase *item)
{
}

void ItemFoldRegard::setEditItem(CZDRAW::EditStatus state, CZBase *item)
{
    if(state == CZDRAW::NewBulid && item)
    {
        item->setAttr(BINDFOLD,"");
    }
}

void ItemFoldRegard::removeItem(CZBase *item)
{
    removeOldBind(item,BEGPOINTID);
    removeOldBind(item,ENDPOINTID);
}

void ItemFoldRegard::addItem(CZBase *item)
{
    D_ISNULLR(item,);
    connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_MoveFoldLine(QString,QString)));
}

void ItemFoldRegard::slot_MoveFoldLine(QString id,QString attrKey)
{
    if(attrKey == POSX || attrKey==POSY)
    {
        CZBase *item = getItemById(id);
        D_ISNULLR(item,);
        moveFoldLine(item);
    }
}
bool ItemFoldRegard::itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    CZBase * item = dynamic_cast<CZBase*>(sourceItem);
    if(event->button() == Qt::LeftButton)
    {
        m_LeftPress = true;
    }
    else
    {
        m_LeftPress = false;
    }
    if(!m_ManagmentItem->getEdit() !=CZDRAW::NoEdit)
    {
        m_CurrentIndex = -1;
        if(item->getClassName() == "FoldLine")//判断是否是折线
        {
            QVariantMap order;
            order.insert(EDITSTATUS,(int)Dr::GetCurrentIndex);
            order.insert(FOLDCURPOINT,event->pos());
            item->upDateData(order,false);
            m_CurrentIndex = item->getDateData().toMap().value(FOLDCURINDEX).toInt();
            if(m_CurrentIndex !=-1)
            {
                return true;
            }
        }
    }
    return false;
}

bool ItemFoldRegard::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    CZBase * item = dynamic_cast<CZBase*>(sourceItem);
    if(item->getClassName() == "FoldLine") //判断是否是折线
    {
        //找到碰撞的图元
        m_CurCollItem = NULL;
        m_JoinPoints.isEmpty();
        QList<QGraphicsItem *> collItems =item->collidingItems(Qt::IntersectsItemShape);
        foreach(QGraphicsItem * cItem ,collItems)
        {
            CZBase *collItem = dynamic_cast<CZBase *> (cItem);
            //判断该图元是否属于本工具,碰撞的图元是否包含当前的鼠标上的点
            if(isBelong(collItem) && collItem->contains(collItem->mapFromScene(event->pos()))
                    && collItem->getClassName() !="FoldLine" )
            {

                //获取和画出该图元可以连线的点集
                m_CurCollItem = collItem;
                m_JoinPoints = getJoinPoints(collItem->getAttrs(),collItem->shape());
                //return true;
                break;
            }
        }
        if(m_CurrentIndex != -1 && m_LeftPress)
        {
            moveFoldPoint(item,m_CurrentIndex,event->pos());
            return true;
        }
    }
    else    //如果是碰撞图元移动的话
    {
        moveFoldLine(item);
    }
    return false;
}

bool ItemFoldRegard::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    m_LeftPress = false;
    CZBase * item = dynamic_cast<CZBase*>(sourceItem);
    //该图元是否是折线
    if(item->getClassName() == "FoldLine")
    {
        //获取折线的头与尾结点的坐标
        QVariantMap foldAttr = item->getAttrs();
        QStringList points = foldAttr.value(FOLDPOINTS).toString().split(JOIN);
        if(points.size() >= 2)
        {
            QPointF begPoint = item->mapToScene(CZStaticFun::QStringToQPointF(points.value(0)));
            QPointF endPoint = item->mapToScene(CZStaticFun::QStringToQPointF(points.value(points.size()-1)));

            //获取点击的{点与索引}
            QPointF nearPoint = begPoint;
            int     nearIndex = 0;
            QString oldKey  = BEGPOINTID;

            //移动是最后一个点
            if(m_CurrentIndex == points.size()-1)
            {
                nearPoint = endPoint;
                nearIndex = points.size()-1;
                oldKey = ENDPOINTID;
            }
            else if(m_CurrentIndex != 0)
            {
                return false;
            }
            //去除旧的绑定
            removeOldBind(item,oldKey,m_CurrentIndex);

            //判断是否有碰撞的图元、衔接的点集
            if(m_CurCollItem && !m_JoinPoints.isEmpty())
            {
                //获取近点与图元衔接的点集最近距离的{点与索引}
                QPointF nearJoin = m_CurCollItem->mapToItem(item,m_JoinPoints.at(0));
                int     nearJoinIndex = 0;
                for(int i =1; i <m_JoinPoints.size(); i++)
                {
                    QPointF joinPoint =m_CurCollItem->mapToItem(item,m_JoinPoints.at(i));
                    if(QLineF(nearPoint,nearJoin).length() > QLineF(nearPoint,joinPoint).length())
                    {
                        nearJoin = joinPoint;
                        nearJoinIndex = i;
                    }
                }

                //移动折线上的点
                moveFoldPoint(item,nearIndex,nearJoin);

                //!--------------------------保存相关属性到碰撞的图元中--------------------

                QStringList bindFoldStrings;
                bindFoldStrings<<item->getId()<<QString::number(nearIndex)
                              <<QString::number(nearJoinIndex);
                QString bindFoldString = bindFoldStrings.join(SJONIN);

                //生成新的绑定
                QString aBindFoldString = m_CurCollItem->getAttrs().value(BINDFOLD).toString();

                if(aBindFoldString.isEmpty())
                {
                    aBindFoldString = bindFoldString;
                }
                else
                {
                    aBindFoldString += ";"+ bindFoldString;
                }

                m_CurCollItem->setAttr(BINDFOLD,aBindFoldString);

                //在折线图元中保存点与碰撞图元的关系
                item->setAttr(oldKey,m_CurCollItem->getId());
            }
        }
    }
    return false;
}

QVariant ItemFoldRegard::dealData(CZBase *item, void *pData)
{
    if(pData == (void*)Dr::Find)
    {
        return m_CurrentIndex;
    }
    return -1;
}
QList<QPointF> ItemFoldRegard::getJoinPoints(QVariantMap attr, QPainterPath path)
{
    QList<QPointF> joinPoints;
    QString jointString = attr.value(JOINPOINTS).toString();

    //获取属性中有配置衔接点，如果没有这取默认
    if(!jointString.isEmpty())
    {
        QStringList points = jointString.split(JOIN);
        if(!points.isEmpty()&& jointString.contains(JOIN))
        {
            foreach (QString point, points)
            {
                joinPoints<<CZStaticFun::QStringToQPointF(point);
            }
        }
        else
        {
            QRectF rect = CZStaticFun::QStringToQRectF(attr.value(BOUNDRECT).toString());
            joinPoints = CZStaticFun::QStringToPointType(rect,jointString);
        }
    }
    else
    {
        joinPoints = path.toFillPolygon().toList();
    }

    return joinPoints;
}

void ItemFoldRegard::moveFoldPoint(CZBase *item, int index, QPointF pos, bool isSave)
{
    D_ISNULLR(item,);
    //移动折线的近点
    QVariantMap order;
    order.insert(FOLDCURINDEX,index);
    order.insert(EDITSTATUS,(int)Dr::Modify);
    order.insert(FOLDCURPOINT,pos);
    item->upDateData(order,false);

    if(isSave)
    {
        //保存到属性中
        QVariantMap saveOrder;
        saveOrder.insert(EDITSTATUS,(int)Dr::OnlySavePoint);
        item->upDateData(saveOrder,false);
    }
}

void ItemFoldRegard::removeOldBind(CZBase *item, QString key, int foldIndex)
{
    QVariantMap foldAttr = item->getAttrs();
    CZBase *oldBinItem = getItemById(foldAttr.value(key).toString());
    if(oldBinItem)
    {
        QStringList aBindFoldStrings =
                oldBinItem->getAttrs().value(BINDFOLD).toString().split(JOIN);

        QString s = item->getId();
        if(foldIndex != -1)
        {
            s += SJONIN+QString::number(foldIndex);
        }
        for(int i =0; i <aBindFoldStrings.size(); i++)
        {
            QString bindFold =  aBindFoldStrings.at(i);

            if(bindFold.startsWith(s))
            {
                aBindFoldStrings.removeAt(i);
            }
        }
        oldBinItem->setAttr(BINDFOLD,aBindFoldStrings.join(JOIN));
    }
}

void ItemFoldRegard::moveFoldLine(CZBase *item)
{
    QVariantMap collAttr = item->getAttrs();
    QList<QPointF> joinPoints = getJoinPoints(collAttr,item->shape());

    QStringList aBindFoldStrings =collAttr.value(BINDFOLD).toString().split(JOIN);

    for(int i =0; i <aBindFoldStrings.size() ;i++)
    {
        QStringList bindFoldStrings =  aBindFoldStrings.at(i).split(SJONIN);
        CZBase * foldItem = getItemById(bindFoldStrings.value(FOLDID));
        if(foldItem)
        {

            int foldIndex = bindFoldStrings.value(FOLDINDEX).toInt();
            int joinIndex = bindFoldStrings.value(FOLDJOININDEX).toInt();
            QPointF nearJoin =item->mapToItem(foldItem,joinPoints.value(joinIndex));
            //联动
            moveFoldPoint(foldItem,foldIndex,nearJoin);
        }
    }
}

MYREGISTER(ItemFoldRegard)
