#include "EditBoundItemTool.h"
#include "CManagementItem.h"
#include "hfdefine.h"
#include <QPointF>
#include <QMouseEvent>
#include "CZStaticFun.h"

EditBoundItemTool::EditBoundItemTool(QObject *parent) : CZBaseTool(parent)
{
    init(false);
}

QString EditBoundItemTool::getClassName()
{
    return "EditBoundItemTool";
}

void EditBoundItemTool::upDataTool(CZBase *item)
{
}

void EditBoundItemTool::setEditItem(CZDRAW::EditStatus state, CZBase *item)
{
    init(state != CZDRAW::NoEdit);
    m_CurrentItem =item;
}

void EditBoundItemTool::removeItem(CZBase *item)
{
    init(false);
}

bool EditBoundItemTool::viewMousePressEvent(QMouseEvent *event)
{
    if(m_ManagmentItem->getEdit() != CZDRAW::NoEdit && event->button() == Qt::LeftButton)
    {
        D_ISNULLR(m_CurrentItem,false);
        if(!isBelong(m_CurrentItem)) return false;
        //m_CurrentItem->upDateData(QRect(),false);
        if(m_ManagmentItem->getEdit() == CZDRAW::NewBulid)
        {
            QPointF pos = m_ManagmentItem->mapToScene(event->pos());
            m_CurrentItem->setPos(pos);
        }
        m_PressLeft = true;
        return true;
    }
    return false;
}

bool EditBoundItemTool::viewMouseReleaseEvent(QMouseEvent *event)
{
    //    m_ManagmentItem->setEdit(false);
    //    D_ISNULLR(m_CurrentItem,false);
    //    m_CurrentItem->sendAttrChanged(EDITEND);
    //m_PressLeft = false;
    return false;
}

bool EditBoundItemTool::viewMouseMoveEvent(QMouseEvent *event)
{
    if(m_ManagmentItem->getEdit()!=CZDRAW::NoEdit)
    {
        D_ISNULLR(m_CurrentItem,false);
        if(!isBelong(m_CurrentItem)) return false;

        QPointF pos = m_ManagmentItem->mapToScene(event->pos());
        if(m_ManagmentItem->getEdit() == CZDRAW::NewBulid && !m_PressLeft)
        {
            QRectF rect(0,0,20,20);
            m_CurrentItem->setPos(pos-rect.center());
            m_CurrentItem->setBounding(rect);
            return false;
        }
        if(CompPoint(pos,m_CurrentItem->pos()))
        {
            QPointF dis = m_ManagmentItem->mapToScene(event->pos()) - m_CurrentItem->pos();
            QRectF rect(0,0,dis.x()+5,dis.y()+5);
            m_CurrentItem->setBounding(rect);
            //m_CurrentItem->setPos(rect.center()+m_CurrentItem->pos());
            m_CurrentItem->sendAttrChanged(BOUNDRECT);
            return true;
        }
    }
    return false;
}

void EditBoundItemTool::init(bool isActiva)
{
    m_CurrentItem = NULL;
    m_PressLeft =false;
    setToolActiva(isActiva);
}


bool EditBoundItemTool::CompPoint(QPointF p1, QPointF p2)
{
    if(p1.x() > p2.x() && p1.y() > p2.y())
        return true;
    return false;
}

MYREGISTER(EditBoundItemTool)

