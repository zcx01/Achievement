#include "ZGraphicsTextItem.h"
#include <QKeyEvent>

ZGraphicsTextItem::ZGraphicsTextItem(QGraphicsItem *parent) :QGraphicsTextItem(parent)
{
    setTextInteractionFlags(Qt::LinksAccessibleByMouse);
}

ZGraphicsTextItem::~ZGraphicsTextItem()
{

}

void ZGraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    if(textInteractionFlags() & Qt::TextEditable)
    {
        setTextInteractionFlags(textInteractionFlags() &~ Qt::TextEditable &~ Qt::TextSelectableByKeyboard);
        emit sig_EditFinsh(this);
    }
    QGraphicsTextItem::focusOutEvent(event);
}


void ZGraphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F2)
    {
        setTextInteractionFlags(textInteractionFlags()| Qt::TextEditable | Qt::TextSelectableByKeyboard);
        setFocus();
    }
    QGraphicsTextItem::keyPressEvent(event);
}
