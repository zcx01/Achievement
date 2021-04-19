#ifndef DRAWCHAR_H
#define DRAWCHAR_H

#include "CZBase.h"
#include <QtCharts/QChart>
using namespace  QtCharts;

class ZSeries;

class ZBaseSignalAndSlot : public CZBase
{
    Q_OBJECT
public:
    ZBaseSignalAndSlot()
    {
        connect(this,SIGNAL(sig_SendCustomAttr(QString,QVariant)),this,SLOT(slot_AttrChanged(QString,QVariant)));
    }

protected:
   virtual void AttrChanged(const QString & id ,const QVariant &pData)=0;

private slots:
    void slot_AttrChanged(const QString & id ,const QVariant &pData)
    {
        AttrChanged(id,pData);
    }
};


class DrawChar : public ZBaseSignalAndSlot , public QChart
{
//    Q_OBJECT
public:
    explicit DrawChar();
    ~DrawChar();

    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QChart *getThis();

    // CZBase interface
public:
    QString getClassName();

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // CZBase interface
protected:
    bool Asynchronous(QVariant &pData);
    virtual void attrUpdate(const QVariantMap &pDate);
    void getAttrUpdate(QVariantMap &pDate);

private:
    void AttrChanged(const QString & id ,const QVariant &pData);

private:

    void SetZSeries(ZSeries *s);

    QString GetSeriseId(const QVariantMap &pDate);

    ZSeries*                                m_ZSeries;

    QHash<QString,QAbstractSeries*>         m_Series;
};

#endif // DRAWCHAR_H
