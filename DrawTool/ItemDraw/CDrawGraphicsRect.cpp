#include "CDrawGraphicsRect.h"
#include <QPainter>

CDrawGraphicsRect::CDrawGraphicsRect(QGraphicsItem *parent) : CZBase(parent)
{

}

void CDrawGraphicsRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawRect(boundingRect());
}

QString CDrawGraphicsRect::getClassName()
{
	return "CDrawGraphicsRect";
}

void CDrawGraphicsRect::attrUpdate(const QVariantMap &pDate)
{

}
MYREGISTER(CDrawGraphicsRect)