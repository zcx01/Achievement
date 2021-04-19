#include "CZBase.h"
#include <qtconcurrentrun.h>
#include <QFuture>
#include <QUuid>
#include "CZStaticFun.h"
#include "DataTransmit.h"
#include <QGraphicsScene>
#include <QPainter>


#define EVENTTR(v) if(DataTransmit::item##v(event,this,m_EventId)) return;

bool CZBase::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if(DataTransmit::itemSceneEventFilter(watched,event,this,m_EventId))
    {
        return true;
    }
    return QGraphicsObject::sceneEventFilter(watched,event);
}

bool CZBase::sceneEvent(QEvent *event)
{
    if(DataTransmit::itemSceneEvent(event,this,m_EventId))
    {
        return true;
    }
    return QGraphicsObject::sceneEvent(event);
}

void CZBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    EVENTTR(ContextMenuEvent);
    QGraphicsObject::contextMenuEvent(event);
}

void CZBase::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    EVENTTR(DragEnterEvent);
    QGraphicsObject::dragEnterEvent(event);
}

void CZBase::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    EVENTTR(DragLeaveEvent);
    QGraphicsObject::dragLeaveEvent(event);
}

void CZBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    EVENTTR(DragMoveEvent);
    QGraphicsObject::dragMoveEvent(event);
}

void CZBase::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    EVENTTR(DropEvent);
    QGraphicsObject::dropEvent(event);
}

void CZBase::focusInEvent(QFocusEvent *event)
{
    EVENTTR(FocusInEvent);
    QGraphicsObject::focusInEvent(event);
}

void CZBase::focusOutEvent(QFocusEvent *event)
{
    EVENTTR(FocusOutEvent);
    QGraphicsObject::focusOutEvent(event);
}

void CZBase::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    EVENTTR(HoverEnterEvent);
    QGraphicsObject::hoverEnterEvent(event);
}

void CZBase::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    EVENTTR(HoverMoveEvent);
    QGraphicsObject::hoverMoveEvent(event);
}

void CZBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    EVENTTR(HoverLeaveEvent);
    QGraphicsObject::hoverLeaveEvent(event);
}

void CZBase::keyPressEvent(QKeyEvent *event)
{
    EVENTTR(KeyPressEvent);
    QGraphicsObject::keyPressEvent(event);
}

void CZBase::keyReleaseEvent(QKeyEvent *event)
{
    EVENTTR(KeyReleaseEvent);
    QGraphicsObject::keyReleaseEvent(event);
}

void CZBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    EVENTTR(MousePressEvent);
    QGraphicsObject::mousePressEvent(event);
}

void CZBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{    
    EVENTTR(MouseMoveEvent);
    QGraphicsObject::mouseMoveEvent(event);
}

void CZBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{   
    EVENTTR(MouseReleaseEvent);
    QGraphicsObject::mouseReleaseEvent(event);
}

void CZBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{   
    EVENTTR(MouseDoubleClickEvent);
    QGraphicsObject::mouseDoubleClickEvent(event);
}

void CZBase::wheelEvent(QGraphicsSceneWheelEvent *event)
{   
    EVENTTR(WheelEvent);
    QGraphicsObject::wheelEvent(event);
}

void CZBase::inputMethodEvent(QInputMethodEvent *event)
{
    EVENTTR(InputMethodEvent);
    QGraphicsObject::inputMethodEvent(event);
}

QVariant CZBase::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(DataTransmit::itemItemChange(change,value,this,m_EventId))
        return value;
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        QSize size = QSize(getThis()->boundingRect().width(),getThis()->boundingRect().height());
        QRectF inRect(newPos,size);
        if (!rect.contains(inRect)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right()-size.width(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom()-size.height(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    return QGraphicsObject::itemChange(change,value);
}

////////////////////////////////////////////////////////////////////////////////////////////

void CZBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    paintOver(painter,option,widget);
}

void CZBase::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

qint64 CZBase::m_LastOrder = -1;
////////////////////////////////////////////////////////////////////////////////////////////
CZBase::CZBase(QGraphicsItem *parnet):QGraphicsObject(parnet)
{
    ++m_LastOrder;
    m_Order = m_LastOrder;
    m_Edit = CZDRAW::NoEdit;
    m_MouseButtons = acceptedMouseButtons();
    setId(QUuid::createUuid().toString());
    ConnectSig(true);
}

CZBase::~CZBase()
{

}

void CZBase::resetOrder()
{
    m_LastOrder = -1;
}

int CZBase::getOrder()
{
    return m_Order;
}

bool CZBase::loadFile(const QString &fileName, bool isAsyn)
{
    if(isAsyn)
    {
        QtConcurrent::run(this,&CZBase::load,fileName);
    }
    else
    {
        return load(fileName);
    }
    return true;
}

void CZBase::setId(QString id)
{
    sendAttrChanged(IDD);
    m_Attrs.insert(IDD,id);
}

QString CZBase::getId()
{
   return m_Attrs.value(IDD).toString();
}

void CZBase::setAttrs(const QVariantMap &attrs)
{
    QString id = getId();
    m_Attrs = attrs;
    if(m_Attrs.value(IDD).toString().isEmpty())
    {
        setId(id);
    }
    upDateAttr(m_Attrs);
    getThis()->update(boundingRect());
}

QVariantMap CZBase::getAttrs()
{
    m_Attrs.insert(ACCEPTDROPS,getThis()->acceptDrops());
    m_Attrs.insert(NOACTIVE,!getThis()->isActive());
    m_Attrs.insert(NOENABLED,(int)!getThis()->isEnabled());
    m_Attrs.insert(FLAGS,(int)getThis()->flags());
    m_Attrs.insert(NOOPACITY,1-getThis()->opacity());
    m_Attrs.insert(POSX,getThis()->x());
    m_Attrs.insert(POSY,getThis()->y());
    m_Attrs.insert(ROTATION,getThis()->rotation());
    m_Attrs.insert(SCALE,getThis()->scale());
    m_Attrs.insert(SELECTED,getThis()->isSelected());
    m_Attrs.insert(NOVISIBLE,(int)!getThis()->isVisible());
    m_Attrs.insert(ZValue,getThis()->zValue());
    m_Attrs.insert(BOUNDRECT,CZStaticFun::QRectFToQString(getThis()->boundingRect()));
    getAttrUpdate(m_Attrs);
    return m_Attrs;
}

//QVariant CZBase::getAttr(const QString &key)
//{
//    return m_Attrs.value(key);
//}

void CZBase::setAttr(const QString &key, const QVariant &attr, bool isUpdateAll)
{
    m_Attrs.insert(key,attr);
    if(isUpdateAll)
    {
        upDateAttr(m_Attrs);
    }
}

QString CZBase::getClassName()
{
    if(metaObject())
    {
        if(strcmp(metaObject()->className(),"CZBase") != 0)
        {
            return metaObject()->className();
        }
    }
    return "";
}

QGraphicsItem *CZBase::getThis()
{
    return this;
}

bool CZBase::Asynchronous(QVariant &pData)
{
    return true;
}

bool CZBase::load(QString fileName)
{
    return false;
}

void CZBase::attrUpdate(const QVariantMap &pDate)
{

}

void CZBase::getAttrUpdate(QVariantMap &pDate)
{

}

void CZBase::SelectdChanged(bool selected)
{

}

void CZBase::asynFinish()
{

}

//--------------------------------------重写-----------------
void CZBase::setPos(const QPointF &pos)
{
    setPos(pos.x(),pos.y());
}

QPointF CZBase::pos()
{
    return getThis()->pos();
}

void CZBase::setPos(qreal x, qreal y)
{
    m_Attrs.insert(POSX,x);
    m_Attrs.insert(POSX,y);
    getThis()->setPos(x,y);
}

void CZBase::setRotation(qreal angle)
{
    m_Attrs.insert(ROTATION,angle);
    getThis()->setRotation(angle);
}

qreal CZBase::rotation()
{
    return getThis()->rotation();
}

void CZBase::setScale(qreal factor)
{
    m_Attrs.insert(SCALE,factor);
    getThis()->setScale(factor);
}

qreal CZBase::scale()
{
    return getThis()->scale();
}

void CZBase::setAcceptDrops(bool on)
{
     m_Attrs.insert(ACCEPTDROPS,on);
     getThis()->setAcceptDrops(on);
}

bool CZBase::acceptDrops()
{
    return getThis()->acceptDrops();
}

void CZBase::setActive(bool active)
{
    m_Attrs.insert(NOACTIVE,!active);
    getThis()->setActive(active);
}

bool CZBase::isActive()
{
    return getThis()->isActive();
}

void CZBase::setEnabled(bool enabled)
{
    m_Attrs.insert(NOENABLED,!enabled);
    getThis()->setEnabled(enabled);
}

bool CZBase::isEnabled()
{
    return getThis()->isEnabled();
}

void CZBase::setFlags(QGraphicsItem::GraphicsItemFlags flags)
{
    m_Attrs.insert(FLAGS,(int) flags);
    getThis()->setFlags(flags);
}

QGraphicsItem::GraphicsItemFlags CZBase::flags()
{
    return getThis()->flags();
}

void CZBase::setFocus(Qt::FocusReason focusReason)
{
    m_Attrs.insert(CANSETFOCUS,(int)focusReason);
    getThis()->setFocus(focusReason);
}

bool CZBase::hasFocus()
{
    return getThis()->hasFocus();
}

void CZBase::clearFocus()
{
    getThis()->clearFocus();
}

void CZBase::setOpacity(qreal opacity)
{
    m_Attrs.insert(NOOPACITY,1-opacity);
    getThis()->setOpacity(opacity);
}

qreal CZBase::opacity()
{
    return getThis()->opacity();
}

void CZBase::setX(qreal x)
{
    m_Attrs.insert(POSX,x);
    getThis()->setX(x);
}

void CZBase::setY(qreal y)
{
    m_Attrs.insert(POSY,y);
    getThis()->setY(y);
}

void CZBase::setToolTip(const QString &toolTip)
{
    m_Attrs.insert(TOOLTIP,toolTip);
    getThis()->setToolTip(toolTip);
}

QString CZBase::toolTip()
{
    return getThis()->toolTip();
}

void CZBase::setVisible(bool visible)
{
    m_Attrs.insert(NOVISIBLE,!visible);
    getThis()->setVisible(visible);
}

bool CZBase::isVisible()
{
    return getThis()->isVisible();
}

void CZBase::setZValue(qreal z)
{
    m_Attrs.insert(ZValue,z);
    getThis()->setZValue(z);
}

qreal CZBase::zValue()
{
    return getThis()->zValue();
}

void CZBase::setTransformOriginPoint(const QPointF &origin)
{
    getThis()->setTransformOriginPoint(origin);
}

bool CZBase::isSelected()
{
    return getThis()->isSelected();
}

void CZBase::setAcceptedMouseButtons(Qt::MouseButtons buttons)
{
    getThis()->setAcceptedMouseButtons(buttons);
    m_MouseButtons = buttons;
}

void CZBase::upDateData(const QVariant &pData, bool isAsyn)
{
    m_UpDateData = pData;
    if(isAsyn)
    {
        QtConcurrent::run(this,&CZBase::AsynchronousFun,m_UpDateData);
    }
    else
    {
        AsynchronousFun(m_UpDateData);
    }
}

QVariant CZBase::getDateData()
{
    return m_UpDateData;
}

bool CZBase::isContainMousePos(QPointF pos)
{
    bool isContain = isContainPos(pos);
    if(!isContain)
    {
        getThis()->setAcceptedMouseButtons(Qt::NoButton);
    }
    else if(m_MouseButtons != getThis()->acceptedMouseButtons())
    {
        getThis()->setAcceptedMouseButtons(m_MouseButtons);
    }
    return isContain;
}

bool CZBase::isContainPos(QPointF pos)
{
    return true;
}

void CZBase::SendCustomAttr(const QString &id,const QVariant &data)
{
    emit sig_SendCustomAttr(id,data);
}

void CZBase::setEdit(CZDRAW::EditStatus state)
{
    m_Edit = state;
}

void CZBase::setBounding(QRectF bound)
{
    prepareGeometryChange();
    m_BoundRect = bound;
    m_Attrs.insert(BOUNDRECT,CZStaticFun::QRectFToQString(bound));
}

void CZBase::sendAttrChanged(QString attrkey)
{
    emit sig_AttrChanged(getId(),attrkey);
}

void CZBase::setSelected(bool selected)
{
    getThis()->setSelected(selected);
    m_Attrs.insert(SELECTED,getThis()->isSelected());
    SelectdChanged(getThis()->isSelected());
}

//---------------------------------------------
void CZBase::slot_AsynFinish()
{
    getThis()->update(boundingRect());
    asynFinish();
}

void CZBase::slot_EnabledChanged()
{
    m_Attrs.insert(NOENABLED,!isEnabled());
    sendAttrChanged(NOENABLED);
}

void CZBase::slot_OpacityChanged()
{
    m_Attrs.insert(NOOPACITY,1-opacity());
    sendAttrChanged(NOOPACITY);
}

void CZBase::slot_ParentChanged()
{
    CZBase *parent = dynamic_cast<CZBase *>(parentItem());
    if(parent)
    {
        QString parentId = parent->getId();
        m_Attrs.insert(PARENTITEM,parentId);
    }
    sendAttrChanged(PARENTITEM);
}

void CZBase::slot_RotationChanged()
{
    m_Attrs.insert(ROTATION,rotation());
    sendAttrChanged(ROTATION);
}

void CZBase::slot_ScaleChanged()
{
    m_Attrs.insert(SCALE,scale());
    sendAttrChanged(SCALE);
}

void CZBase::slot_VisibleChanged()
{
    m_Attrs.insert(NOVISIBLE,!isVisible());
    sendAttrChanged(NOVISIBLE);
}

void CZBase::slot_XChanged()
{
    m_Attrs.insert(POSX,x());
    sendAttrChanged(POSX);
}

void CZBase::slot_YChanged()
{
    m_Attrs.insert(POSY,y());
    sendAttrChanged(POSY);
}

void CZBase::slot_ZChanged()
{
    m_Attrs.insert(ZValue,zValue());
    sendAttrChanged(ZValue);
}

void CZBase::AsynchronousFun(QVariant &pData)
{
    Asynchronous(pData);
    emit sig_AsynFinish();
}

void CZBase::upDateAttr(const QVariantMap &pDate)
{
    setItemType(pDate.value(ITEMTYPE).toString());
    getThis()->setAcceptDrops(pDate.value(ACCEPTDROPS).toBool());
    getThis()->setActive(!pDate.value(NOACTIVE).toBool());
    getThis()->setEnabled(!pDate.value(NOENABLED).toBool());
    int flgs = pDate.value(FLAGS).toInt();
    if(flgs)getThis()->setFlags((GraphicsItemFlags)flgs);
    if(pDate.value(CANSETFOCUS).toBool())getThis()->setFocus((Qt::FocusReason)pDate.value(FOCUS).toInt());
    getThis()->setOpacity(1-pDate.value(NOOPACITY).toDouble());
    getThis()->setX(pDate.value(POSX).toDouble());
    getThis()->setY(pDate.value(POSY).toDouble());
    m_BoundRect = CZStaticFun::QStringToQRectF(pDate.value(BOUNDRECT).toString());
    getThis()->setTransformOriginPoint(CZStaticFun::castShowPoint(m_BoundRect,QRectF(),pDate.value(ORIGINTYPE).toInt()));
    getThis()->setRotation(pDate.value(ROTATION).toDouble());
    getThis()->setScale(pDate.value(SCALE,getThis()->scale()).toDouble());
    getThis()->setSelected(pDate.value(SELECTED).toBool());
    getThis()->setToolTip(pDate.value(TOOLTIP).toString());
    getThis()->setVisible(!pDate.value(NOVISIBLE).toBool());
    getThis()->setZValue(pDate.value(ZValue).toDouble());
    setProperty(BACKGOUNDITEM,pDate.value(BACKGOUNDITEM).toBool());
    getThis()->setData(BACKGOUNDINDEX,pDate.value(BACKGOUNDITEM).toBool());

    QStringList penString = m_Attrs.value(PENS).toString().split(BJOIN);
    int penIndex = m_Attrs.value(PENINDEX).toInt();
    m_Pen = CZStaticFun::QStringToQPen(penString.value(penIndex));

    QStringList brushString = m_Attrs.value(BRUSHS).toString().split(BJOIN);
    int brushIndex = m_Attrs.value(BRUSHINDEX).toInt();
    m_Brush =CZStaticFun::QStringToQBrush(brushString.value(brushIndex));

    attrUpdate(pDate);
}

void CZBase::ConnectSig(const bool &state)
{
    if(state)
    {
        connect(this,SIGNAL(sig_AsynFinish()),this,SLOT(slot_AsynFinish()));
        connect(this,SIGNAL(enabledChanged() ),this,SLOT(slot_EnabledChanged() ));
        connect(this,SIGNAL(opacityChanged() ),this,SLOT(slot_OpacityChanged() ));
        connect(this,SIGNAL(parentChanged()  ),this,SLOT(slot_ParentChanged()  ));
        connect(this,SIGNAL(rotationChanged()),this,SLOT(slot_RotationChanged()));
        connect(this,SIGNAL(scaleChanged()   ),this,SLOT(slot_ScaleChanged()   ));
        connect(this,SIGNAL(visibleChanged() ),this,SLOT(slot_VisibleChanged() ));
        connect(this,SIGNAL(xChanged()       ),this,SLOT(slot_XChanged()       ));
        connect(this,SIGNAL(yChanged()       ),this,SLOT(slot_YChanged()       ));
        connect(this,SIGNAL(zChanged()       ),this,SLOT(slot_ZChanged()       ));
    }
    else
    {
        disconnect(this,SIGNAL(sig_AsynFinish()),this,SLOT(slot_AsynFinish()));
        disconnect(this,SIGNAL(enabledChanged() ),this,SLOT(slot_EnabledChanged() ));
        disconnect(this,SIGNAL(opacityChanged() ),this,SLOT(slot_OpacityChanged() ));
        disconnect(this,SIGNAL(parentChanged()  ),this,SLOT(slot_ParentChanged()  ));
        disconnect(this,SIGNAL(rotationChanged()),this,SLOT(slot_RotationChanged()));
        disconnect(this,SIGNAL(scaleChanged()   ),this,SLOT(slot_ScaleChanged()   ));
        disconnect(this,SIGNAL(visibleChanged() ),this,SLOT(slot_VisibleChanged() ));
        disconnect(this,SIGNAL(xChanged()       ),this,SLOT(slot_XChanged()       ));
        disconnect(this,SIGNAL(yChanged()       ),this,SLOT(slot_YChanged()       ));
        disconnect(this,SIGNAL(zChanged()       ),this,SLOT(slot_ZChanged()       ));
    }
}

QRectF CZBase::boundingRect() const
{
    return m_BoundRect;
}

void CZBase::setEventId(const QString &id)
{
    m_EventId = id;
}

void CZBase::setItemType(const QString &type)
{
    m_ItemType = type;
}

QString CZBase::getItemType()
{
    if(m_ItemType.isEmpty())
    {
        return getClassName();
    }
    return m_ItemType;
}


bool CZBase::isAttrValueValid(const QString &key)
{
    return m_Attrs.value(key).isValid();
}

QVariant::Type CZBase::getKeyType(const QString &key)
{
    return QVariant::Invalid;
}

void CZBase::AddScene(QGraphicsScene *s)
{

}
