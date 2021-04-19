#include "DrawDiamond.h"
#include <QPainter>
#include "../BaseDraw/CZStaticFun.h"

#define CenterPos 2
DrawDiamond::DrawDiamond(QGraphicsItem *parnet) : CZBase(parnet)
{

}


void DrawDiamond::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    QPolygonF polygon;
    QPointF center=boundingRect().center();
    polygon.append(center-QPointF(boundingRect().width()/CenterPos,0));
    polygon.append(center-QPointF(0,boundingRect().height()/CenterPos));
    polygon.append(center+QPointF(boundingRect().width()/CenterPos,0));
    polygon.append(center+QPointF(0,boundingRect().height()/CenterPos));
    polygon.append(center-QPointF(boundingRect().width()/CenterPos,0));
    path.addPolygon(polygon);
    painter->drawPath(path);
}

QString DrawDiamond::getClassName()
{
    return "DrawDiamond";
}

MYREGISTER(DrawDiamond)
