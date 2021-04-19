#ifndef DRAWSVG_H
#define DRAWSVG_H

#if SVGEXIST
/*******************************************************
    created     :   2019/11/26
    file base	:   DrawRect.h
    author      :   zcx
    purpose     :	画SVG图
*******************************************************/
#include <QObject>
#include <QGraphicsSvgItem>//在.pro中加入svg
#include "../BaseDraw/CZBase.h"

class CGraphicsSvgItem  : public QGraphicsSvgItem
{
    friend class DrawSvg;
public:
    explicit CGraphicsSvgItem(QGraphicsItem *parnet = NULL): QGraphicsSvgItem(parnet){}

    void setBoundingRect(QRectF boundingRect ){m_BoundingRect = boundingRect;}

    QRectF boundingRect() const
    {
        if(!m_BoundingRect.isNull())
            return m_BoundingRect;
        return QGraphicsSvgItem::boundingRect();
    }

private:
    QRectF m_BoundingRect;
};

class DrawSvg : public CZBase , public CGraphicsSvgItem
{
    //Q_OBJECT
public:
    explicit DrawSvg(QGraphicsItem *parnet = NULL);

    // QGraphicsItem interface
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
    virtual QString getClassName();
signals:

public:
    CGraphicsSvgItem *getThis();

    void setBounding(QRectF &bound);
protected:
    void attrUpdate(const QVariantMap &pDate);

private:
    QSvgRenderer *renderer;

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif
#endif // DRAWSVG_H
