#ifndef ZSERIES_H
#define ZSERIES_H

#include <QtCharts/QChart>
using namespace  QtCharts;

#include <QObject>

class ZSeries : public QObject
{
    Q_OBJECT
public:
    explicit ZSeries(QObject *parent = nullptr);
    virtual ~ZSeries();

    QAbstractSeries* CreateSeries(const QVariantMap &attr , QChart *chart);

    void UpSeriesData(const QVariantMap &attr , QChart *chart, QAbstractSeries *serise);

    void GetSeriesData(QAbstractSeries *serise,QVariantMap &attr);
signals:

public slots:

protected:

    //自定义创建Series ，如果是自定义成功就返回 true
    virtual bool customSeriesDataChanged(const QVariantMap &attr , QChart *chart, QAbstractSeries *serise);

    virtual bool customGetSeriesData(QAbstractSeries *serise,QVariantMap &attr);

    //线图数据改变
    static void LineData(const QVariantMap &attr , QChart *chart, QAbstractSeries *serise);

    //得到线图数据
    static void GetLineData(QAbstractSeries *serise,QVariantMap &attr);

    //面积图数据改变
    static void AreaData(const QVariantMap &attr , QChart *chart, QAbstractSeries *serise);

    //得到面积图数据
    static void GetAreaData(QAbstractSeries *serise,QVariantMap &attr);

    //柱状图数据改变
    static void AbstractBarData(const QVariantMap &attr,const bool &isX, QChart *chart, QAbstractSeries *serise);

    //得到柱状图数据
    static void GetAbstractBarData(QAbstractSeries *serise,QVariantMap &attr);

    //饼状图
    static void PieData(const QVariantMap &attr , QChart *chart, QAbstractSeries *serise);

    static void GetPieData(QAbstractSeries *serise,QVariantMap &attr);

};

#endif // ZSERIES_H
