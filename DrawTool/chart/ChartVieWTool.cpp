#include "ChartViewTool.h"
#include "hfdefine.h"
#include "CManagementItem.h"
#include "../DrawToolInclude/seriesdefine.h"

ChartViewTool::ChartViewTool(QObject *parent) : CZBaseTool(parent),
    d_ptr(new QChartViewToolPrivate(this))
{

}

void ChartViewTool::setRubberBand(const RubberBands &rubberBands)
{
#ifndef QT_NO_RUBBERBAND
    d_ptr->m_rubberBandFlags = rubberBands;

    if (!d_ptr->m_rubberBandFlags) {
        delete d_ptr->m_rubberBand;
        d_ptr->m_rubberBand = 0;
        return;
    }

    if (!d_ptr->m_rubberBand) {
        d_ptr->m_rubberBand = new QRubberBand(QRubberBand::Rectangle, m_ManagmentItem);
        d_ptr->m_rubberBand->setEnabled(true);
    }
#else
    Q_UNUSED(rubberBand);
    qWarning("Unable to set rubber band because Qt is configured without it.");
#endif
}

ChartViewTool::RubberBands ChartViewTool::rubberBand() const
{
    return d_ptr->m_rubberBandFlags;
}

QString ChartViewTool::getClassName()
{
    return "ChartViewTool";
}

void ChartViewTool::upDataTool(CZBase *item)
{


}

void ChartViewTool::addItem(CZBase *item)
{
    QChart * chart = dynamic_cast<QChart *>(item->getThis());
    if(chart)
    {
        d_ptr->setChart(chart);
    }
}

void ChartViewTool::removeItem(CZBase *item)
{
    CZBase* OnlyItem = dynamic_cast<CZBase *>(d_ptr->m_chart);
    QVariantMap attr = item->getAttrs();
    attr.insert(D_ChartHandleType,DC::DeleteData);
    OnlyItem->upDateData(attr,false);
}

bool ChartViewTool::viewResizeEvent(QResizeEvent *event)
{
    d_ptr->resize();
    return false;
}

bool ChartViewTool::viewMousePressEvent(QMouseEvent *event)
{
#ifndef QT_NO_RUBBERBAND
    D_ISNULLR(d_ptr->m_chart,false);
    QRectF plotArea = d_ptr->m_chart->plotArea();
    if (d_ptr->m_rubberBand && d_ptr->m_rubberBand->isEnabled()
            && event->button() == Qt::LeftButton && plotArea.contains(event->pos())) {
        d_ptr->m_rubberBandOrigin = event->pos();
        d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin, QSize()));
        d_ptr->m_rubberBand->show();
        event->accept();
        return true;
    } else {
#endif
        return false;
#ifndef QT_NO_RUBBERBAND
    }
#endif
    return false;
}

bool ChartViewTool::viewMouseMoveEvent(QMouseEvent *event)
{
#ifndef QT_NO_RUBBERBAND
    if (d_ptr->m_rubberBand && d_ptr->m_rubberBand->isVisible()) {
        QRect rect = d_ptr->m_chart->plotArea().toRect();
        int width = event->pos().x() - d_ptr->m_rubberBandOrigin.x();
        int height = event->pos().y() - d_ptr->m_rubberBandOrigin.y();
        if (!d_ptr->m_rubberBandFlags.testFlag(VerticalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setY(rect.top());
            height = rect.height();
        }
        if (!d_ptr->m_rubberBandFlags.testFlag(HorizontalRubberBand)) {
            d_ptr->m_rubberBandOrigin.setX(rect.left());
            width = rect.width();
        }
        d_ptr->m_rubberBand->setGeometry(QRect(d_ptr->m_rubberBandOrigin.x(), d_ptr->m_rubberBandOrigin.y(), width, height).normalized());
        return true;
    } else {
#endif
        return false;
#ifndef QT_NO_RUBBERBAND
    }
#endif
    return false;
}

bool ChartViewTool::viewMouseReleaseEvent(QMouseEvent *event)
{
#ifndef QT_NO_RUBBERBAND
    if (d_ptr->m_rubberBand && d_ptr->m_rubberBand->isVisible()) {
        if (event->button() == Qt::LeftButton) {
            d_ptr->m_rubberBand->hide();
            QRectF rect = d_ptr->m_rubberBand->geometry();
            // Since plotArea uses QRectF and rubberband uses QRect, we can't just blindly use
            // rubberband's dimensions for vertical and horizontal rubberbands, where one
            // dimension must match the corresponding plotArea dimension exactly.
            if (d_ptr->m_rubberBandFlags == VerticalRubberBand) {
                rect.setX(d_ptr->m_chart->plotArea().x());
                rect.setWidth(d_ptr->m_chart->plotArea().width());
            } else if (d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
                rect.setY(d_ptr->m_chart->plotArea().y());
                rect.setHeight(d_ptr->m_chart->plotArea().height());
            }
            d_ptr->m_chart->zoomIn(rect);
            event->accept();
        }

    } else if (d_ptr->m_rubberBand && event->button() == Qt::RightButton) {
            // If vertical or horizontal rubberband mode, restrict zoom out to specified axis.
            // Since there is no suitable API for that, use zoomIn with rect bigger than the
            // plot area.
            if (d_ptr->m_rubberBandFlags == VerticalRubberBand
                || d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
                QRectF rect = d_ptr->m_chart->plotArea();
                if (d_ptr->m_rubberBandFlags == VerticalRubberBand) {
                    qreal adjustment = rect.height() / 2;
                    rect.adjust(0, -adjustment, 0, adjustment);
                } else if (d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
                    qreal adjustment = rect.width() / 2;
                    rect.adjust(-adjustment, 0, adjustment, 0);
                }
                d_ptr->m_chart->zoomIn(rect);
            } else {
                d_ptr->m_chart->zoomOut();
            }
            event->accept();
            return true;
    } else {
#endif
        return false;
#ifndef QT_NO_RUBBERBAND
    }
#endif
    return false;
}


QChartViewToolPrivate::QChartViewToolPrivate(ChartViewTool *q, QChart *chart)
    : q_ptr(q),
      m_chart(chart),
#ifndef QT_NO_RUBBERBAND
      m_rubberBand(0),
#endif
     m_rubberBandFlags(ChartViewTool::NoRubberBand)
{

}

QChartViewToolPrivate::~QChartViewToolPrivate()
{

}

void QChartViewToolPrivate::setChart(QChart *chart)
{
    D_ISNULLR(chart,);
    if (m_chart == chart)
        return;

    if(m_chart == NULL)
    {
        m_chart = chart;
    }
    else
    {
        CZBase* addItem = dynamic_cast<CZBase *>(chart);
        CZBase* item = dynamic_cast<CZBase *>(m_chart);
        if(addItem && item)
        {
            QVariantMap attr = addItem->getAttrs();
            attr.insert(D_ChartHandleType,DC::ChangedData);
            item->upDateData(attr,false);
            QObject::connect(item,SIGNAL(sig_SendCustomAttr(QString,QVariant)),addItem,SIGNAL(sig_SendCustomAttr(QString,QVariant)));
        }
    }

    resize();
}

void QChartViewToolPrivate::resize()
{
    D_ISNULLR(m_chart,);
    qreal sinA = qAbs(q_ptr->m_ManagmentItem->transform().m21());
    qreal cosA = qAbs(q_ptr->m_ManagmentItem->transform().m11());
    QSize chartSize = q_ptr->m_ManagmentItem->size();

    if (sinA == 1.0) {
        chartSize.setHeight(q_ptr->m_ManagmentItem->size().width());
        chartSize.setWidth(q_ptr->m_ManagmentItem->size().height());
    } else if (sinA != 0.0) {
        // Non-90 degree rotation, find largest square chart that can fit into the view.
        qreal minDimension = qMin(q_ptr->m_ManagmentItem->size().width(), q_ptr->m_ManagmentItem->size().height());
        qreal h = (minDimension - (minDimension / ((sinA / cosA) + 1.0))) / sinA;
        chartSize.setHeight(h);
        chartSize.setWidth(h);
    }

    m_chart->resize(chartSize);
    q_ptr->m_ManagmentItem->setMinimumSize(m_chart->minimumSize().toSize());
    q_ptr->m_ManagmentItem->setSceneRect(m_chart->geometry());
}

MYREGISTER(ChartViewTool)

