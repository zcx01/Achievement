#include "CZDrawManagement.h"
#include "CManagementTool.h"
#include "CManagementItem.h"
#include <QGraphicsScene>
#include "CGraphicsView.h"
#include "CZBaseTool.h"
#include "hfdefine.h"
#include "ZXml/CXml.h"
#include "CZStaticFun.h"

CZDrawManagement::CZDrawManagement(QWidget *parent) : QObject(parent)
{
    CZBase::resetOrder();
    m_ManagmentTool = new CManagementTool(parent);
    m_ManagmentItem = new CManagementItem(parent);
    m_ManagmentItem->setEventId(m_ManagmentTool->getId());
    m_Scene = new QGraphicsScene;
    m_ManagmentItem->setScene(m_Scene);
    qRegisterMetaType<QVariantMap>("QVariantMap");
    connect(m_Scene,SIGNAL(selectionChanged()),this,SIGNAL(sig_SelectChanged()));
    connect(m_ManagmentItem,SIGNAL(sig_CreateItem(QVariantMap)),this,SLOT(slot_CreateItem(QVariantMap)));
    connect(m_ManagmentItem,SIGNAL(sig_CurrentChanged(CZBase*,CZBase*)),this,SLOT(slot_CurrentChanged(CZBase*,CZBase*)));
    connect(m_ManagmentItem,SIGNAL(sig_SendCustomAttr(QString,QVariant)),this,SIGNAL(sig_SendCustomAttr(QString,QVariant)));
}

CZDrawManagement::~CZDrawManagement()
{
    D_Delete(m_ManagmentTool);
    D_Delete(m_Scene);
}

//------------------------------file(文件)----------------------------
//-------------------------------------------------------------------
bool CZDrawManagement::loadTool(QString fileName)
{
    bool res = m_ManagmentTool->loadTool(fileName);
    QList<CZBaseTool *> tools = m_ManagmentTool->getAllTool();
    foreach(CZBaseTool *tool,tools)
    {
        tool->setManagment(m_ManagmentItem);
    }
    return res;
}

bool CZDrawManagement::saveTool(QString fileName)
{
    return m_ManagmentTool->saveTool(fileName);
}

bool CZDrawManagement::configItemTool(QString fileName)
{
    return m_ManagmentTool->configItemTool(fileName);
}

bool CZDrawManagement::saveConfigItemTool(QString fileName)
{
    return m_ManagmentTool->saveConfigItemTool(fileName);
}

bool CZDrawManagement::loadItemFileName(QString fileName)
{
    XmlAtrrPtr rootAtrr = CXml::readXmlConfigFile(fileName);
    if(rootAtrr.isNull()) return false;
    setViewAttr(rootAtrr->attrs);
    createChildItem(NULL,rootAtrr.data());
    m_ManagmentTool->initAllTool();
    return true;
}

bool CZDrawManagement::saveItemFile(QString fileName)
{
    XmlAtrrPtr rootAtrr(new XmlAttr);
    rootAtrr->attrs = getViewAttr();
    QList<CZBase *> items = m_ManagmentItem->getItems();

    //排序
    std::sort(items.begin(),items.end(),CZDrawManagement::CompOrder);
    QHash<QGraphicsItem* ,XmlAttr *> allItemAttrs;
    foreach (CZBase *item, items)
    {
        XmlAttr *attr = new XmlAttr;
        attr->attrs = item->getAttrs();
        attr->tagName = item->getClassName();

        //设置父类
        QGraphicsItem * parentItem = item->parentItem();
        XmlAttr * parentAttr = allItemAttrs.value(parentItem);
        if(parentAttr)
        {
            attr->setParentFilgAttr(parentAttr);
        }
        else
        {
            attr->setParentFilgAttr(rootAtrr.data());
        }
        allItemAttrs.insert(item,attr);
    }

    return CXml::writeXmlConfigFile(fileName,rootAtrr);
}


//------------------------------item（图元）-------------------------------
//-----------------------------------------------------------------------
QString CZDrawManagement::createItem(QString className, const QVariantMap &attr)
{
    CZBase * item=NULL;
    bool isBackgound =attr.value(BACKGOUNDITEM).toBool();

    //通过item管理器创建
    item =  m_ManagmentItem->createItem(className,attr);
    D_ISNULLR(item,"");

    //设置父类
    CZBase* parentItem = m_ManagmentItem->getItemById(attr.value(PARENTITEM).toString());
    item->setParentItem(parentItem);

    //把item加入场景中
    m_Scene->addItem(item->getThis());

    item->AddScene(m_Scene);

    connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SIGNAL(sig_AttrChanged(QString,QString)));
    //connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_AttrChanged(QString,QString)));

    //把item加入所属工具中
//    if(!isBackgound)
    {
        QList<CZBaseTool *> tools = m_ManagmentTool->getTools(item->getItemType());
        foreach(CZBaseTool *tool,tools)
        {
            tool->addOperationItem(item);
        }
    }
    emit sig_CreateFinish(item->getId());
    return item->getId();
}

QString CZDrawManagement::createItemByType(const QString &itemType)
{
    QVariantMap attr = getAttrByItemType(itemType);
    attr.insert(IDD,"");
    return createItem(attr.value(ITEMCLASSNAME).toString(),attr);
}

bool CZDrawManagement::deleteItem(QString id)
{
    CZBase* item = m_ManagmentItem->getItemById(id);
    D_ISNULLR(item,false);
    if(item->getAttrs().value(NOCANDELETE).toBool()) return false;
    setEdit(CZDRAW::NoEdit,id);//移除编辑状态
    QList<CZBaseTool *> tools = m_ManagmentTool->getTools(item->getItemType());
    foreach(CZBaseTool *tool,tools)
    {
        tool->removeOperationItem(item);    //移除item所有工具
    }
    m_ManagmentItem->deleteItem(id);
    return true;
}

void CZDrawManagement::clearAllItem(const bool &clearBackgound)
{
    QList<CZBase*> items = m_ManagmentItem->getItems();
    for(int i=0; i <items.size(); i++)
    {
        CZBase* item = items.at(i);
        if(!item->property(BACKGOUNDITEM).toBool() || clearBackgound)
        {
            QList<CZBaseTool *> tools = m_ManagmentTool->getTools(item->getItemType());
            foreach(CZBaseTool *tool,tools)
            {
                tool->removeOperationItem(item);    //移除item所有工具
            }
        }
    }
    m_ManagmentItem->clearItem(clearBackgound);
}

void CZDrawManagement::setCurrentId(const QString &id)
{
    m_ManagmentItem->setCurrent(m_ManagmentItem->getItemById(id));
}

QString CZDrawManagement::getCurrentId()
{
    CZBase* item = m_ManagmentItem->getCurrent();
    D_ISNULLR(item,"");
    return item->getId();
}

QList<QString> CZDrawManagement::getSelects()
{
    QList<QString> selectIds;
    QList<CZBase*> items = m_ManagmentItem->getSelects();
    foreach (CZBase *item, items)
    {
        selectIds.push_back(item->getId());
    }
    return selectIds;
}


bool CZDrawManagement::setEdit(const CZDRAW::EditStatus &state, QString id)
{
    CZBase* item =NULL;
    if(id.isEmpty())
    {
        item = m_ManagmentItem->getCurrent();
    }
    else
    {
        item =m_ManagmentItem->getItemById(id);
        m_ManagmentItem->setCurrent(item);
    }
    D_ISNULLR(item,false);
    if(getEdit() == state)
        return false;
    m_ManagmentItem->setEdit(item,state);
    m_ManagmentTool->setEditItem(state,item);
    return true;
}

CZDRAW::EditStatus CZDrawManagement::getEdit()
{
    return m_ManagmentItem->getEdit();
}

QVariant::Type CZDrawManagement::getKeyType(const QString &id, const QString &key)
{
    return m_ManagmentItem->getKeyType(id,key);
}

//------------------------------itemAttr(图元属性)---------------------------
//-------------------------------------------------------------------------
bool CZDrawManagement::upDateItemAttr(DrawItemAttrPtr ptr)
{
    if(ptr.isNull()) return false;
    CZBase* item = NULL;
    item = m_ManagmentItem->getItemById(ptr->id);
    D_ISNULLR(item,false);
    item->setAttrs(ptr->attrs);

    //设置父类
    CZBase* parentItem = m_ManagmentItem->getItemById(ptr->attrs.value(PARENTITEM).toString());
    item->setParentItem(parentItem);
    return true;
    //目前不可以移除item的相关工具
}

DrawItemAttrPtr CZDrawManagement::getItemAttr(QString id)
{
    return getItemAttrByHand(m_ManagmentItem->getItemById(id));
}

DrawItemAttrPtr CZDrawManagement::getCurrentAttr()
{
    return getItemAttrByHand(m_ManagmentItem->getCurrent());
}

QVariantMap CZDrawManagement::getAttrByItemType(const QString &itemType)
{
    return m_ManagmentItem->getAttrByItemType(itemType);
}

//------------------------------View--------------------------------------
//------------------------------------------------------------------------
void CZDrawManagement::setVisible(const bool &state)
{
    m_ManagmentItem->setVisible(state);
}

bool CZDrawManagement::getVisible() const
{
    return m_ManagmentItem->isVisible();
}

void CZDrawManagement::setViewAttr(const QVariantMap &attr)
{
    m_ManagmentItem->setViewAttr(attr);
}

QVariantMap CZDrawManagement::getViewAttr()
{
    return m_ManagmentItem->getViewAttr();
}

QWidget *CZDrawManagement::getWidget()
{
    return m_ManagmentItem;
}

void CZDrawManagement::setZoomDelta(qreal delta)
{
    m_ManagmentItem->setZoomDelta(delta);
}

void CZDrawManagement::ZoomIn()
{
    m_ManagmentItem->zoomIn();
}

void CZDrawManagement::ZoomOut()
{
    m_ManagmentItem->zoomOut();
}

void CZDrawManagement::Zoom(float scaleFactor)
{
    m_ManagmentItem->zoom(scaleFactor);
}

void CZDrawManagement::Restore()
{
    m_ManagmentItem->Restore();
}

QGraphicsScene *CZDrawManagement::GetScene()
{
    return m_Scene;
}

//------------------------------Tool--------------------------------------
//------------------------------------------------------------------------
QVariant CZDrawManagement::upDateToolData(QString id, QString toolClassName, void *pData)
{
    CZBase *item = m_ManagmentItem->getItemById(id);
    D_ISNULLR(item,false);
    CZBaseTool* tool = m_ManagmentTool->getTool(toolClassName);
    D_ISNULLR(tool,false);
    return tool->setDealData(item,pData);

//    QList<CZBaseTool *> tools = m_ManagmentTool->getTools(item->getItemType());
//    foreach (CZBaseTool* tool, tools)
//    {
//        if(tool->getClassName() == toolClassName)
//        {
//            return tool->setDealData(item,pData);
//        }
//    }
    //    return QVariant();
}

QVariant CZDrawManagement::ToolDealData(QString id, QString toolClassName, const QVariant &pData)
{
    CZBase *item = m_ManagmentItem->getItemById(id);
    D_ISNULLR(item,false);
    CZBaseTool* tool = m_ManagmentTool->getTool(toolClassName);
    D_ISNULLR(tool,false);
    return tool->dealMinData(item,pData);
}

void CZDrawManagement::upDateTool(const QString toolClassName,const QString &id)
{
    CZBase* item = m_ManagmentItem->getItemById(id);
    D_ISNULLR(item,);
    m_ManagmentTool->upDateTool(toolClassName,item);
}

void CZDrawManagement::upDateItemAllTool(const QString &id)
{
    CZBase* item = m_ManagmentItem->getItemById(id);
    D_ISNULLR(item,);
    m_ManagmentTool->upDateTypeTool(item);
}

QStringList CZDrawManagement::getTypesByToolClassName(QString toolClassName)
{
    return m_ManagmentTool->getTypesByToolClassName(toolClassName);
}

void CZDrawManagement::setCurrentToolActiva(QString toolClassName, bool state)
{
    CZBaseTool * tool = m_ManagmentTool->getTool(toolClassName);
    D_ISNULLR(tool,);
    tool->setToolActiva(state);
}

void CZDrawManagement::addItemToTool(const QString &itemType, const QString &toolClassName)
{
    m_ManagmentTool->addItemToTool(itemType,toolClassName);
}

void CZDrawManagement::createTool(QString toolClassName)
{
    m_ManagmentTool->createTool(toolClassName);
    CZBaseTool *tool = m_ManagmentTool->getTool(toolClassName);
    if(tool) tool->setManagment(m_ManagmentItem);
}

void CZDrawManagement::itemAddFinishToTool(const QString &toolClassName)
{
    CZBaseTool *tool = m_ManagmentTool->getTool(toolClassName);
    if(tool) tool->initTool();
}

void CZDrawManagement::slot_CurrentChanged(CZBase *old, CZBase *current)
{
    QString oldId;
    QString curId;
    if(old)
        oldId = old->getId();
    if(current)
        curId = current->getId();
    emit sig_CurrentChanged(oldId,curId);
}

void CZDrawManagement::slot_AttrChanged(QString id, QString key)
{
    qDebug()<<id<<key;
    emit sig_AttrChanged(id,key);
}

void CZDrawManagement::slot_CreateItem(QVariantMap attr)
{
    createItem(attr.value(ITEMCLASSNAME).toString(),attr);
    upDateItemAllTool(attr.value(IDD).toString());
}

DrawItemAttrPtr CZDrawManagement::getItemAttrByHand(CZBase *item)
{
    D_ISNULLR(item,DrawItemAttrPtr());
    DrawItemAttr *attr = new DrawItemAttr;
    attr->id = item->getId();
    attr->attrs = item->getAttrs();
    attr->className = item->getClassName();
    attr->itmeType = item->getItemType();
    attr->tool = m_ManagmentTool->getTools(item->getItemType());
    foreach (QGraphicsItem *child, item->childItems())
    {
        CZBase* childItem = dynamic_cast<CZBase*>(child);
        D_ISNULLC(childItem);
        attr->childIds.push_back(childItem->getId());
    }
    return DrawItemAttrPtr(attr);
}

void CZDrawManagement::createChildItem(CZBase *parentItem, XmlAttr *parentAttr)
{
    D_ISNULLR(parentAttr,);
    for(int i =0; i < parentAttr->childs.size();i++)
    {
        XmlAttr * attr = parentAttr->childs.at(i);
        if(parentItem)
        {
            attr->attrs.insert(PARENTITEM,parentItem->getId());
        }
        QString itemType = attr->attrs.value(ITEMTYPE).toString();
        if (itemType.isEmpty())
        {
            itemType = attr->tagName;
        }
        QVariantMap attrMap = getAttrByItemType(itemType);
        attrMap.remove(IDD);
        auto iter = attr->attrs.begin();
        for (; iter != attr->attrs.end(); iter++)
        {
            attrMap.insert(iter.key(), iter.value());
        }
        QString id = createItem(attr->tagName, attrMap);
        CZBase *item = m_ManagmentItem->getItemById(id);
        D_ISNULLC(item);
        createChildItem(item,attr);
    }
}

bool CZDrawManagement::CompOrder(CZBase *f, CZBase *t)
{
    if(f->getOrder() < t->getOrder())
        return true;
    return false;
}
