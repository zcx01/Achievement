#include "DataTransmit.h"
#include "hfdefine.h"
#include <QGraphicsSceneEvent>
QHash<QString,CManagementTool*> DataTransmit::m_ManagementTool;
SceneEventFilter                DataTransmit::m_SceneEventFilter = NULL;
SceneEvent                      DataTransmit::m_SceneEvent=NULL;
ContextMenuEvent                DataTransmit::m_ContextMenuEvent=NULL;
DragEnterEvent                  DataTransmit::m_DragEnterEvent=NULL;
DragLeaveEvent                  DataTransmit::m_DragLeaveEvent=NULL;
DragMoveEvent                   DataTransmit::m_DragMoveEvent=NULL;
DropEvent                       DataTransmit::m_DropEvent=NULL;
FocusInEvent                    DataTransmit::m_FocusInEvent=NULL;
FocusOutEvent                   DataTransmit::m_FocusOutEvent=NULL;
HoverEnterEvent                 DataTransmit::m_HoverEnterEvent=NULL;
HoverMoveEvent                  DataTransmit::m_HoverMoveEvent=NULL;
HoverLeaveEvent                 DataTransmit::m_HoverLeaveEvent=NULL;
KeyPressEvent                   DataTransmit::m_KeyPressEvent=NULL;
KeyReleaseEvent                 DataTransmit::m_KeyReleaseEvent=NULL;
MousePressEvent                 DataTransmit::m_MousePressEvent=NULL;
MouseMoveEvent                  DataTransmit::m_MouseMoveEvent=NULL;
MouseReleaseEvent               DataTransmit::m_MouseReleaseEvent=NULL;
MouseDoubleClickEvent           DataTransmit::m_MouseDoubleClickEvent=NULL;
WheelEvent                      DataTransmit::m_WheelEvent=NULL;
InputMethodEvent                DataTransmit::m_InputMethodEvent=NULL;
ItemChange                      DataTransmit::m_ItemChange=NULL;


ViewEvent                       DataTransmit::m_ViewEvent      =NULL;
ViewCustomEvent                 DataTransmit::m_ViewCustomEvent=NULL;
ViewMousePressEvent             DataTransmit::m_ViewMousePressEvent      =NULL;
ViewMouseReleaseEvent           DataTransmit::m_ViewMouseReleaseEvent    =NULL;
ViewMouseDoubleClickEvent       DataTransmit::m_ViewMouseDoubleClickEvent=NULL;
ViewMouseMoveEvent              DataTransmit::m_ViewMouseMoveEvent       =NULL;
ViewWheelEvent                  DataTransmit::m_ViewWheelEvent           =NULL;
ViewKeyPressEvent               DataTransmit::m_ViewKeyPressEvent        =NULL;
ViewKeyReleaseEvent             DataTransmit::m_ViewKeyReleaseEvent      =NULL;
ViewFocusInEvent                DataTransmit::m_ViewFocusInEvent         =NULL;
ViewFocusOutEvent               DataTransmit::m_ViewFocusOutEvent        =NULL;
ViewEnterEvent                  DataTransmit::m_ViewEnterEvent           =NULL;
ViewLeaveEvent                  DataTransmit::m_ViewLeaveEvent           =NULL;
ViewPaintEvent                  DataTransmit::m_ViewPaintEvent           =NULL;
ViewMoveEvent                   DataTransmit::m_ViewMoveEvent            =NULL;
ViewResizeEvent                 DataTransmit::m_ViewResizeEvent          =NULL;
ViewCloseEvent                  DataTransmit::m_ViewCloseEvent           =NULL;
ViewContextMenuEvent            DataTransmit::m_ViewContextMenuEvent     =NULL;
ViewDragEnterEvent              DataTransmit::m_ViewDragEnterEvent       =NULL;
ViewDragMoveEvent               DataTransmit::m_ViewDragMoveEvent        =NULL;
ViewDragLeaveEvent              DataTransmit::m_ViewDragLeaveEvent       =NULL;
ViewDropEvent                   DataTransmit::m_ViewDropEvent            =NULL;
ViewShowEvent                   DataTransmit::m_ViewShowEvent            =NULL;
ViewHideEvent                   DataTransmit::m_ViewHideEvent            =NULL;
ViewInputMethodEvent            DataTransmit::m_ViewInputMethodEvent     =NULL;
ViewFocusNextPrevChild          DataTransmit::m_ViewFocusNextPrevChild   =NULL;

DataTransmit::DataTransmit()
{

}

bool DataTransmit::itemSceneEventFilter(QGraphicsItem *watched, QEvent *event, CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_SceneEventFilter,false);
    return (*m_SceneEventFilter)(watched,event,sourceItem,managementTool);
}

bool DataTransmit::itemSceneEvent(QEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_SceneEvent,false);
    return (*m_SceneEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemContextMenuEvent(QGraphicsSceneContextMenuEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ContextMenuEvent,false);
    return (*m_ContextMenuEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemDragEnterEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_DragEnterEvent,false);
    return (*m_DragEnterEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemDragLeaveEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_DragLeaveEvent,false);
    return (*m_DragLeaveEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemDragMoveEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_DragMoveEvent,false);
    return (*m_DragMoveEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemDropEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_DropEvent,false);
    return (*m_DropEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemFocusInEvent(QFocusEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_FocusInEvent,false);
    return (*m_FocusInEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemFocusOutEvent(QFocusEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_FocusOutEvent,false);
    return (*m_FocusOutEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemHoverEnterEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_HoverEnterEvent,false);
    return (*m_HoverEnterEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemHoverMoveEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_HoverMoveEvent,false);
    return (*m_HoverMoveEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemHoverLeaveEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_HoverLeaveEvent,false);
    return (*m_HoverLeaveEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemKeyPressEvent(QKeyEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_KeyPressEvent,false);
    return (*m_KeyPressEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemKeyReleaseEvent(QKeyEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_KeyReleaseEvent,false);
    return (*m_KeyReleaseEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemMousePressEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_MousePressEvent,false);
    return (m_MousePressEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_MouseMoveEvent,false);
    return (*m_MouseMoveEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_MouseReleaseEvent,false);
    return (*m_MouseReleaseEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemMouseDoubleClickEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_MouseDoubleClickEvent,false);
    return (*m_MouseDoubleClickEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemWheelEvent(QGraphicsSceneWheelEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_WheelEvent,false);
    return (*m_WheelEvent)(event,sourceItem,managementTool);
}

bool DataTransmit::itemInputMethodEvent(QInputMethodEvent *event,CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_InputMethodEvent,false);
    return (*m_InputMethodEvent)(event,sourceItem,managementTool);
}
bool DataTransmit::itemItemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value, CZBase *sourceItem,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ItemChange,false);
    return (*m_ItemChange)(change,value,sourceItem,managementTool);
}

void DataTransmit::addManagementTool(QString id, CManagementTool *tool)
{
    m_ManagementTool.insert(id,tool);
}

void DataTransmit::removeManagementTool(QString id)
{
    m_ManagementTool.remove(id);
}

void DataTransmit::setSceneEventFilter(SceneEventFilter sceneEventFilter)
{
    m_SceneEventFilter =sceneEventFilter;
}

void DataTransmit::setSceneEvent(SceneEvent sceneEvent)
{
    m_SceneEvent =sceneEvent;
}

void DataTransmit::setContextMenuEvent(ContextMenuEvent contextMenuEvent)
{
    m_ContextMenuEvent =contextMenuEvent;
}

void DataTransmit::setDragEnterEvent(DragEnterEvent dragEnterEvent)
{
    m_DragEnterEvent =dragEnterEvent;
}

void DataTransmit::setDragLeaveEvent(DragLeaveEvent dragLeaveEvent)
{
    m_DragLeaveEvent =dragLeaveEvent;
}

void DataTransmit::setDragMoveEvent(DragMoveEvent dragMoveEvent)
{
    m_DragMoveEvent =dragMoveEvent;
}

void DataTransmit::setDropEvent(DropEvent dropEvent)
{
    m_DropEvent =dropEvent;
}

void DataTransmit::setFocusInEvent(FocusInEvent focusInEvent)
{
    m_FocusInEvent =focusInEvent;
}

void DataTransmit::setFocusOutEvent(FocusOutEvent focusOutEvent)
{
    m_FocusOutEvent =focusOutEvent;
}

void DataTransmit::setHoverEnterEvent(HoverEnterEvent hoverEnterEvent)
{
    m_HoverEnterEvent =hoverEnterEvent;
}

void DataTransmit::setHoverMoveEvent(HoverMoveEvent hoverMoveEvent)
{
    m_HoverMoveEvent =hoverMoveEvent;
}

void DataTransmit::setHoverLeaveEvent(HoverLeaveEvent hoverLeaveEvent)
{
    m_HoverLeaveEvent =hoverLeaveEvent ;
}

void DataTransmit::setKeyPressEvent(KeyPressEvent keyPressEvent)
{
    m_KeyPressEvent =keyPressEvent;
}

void DataTransmit::setKeyReleaseEvent(KeyReleaseEvent keyReleaseEvent)
{
    m_KeyReleaseEvent =keyReleaseEvent;
}

void DataTransmit::setMousePressEvent(MousePressEvent mousePressEvent)
{
    m_MousePressEvent =mousePressEvent;
}

void DataTransmit::setMouseMoveEvent(MouseMoveEvent mouseMoveEvent)
{
    m_MouseMoveEvent =mouseMoveEvent;
}

void DataTransmit::setMouseReleaseEvent(MouseReleaseEvent mouseReleaseEvent)
{
    m_MouseReleaseEvent =mouseReleaseEvent;
}

void DataTransmit::setMouseDoubleClickEvent(MouseDoubleClickEvent mouseDoubleClickEvent)
{
    m_MouseDoubleClickEvent =mouseDoubleClickEvent;
}

void DataTransmit::setWheelEvent(WheelEvent wheelEvent)
{
    m_WheelEvent =wheelEvent;
}

void DataTransmit::setInputMethodEvent(InputMethodEvent inputMethodEvent)
{
    m_InputMethodEvent =inputMethodEvent;
}

void DataTransmit::setItemChange(ItemChange itemChange)
{
    m_ItemChange =itemChange;
}

bool DataTransmit::viewEvent(QEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewEvent,false);
    return  (*m_ViewEvent)(event,managementTool);
}

bool DataTransmit::viewCustomEvent(QEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewCustomEvent,false);
     return (*m_ViewCustomEvent)(event,managementTool);
}

bool DataTransmit::viewMousePressEvent(QMouseEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewMousePressEvent,false);
     return (*m_ViewMousePressEvent)(event,managementTool);
}

bool DataTransmit::viewMouseReleaseEvent(QMouseEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewMouseReleaseEvent,false);
     return (*m_ViewMouseReleaseEvent)(event,managementTool);
}

bool DataTransmit::viewMouseDoubleClickEvent(QMouseEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewMouseDoubleClickEvent,false);
     return (*m_ViewMouseDoubleClickEvent)(event,managementTool);
}

bool DataTransmit::viewMouseMoveEvent(QMouseEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewMouseMoveEvent,false);
     return (*m_ViewMouseMoveEvent)(event,managementTool);
}

bool DataTransmit::viewWheelEvent(QWheelEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewWheelEvent,false);
     return (*m_ViewWheelEvent)(event,managementTool);
}

bool DataTransmit::viewKeyPressEvent(QKeyEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewKeyPressEvent,false);
     return (*m_ViewKeyPressEvent)(event,managementTool);
}

bool DataTransmit::viewKeyReleaseEvent(QKeyEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewKeyReleaseEvent,false);
     return (*m_ViewKeyReleaseEvent)(event,managementTool);
}

bool DataTransmit::viewFocusInEvent(QFocusEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewFocusInEvent,false);
     return (*m_ViewFocusInEvent)(event,managementTool);
}

bool DataTransmit::viewFocusOutEvent(QFocusEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewFocusOutEvent,false);
     return (*m_ViewFocusOutEvent)(event,managementTool);
}

bool DataTransmit::viewEnterEvent(QEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewEnterEvent,false);
     return (*m_ViewEnterEvent)(event,managementTool);
}

bool DataTransmit::viewLeaveEvent(QEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewLeaveEvent,false);
     return (*m_ViewLeaveEvent)(event,managementTool);
}

bool DataTransmit::viewPaintEvent(QPaintEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewPaintEvent,false);
     return (*m_ViewPaintEvent)(event,managementTool);
}

bool DataTransmit::viewMoveEvent(QMoveEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewMoveEvent,false);
     return (*m_ViewMoveEvent)(event,managementTool);
}

bool DataTransmit::viewResizeEvent(QResizeEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewResizeEvent,false);
     return (*m_ViewResizeEvent)(event,managementTool);
}

bool DataTransmit::viewCloseEvent(QCloseEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewCloseEvent,false);
     return (*m_ViewCloseEvent)(event,managementTool);
}

bool DataTransmit::viewContextMenuEvent(QContextMenuEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewContextMenuEvent,false);
     return (*m_ViewContextMenuEvent)(event,managementTool);
}

bool DataTransmit::viewDragEnterEvent(QDragEnterEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewDragEnterEvent,false);
     return (*m_ViewDragEnterEvent)(event,managementTool);
}

bool DataTransmit::viewDragMoveEvent(QDragMoveEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewDragMoveEvent,false);
     return (*m_ViewDragMoveEvent)(event,managementTool);
}

bool DataTransmit::viewDragLeaveEvent(QDragLeaveEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewDragLeaveEvent,false);
     return (*m_ViewDragLeaveEvent)(event,managementTool);
}

bool DataTransmit::viewDropEvent(QDropEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewDropEvent,false);
     return (*m_ViewDropEvent)(event,managementTool);
}

bool DataTransmit::viewShowEvent(QShowEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewShowEvent,false);
     return (*m_ViewShowEvent)(event,managementTool);
}

bool DataTransmit::viewHideEvent(QHideEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewHideEvent,false);
     return (*m_ViewHideEvent)(event,managementTool);
}

bool DataTransmit::viewInputMethodEvent(QInputMethodEvent *event,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewInputMethodEvent,false);
     return (*m_ViewInputMethodEvent)(event,managementTool);
}

bool DataTransmit::viewFocusNextPrevChild(bool next,QString eventId)
{
    CManagementTool *managementTool = m_ManagementTool.value(eventId);
    D_ISNULLR(m_ViewFocusNextPrevChild,false);
    return (*m_ViewFocusNextPrevChild)(next,managementTool);
}

void DataTransmit::setViewEvent(ViewEvent viewEvent)
{
    m_ViewEvent = viewEvent;
}

void DataTransmit::setViewCustomEvent(ViewCustomEvent viewCustomEvent)
{
    m_ViewCustomEvent = viewCustomEvent;
}

void DataTransmit::setViewMousePressEvent(ViewMousePressEvent viewMousePressEvent)
{
    m_ViewMousePressEvent = viewMousePressEvent;
}

void DataTransmit::setViewMouseReleaseEvent(ViewMouseReleaseEvent viewMouseReleaseEvent)
{
    m_ViewMouseReleaseEvent = viewMouseReleaseEvent;
}

void DataTransmit::setViewMouseDoubleClickEvent(ViewMouseDoubleClickEvent viewMouseDoubleClickEvent)
{
    m_ViewMouseDoubleClickEvent = viewMouseDoubleClickEvent;
}

void DataTransmit::setViewMouseMoveEvent(ViewMouseMoveEvent viewMouseMoveEvent)
{
    m_ViewMouseMoveEvent = viewMouseMoveEvent;
}

void DataTransmit::setViewWheelEvent(ViewWheelEvent viewWheelEvent)
{
    m_ViewWheelEvent = viewWheelEvent;
}

void DataTransmit::setViewKeyPressEvent(ViewKeyPressEvent viewKeyPressEvent)
{
    m_ViewKeyPressEvent = viewKeyPressEvent;
}

void DataTransmit::setViewKeyReleaseEvent(ViewKeyReleaseEvent viewKeyReleaseEvent)
{
    m_ViewKeyReleaseEvent = viewKeyReleaseEvent;
}

void DataTransmit::setViewFocusInEvent(ViewFocusInEvent viewFocusInEvent)
{
    m_ViewFocusInEvent = viewFocusInEvent;
}

void DataTransmit::setViewFocusOutEvent(ViewFocusOutEvent viewFocusOutEvent)
{
    m_ViewFocusOutEvent = viewFocusOutEvent;
}

void DataTransmit::setViewEnterEvent(ViewEnterEvent viewEnterEvent)
{
    m_ViewEnterEvent = viewEnterEvent;
}

void DataTransmit::setViewLeaveEvent(ViewLeaveEvent viewLeaveEvent)
{
    m_ViewLeaveEvent = viewLeaveEvent;
}

void DataTransmit::setViewPaintEvent(ViewPaintEvent viewPaintEvent)
{
    m_ViewPaintEvent = viewPaintEvent;
}

void DataTransmit::setViewMoveEvent(ViewMoveEvent viewMoveEvent)
{
    m_ViewMoveEvent = viewMoveEvent;
}

void DataTransmit::setViewResizeEvent(ViewResizeEvent viewResizeEvent)
{
    m_ViewResizeEvent = viewResizeEvent;
}

void DataTransmit::setViewCloseEvent(ViewCloseEvent viewCloseEvent)
{
    m_ViewCloseEvent = viewCloseEvent;
}

void DataTransmit::setViewContextMenuEvent(ViewContextMenuEvent viewContextMenuEvent)
{
    m_ViewContextMenuEvent = viewContextMenuEvent;
}

void DataTransmit::setViewDragEnterEvent(ViewDragEnterEvent viewDragEnterEvent)
{
    m_ViewDragEnterEvent = viewDragEnterEvent;
}

void DataTransmit::setViewDragMoveEvent(ViewDragMoveEvent viewDragMoveEvent)
{
    m_ViewDragMoveEvent = viewDragMoveEvent;
}

void DataTransmit::setViewDragLeaveEvent(ViewDragLeaveEvent viewDragLeaveEvent)
{
    m_ViewDragLeaveEvent = viewDragLeaveEvent;
}

void DataTransmit::setViewDropEvent(ViewDropEvent viewDropEvent)
{
    m_ViewDropEvent = viewDropEvent;
}

void DataTransmit::setViewShowEvent(ViewShowEvent viewShowEvent)
{
    m_ViewShowEvent = viewShowEvent;
}

void DataTransmit::setViewHideEvent(ViewHideEvent viewHideEvent)
{
    m_ViewHideEvent = viewHideEvent;
}

void DataTransmit::setViewInputMethodEvent(ViewInputMethodEvent viewInputMethodEvent)
{
    m_ViewInputMethodEvent = viewInputMethodEvent;
}

void DataTransmit::setViewFocusNextPrevChild(ViewFocusNextPrevChild viewFocusNextPrevChild)
{
    m_ViewFocusNextPrevChild = viewFocusNextPrevChild;
}
