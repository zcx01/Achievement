#include "DrawChar.h"
#include "hfdefine.h"
#include "ZSeries.h"
#include "../DrawToolInclude/seriesdefine.h"
#include "../BaseDraw/CZStaticFun.h"
#include <QGraphicsSceneMouseEvent>



DrawChar::DrawChar()
{
    m_ZSeries = new ZSeries;
    this->createDefaultAxes();
}

DrawChar::~DrawChar()
{
    qDeleteAll(m_Series.values());
    m_Series.clear();
}

void DrawChar::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QChart::paint(painter,option,widget);
}

QChart *DrawChar::getThis()
{
    return (QChart*)this;
}

QString DrawChar::getClassName()
{
    return "DrawChar";
}

void DrawChar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mousePressEvent(event);
    QChart::mousePressEvent(event);
    if(getThis()->flags() & ItemIsMovable)
    {
        event->accept();
    }
}

void DrawChar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QChart::mouseMoveEvent(event);
    CZBase::mouseMoveEvent(event);
    if(getThis()->flags() & ItemIsMovable)
    {
        emit CZBase::xChanged();
        emit CZBase::yChanged();
    }
}

void DrawChar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    CZBase::mouseReleaseEvent(event);
    QChart::mouseReleaseEvent(event);
}


bool DrawChar::Asynchronous(QVariant &pData)
{
    const QVariantMap attr = pData.toMap();
    int type = attr.value(D_ChartHandleType,-1).toInt();
    switch (type)
    {
    case DC::ChangedData:
        attrUpdate(attr);
        break;
    case DC::DeleteData:
    {
        QString seriseId = GetSeriseId(attr);
        QAbstractSeries * serise = m_Series.value(seriseId);
        if(serise)
            this->removeSeries(serise);
    }
        break;
    default:
        break;
    }
    return true;
}

void DrawChar::attrUpdate(const QVariantMap &pDate)
{

    //    if(!pDate.value(D_OnlySerise).toBool()) return;
    QString zClassName = pDate.value(D_ZSeriseClassName).toString();
    if(!zClassName.isEmpty())
    {
        ZSeries *zSeries = static_cast<ZSeries *>
                (CMyRegisterSingle::instance()->getClass(zClassName));
        SetZSeries(zSeries);
    }

    QString seriesId = GetSeriseId(pDate);

    QAbstractSeries * series = m_Series.value(seriesId);

    if(!series)
    {
        series  = m_ZSeries->CreateSeries(pDate,this);
        if(series)
        {
            this->addSeries(series);
            m_Series.insert(seriesId,series);
        }
    }
    else
    {
        m_ZSeries->UpSeriesData(pDate,this,series);
    }

    this->setTitle(pDate.value(D_ChartTitle).toString());

    int opt = CZStaticFun::getEnums<QChart>
            (CS(AnimationOption),pDate.value(D_AnimationOptions).toString(),QChart::NoAnimation);

    this->setAnimationOptions((QChart::AnimationOption)opt);
}

void DrawChar::getAttrUpdate(QVariantMap &pDate)
{
    QString seriesId = GetSeriseId(pDate);
    QAbstractSeries * series = m_Series.value(seriesId);
    m_ZSeries->GetSeriesData(series,pDate);
    for(auto  iter = m_Series.begin(); iter != m_Series.end(); iter++)
    {
        if(iter.key() != seriesId)
        {
            //            QVariant attr;
            QVariantMap mapAttr;
            m_ZSeries->GetSeriesData(iter.value(),mapAttr);
            SendCustomAttr(iter.key(),mapAttr);
        }
    }
}

void DrawChar::AttrChanged(const QString &id, const QVariant &pData)
{
    if(id == GetSeriseId(m_Attrs))
    {
        QVariantMap attr = pData.toMap();
        for(auto iter = attr.begin(); iter != attr.end(); iter++)
        {
            m_Attrs.insert(iter.key(),iter.value());
        }
    }
}

void DrawChar::SetZSeries(ZSeries *s)
{
    D_ISNULLR(s,);

    if(s == m_ZSeries)
        return;

    D_Delete(m_ZSeries);

    m_ZSeries = s;
}

QString DrawChar::GetSeriseId(const QVariantMap &pDate)
{
    QString seriesId = pDate.value(D_SeriseId).toString();
    if(seriesId.isEmpty())
        seriesId =pDate.value(IDD).toString();
    return seriesId;
}
MYREGISTER(DrawChar)
