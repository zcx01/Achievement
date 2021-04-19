#ifndef DRAWRECT_H
#define DRAWRECT_H

/*******************************************************
    created     :   2019/08/21
    file base	:   DrawRect.h
    author      :   zcx
    purpose     :	画矩形
*******************************************************/
#include <QObject>
#include "../BaseDraw/CZBase.h"

class DrawRect : public CZBase
{
    Q_OBJECT
public:
    explicit DrawRect(QGraphicsItem *parnet = NULL);

    // QGraphicsItem interface
    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
    virtual QString getClassName();
signals:
};

#endif // DRAWRECT_H
