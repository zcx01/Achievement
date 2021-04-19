#ifndef DRAWELLIPSE_H
#define DRAWELLIPSE_H
/*******************************************************
    created		:	2019/12/03
    file base   :	DrawEllipse.h
    author		:	zcx
    purpose		:	画椭圆
*******************************************************/
#include <QObject>
#include "../BaseDraw/CZBase.h"

class DrawEllipse : public CZBase
{
    Q_OBJECT
public:
    explicit DrawEllipse(QGraphicsItem *parnet = 0);

signals:

public slots:

    // QGraphicsItem interface
public:
    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void AddScene(QGraphicsScene *s);

    // CZBase interface
public:
    QString getClassName();

    // CZBase interface
protected:
    bool isContainPos(QPointF pos);

    // CZBase interface
protected slots:
    void slot_SelectdChanged();
};

#endif // DRAWELLIPSE_H
