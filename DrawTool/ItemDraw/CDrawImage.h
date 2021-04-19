#ifndef CDRAWIMAGE_H
#define CDRAWIMAGE_H

/*******************************************************
    created     :   2019/09/27
    file base	:   CDrawImage.h
    author      :   zcx
    purpose     :	绘画图片，支持切换
*******************************************************/

#include "../BaseDraw/CZBase.h"
class CDrawImage : public CZBase
{
    Q_OBJECT
public:
    explicit CDrawImage(QGraphicsItem *parent = nullptr);

signals:

public slots:

    // QGraphicsItem interface
public:
    virtual void paintOver(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
public:
    virtual QString getClassName();

    // CZBase interface
protected:
    virtual void attrUpdate(const QVariantMap &pDate);

private:
    void initData();

    QHash<int,QString>  m_FileName;
    int                 m_CurrentIndex;
};

#endif // CDRAWIMAGE_H
