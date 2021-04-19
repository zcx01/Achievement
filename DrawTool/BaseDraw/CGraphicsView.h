#ifndef WIDGET_H
#define WIDGET_H
/*******************************************************************
 * QGraphicsView视图的左上角是（0,0），X轴正方向向右，Y轴正方向向下
 *
 *
 *
 *
 * */
#include <QGraphicsView>
class QGraphicsItem;

class  CGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CGraphicsView(QWidget *parent = 0);
    ~CGraphicsView();

    //平移,delta:平移的单位
    void translate(QPointF delta);

    // 平移速度
    void setTranslateSpeed(qreal speed);

    qreal translateSpeed() const;

    // 缩放的增量
    void setZoomDelta(qreal delta);

    qreal zoomDelta() const;

    //缩放，scaleFactor倍数
    void zoom(float scaleFactor);

    //按照设置的倍数放大
    void zoomIn();

    //按照设置的倍数缩小
    void zoomOut();

    //ctrl是否按下
    bool getCtrlKeyPress();

    //设置能够缩放
    void setCanZoom(const bool &can);

    //得到能够缩放
    bool getCanZoom();

    //设置能够平移
    void setCanTranslate(const bool &can);

    //得到能够平移
    bool getCanTranslate();

    //还原
    void Restore();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void ini();
    Qt::MouseButton              m_translateButton;  //平移按钮
    qreal                        m_translateSpeed;   //平移速度
    qreal                        m_zoomDelta;        //缩放的增量
    bool                         m_bMouseTranslate;  //平移标识
    QPoint                       m_lastMousePos;     //鼠标最后按下的位置
    qreal                        m_scale;            //缩放值
    bool                         m_CtrlKeyPress;     //Ctrl按下
    bool                         m_CanZoom;          //能够通过滚轮缩放
    bool                         m_CanTranslate;     //能够平移

};

#endif // WIDGET_H
