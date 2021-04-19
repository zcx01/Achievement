#include "DrawEllipse.h"
#include <QPainter>
#include "../BaseDraw/ComputeGeometry.h"
#include "../BaseDraw/CZStaticFun.h"
#include <QRegion>
#include <QDebug>

DrawEllipse::DrawEllipse(QGraphicsItem *parnet) : CZBase(parnet)
{

}


void DrawEllipse::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(boundingRect());
}

void DrawEllipse::AddScene(QGraphicsScene *s)
{
    connect(s,SIGNAL(selectionChanged()),this,SLOT(slot_SelectdChanged()));
}

QString DrawEllipse::getClassName()
{
    return "DrawEllipse";
}
bool DrawEllipse::isContainPos(QPointF pos)
{
    QRegion region(boundingRect().toRect(),QRegion::Ellipse);
    return region.contains(mapFromScene(pos).toPoint());

}

void DrawEllipse::slot_SelectdChanged()
{
    setAttr(BRUSHINDEX,isSelected() ? 1 : 0);
    QStringList penString = m_Attrs.value(PENS).toString().split(BJOIN);
    int penIndex = m_Attrs.value(PENINDEX).toInt();
    m_Pen = CZStaticFun::QStringToQPen(penString.value(penIndex));

    QStringList brushString = m_Attrs.value(BRUSHS).toString().split(BJOIN);
    int brushIndex = m_Attrs.value(BRUSHINDEX).toInt();
    m_Brush =CZStaticFun::QStringToQBrush(brushString.value(brushIndex));
}
MYREGISTER(DrawEllipse)
