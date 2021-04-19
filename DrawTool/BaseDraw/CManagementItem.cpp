#include "CManagementItem.h"
#include "hfdefine.h"
#include "ZXml/CXml.h"
#include "CZBase.h"
#include "DataTransmit.h"
#include <QMouseEvent>
#include <QTime>
#include <QMimeData>
#include "CZStaticFun.h"

#define EVENTTRANSMIT(v) if(DataTransmit::view##v(event,m_EventId)) return;

CManagementItem::CManagementItem(QWidget *parent) : CGraphicsView(parent)
{
    initData();
}

CManagementItem::~CManagementItem()
{
    //clearItem();
}

void CManagementItem::initData()
{
    m_CurrentItem = NULL;
    m_Edit = CZDRAW::NoEdit;
    setAcceptDrops(true);
}

CZBase *CManagementItem::createItem(QString className, const QVariantMap &attr)
{
    CZBase *item = static_cast<CZBase*>(CMyRegisterSingle::instance()->getClass(className));
    D_ISNULLR(item,NULL);
    if(attr.value(CONFIGFILENAME).isNull())
    {
        item->setAttrs(attr);
    }
    else
    {
        item->loadFile(attr.value(CONFIGFILENAME).toString());
    }
    //设置时间传递的Id
    item->setEventId(m_EventId);

    //加入类型属性关联容器,以最后一个为准
    QString itemType = item->getItemType();
    //if(!m_ItemTypeAttr.contains(itemType))
    //{
    m_ItemTypeAttr.insert(itemType,attr);
    m_ItemTypeAttr[itemType].insert(ITEMTYPE,itemType);
    m_ItemTypeAttr[itemType].insert(ITEMCLASSNAME,item->getClassName());
    //}
    addItem(item);
    return item;
}

bool CManagementItem::deleteItem(QString id)
{
    CZBase *item = getItemById(id);
    D_ISNULLR(item,false);
    QList<QGraphicsItem *> childItem = item->childItems();

    //子类一个一个删除
    foreach (QGraphicsItem * cItem, childItem)
    {
        CZBase* bItem = dynamic_cast<CZBase *>(cItem);
        if(bItem)
        {
            if(m_CurrentItem == bItem)
            {
                m_CurrentItem = NULL;
            }
            if(m_Items.values().contains(bItem))
            {
                deleteItem(bItem->getId());
            }
        }

    }
    if(!item->parentItem())
    {
        removeItem(item);//移除容器中的item
        D_Delete(item);
    }
    return true;
}

void CManagementItem::setEdit(CZBase *item, const CZDRAW::EditStatus &state)
{
    D_ISNULLR(item,);
    m_Edit = state;
    item->setEdit(m_Edit);
}

CZDRAW::EditStatus CManagementItem::getEdit()
{
    return m_Edit;
}

void CManagementItem::setSelects(QList<CZBase*  > items)
{
    foreach (CZBase *item, items)
    {
        item->setSelected(true);
    }
}

void CManagementItem::addSelect(CZBase *item)
{
    if(item)
        item->setSelected(true);
}

void CManagementItem::removeSelect(CZBase *item)
{
    if(item)
        item->setSelected(false);
}


void CManagementItem::clearSelect()
{
    if(scene())
    {
        QList<QGraphicsItem *> CItems = scene()->selectedItems();
        foreach (QGraphicsItem *CItem, CItems)
        {
            CZBase* item = dynamic_cast<CZBase*>(CItem);
            if(item)
                item->setSelected(false);
        }
    }
}

QList<CZBase*  > CManagementItem::getSelects()
{
    QList<CZBase*  > items;
    if(scene())
    {
        QList<QGraphicsItem *> CItems = scene()->selectedItems();
        foreach (QGraphicsItem *CItem, CItems)
        {
            CZBase* item = dynamic_cast<CZBase*>(CItem);
            if(item)
                items<<item;
        }
    }
    return items;
}

void CManagementItem::setCurrent(CZBase*   item)
{
    CZBase* old = m_CurrentItem;
    m_CurrentItem = item;
    scene()->setFocusItem(m_CurrentItem);
    if(item)
    {
        item->setFocus();
    }
    emit sig_CurrentChanged(old,item);
}

CZBase*   CManagementItem::getCurrent()
{
    return m_CurrentItem;
}

void CManagementItem::addItem(CZBase*   item)
{
    m_Items.insert(item->getId(),item);
}

void CManagementItem::removeItem(CZBase*   item)
{
    m_Items.remove(item->getId());
    if(m_CurrentItem == item)
        m_CurrentItem = NULL;
}

void CManagementItem::clearItem(const bool &clearBackgound)
{
    auto iter = m_Items.begin();
    QHash<QString,CZBase*> tmpItems;
    QList<QString> deleteIds;
    for(;iter != m_Items.end(); iter++)
    {
        //不是背景或者可以清楚背景，就删除
        if(!iter.value()->property(BACKGOUNDITEM).toBool() || clearBackgound)
        {
            if(iter.value()->parentItem() == NULL)
            {
              deleteIds<<iter.value()->getId();
            }
        }
        else
        {
            tmpItems.insert(iter.key(),iter.value());
        }
    }
    foreach (QString id, deleteIds)
    {
        deleteItem(id);
    }
    m_Items.clear();
    m_Items.swap(tmpItems);
    initData();

    if(clearBackgound)
    {
        QGraphicsScene * scene = this->scene();
        D_ISNULLR(scene,);
        scene->clear();
    }
}

QList<CZBase*  > CManagementItem::getItems()
{
    return m_Items.values();
}

CZBase *CManagementItem::getItemById(QString id)
{
    return m_Items.value(id);
}

void CManagementItem::setEventId(const QString &id)
{
    m_EventId = id;
}

void CManagementItem:: setViewAttr(const QVariantMap &attrs)
{
    QPointF size = CZStaticFun::QStringToQPointF(attrs.value(VIEWSIZE).toString());
    if(!size.isNull())
    {
        resize(size.x(),size.y());
    }

    QRectF sizeRect = CZStaticFun::QStringToQRectF(attrs.value(SCENESIZE).toString());
    if(!sizeRect.isNull())
    {
        if(this->scene())
            this->scene()->setSceneRect(sizeRect);
    }
    setCanZoom(attrs.value(CANZOOM).toBool());
    setCanTranslate(attrs.value(CANTRANSLATE).toBool());
}

QVariantMap CManagementItem::getViewAttr()
{
    QVariantMap attr;
    QString Viewsize = CZStaticFun::QPointFTOQString(QPointF(size().width(),size().height()));
    attr.insert(VIEWSIZE,Viewsize);
    attr.insert(SCENESIZE,CZStaticFun::QRectFToQString(this->sceneRect()));
    attr.insert(CANZOOM,getCanZoom());
    attr.insert(CANTRANSLATE,getCanTranslate());
    return attr;
}

QVariantMap CManagementItem::getAttrByItemType(const QString &itemType)
{
    return m_ItemTypeAttr.value(itemType);
}

QVariant::Type CManagementItem::getKeyType(const QString &id, const QString &key)
{
    CZBase *item = getItemById(id);
    D_ISNULLR(item,QVariant::Invalid);
    return item->getKeyType(key);
}

void CManagementItem::SendCreateItem(const QVariantMap &data)
{
    emit sig_CreateItem(data);
}

void CManagementItem::SendCustomAttr(const QString &id,const QVariant &data)
{
    emit sig_SendCustomAttr(id,data);
}

bool CManagementItem::event(QEvent *event)
{
    if(DataTransmit::viewEvent(event,m_EventId))
    {
        return true;
    }
    return CGraphicsView::event(event);
}

void CManagementItem::customEvent(QEvent *event)
{
    EVENTTRANSMIT(CustomEvent);
    CGraphicsView::customEvent(event);
}

void CManagementItem::mousePressEvent(QMouseEvent *event)
{
    EVENTTRANSMIT(MousePressEvent);
    if(event->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *>  clickItems = items(event->pos());
        CZBase * sourceItem = NULL;
        foreach (QGraphicsItem * clickItem, clickItems)
        {
            CZBase *bItem = dynamic_cast<CZBase *>(clickItem);
            if(bItem && bItem->isContainMousePos(this->mapToScene(event->pos())))
            {
                sourceItem = bItem;
                break;
            }
        }
        setCurrent(sourceItem);
//                if(sourceItem && !sourceItem->property(BACKGOUNDITEM).toBool())
//                {
//                    if(getCtrlKeyPress())
//                    {
//                        if(getSelects().contains(sourceItem))  //再点一下取消选择
//                        {
//                            qDebug()<<"移除选中--------"<<sourceItem->getId();
//                            removeSelect(sourceItem);
//                        }
//                        else
//                        {
//                            qDebug()<<"添加选中--------"<<sourceItem->getId();
//                            addSelect(sourceItem);
//                        }
//                    }
//                    else
//                    {
//                        qDebug()<<"选中唯一--------";
//                        clearSelect();
//                        addSelect(sourceItem);
//                    }
//                }
//                else
//                {
//                    qDebug()<<"移除所有选中--------";
//                    clearSelect();
//                }
    }
    CGraphicsView::mousePressEvent(event);
}

void CManagementItem::mouseReleaseEvent(QMouseEvent *event)
{
    EVENTTRANSMIT(MouseReleaseEvent);
    CGraphicsView::mouseReleaseEvent(event);
}

void CManagementItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    EVENTTRANSMIT(MouseDoubleClickEvent);
    CGraphicsView::mouseDoubleClickEvent(event);
}

void CManagementItem::mouseMoveEvent(QMouseEvent *event)
{
    EVENTTRANSMIT(MouseMoveEvent);
    CGraphicsView::mouseMoveEvent(event);
}

void CManagementItem::wheelEvent(QWheelEvent *event)
{
    EVENTTRANSMIT(WheelEvent);
    CGraphicsView::wheelEvent(event);
}

void CManagementItem::keyPressEvent(QKeyEvent *event)
{
    EVENTTRANSMIT(KeyPressEvent);
    CGraphicsView::keyPressEvent(event);
}

void CManagementItem::keyReleaseEvent(QKeyEvent *event)
{
    EVENTTRANSMIT(KeyReleaseEvent);
    CGraphicsView::keyReleaseEvent(event);
}

void CManagementItem::focusInEvent(QFocusEvent *event)
{
    EVENTTRANSMIT(FocusInEvent);
    CGraphicsView::focusInEvent(event);
}

void CManagementItem::focusOutEvent(QFocusEvent *event)
{
    EVENTTRANSMIT(FocusOutEvent);
    CGraphicsView::focusOutEvent(event);
}

void CManagementItem::enterEvent(QEvent *event)
{
    EVENTTRANSMIT(EnterEvent);
    CGraphicsView::enterEvent(event);
}

void CManagementItem::leaveEvent(QEvent *event)
{
    EVENTTRANSMIT(LeaveEvent);
    CGraphicsView::leaveEvent(event);
}

void CManagementItem::paintEvent(QPaintEvent *event)
{
    EVENTTRANSMIT(PaintEvent);
    CGraphicsView::paintEvent(event);
}

void CManagementItem::moveEvent(QMoveEvent *event)
{
    EVENTTRANSMIT(MoveEvent);
    CGraphicsView::moveEvent(event);
}

void CManagementItem::resizeEvent(QResizeEvent *event)
{
    EVENTTRANSMIT(ResizeEvent);
    CGraphicsView::resizeEvent(event);
}

void CManagementItem::closeEvent(QCloseEvent *event)
{
    EVENTTRANSMIT(CloseEvent);
    CGraphicsView::closeEvent(event);
}

void CManagementItem::contextMenuEvent(QContextMenuEvent *event)
{
    EVENTTRANSMIT(ContextMenuEvent);
    CGraphicsView::contextMenuEvent(event);
}

void CManagementItem::dragEnterEvent(QDragEnterEvent *event)
{
    EVENTTRANSMIT(DragEnterEvent);
    event->setDropAction(Qt::MoveAction);
    event->accept();
    //CGraphicsView::dragEnterEvent(event);
}

void CManagementItem::dragMoveEvent(QDragMoveEvent *event)
{
    EVENTTRANSMIT(DragMoveEvent);
    //CGraphicsView::dragMoveEvent(event);
}

void CManagementItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    EVENTTRANSMIT(DragLeaveEvent);
    //CGraphicsView::dragLeaveEvent(event);
}

void CManagementItem::dropEvent(QDropEvent *event)
{
    EVENTTRANSMIT(DropEvent);
    QMimeData *data = const_cast<QMimeData *>(event->mimeData());
    if(data)
    {
        QVariant pData = data->property(DROPDATA);
        if(pData.isNull())
        {
            return;
        }
        QVariantMap attr = pData.value<QVariantMap>();
        QPointF pos = this->mapToScene(event->pos());
        attr.insert(POSX,pos.rx());
        attr.insert(POSY,pos.ry());
        emit sig_CreateItem(attr);
        event->setDropAction(Qt::MoveAction);
        event->acceptProposedAction();
    }
    else
        CGraphicsView::dropEvent(event);
}

void CManagementItem::showEvent(QShowEvent *event)
{
    EVENTTRANSMIT(ShowEvent);
    CGraphicsView::showEvent(event);
}

void CManagementItem::hideEvent(QHideEvent *event)
{
    EVENTTRANSMIT(HideEvent);
    CGraphicsView::hideEvent(event);
}

void CManagementItem::inputMethodEvent(QInputMethodEvent *event)
{
    EVENTTRANSMIT(InputMethodEvent);
    CGraphicsView::inputMethodEvent(event);
}

bool CManagementItem::focusNextPrevChild(bool next)
{
    if(DataTransmit::viewFocusNextPrevChild(next,m_EventId))
        return true;
    return CGraphicsView::focusNextPrevChild(next);
}

void CManagementItem::scrollContentsBy(int dx, int dy)
{
    CGraphicsView::scrollContentsBy(dx,dy);
}
