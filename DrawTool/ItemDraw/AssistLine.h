#ifndef ASSISTLINE_H
#define ASSISTLINE_H
/*******************************************************
    created		:	2019/12/20
    file base   :	AssistLine.h
    author		:	zcx
    purpose		:	移动过程中的辅助线
                    要配置ID为BoundChanged,才会在BoundChanged生效
*******************************************************/
#include "../BaseDraw/CZBase.h"

class AssistLine : public CZBase
{
    Q_OBJECT
public:
    enum LineDirection
    {
        Vertical,
        horizontal
    };

    explicit AssistLine(QGraphicsItem *parnet = NULL);

    // QGraphicsItem interface
    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QRectF boundingRect() const;

    // CZBase interface
    virtual QString getClassName();


    // CZBase interface
protected:
    bool Asynchronous(QVariant &pData);

private:
    LineDirection m_Direction;

    // CZBase interface
protected:
    void attrUpdate(const QVariantMap &pDate);

private:
};

#endif // ASSISTLINE_H
