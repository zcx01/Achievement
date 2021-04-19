#include "CGraphicsView.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QScrollBar>
#include <QDebug>
#include "czdrawstruct.h"
#include <QGraphicsItem>
#include <CZBase.h>

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

CGraphicsView::CGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    ini();
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setRenderHint(QPainter::Antialiasing);
    //setSceneRect(0,0, INT_MAX, INT_MAX);
    centerOn(0, 0);
    //this->horizontalScrollBar()->setEnabled(false);//要禁用，不然，使用滚轮缩小时，出现滚动条，会把Item的坐标改变
    //this->verticalScrollBar()->setEnabled(false);
    //this->setScene(new CGraphicsScene());
}

CGraphicsView::~CGraphicsView()
{
    
}

void CGraphicsView::ini()
{
    m_scale = 1.0;
    m_zoomDelta = 0.1;
    m_translateSpeed = 1.0;
    m_bMouseTranslate = false;
    m_translateButton = Qt::LeftButton;
    m_CtrlKeyPress = false;
    m_CanZoom = true;
    m_CanTranslate = true;
}

void CGraphicsView::translate(QPointF delta)
{
    delta *= m_scale;           // 根据当前 zoom 缩放平移数
    delta *= m_translateSpeed;  //平移速度

    // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    //设置新的点
    QPoint newCenter(VIEW_WIDTH / 2 - delta.x(),  VIEW_HEIGHT / 2 - delta.y());
    centerOn(mapToScene(newCenter));

    // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void CGraphicsView::setTranslateSpeed(qreal speed)
{
    m_translateSpeed = speed;
}

qreal CGraphicsView::translateSpeed() const
{
    return m_translateSpeed;
}

void CGraphicsView::setZoomDelta(qreal delta)
{
    m_zoomDelta = delta;
}

qreal CGraphicsView::zoomDelta() const
{
    return m_zoomDelta;
}

void CGraphicsView::zoom(float scaleFactor)
{
    // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // 防止过小或过大
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;
    scale(scaleFactor, scaleFactor);
    m_scale *= scaleFactor;

    // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void CGraphicsView::zoomIn()
{
    zoom(1 + m_zoomDelta);
}

void CGraphicsView::zoomOut()
{
    zoom(1 - m_zoomDelta);
}

bool CGraphicsView::getCtrlKeyPress()
{
    return m_CtrlKeyPress;
}

void CGraphicsView::setCanZoom(const bool &can)
{
    m_CanZoom = can;
}

bool CGraphicsView::getCanZoom()
{
    return m_CanZoom;
}

void CGraphicsView::setCanTranslate(const bool &can)
{
    m_CanTranslate = can;
}

bool CGraphicsView::getCanTranslate()
{
    return m_CanTranslate;
}

void CGraphicsView::Restore()
{
    ini();
    resetTransform();
}

void CGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == m_translateButton)
    {
        // 当光标底下没有 item 时，才能移动
        //QPointF point = mapToScene(event->pos());
        QGraphicsItem *item= itemAt(event->pos());
        CZBase *bItem = dynamic_cast<CZBase *> (item);
        if(!item || item->data(BACKGOUNDINDEX).toBool() || (bItem && !bItem->isContainMousePos(event->pos())))
        {
            m_bMouseTranslate = true;
            m_lastMousePos = event->pos();
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == m_translateButton)
        m_bMouseTranslate = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void CGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}

void CGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMouseTranslate && m_CanTranslate)
    {
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(mouseDelta);
    }
    m_lastMousePos = event->pos();

    QGraphicsView::mouseMoveEvent(event);
}

void CGraphicsView::wheelEvent(QWheelEvent *event)
{
    // 滚轮的滚动量
    if(m_CanZoom)
    {
#if QT_VERSION >=0x050000
        QPoint scrollAmount = event->angleDelta();
        // 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
        scrollAmount.y() > 0 ? zoomIn() : zoomOut();
#else
        event->delta()  > 0 ? zoomIn() : zoomOut();
#endif
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

void CGraphicsView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Up:
        //translate(QPointF(0, -2));  // 上移
        break;
    case Qt::Key_Down:
        //translate(QPointF(0, 2));  // 下移
        break;
    case Qt::Key_Left:
        //translate(QPointF(-2, 0));  // 左移
        break;
    case Qt::Key_Right:
        //translate(QPointF(2, 0));  // 右移
        break;
    case Qt::Key_Plus:  // 放大
        //zoomIn();
        break;
    case Qt::Key_Minus:  // 缩小
        //zoomOut();
        break;
    case Qt::Key_Space:  // 逆时针旋转
        // rotate(-5);
        break;
    case Qt::Key_Enter:  // 顺时针旋转
    case Qt::Key_Return:
        // rotate(5);
        break;
    case Qt::Key_Control:
        m_CtrlKeyPress = true;
        break;
    }
}

void CGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
        m_CtrlKeyPress = false;
        break;
    }
    QGraphicsView::keyReleaseEvent(event);
}
