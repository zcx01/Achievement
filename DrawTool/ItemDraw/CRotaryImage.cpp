#include "CRotaryImage.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "../DrawToolInclude/zattrdefine.h"

CRotaryImage::CRotaryImage(QGraphicsItem *parent) : CZBase(parent)
{
    m_MousePress = false;
    m_ClickVisible = false;
}


void CRotaryImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString fileName;
    if(!m_MousePress)
    {
        fileName = m_Image;
    }
    else
    {
        fileName = m_SelectImage;
    }
    painter->drawPixmap(boundingRect().toRect(),QPixmap(fileName));
}

QString CRotaryImage::getClassName()
{
    return "CRotaryImage";
}

void CRotaryImage::attrUpdate(const QVariantMap &pDate)
{
    m_Image = pDate.value(IMAGE).toString();
    m_SelectImage = pDate.value(SELECTIMAGE).toString();
    m_ClickVisible =pDate.value(CLICKVISIBLE).toBool();
}

void CRotaryImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_MousePress = true;
        update();
        if(m_ClickVisible)
        {
            setVisible(true);
        }
    }
    CZBase::mousePressEvent(event);
}

void CRotaryImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_MousePress = false;
    update(boundingRect());
    if(m_ClickVisible)
    {
        setVisible(false);
    }
    CZBase::mouseReleaseEvent(event);
}
MYREGISTER(CRotaryImage)
