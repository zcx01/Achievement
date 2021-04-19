#ifndef TIMESCALE_H
#define TIMESCALE_H

/*******************************************************
    purpose     :	时间刻度线
*******************************************************/
#include "../BaseDraw/CZBase.h"
#include <QFontMetrics>
class TimeScale : public CZBase
{
    Q_OBJECT
    friend class TimeScaleFrame;
public:
    explicit TimeScale(QGraphicsItem *parent = nullptr);

    QString getClassName();
    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:

public slots:

    // CZBase interface
protected:
    bool Asynchronous(QVariant &pData);
    void attrUpdate(const QVariantMap &pDate);

    // QGraphicsItem interface
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    /**
     * @brief 计算比例尺
     * @param sTime:开始的时间
     * @param eTime:结束的时间
     * @param width:宽度
     * @param height:高度
     * @param ratio:非整数刻度占整数刻度的比例
     * @param ori:原点
     * @return 线段集
     */
    QList<QLineF>  calScale(double sTime, double eTime, double width, double height, double ratio,QPointF &ori);

    /**
     * @brief 得到时间对应的刻度
     * @param time:时间
     * @return 横坐标
     */
    double Conver(double time);

    /**
     * @brief 得到时间字符串
     * @param time:时间
     * @return 字符串
     */
    QString GetTimeString(double time);

    /**
     * @brief 得到时间的宽度
     * @param time:时间
     * @return 宽度
     */
    int GetTimeStringWidth(double time);

    /**
     * @brief 通过距离计算间隔的时间
     * @return 时间的时间
     */
    double CalSpaceTimeByDistance(const double &distance);

    /**
     * @brief 判断小数
     * @param d:数据
     * @return 是小数
     */
    bool isDouble(const double & d);

    /**
     * @brief 得到小数
     * @param d:数据
     * @return 小数
     */
    double GetDouble(const double &d);

    void MouveTime(const double &time);

    double          m_STime;        //开始的时间
    double          m_ETime;        //结束的时间
    double          m_ScaleSpace;   //刻度的间距
    int             m_LeftMargin;   //左边距
    int             m_TextMargin;   //文字边距
    QPointF         m_OriCoor;      //刻度尺参考的源坐标
    QFontMetrics    m_FontMetrics;  //字体
    QPointF         m_PressPos;     //按下的点
    bool            m_Press;        //是否按下
    bool            m_Send;         //在重画的时候是否发送信号
    bool            m_OneGrid;      //是否一格一格的移动
};


class TimeScaleFrame : public CZBase
{
    Q_OBJECT

    // CZBase interface
public:
    TimeScaleFrame();
    QString getClassName();
    void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void AddScene(QGraphicsScene *s);

protected:
    bool Asynchronous(QVariant &pData);

    void attrUpdate(const QVariantMap &pDate);

private slots:

    void slot_SendAttr(QString id,QString attr);

private:
    TimeScale*  m_TimeScale;    //时间刻度
    double      m_LeftTime;     //最左边的时间
};
#endif // TIMESCALE_H
