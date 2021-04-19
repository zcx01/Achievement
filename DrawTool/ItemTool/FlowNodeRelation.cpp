#include "FlowNodeRelation.h"
#include "hfdefine.h"
#include <QGraphicsScene>
#include "../DrawToolInclude/itemtooldefine.h"
#include "../DrawToolInclude/commdefine.h"
#include "../DrawToolInclude/zattrdefine.h"
#include "../BaseDraw/CZStaticFun.h"
#include "../BaseDraw/CManagementItem.h"
#include "../BaseDraw/czdrawstruct.h"
#include <QUuid>
#include <QDebug>

FlowNodeRelation::FlowNodeRelation()
{
    initData();
}

QString FlowNodeRelation::getClassName()
{
    return "FlowNodeRelation";
}

void FlowNodeRelation::upDataTool(CZBase *item)
{
    D_ISNULLR(item,);
}

void FlowNodeRelation::addItem(CZBase *item)
{
    D_ISNULLR(item,);
    if(item->getClassName() == "TimeScaleFrame")
    {
        m_TimeScale = item;
        connect(m_TimeScale,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_TimeShow(QString,QString)));
    }
    else if(item->getClassName() == "FlowTextGrid")
    {
        m_Grids.insert(item->getId(),item);
    }
    else
    {
        if(m_TimeScale && m_TimeScale->getAttrs().value(SizeChanged).toBool())
        {
            CalItemPos(item);
            InsertNode(item);
        }
        connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_PosChanged(QString,QString)));
    }
}

void FlowNodeRelation::removeItem(CZBase *item)
{
    D_ISNULLR(item,);
    if(m_TimeScale == item) m_TimeScale = NULL;
    m_Grids.remove(item->getId());

    //移除连线
    CZBase * polygon = m_RelationLines.value(item);
    if(polygon)
    {
        //D_Delete(polygon);
        m_RelationLines.remove(item);
    }
}

bool FlowNodeRelation::viewResizeEvent(QResizeEvent *event)
{

    return false;
}

void FlowNodeRelation::slot_TimeShow(QString id, QString attr)
{
    if(m_TimeScale && m_TimeScale->getId() == id && attr == SizeChanged)
    {
        CalAllItemPos();
    }
}

void FlowNodeRelation::slot_PosChanged(QString id, QString attr)
{
    CZBase * item = getItemById(id);
    D_ISNULLR(item,);
    if(attr == POSX || attr == POSY)
    {
        CalItemRelation(item);
    }
}

void FlowNodeRelation::initData()
{
    m_TimeScale = NULL;
}

void FlowNodeRelation::CalItemPos(CZBase *item)
{
    D_ISNULLR(item,);
    D_ISNULLR(m_TimeScale,);
    QVariantMap attrs = item->getAttrs();
    CZBase * grid = m_Grids.value(attrs.value(F_FlowName).toString());
    D_ISNULLR(grid,);
    SetParentItem(item,grid);

    //设置位置
    QVariantMap order;
    order.insert(F_GetPosType,(int)Dr::TimeScaleWidth);
    order.insert(F_NodeSTime,attrs.value(F_NodeSTime));
    order.insert(F_NodeETime,attrs.value(F_NodeETime));
    m_TimeScale->upDateData(order,false);
    double x = m_TimeScale->getDateData().toMap().value(F_NodeX).toDouble();
    double w = m_TimeScale->getDateData().toMap().value(F_NodeW).toDouble();

    order.clear();
    order.insert(F_GetPosType,(int)Dr::GridHeight);
    order.insert(F_PlatformName,attrs.value(F_PlatformName));
    grid->upDateData(order,false);
    double y = grid->getDateData().toMap().value(F_NodeY).toDouble();
    double h = grid->getDateData().toMap().value(F_NodeH).toDouble();
    item->setPos(PosCover(item,QPointF(x,y)));
    item->setBounding(QRectF(item->boundingRect().topLeft(),QSize(w,h)));
    item->sendAttrChanged(BOUNDRECT);

}

void FlowNodeRelation::CalAllItemPos()
{
    QList<CZBase*>  items = GetNodeItems();
    foreach (CZBase* item, items)
    {
        CalItemPos(item);
    }

    //    foreach (CZBase* item, items)
    //    {
    //        AutoCalPreNode(item);
    //    }
}

void FlowNodeRelation::CalItemRelation(CZBase *item)
{
    D_ISNULLR(item,);
    QVariantMap attrs = item->getAttrs();
    CZBase *preItem = getItemById(attrs.value(F_NodePreId).toString());
    D_ISNULLR(preItem,);

    CZBase *foldLine = m_RelationLines.value(item);
    bool isAdd = false;
    if(!foldLine)
    {
        //创建折线
        QString id = QUuid::createUuid().toString();
        QVariantMap attr;
        attr.insert(IDD,id);
        attr.insert(FOLDARROWSSTYLE,"NoSealTriangle");
        attr.insert(FOLDANODESTYLE,"NoNodeStyle");
        attr.insert(ITEMCLASSNAME,"FoldLine");
        attr.insert(FOLDDEFAULT,false);
        attr.insert(FOLDPOINTRANGE,10);
        m_ManagmentItem->SendCreateItem(attr);
        foldLine = m_ManagmentItem->getItemById(id);
        m_RelationLines.insert(item,foldLine);
        if(!item->parentItem())
        {
            CZBase * grid = m_Grids.value(attrs.value(F_FlowName).toString());
            SetParentItem(item,grid);
        }
        foldLine->setParentItem(item->parentItem());
        isAdd = true;
    }
    D_ISNULLR(foldLine,);
    int posIndex = 0;

    //设置折线的点
    if(item->boundingRect().isEmpty())
    {
        CalItemPos(item);
    }

    QPointF ePos = item->mapToScene(CZStaticFun::castRectPoint(item->boundingRect(),CZStaticFun::LeftCenter));
    if(preItem->pos().y() != item->pos().y())     //不在一个平台下
    {
        if(preItem->boundingRect().isEmpty())
        {
            CalItemPos(preItem);
        }
        QPointF sPos = preItem->mapToScene(CZStaticFun::castRectPoint(preItem->boundingRect(),
                                                                      preItem->pos().y() > item->pos().y() ?
                                                                          CZStaticFun::TopCenter : CZStaticFun::DownCenter));
        QPointF mPos(sPos.x(),ePos.y());

        //计算是否碰撞、开始点是否被使用
        if(foldIsNodeIn(PosCover(foldLine,sPos),item) || nodePosIsUse(preItem,sPos))
        {
            sPos = preItem->mapToScene(CZStaticFun::castRectPoint(preItem->boundingRect(), CZStaticFun::RightCenter));
            ePos = item->mapToScene(CZStaticFun::castRectPoint(item->boundingRect(),
                                                               preItem->pos().y() < item->pos().y() ?
                                                                   CZStaticFun::TopCenter : CZStaticFun::DownCenter));
            mPos = QPointF(ePos.x(),sPos.y());
        }
        SendFoldPos(sPos,posIndex,foldLine,isAdd);
        SendFoldPos(mPos,++posIndex,foldLine,isAdd);
    }
    else
    {
        QPointF sPos = preItem->mapToScene(CZStaticFun::castRectPoint(preItem->boundingRect(),CZStaticFun::RightCenter));
        SendFoldPos(sPos,posIndex,foldLine,isAdd);
    }
    SendFoldPos(ePos,++posIndex,foldLine,isAdd);
}

void FlowNodeRelation::SendFoldPos(const QPointF &pos, int index, CZBase * item,const bool &isAdd)
{
    D_ISNULLR(item,);
    Dr::EditFoldType type = isAdd ? Dr::ADD :Dr::Modify;
    QVariantMap order;
    order.insert(EDITSTATUS,(int)type);
    order.insert(FOLDCURINDEX,index);
    order.insert(FOLDCURPOINT,PosCover(item,pos));
    item->upDateData(order,false);
}

void FlowNodeRelation::SetParentItem(CZBase *item,CZBase *grid)
{
    D_ISNULLR(grid,);
    if(item->parentItem()) return;
    Dr::GetPosType type = Dr::SetParentItem;
    QVariantMap order;
    order.insert(F_GetPosType,(int)type);
    QVariant data;
    data.setValue(item);
    order.insert(F_NodeParent,data);
    grid->upDateData(order,false);
}

QPointF FlowNodeRelation::PosCover(CZBase *item, QPointF pos)
{
    return item->mapToParent(item->mapFromScene(pos));
}

void FlowNodeRelation::AutoCalPreNode(CZBase *item)
{
    QVariantMap attrs = item->getAttrs();
    QString preItemId = attrs.value(F_NodePreId).toString();
    if(!preItemId.isEmpty()) return;
    double sTime = attrs.value(F_NodeSTime).toDouble(); //得到开始的时间
    CZBase *preItem = NULL;
    CZBase *nextItem = NULL;
    QList<CZBase *> operatorItems = GetNodeItems();
    operatorItems.removeOne(item);
    //std::sort(operatorItems.begin(),operatorItems.end(),ItemBySTime);
    bool isLast = true;
    for(int i =0 ; i < operatorItems.size(); i++)
    {
        CZBase* oItem = operatorItems.at(i);
        if(oItem->getAttrs().value(F_NodeSTime).toDouble() > sTime)
        {
            preItem = operatorItems.value(i-1,NULL);
            nextItem = oItem;
            isLast = false;
            break;
        }
    }
    if(!preItem && isLast) preItem = operatorItems.value(operatorItems.size() - 1);
    InsertNode(preItem,item,nextItem);
}

void FlowNodeRelation::InsertNode(CZBase *item)
{
    D_ISNULLR(item,);
    CZBase* preItem = getItemById(item->getAttrs().value(F_NodePreId).toString());
    QList<CZBase* > nodeItems = GetNodeItems();
    CZBase* nextItem = NULL;
    foreach (CZBase *nodeItem, nodeItems)
    {
        if(nodeItem->getAttrs().value(F_NodeETime).toString() == item->getAttrs().value(F_NodePreId).toString())
        {
            nextItem = nodeItem;
            break;
        }
    }
    InsertNode(preItem,item,nextItem);
}

void FlowNodeRelation::InsertNode(CZBase *preItem, CZBase *item, CZBase *nextItem)
{
    if(!preItem) return;
    item->setAttr(F_NodePreId,preItem->getId());
    if(nextItem)
    {
        nextItem->setAttr(F_NodePreId,item->getId());
        delete m_RelationLines.value(nextItem);
        m_RelationLines.remove(nextItem); //移除关系线
    }
    CalItemRelation(item);
    CalItemRelation(nextItem);
}

bool FlowNodeRelation::foldIsNodeIn(const QPointF &pos,CZBase *except)
{
    QList<CZBase *> nodeItems = GetNodeItems();
    nodeItems.removeOne(except);
    //bool isDown = except->pos().y() > pos.y();  //是否值判断在pos下方图元

    double minY = qMin(except->pos().y(),pos.y());
    double maxY = qMax(except->pos().y(),pos.y());
    bool isDown = false;
    if(minY == pos.y()) //在下面
    {
        maxY = except->pos().y()+except->boundingRect().width();
        isDown = true;
    }
    foreach (CZBase* item, nodeItems)
    {
        //qDebug()<<minY<<maxY<<item->boundingRect()<<item->pos()<<pos<<"dddddfff ";
        double Y = isDown ? item->pos().y() : item->pos().y() + item->boundingRect().height();
        if(minY < Y && Y < maxY)
        {
            if(item->pos().x() < pos.x() && pos.x() < item->pos().x()+item->boundingRect().width())
            {
                return true;
            }
        }

    }
    return false;
}

bool FlowNodeRelation::nodePosIsUse(CZBase *item, const QPointF &pos)
{
    CZBase *foldLine = m_RelationLines.value(item);
    D_ISNULLR(foldLine,false);
    QVariantMap order;
    order.insert(EDITSTATUS,(int)Dr::GetCurrentIndex);
    order.insert(FOLDCURPOINT,pos);
    foldLine->upDateData(order,false);
    int Index = foldLine->getDateData().toMap().value(FOLDCURINDEX).toInt();
    return Index != -1;
}

QList<CZBase *> FlowNodeRelation::GetNodeItems()
{
    QList<CZBase *> operatorItems = getOperationItems();
    operatorItems.removeOne(m_TimeScale);
    QList<CZBase *> grids = m_Grids.values();
    foreach (CZBase *g, grids)
    {
        operatorItems.removeOne(g);
    }
    std::sort(operatorItems.begin(),operatorItems.end(),ItemBySTime);
    return operatorItems;
}

bool FlowNodeRelation::ItemBySTime(CZBase *f, CZBase *t)
{
    return f->getAttrs().value(F_NodeSTime).toDouble() < t->getAttrs().value(F_NodeSTime).toDouble();
}

MYREGISTER(FlowNodeRelation)
