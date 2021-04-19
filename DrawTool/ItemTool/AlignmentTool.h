#ifndef ALIGNMENTTOOL_H
#define ALIGNMENTTOOL_H
/*******************************************************
    purpose     :	选中图元对齐对齐工具
*******************************************************/
#include "../BaseDraw/CZBaseTool.h"

class AlignmentTool : public CZBaseTool
{
    Q_GADGET
public:
    enum AlignmentType  //对齐的方式
    {
        HorizontalAlignment=0x0001,     //水平
        VerticalAlignment =0x0002,      //垂直
        HorizontalEquidistant=0x0004,   //水平等距
        VerticalEquidistant=0x0008,     //垂直等距
        LeftOrTop=0x0010,
        Center=0x0020,
        RightOrDowm=0x0040

    };
    Q_DECLARE_FLAGS(AlignmentTypes,AlignmentType)
    explicit AlignmentTool(QObject *parent = nullptr);
    QString getClassName();
    void upDataTool(CZBase *item);
protected:
    QVariant dealData(CZBase *item, void *pData);

private:
    void Alignment(CZBase *reference, AlignmentTypes type, double distance);

    QList<QRectF> getBoundRects(QList<CZBase*> items);

    AlignmentTypes  m_AlignmentTypes;

    static double calQRectMixH(const QRectF &f, const QRectF &t);

    static double calQRectMixV(const QRectF &f, const QRectF &t);

    static double calQRectMinDistance(const double &f,const double &d, const double &t);

    static bool QRectCompX(const QRectF &f,const QRectF &t);

    static bool QRectCompY(const QRectF &f,const QRectF &t);

    static bool ItemCompX(const CZBase *f,const CZBase *t);

    static bool ItemCompY(const CZBase *f,const CZBase *t);

    Q_ENUMS(AlignmentType)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AlignmentTool::AlignmentTypes)

#endif // ALIGNMENTTOOL_H
