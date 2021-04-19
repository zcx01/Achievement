#ifndef DRAWDIAMOND_H
#define DRAWDIAMOND_H

/*******************************************************
    created     :   2019/11/26
    file base	:   DrawRect.h
    author      :   zcx
    purpose     :	画菱形
*******************************************************/
#include <QObject>
#include "../BaseDraw/CZBase.h"

class DrawDiamond : public CZBase
{
    Q_OBJECT
public:
    explicit DrawDiamond(QGraphicsItem *parnet = NULL);

    // QGraphicsItem interface
    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
    virtual QString getClassName();
signals:

public slots:
};

#endif // DRAWDIAMOND_H
