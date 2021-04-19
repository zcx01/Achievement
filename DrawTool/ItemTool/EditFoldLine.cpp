#include "EditFoldLine.h"
#include "hfdefine.h"
#include <QPointF>
#include <QMouseEvent>
#include "CManagementItem.h"
#include "../DrawToolInclude/commdefine.h"

EditFoldLine::EditFoldLine(QObject *parent) : CZBaseTool(parent)
{
    init(false);
}


QString EditFoldLine::getClassName()
{
    return "EditFoldLine";
}

void EditFoldLine::upDataTool(CZBase *item)
{
}

void EditFoldLine::removeItem(CZBase *item)
{
    if(m_CurrentItem == item)
    {
        m_CurrentItem = NULL;
    }
}

QVariant EditFoldLine::dealData(CZBase *item, void *pData)
{
    D_ISNULLR(item,false);
    QList<int>* tmp = (QList<int>*)pData;
    int hand =tmp->value(0);
    m_CurrentItem = item;
    switch (hand)
    {
    case Dr::Insert:
    {
        m_IsInsert =true;
        m_CurrentIndex = tmp->value(1);
    }
        break;
    case Dr::Delete:
    {
        DeletePoint(tmp->value(1));
    }
        break;
    default:
        break;
    }
    return true;
}

bool EditFoldLine::viewMousePressEvent(QMouseEvent *event)
{
    if(m_ManagmentItem->getEdit()!=CZDRAW::NoEdit)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(!isBelong(m_CurrentItem)) return false;
            QPointF pos = m_ManagmentItem->mapToScene(event->pos());
            //修改当前点(指令)
            AddOrModifyPoint(m_CurrentIndex,pos,Dr::Modify);
            //m_CurrentItem->sendAttrChanged(BOUNDRECT);

            //新增一个点
            m_IsAdd = true;
        }
        return true;
    }
    return false;
}

bool EditFoldLine::viewMouseReleaseEvent(QMouseEvent *event)
{
    //    m_PressLeft = false;
    return false;
}

bool EditFoldLine::viewMouseMoveEvent(QMouseEvent *event)
{
    if(m_ManagmentItem->getEdit() != CZDRAW::NoEdit/* && m_PressLeft*/)
    {
        D_ISNULLR(m_CurrentItem,false);
        if(!isBelong(m_CurrentItem)) return false;
        QPointF pos = m_ManagmentItem->mapToScene(event->pos());
        if(m_IsAdd)
        {
            //添加一个点(指令)
            AddOrModifyPoint(++m_CurrentIndex,pos,Dr::ADD);
            m_IsAdd =false;
            //m_CurrentIndex++;
            //            m_CurrentIndex = m_CurrentItem->getAttrs().value(FOLDPOINTS).toString().split(";").size()-1;
            //            if(m_CurrentIndex < 0 ) m_CurrentIndex++;
            return true;
        }

        //修改当前点，让最后一个变成动态点(指令)
        AddOrModifyPoint(m_CurrentIndex,pos,Dr::Modify);
    }
    return false;
}

void EditFoldLine::DeletePoint(int index)
{
    D_ISNULLR(m_CurrentItem,);
    QVariantMap order;
    order.insert(EDITSTATUS,(int)Dr::Delete);
    order.insert(FOLDCURINDEX,index);
    m_CurrentItem->upDateData(order,false);
}

void EditFoldLine::AddOrModifyPoint(int index, QPointF pos,int hand)
{
    D_ISNULLR(m_CurrentItem,);
    QVariantMap order;
    order.insert(EDITSTATUS,(int)hand);
    order.insert(FOLDCURINDEX,index);
    order.insert(FOLDCURPOINT,pos);
    m_CurrentItem->upDateData(order,false);
}

void EditFoldLine::init(bool isActiva)
{
    setToolActiva(isActiva);
    m_CurrentItem = NULL;
    m_CurrentIndex = -1;
    m_IsInsert = false;
    m_IsAdd =true;
}
void EditFoldLine::setEditItem(CZDRAW::EditStatus state, CZBase *item)
{
    if(state == CZDRAW::NoEdit)
    {
        D_ISNULLR(m_CurrentItem,);
        if(!m_IsInsert)
        {
            DeletePoint(m_CurrentIndex);
        }
        //ItemIsSelectable让item可以选中
        m_CurrentItem->setFlags(m_CurrentItem->flags() | QGraphicsItem::ItemIsSelectable);

        //把画好的数据压入属性中(指令)
        QVariantMap order;
        order.clear();
        order.insert(EDITSTATUS,(int)Dr::Save);
        m_CurrentItem->upDateData(order,false);
    }
    init(state);
    m_CurrentItem =item;

    if(state != CZDRAW::NoEdit)
    {
        D_ISNULLR(item,);
        QVariantMap attr = item->getAttrs();
        //如果设置
        if(!attr.value(FOLDCURINDEX).toString().isEmpty())
        {
            m_CurrentIndex = attr.value(FOLDCURINDEX).toInt();
            m_IsAdd = false;
        }
        else
        {
            //默认是最后一个点
            QStringList posList= attr.value(FOLDPOINTS).toString().split(";");
            int s = posList.size();
            if(s >= 1 && !posList.value(0).isEmpty() )
            {
                m_CurrentIndex = s -1;
            }
        }
    }
}
MYREGISTER(EditFoldLine)
