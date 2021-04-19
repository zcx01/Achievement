#ifndef CDRAWGRAPHICSRECT_H
#define CDRAWGRAPHICSRECT_H

#include "../BaseDraw/CZBase.h"

class CDrawGraphicsRect : public CZBase
{
    Q_OBJECT
public:
	explicit CDrawGraphicsRect(QGraphicsItem *parent = nullptr);

public:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	virtual QString getClassName();

protected:
	virtual void attrUpdate(const QVariantMap &pDate);

public slots:
};

#endif // CDRAWGRAPHICSRECT_H