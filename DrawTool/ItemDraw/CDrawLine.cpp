#include "CDrawLine.h"
#include <QPainter>
#include "../BaseDraw/CZStaticFun.h"
#include "../DrawToolInclude/zattrdefine.h"

CDrawLine::CDrawLine()
{

}


void CDrawLine::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(m_Pen);
    painter->drawLine(boundingRect().x(),boundingRect().y(),boundingRect().width(),boundingRect().height());
}

QString CDrawLine::getClassName()
{
    return "CDrawLine";
}

void CDrawLine::attrUpdate(const QVariantMap &pDate)
{
    m_Pen  = CZStaticFun::QStringToQPen(pDate.value(LINEPEN).toString());
}
MYREGISTER(CDrawLine)
