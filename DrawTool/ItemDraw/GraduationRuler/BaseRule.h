#ifndef BASERULE_H
#define BASERULE_H

#include "../BaseDraw/CZBase.h"

class BaseRule : public CZBase
{
    Q_OBJECT
public:
    explicit BaseRule();
    virtual ~BaseRule();

    virtual double ScaleConverCoord(const double &scale);

    virtual double CoordConverScale(const double &coord);

protected:

    void initData();

    void DrawScale(QPainter *p);

    void CalPointF(QList<QPointF> &pointFs);

    double      m_Max;
    double      m_Mix;
    double      m_Length;
    QPointF     m_StartPointF;
};

#endif // BASERULE_H
