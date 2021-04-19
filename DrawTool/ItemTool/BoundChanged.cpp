#include "BoundChanged.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include "CManagementItem.h"
#include <QMouseEvent>
#include "hfdefine.h"
#include "../DrawToolInclude/itemtooldefine.h"
#define AMBIT 6
#define MIX 30

BoundChanged::BoundChanged(QObject *parent) : CZBaseTool(parent)
{
    m_IsMousePress = false;
    m_CurrentStyle = CursorNormal;
    m_TAssistLine = NULL;
    m_fAssistLine = NULL;
    m_ControlModifier = false;
}


QString BoundChanged::getClassName()
{
    return "BoundChanged";
}

void BoundChanged::upDataTool(CZBase *item)
{
}

void BoundChanged::initTool()
{
    m_fAssistLine = getItemById(VASSISTLINE);
    m_TAssistLine = getItemById(HASSISTLINE);
}

void BoundChanged::removeItem(CZBase *item)
{
    if(m_fAssistLine == item) m_fAssistLine =NULL;
    if(m_TAssistLine == item) m_TAssistLine =NULL;
}
bool BoundChanged::itemMousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    m_IsMousePress = true;
    return false;
}

bool BoundChanged::viewMouseMoveEvent(QMouseEvent *event)
{
    if(m_ManagmentItem->getEdit() != CZDRAW::NoEdit) return false;
    QList<QGraphicsItem *> clickItems = m_ManagmentItem->items(event->pos());
    foreach (QGraphicsItem * clickItem, clickItems)
    {
        CZBase * item = dynamic_cast<CZBase*>(clickItem);
        if(item && isBelong(item) && !m_IsMousePress
                && item->isContainMousePos(m_ManagmentItem->mapToScene(event->pos())))
        {
            setCursorStyle(item->mapFromScene(m_ManagmentItem->mapToScene(event->pos())),item);
            break;
        }
    }
    return false;
}
bool BoundChanged::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    if(m_ManagmentItem->getEdit() != CZDRAW::NoEdit) return false;
    CZBase * item = dynamic_cast<CZBase*>(sourceItem);
    if(m_IsMousePress)
    {
        if(m_CurrentStyle != CursorNormal)
        {
            m_ManagmentItem->removeSelect(item);
            castSize(m_CurrentStyle,event->pos(),item);
            return true;
        }
    }
    //    else
    //    {
    //        setCursorStyle(event->pos(),item);
    //    }
    return false;
}

bool BoundChanged::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
{
    m_IsMousePress = false;
    HideAssistLine();
    return false;
}

bool BoundChanged::itemKeyPressEvent(QKeyEvent *event, QGraphicsItem *sourceItem)
{
    if(event->modifiers()==Qt::ControlModifier)
    {
        m_ControlModifier = true;
    }
    switch (event->key())
    {
    case Qt::Key_Up:
        moveItem(sourceItem,QPointF(0, -2));  // 上移
        return true;
    case Qt::Key_Down:
        moveItem(sourceItem,QPointF(0, 2));  // 下移
        return true;
    case Qt::Key_Left:
        moveItem(sourceItem,QPointF(-2, 0));  // 左移
        return true;
    case Qt::Key_Right:
        moveItem(sourceItem,QPointF(2, 0));  // 右移
        return true;
    default:
        break;
    }
    return false;
}

bool BoundChanged::itemKeyReleaseEvent(QKeyEvent *event, QGraphicsItem *sourceItem)
{
    if(event->key()==Qt::Key_Control)
        m_ControlModifier =false;
    if(!m_ControlModifier)
    {
        HideAssistLine();
    }
    return false;
}
bool BoundChanged::itemFocusOutEvent(QFocusEvent *event, QGraphicsItem *sourceItem)
{
    HideAssistLine();
    return false;
}
void BoundChanged::setCursorStyle(const QPointF &curPoint,CZBase *item)
{
    int nCurWidth = item->boundingRect().width();
    int nCurHeight = item->boundingRect().height();

    CursorCtrlStyle nRes = CursorNormal;

    if(curPoint.x() <=AMBIT && curPoint.y() <=AMBIT)
    {
        item->setCursor(Qt::SizeFDiagCursor);
        nRes = CursorHorVerleftTop;
    }
    else if(nCurWidth -curPoint.x() <=AMBIT && nCurHeight - curPoint.y() <= AMBIT)
    {
        item->setCursor(Qt::SizeFDiagCursor);
        nRes = CursorHorVerRightDown;
    }
    else if (nCurWidth - curPoint.x() <= AMBIT && curPoint.y() <= AMBIT)
    {
        item->setCursor(Qt::SizeBDiagCursor);
        nRes = CurSorHorVerRightTop;
    }
    else if (nCurHeight - curPoint.y() <= AMBIT && curPoint.x() <= AMBIT)
    {
        item->setCursor(Qt::SizeBDiagCursor);
        nRes = CursorHorVerleftDow;
    }
    else if (curPoint.x() <= AMBIT)
    {
        item->setCursor(Qt::SizeHorCursor);
        nRes = Cursorleft;
    }
    else if (curPoint.y() <= AMBIT)
    {
        item->setCursor(Qt::SizeVerCursor);
        nRes = CursorTop;
    }
    else if(nCurHeight - curPoint.y() <= AMBIT)
    {
        item->setCursor(Qt::SizeVerCursor);
        nRes = CursorDowm;
    }
    else if(nCurWidth -curPoint.x() <=AMBIT )
    {
        item->setCursor(Qt::SizeHorCursor);
        nRes = CursorRight;
    }
    else
    {
        item->setCursor(Qt::ArrowCursor);
        nRes = CursorNormal;
    }
    m_CurrentStyle = nRes;
}

void BoundChanged::castSize(BoundChanged::CursorCtrlStyle cursorStyle,
                            const QPointF &curPoint, CZBase *item)
{
    qreal pWidth = item->boundingRect().width();
    qreal pHeight = item->boundingRect().height();
    qreal pX = item->pos().x();
    qreal pY = item->pos().y();
    switch (cursorStyle)
    {
    case CursorTop:
        pHeight -= curPoint.y();
        pY = item->mapToParent(curPoint).y();
        ShowAssistLine(0,pY,HTAssist,pWidth,pHeight,item);
        break;
    case CursorDowm:
        pHeight = curPoint.y();
        ShowAssistLine(0,pY+pHeight,HTAssist,pWidth,pHeight,item);
        break;
    case Cursorleft:
        pWidth -= curPoint.x();
        pX = item->mapToParent(curPoint).x();
        ShowAssistLine(pX,0,VFAssist,pWidth,pHeight,item);
        break;
    case CursorRight:
        pWidth = curPoint.x();
        ShowAssistLine(pX+pWidth,0,VFAssist,pWidth,pHeight,item);
        break;
    case CursorHorVerleftTop:
        pHeight -= curPoint.y();
        pWidth -= curPoint.x();
        pX = item->mapToParent(curPoint).x();
        pY = item->mapToParent(curPoint).y();
        ShowAssistLine(pX,pY,VHAssist,pWidth,pHeight,item);
        break;
    case CursorHorVerleftDow:
        pWidth -= curPoint.x();
        pHeight = curPoint.y();
        pX = item->mapToParent(curPoint).x();
        ShowAssistLine(pX,pY+pHeight,VHAssist,pWidth,pHeight,item);
        break;
    case CursorHorVerRightDown:
        pWidth = curPoint.x();
        pHeight = curPoint.y();
        ShowAssistLine(pX+pWidth,pY+pHeight,VHAssist,pWidth,pHeight,item);
        break;
    case CurSorHorVerRightTop:
        pWidth = curPoint.x();
        pHeight -= curPoint.y();
        pY = item->mapToParent(curPoint).y();
        ShowAssistLine(pX+pWidth,pY,VHAssist,pWidth,pHeight,item);
        break;
    default:
        break;
    }
    if(pHeight<MIX || pWidth <MIX)
    {
        return;
    }
    if(pHeight > MIX)
        item->setPos(pX,pY);
    item->setBounding(QRectF(item->boundingRect().x(),item->boundingRect().y(),pWidth,pHeight));
    item->sendAttrChanged(BOUNDRECT);
}

void BoundChanged::ShowAssistLine(qreal pos1, qreal pos2, ShowAssistTypes type, qreal w, qreal h, CZBase *item)
{
    D_ISNULLR(item,);
    if(w<MIX || h <MIX)
    {
        return;
    }
    if(type & VFAssist)
    {
        AssistLineChanged(m_fAssistLine,QPointF(pos1,0),0);
    }
    if(type & HTAssist)
    {
        AssistLineChanged(m_TAssistLine,QPointF(0,pos2),1);
    }
    if(type &VTAssist)
    {
        AssistLineChanged(m_TAssistLine,QPointF(pos2,0),0);
    }
    if(type &HFAssist)
    {
        AssistLineChanged(m_fAssistLine,QPointF(0,pos1),1);
    }
}

void BoundChanged::HideAssistLine()
{
    if(m_TAssistLine) m_TAssistLine->setVisible(false);
    if(m_fAssistLine) m_fAssistLine->setVisible(false);
}

void BoundChanged::AssistLineChanged(CZBase *assistLine,QPointF pos,int type)
{
    if(assistLine)
    {
        assistLine->setPos(pos);
        assistLine->show();
        assistLine->upDateData(type,false);
    }
}

void BoundChanged::moveItem(QGraphicsItem *item, QPointF pos)
{
    D_ISNULLR(item,);
    QPointF spos = item->pos();
    QPointF tPos = spos+pos;
    item->setPos(tPos);
    CZBase *cItem = dynamic_cast<CZBase *>(item);
    if(pos.x() == 0)
    {
        ShowAssistLine(tPos.y(),tPos.y()+item->boundingRect().height(),HHAssist
                       ,item->boundingRect().width(),
                       item->boundingRect().height(),cItem);
    }
    else
    {
        ShowAssistLine(tPos.x(),tPos.x()+item->boundingRect().width(),VVAssist
                       ,item->boundingRect().width(),
                       item->boundingRect().height(),cItem);
    }
}

MYREGISTER(BoundChanged)
