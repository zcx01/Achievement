#include "DisPlayName.h"
#include "../DrawToolInclude/itemtooldefine.h"
#include <QGraphicsScene>
#include <CZStaticFun.h>
#include "hfdefine.h"
#include <QTextCursor>
#include <QTextDocument>
#include <QKeyEvent>
#include <QDebug>
#include "../DrawToolPublic/ZGraphicsTextItem.h"
///////
DisPlayName::DisPlayName()
{

}


QString DisPlayName::getClassName()
{
    return "DisPlayName";
}

void DisPlayName::upDataTool(CZBase *item)
{
    D_ISNULLR(item,);
    QVariantMap attr = item->getAttrs();

    QString name = attr.value(ITEMNAME).toString();
    ZGraphicsTextItem* textItem = dynamic_cast<ZGraphicsTextItem *>(m_TextItems.value(item));
    if(name.isEmpty())
    {
        if(textItem)
        {
            textItem->document()->clear();
        }
        return;
    }


    if(!textItem)
    {
        textItem=new ZGraphicsTextItem();
        if(!attr.value(EBLEEDIT,true).toBool()) textItem->setTextInteractionFlags(Qt::NoTextInteraction);
        textItem->setFont(QFont());//一定要设置字体
        item->scene()->addItem(textItem);
        m_TextItems.insert(item,textItem);
        textItem->setParentItem(item);
        connect(textItem,SIGNAL(sig_EditFinsh(QGraphicsTextItem*)),this,
                SLOT(slot_ContentsChanged(QGraphicsTextItem*)));
    }
    else
    {
        textItem->document()->clear();
    }
    connect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_BoundChanged(QString,QString)),Qt::UniqueConnection);
    QTextCharFormat charFormat;

    QBrush brush = CZStaticFun::QStringToQColor(attr.value(NAMEBRUSH).toString());
    if(brush.color().isValid())
        charFormat.setBackground(brush);

    QPen pen = CZStaticFun::QStringToQPen(attr.value(NAMEPEN).toString());
    charFormat.setFontWeight(pen.width());
    charFormat.setForeground(pen.color());

    QFont font =CZStaticFun::QStringToQFont(attr.value(NAMEFONT).toString());

    charFormat.setFont(font);
    //换行计算
    if(!attr.value(EBLEEDIT,true).toBool())
    {
        QFontMetrics metrics(font);

        if(metrics.width(name) > item->boundingRect().width())
        {
            name.insert(name.size()/2,"\n");
        }
    }

    textItem->textCursor().insertText(name,charFormat);

    //计算位置
    int type = attr.value(NAMEPOS).toInt();

    QPointF pos = CZStaticFun::castShowPoint(item->boundingRect(),textItem->boundingRect(),type);
    if(!attr.value(ISITEMIN).toBool())
    {
        switch (type) {
        case 0:
            pos.setX(pos.x() - textItem->boundingRect().width());
            break;
        case 1:
            pos.setX(pos.x() + textItem->boundingRect().width());
            break;
        case 2:
            pos.setX(pos.x() - textItem->boundingRect().width());
            break;
        case 3:
            pos.setX(pos.x() + textItem->boundingRect().width());
            break;
        case 4:
            break;
        case 5:
            pos.setY(pos.y() - textItem->boundingRect().height());
            break;
        case 6:
            pos.setY(pos.y() + textItem->boundingRect().height());
            break;
        case 7:
            pos.setX(pos.x() - textItem->boundingRect().width());
            break;
        case 8:
            pos.setX(pos.x() + textItem->boundingRect().width());
            break;
        default:
            pos.setX(pos.x() - textItem->boundingRect().width());
            pos.setY(pos.y() - textItem->boundingRect().height());
            break;
        }
    }
    QPointF distance = CZStaticFun::QStringToQPointF(attr.value(NAMEDIS).toString());
    pos+=distance;
    textItem->setPos(pos);
}

void DisPlayName::removeItem(CZBase *item)
{
    m_TextItems.remove(item);
}

void DisPlayName::setEditItem(CZDRAW::EditStatus state, CZBase *item)
{
    //    QGraphicsSimpleTextItem* textItem = m_TextItems.value(item);
    //    D_ISNULLR(textItem,);
    //    if(state)
    //    {
    //        textItem->setText("");
    //    }
    QGraphicsTextItem* textItem = m_TextItems.value(item);
    D_ISNULLR(textItem,);
    if(state != CZDRAW::NoEdit)
    {
        textItem->document()->clear();
        disconnect(item,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_BoundChanged(QString,QString)));
    }
}

bool DisPlayName::itemKeyPressEvent(QKeyEvent *event, QGraphicsItem *sourceItem)
{
    //    if(event->key() == Qt::Key_F2)
    //    {
    //        QGraphicsTextItem* textItem = m_TextItems.value((CZBase*)sourceItem);
    //        D_ISNULLR(textItem,false);
    //        textItem->setTextInteractionFlags(Qt::TextEditable);
    //        textItem->setActive(true);
    //        textItem->setFocus();
    //    }
    return false;
}

void DisPlayName::slot_ContentsChanged(QGraphicsTextItem *textItem)
{
    CZBase *item = m_TextItems.key(textItem);
    D_ISNULLR(item,);
    item->setAttr(ITEMNAME,textItem->toPlainText());
    upDataTool(item);
}

void DisPlayName::slot_BoundChanged(QString id, QString attr)
{
    CZBase *item = getItemById(id);
    if(attr == BOUNDRECT)
    {
        upDataTool(item);
    }

}

MYREGISTER(DisPlayName)
