#include "AssistLine.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QWidget>
#include "hfdefine.h"
#include "../BaseDraw/ComputeGeometry.h"
#include "../DrawToolInclude/zattrdefine.h"

AssistLine::AssistLine(QGraphicsItem *parnet) : CZBase(parnet)
{
    m_Direction = horizontal;
    setAcceptedMouseButtons(Qt::NoButton);
}

void AssistLine::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF p1;
    QPointF p2;
    switch (m_Direction)
    {
    case Vertical:
        p2.setY(scene()->sceneRect().height());
        break;
    case horizontal:
        p2.setX(scene()->sceneRect().width());
        break;
    default:
        break;
    }
    painter->drawLine(p1,p2);
}

QRectF AssistLine::boundingRect() const
{
    QPointF p1;
    QPointF p2;
    QRectF rect;
    int penWidth = m_Pen.width();
    D_ISNULLR(scene(),rect);
    switch (m_Direction)
    {
    case Vertical:
        p2.setY(scene()->sceneRect().height());
        rect =QRect(-penWidth,-penWidth,penWidth,ComputeGeometry::GetLineDistance(p1,p2));
        break;
    case horizontal:
        p2.setX(scene()->sceneRect().width());
        rect =QRect(-penWidth,-penWidth,ComputeGeometry::GetLineDistance(p1,p2),penWidth);
        break;
    default:
        break;
    }
    return rect;
}

QString AssistLine::getClassName()
{
    return "AssistLine";
}

bool AssistLine::Asynchronous(QVariant &pData)
{
    m_Direction = (LineDirection)pData.toInt();
    prepareGeometryChange();
    return true;
}

void AssistLine::attrUpdate(const QVariantMap &pDate)
{
    setVisible(false);
}
MYREGISTER(AssistLine)
