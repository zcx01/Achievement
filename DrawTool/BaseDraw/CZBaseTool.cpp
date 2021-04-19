#include "CZBaseTool.h"
#include <QEvent>
#include <QGraphicsSceneEvent>
#include <QFocusEvent>
#define EVETDEFAULT return false;
bool CZBaseTool::itemSceneEventFilter(QGraphicsItem *watched, QEvent *event, QGraphicsItem *sourceItem)
{
    EVETDEFAULT
}

bool CZBaseTool::itemSceneEvent(QEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT
}

bool CZBaseTool::itemContextMenuEvent(QGraphicsSceneContextMenuEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemDragEnterEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemDragLeaveEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemDragMoveEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemDropEvent(QGraphicsSceneDragDropEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemFocusInEvent(QFocusEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemFocusOutEvent(QFocusEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemHoverEnterEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemHoverMoveEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemHoverLeaveEvent(QGraphicsSceneHoverEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemKeyPressEvent(QKeyEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemKeyReleaseEvent(QKeyEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemMousePressEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemMouseDoubleClickEvent(QGraphicsSceneMouseEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemWheelEvent(QGraphicsSceneWheelEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemInputMethodEvent(QInputMethodEvent *event,QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::itemInputMethodQuery(Qt::InputMethodQuery query,QGraphicsItem *sourceItem) const
{
    EVETDEFAULT;
}

bool CZBaseTool::itemItemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value, QGraphicsItem *sourceItem)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewEvent(QEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewCustomEvent(QEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewMousePressEvent(QMouseEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewMouseReleaseEvent(QMouseEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewMouseDoubleClickEvent(QMouseEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewMouseMoveEvent(QMouseEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewWheelEvent(QWheelEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewKeyPressEvent(QKeyEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewKeyReleaseEvent(QKeyEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewFocusInEvent(QFocusEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewFocusOutEvent(QFocusEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewEnterEvent(QEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewLeaveEvent(QEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewPaintEvent(QPaintEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewMoveEvent(QMoveEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewResizeEvent(QResizeEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewCloseEvent(QCloseEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewContextMenuEvent(QContextMenuEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewDragEnterEvent(QDragEnterEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewDragMoveEvent(QDragMoveEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewDragLeaveEvent(QDragLeaveEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewDropEvent(QDropEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewShowEvent(QShowEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewHideEvent(QHideEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewInputMethodEvent(QInputMethodEvent *event)
{
    EVETDEFAULT;
}

bool CZBaseTool::viewFocusNextPrevChild(bool next)
{
    EVETDEFAULT;
}

CZBaseTool::CZBaseTool(QObject *parnet):QObject(parnet)
{
    initData();
}

CZBaseTool::~CZBaseTool()
{
}

void CZBaseTool::setOperationItems(QList<CZBase *> items)
{
    foreach (CZBase *item, m_OperationItems.values())
    {
        removeItem(item);
    }
    m_OperationItems.clear();
    foreach (CZBase *item, items)
    {
        addOperationItem(item);
    }
}

void CZBaseTool::addOperationItem(CZBase *item)
{
    m_OperationItems.insert(item->getId(),item);
    addItem(item);
}

void CZBaseTool::removeOperationItem(CZBase *item)
{
    m_OperationItems.remove(item->getId());
    removeItem(item);
}

CZBase *CZBaseTool::getItemById(const QString &id)
{
    return m_OperationItems.value(id);
}

QList<CZBase *> CZBaseTool::getOperationItems()
{
    return m_OperationItems.values();
}

QVariant CZBaseTool::setDealData(CZBase *item, void *pData)
{
    return dealData(item,pData);
}

void CZBaseTool::setToolActiva(bool state)
{
    m_IsActiva = state;
}

bool CZBaseTool::getToolActiva()
{
    return m_IsActiva;
}

void CZBaseTool::setManagment(CManagementItem *managmentItem)
{
    m_ManagmentItem = managmentItem;
}

void CZBaseTool::initTool()
{
    QList<CZBase *> operationItems = getOperationItems();
    foreach (CZBase *item, operationItems)
    {
        upDataTool(item);
    }
}

void CZBaseTool::upDataTool(CZBase *item)
{

}

bool CZBaseTool::isBelong(CZBase *item)
{
    if(!item) return false;
    return m_OperationItems.contains(item->getId());
}

void CZBaseTool::setEditItem(CZDRAW::EditStatus state, CZBase *item)
{

}

void CZBaseTool::addItem(CZBase *item)
{

}

void CZBaseTool::removeItem(CZBase *item)
{

}

QVariant CZBaseTool::dealData(CZBase *item, void *pData)
{
    return QVariant();
}

QVariant CZBaseTool::dealMinData(CZBase *item, const QVariant &pData)
{
    return QVariant();
}

void CZBaseTool::initData()
{
    m_IsActiva = true;
}
