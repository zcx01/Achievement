#ifndef CROTARYIMAGE_H
#define CROTARYIMAGE_H

/*******************************************************
    created     :   2019/07/27
    file base	:   CRotaryImage.h
    author      :   zcx
    purpose     :	点图片，进行旋转
*******************************************************/
#include "../BaseDraw/CZBase.h"

class CRotaryImage : public CZBase
{
public:
    CRotaryImage(QGraphicsItem *parent =NULL);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // CZBase interface
public:
    virtual QString getClassName();

protected:
    virtual void attrUpdate(const QVariantMap &pDate);

    // QGraphicsItem interface
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QString     m_Image;        //默认的图片
    QString     m_SelectImage;  //选中的图片
    bool        m_MousePress;   //鼠标是否按下
    bool        m_ClickVisible; //点击的时候才会显示
};

#endif // CROTARYIMAGE_H
