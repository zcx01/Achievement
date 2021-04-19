#ifndef DSECTOR_H
#define DSECTOR_H

#include "../BaseDraw/CZBase.h"

class DSector : public CZBase
{
    Q_OBJECT
public:
    explicit DSector();

signals:

public slots:

    // CZBase interface
public:
    QString getClassName();

    // CZBase interface
public:
    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
protected:
    void attrUpdate(const QVariantMap &pDate);

private:
    int  m_S;
    int  m_E;
};

#endif // DSECTOR_H
