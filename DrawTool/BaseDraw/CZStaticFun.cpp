#include "CZStaticFun.h"
#include <QLineF>
#include <QDebug>

#define PI          3.14159126
#define sub(v,w)    (v-w)
#define NUM(v)      QString::number(v)
CZStaticFun::CZStaticFun()
{

}

QPointF CZStaticFun::castRectPoint(QRectF rect, PointTypes type)
{
    QPointF pos(0,0);
    int castX =0, castY =0;
    if(type & LeftTop)
    {
        castX = 0;
        castY = 0;
    }
    if(type & TopCenter)
    {
        castX = rect.width() / 2;
    }
    if(type & RightTop)
    {
        castX = rect.width();
    }
    if(type & LeftCenter)
    {
        castY = rect.height()/2;
    }
    if( type & LeftDown)
    {
        castY = rect.height();
    }
    pos.setX(castX);
    pos.setY(castY);
    return pos;
}

QList<QPointF> CZStaticFun::QStringToPointType(QRectF rect, QString pointType)
{
    QList<QPointF> points;
    QStringList pointTypes = pointType.split(SJOIN);
    foreach (QString type, pointTypes)
    {
        points << castRectPoint(rect,(PointType)getEnums<CZStaticFun>("PointType",type));
    }
    return points;
}

QPointF CZStaticFun::castShowPoint(QRectF firstRect, QRectF towRect, int type)
{
    QPointF pos(0,0);
    int castX =0, castY =0;
    switch (type)
    {
    case 0:
        break;
    case 1:
        castX = sub(firstRect.width(),towRect.width());
        break;
    case 2:
        castY = sub(firstRect.height(),towRect.height());
        break;
    case 3:
        castX = sub(firstRect.width(),towRect.width());
        castY = sub(firstRect.height(),towRect.height());
        break;
    case 4:
        castX = sub(firstRect.width(),towRect.width())/2;
        castY = sub(firstRect.height(),towRect.height())/2;
        break;
    case 5:
        castX =  sub(firstRect.width(),towRect.width())/2;
        break;
    case 6:
        castX = sub(firstRect.width(),towRect.width())/2;
        castY = sub(firstRect.height(),towRect.height());
        break;
    case 7:
        castY = sub(firstRect.height(),towRect.height())/2;
        break;
    case 8:
        castX = sub(firstRect.width(),towRect.width());
        castY = sub(firstRect.height(),towRect.height())/2;
        break;
    default:
        break;
    }
    pos.setX(castX);
    pos.setY(castY);
    return pos;
}

QPointF CZStaticFun::QStringToQPointF(QString str)
{
    QStringList s = str.split(SJOIN);
    QPointF pointF;
    if(s.size() <2)  return pointF;
    pointF.setX(s.at(0).toDouble());
    pointF.setY(s.at(1).toDouble());
    return pointF;
}

QString CZStaticFun::QPointFTOQString(QPointF point)
{
    return QString::number(point.x())+SJOIN+QString::number(point.y());
}

void CZStaticFun::QStringToQPointFs(const QString &str, QList<QPointF> &pointFs)
{
    QStringList pointStrings = str.split(MJOIN);
    foreach (QString pointString, pointStrings) {
        pointFs << QStringToQPointF(pointString);
    }
}

void CZStaticFun::QPointFsToQString(const QList<QPointF> &pointFs, QString &str)
{
    QStringList pointStrings;
    foreach (QPointF p, pointFs) {
        pointStrings << QPointFTOQString(p);
    }
    str = pointStrings.join(MJOIN);
}

QSize CZStaticFun::QStringToQSizeF(QString str,const QSize &defaultValue)
{
    QStringList s = str.split(SJOIN);
    if(s.size() <2)  return defaultValue;
    QSize size;
    size.setWidth(s.at(0).toInt());
    size.setHeight(s.at(1).toInt());
    return size;
}

QString CZStaticFun::QSizeTOQString(QSize s)
{
    return QString::number(s.width())+SJOIN+QString::number(s.height());
}

QRectF CZStaticFun::QStringToQRectF(QString str)
{
    QStringList s = str.split(SJOIN);
    QRectF rectF;
    if(s.size() <4)  return rectF;
    rectF.setRect(s.at(0).toDouble(),
                  s.at(1).toDouble(),
                  s.at(2).toDouble(),
                  s.at(3).toDouble());
    return rectF;
}

QString CZStaticFun::QRectFToQString(QRectF rect)
{
    if(rect.isNull()) return QString("");
    return  QString::number(rect.x())+SJOIN+
            QString::number(rect.y())+SJOIN+
            QString::number(rect.width())+SJOIN+
            QString::number(rect.height());
}


QPen CZStaticFun::QStringToQPen(QString penString)
{
    QPen p;
    QString pString;
    QList<QString> penStrings = penString.split(MJOIN);
    if(penStrings.size() > 0)
    {
        pString = penStrings.at(0);
        p.setWidth(pString.toInt());
    }
    if(penStrings.size() > 1)
    {
        pString = penStrings.at(1);
        QColor color = QStringToQColor(pString);
        p.setColor(color);
    }

    if(penStrings.size() > 2)
    {
        pString = penStrings.at(2);
        Qt::PenStyle style = Qt::PenStyle(pString.toInt());
        p.setStyle(style);
    }
    return p;
}

QString CZStaticFun::QPenToQString(const QPen &p)
{
    QStringList penString;
    penString<<NUM(p.width())
            <<QColorToQString(p.color())
           <<NUM((int)p.style());
    return penString.join(MJOIN);
}

QFont CZStaticFun::QStringToQFont(QString fonString)
{
    QFont font;
    QString pString;
    QList<QString> penStrings = fonString.split(SJOIN);
    if(penStrings.size() > 0)   //大小
    {
        pString = penStrings.at(0);
        if(pString.toInt()>0)
            font.setPixelSize(pString.toInt());
    }
    if(penStrings.size() > 1)//加粗
    {
        pString = penStrings.at(1);
        font.setBold(pString.toInt());
    }
    if(penStrings.size() > 2)//斜体
    {
        pString = penStrings.at(2);
        font.setItalic(pString.toInt());
    }
    if(penStrings.size() > 3)//下划线
    {
        pString = penStrings.at(3);
        font.setUnderline(pString.toInt());
    }
    if(penStrings.size() > 4)//上划线
    {
        pString = penStrings.at(4);
        font.setOverline(pString.toInt());
    }
    if(penStrings.size() > 5)//文字的间距
    {
        pString = penStrings.at(5);
        font.setWordSpacing(pString.toInt());
    }
    return font;
}

QString CZStaticFun::QFontToQString(QFont font)
{
    QStringList fontStrings;
    qDebug()<<font.pixelSize();
    fontStrings<<NUM(font.pixelSize());
    fontStrings<<NUM(font.bold());
    fontStrings<<NUM(font.italic());
    fontStrings<<NUM(font.underline());
    fontStrings<<NUM(font.overline());
    fontStrings<<NUM(font.wordSpacing());
    return fontStrings.join(SJOIN);
}

QString CZStaticFun::QStringSplit(QString &oriString, const QString &sep, const bool &self, int many, const bool &left)
{
    QString pString=oriString;
    int index =0;
    many++;
    for(int i =0; i <many;i++)
    {
        index =pString.indexOf(sep,index);
        if(index == -1)
        {
            break;
        }
        index++;
    }
    int lenght =index-1;
    if(left)
        pString = pString.left(lenght);
    else
        pString = pString.right(lenght);
    if(self)
        oriString = pString;
    return  pString;
}

QColor CZStaticFun::QStringToQColor(QString colorString)
{
    QList<QString> fontColorSize = colorString.split(SJOIN);
    QColor fontColor;
    if(fontColorSize.size() > 3)
        fontColor.setRgb(fontColorSize.at(0).toInt(),fontColorSize.at(1).toInt(),
                         fontColorSize.at(2).toInt(),fontColorSize.at(3).toInt());
    else if(fontColorSize.size() > 2)
        fontColor.setRgb(fontColorSize.at(0).toInt(),fontColorSize.at(1).toInt(),
                         fontColorSize.at(2).toInt());
    else
        fontColor.setNamedColor(colorString);
    return fontColor;
}

QString CZStaticFun::QColorToQString(QColor color)
{
    QStringList str;
    if(!color.isValid())
    {
        return "";
    }
    str<<NUM(color.red())<<NUM(color.green())<<NUM(color.blue())<<NUM(color.alpha());
    return str.join(SJOIN);
}

QBrush CZStaticFun::QStringToQBrush(QString brushString)
{
    if(brushString.isEmpty()) return QBrush();
    QStringList brushStrings = brushString.split(MJOIN);
    QBrush brush(QStringToQColor(brushStrings.value(0)));
    brush.setStyle((Qt::BrushStyle)brushStrings.value(1).toInt());
    return brush;
}

QString CZStaticFun::QBrushToQString(QBrush brush)
{
    if(!brush.style()) return "";
    QStringList brushStrings;
    brushStrings<<QColorToQString(brush.color());
    brushStrings<<NUM(brush.style());
    return brushStrings.join(MJOIN);
}

