#include "SelectBound.h"
#include "../BaseDraw/CManagementItem.h"
#include "hfdefine.h"

SelectBound::SelectBound()
{

}

QString SelectBound::getClassName()
{
    return "SelectBound";
}

void SelectBound::upDataTool(CZBase *item)
{

}

void SelectBound::initTool()
{
    connect(m_ManagmentItem->scene(),SIGNAL(selectionChanged()),this,SLOT(slot_SelectChanged()));
}

void SelectBound::removeItem(CZBase *item)
{
    removeSelect(item);
}

void SelectBound::slot_SelectChanged()
{
    QList<CZBase* > selectItems = m_ManagmentItem->getSelects();
    foreach (CZBase *item, selectItems)
    {
        if(isBelong(item))
            addSelect(item);
    }
    QList<CZBase*> removeItems;
    for(int i=0; i < m_Rects.keys().size(); i++)
    {
        CZBase * re = m_Rects.keys().at(i);
        if(!selectItems.contains(re))
        {
            removeItems<<re;
        }
    }
    foreach (CZBase *item, removeItems)
    {
        removeSelect(item);
    }
}

void SelectBound::addSelect(CZBase *item)
{
    D_ISNULLR(item,);
    if(m_Rects.value(item))
    {
        QGraphicsRectItem* rectItem = (QGraphicsRectItem *)m_Rects.value(item);
        rectItem->setRect(item->boundingRect());
    }
    else
    {
        QGraphicsRectItem* rectItem = new QGraphicsRectItem(item);
        m_Rects.insert(item,rectItem);
        rectItem->setRect(item->boundingRect());
        QPen pen;
        pen.setStyle(Qt::DashLine);
        pen.setColor(Qt::blue);
        rectItem->setPen(pen);
    }
}

void SelectBound::removeSelect(CZBase *item)
{
    D_ISNULLR(item,);
    QGraphicsItem *rectItem = m_Rects.value(item);
    if(rectItem)
    {
        m_Rects.remove(item);
        item->scene()->removeItem(rectItem);
        D_Delete(rectItem);
    }
}
MYREGISTER(SelectBound)
