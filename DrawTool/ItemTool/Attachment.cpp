#include "Attachment.h"
#include "CManagementItem.h"
#include "hfdefine.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "CZStaticFun.h"
#include "ZXml/CXml.h"
#include <QGraphicsLineItem>
#include "../DrawToolInclude/itemtooldefine.h"

Attachment::Attachment(QObject *parent) : CZBaseTool(parent)
{

}

QString Attachment::getClassName()
{
    return "Attachment";
}

void Attachment::upDataTool(CZBase *item)
{
    D_ISNULLR(item,);
    QVariantMap attrs = item->getAttrs();
    QString attachmentId = attrs.value(ATTACHMENTID).toString();
    if(isExitst(item->getId(),attachmentId)) return;
    if(!attachmentId.isEmpty())
    {
        CZBase* attachmentItem = getItemById(attachmentId);
        D_ISNULLR(attachmentItem,);
        D_ISNULLR(item->scene(),);
        QGraphicsLineItem *lineLine = item->scene()->
                addLine(QLineF(item->pos()+item->boundingRect().center(),
                               attachmentItem->pos()+attachmentItem->boundingRect().center()));
        lineLine->setPen(CZStaticFun::QStringToQPen(attrs.value("Pen").toString()));
        lineLine->stackBefore(item);//item在lineLine前面
        lineLine->stackBefore(attachmentItem);
        Info info;
        info.startId = item->getId();
        info.endId = attachmentId;
        info.line = lineLine;
        m_Infos.push_back(info);
        connect(attachmentItem,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_LineChanged()),Qt::UniqueConnection);
    }
    connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_LineChanged()),Qt::UniqueConnection);
}

void Attachment::addItem(CZBase *item)
{
    D_ISNULLR(item,);
}

void Attachment::removeItem(CZBase *item)
{
    D_ISNULLR(item,);
    for(int i =0; i <m_Infos.size(); i++)
    {
        Info info = m_Infos.at(i);
        if(info.startId == item->getId() || info.endId == item->getId())
        {
            QGraphicsLineItem *lineLine =info.line;
            D_ISNULLR(item->scene(),);
            item->scene()->removeItem(lineLine);
            D_Delete(lineLine);
            m_Infos.removeAt(i);
            return;
        }
    }
}

void Attachment::slot_LineChanged()
{
    CZBase* base = dynamic_cast<CZBase*>(sender());
    lineChanged(base);

}
//bool Attachment::itemMouseMoveEvent(QGraphicsSceneMouseEvent *event, QGraphicsItem *sourceItem)
//{

//}

bool Attachment::isExitst(QString startId, QString endId)
{
    foreach (Info info, m_Infos)
    {
        if(info.isExist(startId,endId))
        {
            return true;
        }
    }
    return false;
}

bool Attachment::lineChanged(CZBase *item)
{
    //CZBase *item = dynamic_cast<CZBase*>(sourceItem);
    D_ISNULLR(item,false);
    foreach (Info info, m_Infos)
    {
        QGraphicsLineItem *lineLine = NULL;
        QString attachmentId;
        CZBase* startItem = NULL;
        if(info.startId == item->getId() )
        {
            lineLine =info.line;
            attachmentId = info.endId;
            startItem = item;
        }
        else if(info.endId == item->getId())
        {
            lineLine =info.line;
            attachmentId = info.endId;
            startItem= getItemById(info.startId);
        }
        if(lineLine && startItem)
        {
            CZBase* attachmentItem = getItemById(attachmentId);
            D_ISNULLC(attachmentItem);
            lineLine->setLine(QLineF(startItem->pos()+item->boundingRect().center(),
                                     attachmentItem->pos()+attachmentItem->boundingRect().center()));
        }
    }
    return false;
}

MYREGISTER(Attachment)
