#include "DSector.h"
#include <QPainter>
#include "../BaseDraw/ComputeGeometry.h"
#include "../DrawToolInclude/zattrdefine.h"

#define span    16
DSector::DSector()
{
    m_S = 0;
    m_E = 0;
}

QString DSector::getClassName()
{
    return "DSector";
}

void DSector::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPie(this->boundingRect(),m_S * span,m_E *span);
}

void DSector::attrUpdate(const QVariantMap &pDate)
{
    m_S = 360- pDate.value(DS_EAngle).toInt();
    m_E = pDate.value(DS_EAngle).toInt()  - pDate.value(DS_SAngle).toInt();

    double lenght =  pDate.value(DS_Lenght).toDouble();
    setBounding(QRectF(0,0,lenght *2 ,lenght *2));

//    QPointF pos = this->pos();
//    getThis()->setPos(pos.x() - lenght,pos.y() - lenght);
}

MYREGISTER(DSector)
