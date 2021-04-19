#ifndef CHARTVIEWTOOL_H
#define CHARTVIEWTOOL_H

#include "CZBaseTool.h"
#include <QRubberBand>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QChart>
#include <QScopedPointer>

using namespace QtCharts;

class QChartViewToolPrivate;

class ChartViewTool : public CZBaseTool
{
    Q_OBJECT
    friend class QChartViewToolPrivate;
    Q_ENUMS(RubberBand)
public:
    enum  RubberBand {
        NoRubberBand = 0x0,
        VerticalRubberBand = 0x1,
        HorizontalRubberBand = 0x2,
        RectangleRubberBand = 0x3
    };

    Q_DECLARE_FLAGS(RubberBands, RubberBand)
    explicit ChartViewTool(QObject *parent = nullptr);


    void setRubberBand(const RubberBands &rubberBands);
    RubberBands rubberBand() const;
public:
    QString getClassName();
    void upDataTool(CZBase *item);
    void addItem(CZBase *item);
    void removeItem(CZBase *item);

    QScopedPointer<QChartViewToolPrivate> d_ptr;

protected:


    // CZBaseTool interface
protected:
    bool viewResizeEvent(QResizeEvent *event);
    bool viewMousePressEvent(QMouseEvent *event);
    bool viewMouseMoveEvent(QMouseEvent *event);
    bool viewMouseReleaseEvent(QMouseEvent *event);
};


class  QChartViewToolPrivate
{
public:
    explicit QChartViewToolPrivate(ChartViewTool *q, QChart *chart = 0);
    virtual ~QChartViewToolPrivate();
    void setChart(QChart *chart);
    void resize();

protected:
    ChartViewTool *q_ptr;

public:
    QGraphicsScene *m_scene;
    QChart *m_chart;
    QPoint m_rubberBandOrigin;
#ifndef QT_NO_RUBBERBAND
    QRubberBand *m_rubberBand;
#endif
    ChartViewTool::RubberBands m_rubberBandFlags;
};
#endif // CHARTVIEWTOOL_H
