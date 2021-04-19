#include "CManagementTool.h"
#include "ZXml/CXml.h"
#include "CZBaseTool.h"
#include "hfdefine.h"
#include "DataTransmit.h"
#include "CZStaticFun.h"

#define EVENTITEM(v)   if(tool->item##v(event,sourceItem->getThis())) return true;
#define EVENTVIEW(v)   if(tool->view##v(event)) return true;
CManagementTool::CManagementTool(QObject *parent) : QObject(parent)
{
    m_Id = QUuid::createUuid().toString();
    registerCallBackFun();
}

CManagementTool::~CManagementTool()
{
    clear();
    DataTransmit::removeManagementTool(getId());
}

bool CManagementTool::loadTool(QString fileName)
{
    clear();
    QList<XmlAtrrPtr> attrs = CXml::readNewXmlConfigFile(fileName);
    if(attrs.isEmpty()) return false;
    foreach (XmlAtrrPtr attr, attrs)
    {
        createTool(attr->tagName);
    }
    return true;
}

bool CManagementTool::saveTool(QString fileName)
{
    XmlAtrrPtr rootPtr(new XmlAttr);
    foreach (CZBaseTool *tool, m_Tools)
    {
        XmlAttr *attr = new XmlAttr;
        attr->setParentFilgAttr(rootPtr.data());
        attr->tagName = tool->getClassName();
    }
    return CXml::writeXmlConfigFile(fileName,rootPtr);
}

bool CManagementTool::configItemTool(QString fileName)
{
    m_ItemHaveTools.clear();
    QList<XmlAtrrPtr> attrs = CXml::readNewXmlConfigFile(fileName);
    if(attrs.isEmpty()) return false;
    foreach (XmlAtrrPtr attr, attrs)
    {
        QList<CZBaseTool*> tools;
        QStringList toolClassNames = attr->attrs.value(TOOLCLASSNAMES).toString().split(SJOIN);

        //获取item对应的工具
        foreach (CZBaseTool *tool, m_Tools)
        {
            if(toolClassNames.contains(tool->getClassName()))
            {
                tools.push_back(tool);
            }
        }
        m_ItemHaveTools.insert(attr->tagName,tools);
    }
    return true;
}

bool CManagementTool::saveConfigItemTool(QString fileName)
{
    XmlAtrrPtr rootPtr(new XmlAttr);
    for(auto iter = m_ItemHaveTools.begin(); iter != m_ItemHaveTools.end(); iter++)
    {
        XmlAttr *attr = new XmlAttr;
        attr->setParentFilgAttr(rootPtr.data());
        attr->tagName = iter.key();
        QStringList toolClassNames;
        foreach (CZBaseTool *tool, iter.value())
        {
            toolClassNames<<tool->getClassName();
        }
        attr->attrs.insert(TOOLCLASSNAMES,toolClassNames.join(SJOIN));
    }
    return CXml::writeXmlConfigFile(fileName,rootPtr);
}

void CManagementTool::createTool(QString toolClassName)
{
    try
    {
        foreach (CZBaseTool *tool, m_Tools)
        {
            if(tool->getClassName() == toolClassName)
            {
                throw std::logic_error(TOOLEXIST);
            }
        }
         CZBaseTool *tool = static_cast<CZBaseTool*>(CMyRegisterSingle::instance()->getClass(toolClassName));
         if(tool)
         {
             m_Tools<<tool;
         }
         else
         {
             throw std::logic_error(TOOLNONAME);
         }
    }
    catch(std::logic_error error)
    {
        qWarning(error.what());
        throw;
    }
}

QList<CZBaseTool *> CManagementTool::getTools(QString itemType)
{
    return m_ItemHaveTools.value(itemType);
}

QStringList CManagementTool::getTypesByToolClassName(QString toolClassName)
{
    QStringList itemTypes;
    CZBaseTool* tool = getTool(toolClassName);
    D_ISNULLR(tool,itemTypes);
    for(auto iter = m_ItemHaveTools.begin(); iter != m_ItemHaveTools.end(); iter++)
    {
        if(iter.value().contains(tool))
        {
            itemTypes<<iter.key();
        }
    }
    return itemTypes;
}

QList<CZBaseTool *> CManagementTool::getAllTool()
{
    return m_Tools;
}

CZBaseTool *CManagementTool::getTool(QString toolClassName)
{
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getClassName() == toolClassName)
            return tool;
    }
    return NULL;
}

void CManagementTool::initAllTool()
{
    foreach (CZBaseTool *tool, m_Tools)
    {
        tool->initTool();
    }
}

void CManagementTool::upDateTool(const QString toolClassName, CZBase *item)
{
    CZBaseTool *tool = getTool(toolClassName);
    D_ISNULLR(tool,);
    tool->upDataTool(item);
}

void CManagementTool::upDateTypeTool(CZBase *item)
{
    D_ISNULLR(item,);
    QString itemType = item->getItemType();
    QList<CZBaseTool*> tools = getTools(itemType);
    foreach (CZBaseTool *tool, tools)
    {
        tool->upDataTool(item);
    }
}

QString CManagementTool::getId()
{
    return m_Id;
}

void CManagementTool::clear()
{
    foreach (CZBaseTool *tool, m_Tools)
    {
        D_Delete(tool)
    }
    m_Tools.clear();
    m_ItemHaveTools.clear();
}

void CManagementTool::setEditItem(const CZDRAW::EditStatus  &state, CZBase *item)
{
    D_ISNULLR(item,);
    QString itemType = item->getItemType();
    QList<CZBaseTool*> tools = getTools(itemType);
    foreach (CZBaseTool *tool, tools)
    {
        tool->setEditItem(state,item);
    }
}

void CManagementTool::addItemToTool(const QString &itemType, const QString &toolClassName)
{
    try
    {
        CZBaseTool *tool = getTool(toolClassName);
        if(tool)
        {
            if(!m_ItemHaveTools[itemType].contains(tool))
            {
                m_ItemHaveTools[itemType].append(tool);
            }
            else
            {
                throw std::logic_error(TOOLADD);
            }
        }
        else
        {
            throw std::logic_error(TOOLISNULL);
        }
    }
    catch(std::logic_error error)
    {
        qWarning(error.what());
        throw;
    }
}

void CManagementTool::registerCallBackFun()
{
    DataTransmit::addManagementTool(getId(),this);
    DataTransmit::setSceneEventFilter(CManagementTool::itemSceneEventFilter);
    DataTransmit::setSceneEvent(CManagementTool::itemSceneEvent);
    DataTransmit::setContextMenuEvent(CManagementTool::itemContextMenuEvent);
    DataTransmit::setDragEnterEvent(CManagementTool::itemDragEnterEvent);
    DataTransmit::setDragLeaveEvent(CManagementTool::itemDragLeaveEvent);
    DataTransmit::setDragMoveEvent(CManagementTool::itemDragMoveEvent);
    DataTransmit::setDropEvent(CManagementTool::itemDropEvent);
    DataTransmit::setFocusInEvent(CManagementTool::itemFocusInEvent);
    DataTransmit::setFocusOutEvent(CManagementTool::itemFocusOutEvent);
    DataTransmit::setHoverEnterEvent(CManagementTool::itemHoverEnterEvent);
    DataTransmit::setHoverMoveEvent(CManagementTool::itemHoverMoveEvent);
    DataTransmit::setHoverLeaveEvent(CManagementTool::itemHoverLeaveEvent);
    DataTransmit::setKeyPressEvent(CManagementTool::itemKeyPressEvent);
    DataTransmit::setKeyReleaseEvent(CManagementTool::itemKeyReleaseEvent);
    DataTransmit::setMousePressEvent(CManagementTool::itemMousePressEvent);
    DataTransmit::setMouseMoveEvent(CManagementTool::itemMouseMoveEvent);
    DataTransmit::setMouseReleaseEvent(CManagementTool::itemMouseReleaseEvent);
    DataTransmit::setMouseDoubleClickEvent(CManagementTool::itemMouseDoubleClickEvent);
    DataTransmit::setWheelEvent(CManagementTool::itemWheelEvent);
    DataTransmit::setInputMethodEvent(CManagementTool::itemInputMethodEvent);
    DataTransmit::setItemChange(CManagementTool::itemItemChange);


    DataTransmit::setViewEvent                (CManagementTool::viewEvent                );
    DataTransmit::setViewCustomEvent          (CManagementTool::viewCustomEvent          );
    DataTransmit::setViewMousePressEvent      (CManagementTool::viewMousePressEvent      );
    DataTransmit::setViewMouseReleaseEvent    (CManagementTool::viewMouseReleaseEvent    );
    DataTransmit::setViewMouseDoubleClickEvent(CManagementTool::viewMouseDoubleClickEvent);
    DataTransmit::setViewMouseMoveEvent       (CManagementTool::viewMouseMoveEvent       );
    DataTransmit::setViewWheelEvent           (CManagementTool::viewWheelEvent           );
    DataTransmit::setViewKeyPressEvent        (CManagementTool::viewKeyPressEvent        );
    DataTransmit::setViewKeyReleaseEvent      (CManagementTool::viewKeyReleaseEvent      );
    DataTransmit::setViewFocusInEvent         (CManagementTool::viewFocusInEvent         );
    DataTransmit::setViewFocusOutEvent        (CManagementTool::viewFocusOutEvent        );
    DataTransmit::setViewEnterEvent           (CManagementTool::viewEnterEvent           );
    DataTransmit::setViewLeaveEvent           (CManagementTool::viewLeaveEvent           );
    DataTransmit::setViewPaintEvent           (CManagementTool::viewPaintEvent           );
    DataTransmit::setViewMoveEvent            (CManagementTool::viewMoveEvent            );
    DataTransmit::setViewResizeEvent          (CManagementTool::viewResizeEvent          );
    DataTransmit::setViewCloseEvent           (CManagementTool::viewCloseEvent           );
    DataTransmit::setViewContextMenuEvent     (CManagementTool::viewContextMenuEvent     );
    DataTransmit::setViewDragEnterEvent       (CManagementTool::viewDragEnterEvent       );
    DataTransmit::setViewDragMoveEvent        (CManagementTool::viewDragMoveEvent        );
    DataTransmit::setViewDragLeaveEvent       (CManagementTool::viewDragLeaveEvent       );
    DataTransmit::setViewDropEvent            (CManagementTool::viewDropEvent            );
    DataTransmit::setViewShowEvent            (CManagementTool::viewShowEvent            );
    DataTransmit::setViewHideEvent            (CManagementTool::viewHideEvent            );
    DataTransmit::setViewInputMethodEvent     (CManagementTool::viewInputMethodEvent     );
    DataTransmit::setViewFocusNextPrevChild   (CManagementTool::viewFocusNextPrevChild   );
}


bool CManagementTool::itemSceneEventFilter(QGraphicsItem *watched, QEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            if(tool->itemSceneEventFilter(watched,event,sourceItem->getThis()))
                return true;
        }
    }
    return false;
}

bool CManagementTool::itemSceneEvent(QEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(SceneEvent);
        }
    }
    return false;
}

bool CManagementTool::itemContextMenuEvent(QGraphicsSceneContextMenuEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(ContextMenuEvent);
        }
    }
    return false;
}

bool CManagementTool::itemDragEnterEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(DragEnterEvent);
        }
    }
    return false;
}

bool CManagementTool::itemDragLeaveEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(DragLeaveEvent);
        }
    }
    return false;
}

bool CManagementTool::itemDragMoveEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(DragMoveEvent);
        }
    }
    return false;
}

bool CManagementTool::itemDropEvent(QGraphicsSceneDragDropEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(DropEvent);
        }
    }
    return false;
}

bool CManagementTool::itemFocusInEvent(QFocusEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(FocusInEvent);
        }
    }
    return false;
}

bool CManagementTool::itemFocusOutEvent(QFocusEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(FocusOutEvent);
        }
    }
    return false;
}

bool CManagementTool::itemHoverEnterEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(HoverEnterEvent);
        }
    }
    return false;
}

bool CManagementTool::itemHoverMoveEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(HoverMoveEvent);
        }
    }
    return false;
}

bool CManagementTool::itemHoverLeaveEvent(QGraphicsSceneHoverEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(HoverLeaveEvent);
        }
    }
    return false;
}

bool CManagementTool::itemKeyPressEvent(QKeyEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(KeyPressEvent);
        }
    }
    return false;
}

bool CManagementTool::itemKeyReleaseEvent(QKeyEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(KeyReleaseEvent);
        }
    }
    return false;
}

bool CManagementTool::itemMousePressEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(MousePressEvent);
        }
    }
    return false;
}

bool CManagementTool::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(MouseMoveEvent);
        }
    }
    return false;
}

bool CManagementTool::itemMouseReleaseEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(MouseReleaseEvent);
        }
    }
    return false;
}

bool CManagementTool::itemMouseDoubleClickEvent(QGraphicsSceneMouseEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(MouseDoubleClickEvent);
        }
    }
    return false;
}

bool CManagementTool::itemWheelEvent(QGraphicsSceneWheelEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(WheelEvent);
        }
    }
    return false;
}

bool CManagementTool::itemInputMethodEvent(QInputMethodEvent *event,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTITEM(InputMethodEvent);
        }
    }
    return false;
}

bool CManagementTool::itemItemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value,CZBase *sourceItem,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    QList<CZBaseTool *> m_Tools= managementTool->getTools(sourceItem->getItemType());
    foreach (CZBaseTool *tool, m_Tools)
    {
        if(tool->getToolActiva())
        {
            if(tool->itemItemChange(change,value,sourceItem->getThis()))
                return true;
        }
    }
    return false;
}

bool CManagementTool::viewEvent(QEvent *event, CManagementTool *managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(Event);
        }
    }
    return false;
}

bool CManagementTool::viewCustomEvent(QEvent *event, CManagementTool *managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(CustomEvent);
        }
    }
    return false;
}

bool CManagementTool::viewMousePressEvent(QMouseEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(MousePressEvent);
        }
    }
    return false;
}

bool CManagementTool::viewMouseReleaseEvent(QMouseEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(MouseReleaseEvent);
        }
    }
    return false;
}

bool CManagementTool::viewMouseDoubleClickEvent(QMouseEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(MouseDoubleClickEvent);
        }
    }
    return false;
}

bool CManagementTool::viewMouseMoveEvent(QMouseEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(MouseMoveEvent);
        }
    }
    return false;
}

bool CManagementTool::viewWheelEvent(QWheelEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(WheelEvent);
        }
    }
    return false;
}

bool CManagementTool::viewKeyPressEvent(QKeyEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(KeyPressEvent);
        }
    }
    return false;
}

bool CManagementTool::viewKeyReleaseEvent(QKeyEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(KeyReleaseEvent);
        }
    }
    return false;
}

bool CManagementTool::viewFocusInEvent(QFocusEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(FocusInEvent);
        }
    }
    return false;
}

bool CManagementTool::viewFocusOutEvent(QFocusEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(FocusOutEvent);
        }
    }
    return false;
}

bool CManagementTool::viewEnterEvent(QEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(EnterEvent);
        }
    }
    return false;
}

bool CManagementTool::viewLeaveEvent(QEvent *event, CManagementTool *managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(LeaveEvent);
        }
    }
    return false;
}

bool CManagementTool::viewPaintEvent(QPaintEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(PaintEvent);
        }
    }
    return false;
}

bool CManagementTool::viewMoveEvent(QMoveEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(MoveEvent);
        }
    }
    return false;
}

bool CManagementTool::viewResizeEvent(QResizeEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(ResizeEvent);
        }
    }
    return false;
}

bool CManagementTool::viewCloseEvent(QCloseEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(CloseEvent);
        }
    }
    return false;
}

bool CManagementTool::viewContextMenuEvent(QContextMenuEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(ContextMenuEvent);
        }
    }
    return false;
}

bool CManagementTool::viewDragEnterEvent(QDragEnterEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(DragEnterEvent);
        }
    }
    return false;
}

bool CManagementTool::viewDragMoveEvent(QDragMoveEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(DragMoveEvent);
        }
    }
    return false;
}

bool CManagementTool::viewDragLeaveEvent(QDragLeaveEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(DragLeaveEvent);
        }
    }
    return false;
}

bool CManagementTool::viewDropEvent(QDropEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(DropEvent);
        }
    }
    return false;
}

bool CManagementTool::viewShowEvent(QShowEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(ShowEvent);
        }
    }
    return false;
}

bool CManagementTool::viewHideEvent(QHideEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(HideEvent);
        }
    }
    return false;
}

bool CManagementTool::viewInputMethodEvent(QInputMethodEvent *event,CManagementTool* managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            EVENTVIEW(InputMethodEvent);
        }
    }
    return false;
}

bool CManagementTool::viewFocusNextPrevChild(bool next, CManagementTool *managementTool)
{
    D_ISNULLR(managementTool,false);
    foreach (CZBaseTool *tool, managementTool->m_Tools)
    {
        if(tool->getToolActiva())
        {
            if(tool->viewFocusNextPrevChild(next))
                return true;
        }
    }
    return false;
}
