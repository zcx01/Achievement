#include "DrawRect.h"
#include <QPainter>
#include "../BaseDraw/CZStaticFun.h"

DrawRect::DrawRect(QGraphicsItem *parnet) : CZBase(parnet)
{

}


void DrawRect::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());
}

QString DrawRect::getClassName()
{
    return "DrawRect";
}

MYREGISTER(DrawRect)
