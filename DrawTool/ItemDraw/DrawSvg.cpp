#include "DrawSvg.h"
#if SVGEXIST
#include <QPainter>
#include "../DrawToolInclude/zattrdefine.h"
#include <QSvgRenderer>
#include <QGraphicsSceneMouseEvent>

DrawSvg::DrawSvg(QGraphicsItem *parnet) : CZBase(parnet) ,CGraphicsSvgItem(parnet)
{
    renderer = new QSvgRenderer;
}

void DrawSvg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsSvgItem::paint(painter,option,widget);
}

CGraphicsSvgItem *DrawSvg::getThis()
{
    return (CGraphicsSvgItem*)this;
}

void DrawSvg::setBounding(QRectF &bound)
{
    getThis()->prepareGeometryChange();
    setBoundingRect(bound);
}
QString DrawSvg::getClassName()
{
    return "DrawSvg";
}

void DrawSvg::attrUpdate(const QVariantMap &pDate)
{
    QRectF rect = ((CZBase*)this)->boundingRect();//设置了才生效
    renderer->load(pDate.value(SVGFILENAME).toString());
    getThis()->setSharedRenderer(renderer);
    getThis()->setElementId(pDate.value(SVGELEMENTID).toString());
    if(!rect.isNull())
        getThis()->setBoundingRect(rect);
    else
        CZBase::setBounding(getThis()->boundingRect());
    //black->setElementId(QLatin1String("background"));
}

void DrawSvg::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mousePressEvent(event);
    CGraphicsSvgItem::mousePressEvent(event);
    if(getThis()->flags() & ItemIsMovable)
    {
        event->accept();
    }
}

void DrawSvg::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    CGraphicsSvgItem::mouseMoveEvent(event);
    CZBase::mouseMoveEvent(event);
    if(getThis()->flags() & ItemIsMovable)
    {
        emit CZBase::xChanged();
        emit CZBase::yChanged();
    }
}

MYREGISTER(DrawSvg)
#endif
