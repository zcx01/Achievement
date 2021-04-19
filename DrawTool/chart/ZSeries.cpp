#include "ZSeries.h"
#include "hfdefine.h"
#include "../DrawToolInclude/seriesdefine.h"
#include "../BaseDraw/CZStaticFun.h"
#include "./HfFrameReflect/cmyregistersingle.h"
#include "./HfFrameReflect/cmyregister_hf.h"
#include <QDebug>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QHorizontalPercentBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QBoxPlotSeries>
#include <QtCharts/QCandlestickSeries>


MYREGISTER(QLineSeries)
MYREGISTER(QAreaSeries)
MYREGISTER(QBarSeries)
MYREGISTER(QStackedBarSeries)
MYREGISTER(QPercentBarSeries)
MYREGISTER(QHorizontalBarSeries)
MYREGISTER(QHorizontalStackedBarSeries)
MYREGISTER(QHorizontalPercentBarSeries)
MYREGISTER(QScatterSeries)
MYREGISTER(QSplineSeries)
MYREGISTER(QBoxPlotSeries)
MYREGISTER(QCandlestickSeries)

ZSeries::ZSeries(QObject *parent) : QObject(parent)
{

}

ZSeries::~ZSeries()
{

}

QAbstractSeries *ZSeries::CreateSeries(const QVariantMap &attr, QChart *chart)
{
    QAbstractSeries *serise = static_cast<QAbstractSeries *>
            (CMyRegisterSingle::instance()->getClass(attr.value(SeriesClasName).toString()));
    D_ISNULLR(serise,NULL);
    UpSeriesData(attr,chart,serise);
    return serise;
}

void ZSeries::UpSeriesData(const QVariantMap &attr, QChart *chart, QAbstractSeries *serise)
{
    //自定义创建Series
    if(customSeriesDataChanged(attr,chart,serise)) return;

    //默认创建Series
    switch (serise->type())
    {
    case QAbstractSeries::SeriesTypeLine:                //线图
    {
        LineData(attr,chart,serise);
    }
        break;
    case QAbstractSeries::SeriesTypeArea:                //面积图
    {
        AreaData(attr,chart,serise);
    }
        break;
    case QAbstractSeries::SeriesTypeBar:                  //独立柱状图
    case QAbstractSeries::SeriesTypeStackedBar:           //堆叠柱状图
    case QAbstractSeries::SeriesTypePercentBar:           //百分比柱状图
    {
        AbstractBarData(attr,true,chart,serise);
    }
        break;
    case QAbstractSeries::SeriesTypeHorizontalBar:        //独立柱状图
    case QAbstractSeries::SeriesTypeHorizontalStackedBar: //堆叠柱状图
    case QAbstractSeries::SeriesTypeHorizontalPercentBar: //百分比柱状图
    {
        AbstractBarData(attr,false,chart,serise);
    }
        break;
    case QAbstractSeries::SeriesTypePie:
    {
        PieData(attr,chart,serise);
    }
        break;
    default:
        break;
    }
}

void ZSeries::GetSeriesData(QAbstractSeries *serise, QVariantMap &attr)
{
    if(customGetSeriesData(serise,attr)) return;
    //默认创建Series
    switch (serise->type())
    {
    case QAbstractSeries::SeriesTypeLine:                //线图
    {
        GetLineData(serise,attr);
    }
        break;
    case QAbstractSeries::SeriesTypeArea:                //面积图
    {
        GetAreaData(serise,attr);
    }
        break;
    case QAbstractSeries::SeriesTypeBar:                  //独立柱状图
    case QAbstractSeries::SeriesTypeStackedBar:           //堆叠柱状图
    case QAbstractSeries::SeriesTypePercentBar:           //百分比柱状图
    {
        GetAbstractBarData(serise,attr);
    }
        break;
    case QAbstractSeries::SeriesTypeHorizontalBar:        //独立柱状图
    case QAbstractSeries::SeriesTypeHorizontalStackedBar: //堆叠柱状图
    case QAbstractSeries::SeriesTypeHorizontalPercentBar: //百分比柱状图
    {
        GetAbstractBarData(serise,attr);
    }
        break;
    case QAbstractSeries::SeriesTypePie:
    {
        GetPieData(serise,attr);
    }
        break;
    default:
        break;
    }
}

bool ZSeries::customSeriesDataChanged(const QVariantMap &attr, QChart *chart, QAbstractSeries *serise)
{
    return false;
}

bool ZSeries::customGetSeriesData(QAbstractSeries *serise, QVariantMap &attr)
{
    return false;
}

void ZSeries::LineData(const QVariantMap &attr, QChart *chart, QAbstractSeries *serise)
{
    QLineSeries *line = dynamic_cast<QLineSeries *> (serise);
    D_ISNULLR(line,);
    line->clear();
    QList<QPointF> pointFs;
    CZStaticFun::QStringToQPointFs(attr.value(S_LinePointFs).toString(),pointFs);
    *line << pointFs;

    qDebug()<<pointFs<<"ddddssdsada";
}

void ZSeries::GetLineData(QAbstractSeries *serise, QVariantMap &attr)
{
    QLineSeries *line = dynamic_cast<QLineSeries *> (serise);
    D_ISNULLR(line,);
    QString pointS;
    CZStaticFun::QPointFsToQString(line->points(),pointS);
    attr.insert(S_LinePointFs,pointS);
}

void ZSeries::AreaData(const QVariantMap &attr, QChart *chart, QAbstractSeries *serise)
{

    QAreaSeries * area = dynamic_cast<QAreaSeries *>( serise );

     D_ISNULLR(area,);

    QLineSeries *series0 = area->upperSeries();
    QLineSeries *series1 = area->lowerSeries();

    if(!series0)
    {
        series0 = new QLineSeries();
        area->setUpperSeries(series0);
    }
    else
    {
        series0->clear();
    }

    if(!series1)
    {
        series1 = new QLineSeries();
        area->setLowerSeries(series1);
    }
    else
    {
        series1->clear();
    }

    QList<QPointF> pointFfs;
    CZStaticFun::QStringToQPointFs(attr.value(S_AreaPointFfs).toString(),pointFfs);

    *series0 << pointFfs;

    QList<QPointF> pointFts;
    CZStaticFun::QStringToQPointFs(attr.value(S_LinePointFs).toString(),pointFts);

    *series1 << pointFts;
}

void ZSeries::GetAreaData(QAbstractSeries *serise, QVariantMap &attr)
{
    QAreaSeries * area = dynamic_cast<QAreaSeries *>( serise );

    D_ISNULLR(area,);

    QLineSeries *series0 = area->upperSeries();
    QLineSeries *series1 = area->lowerSeries();

    QString pointS;
    if(series0)
    {
        CZStaticFun::QPointFsToQString(series0->points(),pointS);
        attr.insert(S_AreaPointFfs,pointS);
    }

    if(series1)
    {
        CZStaticFun::QPointFsToQString(series1->points(),pointS);
        attr.insert(S_LinePointFs,pointS);
    }
}


void ZSeries::AbstractBarData(const QVariantMap &attr, const bool &isX, QChart *chart, QAbstractSeries *serise)
{
    QAbstractBarSeries *bar = dynamic_cast<QAbstractBarSeries *> (serise);
    D_ISNULLR(bar,);
    bar->clear();

    QStringList barTexts = attr.value(S_BarTexts).toString().split(SJOIN);
    QList<QBarSet *> barSets;
    foreach (QString barText, barTexts)
    {
        QBarSet * set = new QBarSet(barText);
        QStringList barValues = attr.value(barText).toString().split(SJOIN);
        foreach (QString value, barValues)
        {
            *set << value.toDouble();

        }
        barSets << set;
    }

    bar->append(barSets);
    bar->setLabelsVisible(attr.value(S_ValueShow).toBool());
    chart->addSeries(bar);

    QStringList categories = attr.value(S_XCategories).toString().split(SJOIN);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    isX ? chart->setAxisX(axis, serise) : chart->setAxisY(axis, serise);
}

void ZSeries::GetAbstractBarData(QAbstractSeries *serise, QVariantMap &attr)
{
    QAbstractBarSeries *bar = dynamic_cast<QAbstractBarSeries *> (serise);
    D_ISNULLR(bar,);
    QList<QBarSet *> barSets = bar->barSets();
    QStringList barTexts;
    foreach (QBarSet *set, barSets)
    {
        QStringList barValues;
        for(int i =0; i < set->count(); i++)
        {
            barValues << QString::number(set->at(i));
        }
        QString text = set->label();
        attr.insert(text,barValues.join(SJOIN));
        barTexts << text;
    }
    attr.insert(S_BarTexts,barTexts.join(SJOIN));
}

void ZSeries::PieData(const QVariantMap &attr, QChart *chart, QAbstractSeries *serise)
{
    QPieSeries *pie = dynamic_cast<QPieSeries *> (serise);
    D_ISNULLR(pie,);
    pie->clear();

    QStringList pieTexts = attr.value(S_PieTexts).toString().split(SJOIN);
    foreach (QString pieText, pieTexts)
    {
        double pieValues = attr.value(pieText).toDouble();
        pie->append(pieText,pieValues);
    }

     QPieSlice *slice = pie->slices().value(attr.value(S_PieCurIndex).toInt());
     if(slice)
     {
         slice->setExploded();
         slice->setLabelVisible(true);
     }
}

void ZSeries::GetPieData(QAbstractSeries *serise, QVariantMap &attr)
{
    QPieSeries *pie = dynamic_cast<QPieSeries *> (serise);
    D_ISNULLR(pie,);
    QList<QPieSlice *> slices = pie->slices();
    QStringList pieTexts;
    foreach (QPieSlice* slice , slices)
    {
        QString pieText = slice->label();
        attr.insert(pieText,slice->value());
        pieTexts << pieText;
    }
    attr.insert(S_PieTexts,pieTexts.join(SJOIN));
}


MYREGISTER(ZSeries)

