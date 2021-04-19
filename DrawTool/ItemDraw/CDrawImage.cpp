#include "CDrawImage.h"
#include <QPainter>
#include "../DrawToolInclude/zattrdefine.h"


CDrawImage::CDrawImage(QGraphicsItem *parent) : CZBase(parent)
{
    initData();
}


void CDrawImage::paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     QString fileName = m_FileName.value(m_CurrentIndex);
     painter->drawPixmap(boundingRect().toRect(),QPixmap(fileName));
// 	painter->drawRect(boundingRect().toRect());
}

QString CDrawImage::getClassName()
{
    return "CDrawImage";
}

void CDrawImage::attrUpdate(const QVariantMap &pDate)
{
    m_FileName.clear();
    QList<QString> fileNames = pDate.value(IMAGEFILENAMES).toString().split(",");
    for(int i =0; i <fileNames.size(); i++)
    {
        m_FileName.insert(i,fileNames.at(i));
    }
    m_CurrentIndex = pDate.value(CURRENTINDEX).toInt();
}

void CDrawImage::initData()
{
    m_CurrentIndex = 0;
}

MYREGISTER(CDrawImage)
