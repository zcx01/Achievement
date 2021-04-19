#ifndef CDRAWLINE_H
#define CDRAWLINE_H
/*******************************************************
    created     :   2019/08/21
    file base	:   CDrawLine.h
    author      :   zcx
    purpose     :	画线
*******************************************************/
#include "../BaseDraw/CZBase.h"
#include <QPen>

class CDrawLine : public CZBase
{
public:
    CDrawLine();

    // QGraphicsItem interface
public:
    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
public:
    virtual QString getClassName();

    // CZBase interface
protected:
    virtual void attrUpdate(const QVariantMap &pDate);

private:

    QPen    m_Pen;
};

#endif // CDRAWLINE_H
