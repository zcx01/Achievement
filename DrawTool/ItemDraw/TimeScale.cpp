#include "TimeScale.h"
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QUuid>
#include "DrawToolInclude/zattrdefine.h"
#include "DrawToolInclude/commdefine.h"
#include "../BaseDraw/ComputeGeometry.h"

#define DENGFEN     6   //一个小时被分成的份数
#define DefaultS    0   //默认开始的时间
#define DefaultE    24  //默认结束的时间
TimeScale::TimeScale(QGraphicsItem *parent) : CZBase(parent),m_FontMetrics(QFont())
{
    m_STime = DefaultS;
    m_ETime = DefaultE;
    m_ScaleSpace = 0;
    m_LeftMargin = 0;
    m_TextMargin = 10;
    m_Press = false;
    m_Send = true;
    m_OneGrid = false;
}

QString TimeScale::getClassName()
{
    return    "TimeScale";
}

void TimeScale::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画刻度
    QPointF oldOrid = m_OriCoor;
    m_FontMetrics = option->fontMetrics;
    double scaleHeight =this->boundingRect().height() - m_FontMetrics.height() - m_TextMargin;  //刻度尺的高度
    double leftDis = isDouble(m_STime) ? 0 : m_FontMetrics.width(GetTimeString(m_STime))/2 + m_LeftMargin;
    double RightDis = m_FontMetrics.width(GetTimeString(m_ETime))/2;

    double scaleWidth = this->boundingRect().width() - leftDis - RightDis;


    m_OriCoor = QPointF(leftDis,0);
    QList<QLineF> scaleLine = calScale(m_STime,m_ETime,scaleWidth,scaleHeight,0.8,m_OriCoor);
    painter->drawLines(scaleLine.toVector());

    int sTime = isDouble(m_STime) ? m_STime +1 : m_STime;
    int eTime = isDouble(m_ETime) ? m_ETime +1 : m_ETime;

    //画时间文本
    for( int i = sTime; i <= eTime; i++)
    {
        int timeString = i % 24;
        QString text = GetTimeString(timeString);
        QRect rect = m_FontMetrics.boundingRect(text);
        double textX = Conver(i);
        double textY = scaleHeight + m_FontMetrics.height() / 2;
        rect.moveCenter(QPoint(textX,textY));
        painter->drawText(rect,text);
    }

    if(oldOrid != m_OriCoor && m_Send)
    {
        sendAttrChanged(SizeChanged);
        setAttr(SizeChanged,true);
    }
}

bool TimeScale::Asynchronous(QVariant &pData)
{
    QVariantMap attr = pData.toMap();
    int type = attr.value(F_GetPosType).toInt();
    switch (type) {
    case Dr::TimeScaleWidth:
    {
        double s = Conver(attr.value(F_NodeSTime).toDouble());
        double e = Conver(attr.value(F_NodeETime).toDouble());
        double w = e - s ;
        QPointF pos = mapToScene(QPointF(s,0));
        attr.insert(F_NodeX,pos.x());
        attr.insert(F_NodeW,w);
    }
        break;
    default:
        break;
    }
    pData.setValue(attr);
    return true;
}

void TimeScale::attrUpdate(const QVariantMap &pDate)
{
    m_STime = pDate.value(D_STime,DefaultS).toDouble();
    m_ETime = pDate.value(D_ETime,DefaultE).toDouble();
    m_LeftMargin = pDate.value(D_LeftMargin,m_LeftMargin).toInt();
    m_TextMargin = pDate.value(D_TextMargin,m_TextMargin).toInt();

    setFlags(flags() | QGraphicsItem::ItemIsFocusable);
}

void TimeScale::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_PressPos = event->pos();
        event->accept();
        m_Press = true;
        m_OneGrid = true;
    }
}

void TimeScale::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mouseMoveEvent(event);
    if(m_Press)
    {
        double mouseDis = event->pos().x() - m_PressPos.x();
        double time = CalSpaceTimeByDistance(-mouseDis);
        MouveTime(time);
        m_PressPos = event->pos();
    }
}

void TimeScale::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_Press = false;
    m_OneGrid = false;
    CZBase::mouseReleaseEvent(event);
}

QList<QLineF> TimeScale:: calScale(double sTime, double eTime, double width, double height, double ratio,QPointF &ori)
{
    QList<QLineF> lines;
    //画中间轴
    QPointF mOri(m_LeftMargin,height / 2);
    QPointF mEnd = ComputeGeometry::pointByDistance(mOri,this->boundingRect().width(),360);
    lines<<QLineF(mOri,mEnd);

    double spaceTime = eTime - sTime;
    int allScale = spaceTime * DENGFEN; //总刻度
    m_ScaleSpace =(double) width / allScale;//平移的像素

    if(!m_OneGrid)  //一格一格的移动
    {
        double startDistance = GetDouble(GetDouble(sTime * DENGFEN)) * m_ScaleSpace;   //开始的刻度
        if(isDouble(GetDouble(GetDouble(sTime * DENGFEN))))
        {
            int textWidth = m_FontMetrics.width(GetTimeString(sTime))/2;
            ori.setX(ori.x() + startDistance - textWidth);
        }
    }

    int startScale =isDouble(sTime)  ?  (1 -GetDouble(sTime)) * DENGFEN : 0;   //开始的整数刻度
    QLineF hLine(ori,ComputeGeometry::pointByDistance(ori,height,90));

    for(int i =0; i <=allScale; i++)
    {
        QLineF tLineF = hLine.translated(m_ScaleSpace * i,0);
        int sIndex = i - startScale;
        if( sIndex <0 || sIndex % DENGFEN != 0)
        {
            qreal tLength =  tLineF.length();
            tLineF.setLength(tLength * ratio);
            tLineF.translate(0,tLength * (1 - ratio) / 2);
        }
        lines << tLineF;
    }
    return lines;
}

double TimeScale::Conver(double time)
{
    if(m_OriCoor.isNull())
    {
        show();
        update();
    }
    double spaceTime = time - m_STime;
    return m_ScaleSpace * spaceTime * DENGFEN + m_OriCoor.x() /*- m_OriCoor.x() + m_ScaleSpace*/;
}

QString TimeScale::GetTimeString(double time)
{
    //QStringList timeStrings = QString::number(time).split(".");
    QString h = QString::number((int)time);
    double d = time -(int)time;
    QString m = QString::number(d * 60);
    if(m.size() < 2) m += "0";
    return h+":"+m.mid(0,2);
}

int TimeScale::GetTimeStringWidth(double time)
{
    return m_FontMetrics.width(GetTimeString(time));
}

double TimeScale::CalSpaceTimeByDistance(const double &distance)
{
    if(m_ScaleSpace == 0) return 0;
    return (double)distance / (m_ScaleSpace * DENGFEN);
}

bool TimeScale::isDouble(const double &d)
{
    return d - (int)d != 0;
}

double TimeScale::GetDouble(const double &d)
{
    return d - (int)d;
}

void TimeScale::MouveTime(const double &time)
{
    m_STime += time;
    if(m_STime < m_Attrs.value(D_STime,DefaultS).toDouble())
    {
        m_STime = m_Attrs.value(D_STime,DefaultS).toDouble();
        m_ETime = m_Attrs.value(D_ETime,DefaultE).toDouble();
    }
    else
    {
        m_ETime += time;
    }
    m_Send = false;
    update();
    m_Send = true;
    sendAttrChanged(SizeChanged);
}
MYREGISTER(TimeScale)


TimeScaleFrame::TimeScaleFrame()
{
    m_TimeScale = new TimeScale(this);
    m_LeftTime =0;
    connect(m_TimeScale,SIGNAL(sig_AttrChanged(QString,QString)),this,SLOT(slot_SendAttr(QString,QString)));
}

QString TimeScaleFrame::getClassName()
{
    return "TimeScaleFrame";
}

void TimeScaleFrame::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //画时间左边框
    QLineF leftLine(boundingRect().topLeft(),boundingRect().bottomLeft());
    painter->drawLine(leftLine.translated(m_LeftTime,0));

    //画下边框
    painter->drawLine(boundingRect().bottomLeft(),boundingRect().bottomRight());


}

void TimeScaleFrame::AddScene(QGraphicsScene *s)
{
    double x = boundingRect().x();
    double y = boundingRect().y();
    double w = s->sceneRect().width() - pos().x();
    double h = boundingRect().height();
    setBounding(QRectF(x,y,w,h));
    m_TimeScale->setBounding(this->boundingRect());
}

bool TimeScaleFrame::Asynchronous(QVariant &pData)
{
    m_TimeScale->Asynchronous(pData);
    return true;
}

void TimeScaleFrame::attrUpdate(const QVariantMap &pDate)
{
    setFlags(flags() | QGraphicsItem::ItemClipsChildrenToShape | QGraphicsItem::ItemIsFocusable); //ItemClipsChildrenToShape超出父类部分隐藏
    m_TimeScale->setAttrs(pDate);
    m_TimeScale->setId(QUuid::createUuid().toString());
    m_LeftTime = pDate.value(D_LeftTime,m_LeftTime).toDouble();
    m_TimeScale->setX(m_LeftTime);
}

void TimeScaleFrame::slot_SendAttr(QString id, QString attr)
{
    sendAttrChanged(attr);
}
MYREGISTER(TimeScaleFrame)

