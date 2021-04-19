#ifndef CZSTATICFUN_H
#define CZSTATICFUN_H

#include <QObject>
#include <QRectF>
#include <QPen>
#include <QFont>
#include "cdraw_global.h"
#include <QMetaEnum>
#include <QMetaObject>

#define MJOIN       "|"
#define SJOIN       ","
#define BJOIN       ";"
#define CS(v)       #v      //字符串化
class CDRAW_EXPORT CZStaticFun
{
    Q_GADGET
public:
    CZStaticFun();
    enum PointType
    {
        LeftTop =0x0001,
        TopCenter = 0x0002,
        RightTop = 0x0004,
        LeftCenter = 0x0008,
        Center = LeftCenter | TopCenter,
        RightCenter = LeftCenter | RightTop,
        LeftDown = 0x0010,
        DownCenter = LeftDown | TopCenter,
        RightDown = LeftDown| RightTop,
    };
    Q_DECLARE_FLAGS(PointTypes,PointType)

    template<typename T>  inline static int getEnum(const QString &enumName,const QString &keys,
                                             int defaultValue =-1)
    {
        return StringToEnum<T>(enumName,keys,false,defaultValue);
    }

    template<typename T> inline static int getEnums(const QString &enumName,
                                                    const QString &keys,int defaultValue =-1)
    {
        return StringToEnum<T>(enumName,keys,true,defaultValue);
    }

    template<typename T> inline static int StringToEnum(const QString &enumName,
                                                        const QString &keys,const bool &isMulti,int defaultValue =-1)
    {
        if(keys=="0" || keys.toInt() !=0)
        {
            return keys.toInt();
        }
        QMetaObject mo = T::staticMetaObject;
        QMetaEnum metaEnum = mo.enumerator(mo.indexOfEnumerator(enumName.toLocal8Bit().constData()));
        int enumValue = isMulti ? metaEnum.keysToValue(keys.toLocal8Bit().constData()) :
                              metaEnum.keyToValue(keys.toLocal8Bit().constData());
        return enumValue ==-1 ? defaultValue :enumValue;
    }

    /**
    * @fn       castRectPoint(QRectF rect,PointTypes type);
    * @brief    计算矩形的特殊位置
    * @date     2019/05/12
    * @author   zcx
    * @param    rect:矩形 type:位置类型
    * @return   位置
    */
    static QPointF castRectPoint(QRectF rect,PointTypes type);

    /**
     * @brief   根据类型名组合计算矩形特殊位置组合
     * @param   rect:矩形
     * @param   pointType:类型名组合
     * @return  矩形特殊位置组合
     */
    static QList<QPointF> QStringToPointType(QRectF rect, QString pointType);

    /**
    * @fn       ccastShowPoint(QRect firstRect,QRect towRect,int type);
    * @brief    计算towRect在firstRect的位置
    * @date     2019/07/11
    * @author   zcx
    * @param    firstRect:第一个矩形，towRect:第二个矩形
    *           type:0表示左上角，1表示右上角，2表示左下角，3表示右下角，4表示居中
    *           5表示上居中，6表示下居中，7表示左居中，8表示右居中，其余表示表示左上角
    * @return
    */
    static QPointF castShowPoint(QRectF firstRect,QRectF towRect,int type);

    /**
    * @fn       QStringToQPointF(QString str);
    * @brief    QString转QPointF
    * @date     2019/07/11
    * @author   zcx
    * @param    str:字符串
    * @return   QPointF
    */
    static QPointF QStringToQPointF(QString str);


    /**
    * @fn       QPointFTOQString(QPointF point);
    * @brief    QPointF转QString
    * @date     2019/07/11
    * @author   zcx
    * @param    point:QPointF
    * @return   字符串
    */
    static QString QPointFTOQString(QPointF point);

    /**
     * @brief QString转QList<QPointF>
     * @param str:字符串
     * @param pointFs:点集合
     */
    static void QStringToQPointFs(const QString &str,QList<QPointF> &pointFs);

    /**
     * @brief QList<QPointF>转QString
     * @param str:字符串
     * @param pointFs:点集合
     */
    static void QPointFsToQString(const QList<QPointF> &pointFs,QString &str);

    /**
    * @fn       QStringToQPointF(QString str);
    * @brief    QString转QPointF
    * @date     2019/07/11
    * @author   zcx
    * @param    str:字符串
    * @return   QPointF
    */
    static QSize QStringToQSizeF(QString str, const QSize &defaultValue = QSize());

    /**
    * @fn       QPointFTOQString(QPointF point);
    * @brief    QPointF转QString
    * @date     2019/07/11
    * @author   zcx
    * @param    point:QPointF
    * @return   字符串
    */
    static QString QSizeTOQString(QSize s);

    /**
    * @fn       QStringToQRectF(QString str);
    * @brief    QString转QRectF
    * @date     2019/07/25
    * @author   zcx
    * @param    str:字符串
    * @return   QRectF
    */
    static QRectF  QStringToQRectF(QString str);

    /**
    * @fn       QRectFToQString(QRectF rect);
    * @brief    QRectF转QString
    * @date     2019/08/07
    * @author   zcx
    * @param    rect:矩形
    * @return   字符串
    */
    static QString QRectFToQString(QRectF rect);

    /**
    * @fn       QStringToQPen(QString penString);
    * @brief    QString转QPen
    * @date     2019/05/12
    * @author   zcx
    * @param    penString:依次为线宽[0-1]|颜色[1-4]|风格[4-5]
    * @return   画笔
    */
    static QPen QStringToQPen(QString penString);

    /**
    * @fn       QPenToQString(const QPen &p);
    * @brief    QPen转QString
    * @date     2020/5/20
    * @author   zcx
    * @param    p:画笔
    * @return   penString:依次为线宽[0-1]|颜色[1-4]|风格[4-5]
    */
    static QString QPenToQString(const QPen &p);

    /**
    * @fn       QStringToQFont(QString fonString);
    * @brief    QString转QFont
    * @date     2019/08/11
    * @author   zcx
    * @param    fonString:依次为大小,加粗,斜体,下划线,上划线,文字的间距
    * @return   字体
    */
    static QFont QStringToQFont(QString fonString);

    /**
    * @fn       QFontToQString(QFont fon);
    * @brief    QFont转QString
    * @date     2019/12/12
    * @author   zcx
    * @param    fon:字体
    * @return   依次为大小,加粗,斜体,下划线,上划线,文字的间距
    */
    static QString QFontToQString(QFont font);

    /**
    * @fn       QStringSplit(QString &oriString, const QString &sep,const bool &self = true, int many=0, const bool & left = true);
    * @brief    把字符串分割两半
    * @date     2019/05/12
    * @author   zcx
    * @param    oriString:源字符串 sep:分割符 self:自己是否改变 many:第几个分隔符 left:是否是左边
    * @return   分割之后的字符串
    */
    static QString QStringSplit(QString &oriString, const QString &sep,const bool &self = true, int many=0, const bool & left = true);

    /**
    * @fn       QStringToQColor(QString colorString);
    * @brief    QString转QColor
    * @date     2019/03/07
    * @author   zcx
    * @param    colorString:字符串
    * @return   颜色
    */
    static QColor QStringToQColor(QString colorString);

    /**
    * @fn       QColorToQString(QColor color);
    * @brief    QColor转QString
    * @date     2019/12/12
    * @author   zcx
    * @param    color:颜色
    * @return   字符串
    */
    static QString QColorToQString(QColor color);

    /**
    * @fn       QStringToQBrush(QString brushString);
    * @brief    QString转QBrush
    * @date     2019/03/07
    * @author   zcx
    * @param    brushString:颜色|风格 要有画刷风格不能为0
    * @return   画刷
    */
    static QBrush QStringToQBrush(QString brushString);

    /**
    * @fn       QBrushToQString(QBrush brush);
    * @brief    QBrush转QString
    * @date     2019/12/12
    * @author   zcx
    * @param    brush:画刷
    * @return   字符串
    */
    static QString QBrushToQString(QBrush brush);
    Q_ENUMS(PointType)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CZStaticFun::PointTypes)
#endif // CZSTATICFUN_H
