#include "CDragButton.h"
#include <QMimeData>
#include "../BaseDraw/czdrawstruct.h"
#include <QDrag>
#include <QMouseEvent>
#include <QPixmap>
#include <QApplication>

CDragButton::CDragButton(QWidget *parent) : QPushButton(parent)
{
    setAcceptDrops(true);
}

void CDragButton::sendDataFinished()
{

}

void CDragButton::setDropData(const QVariantMap &data)
{
    m_Attrs = data;
}

void CDragButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        m_StartPos = event->pos();
    QPushButton::mousePressEvent(event);
}

void CDragButton::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - m_StartPos).manhattanLength(); //曼哈顿长度
        if(distance >= QApplication::startDragDistance() && this->acceptDrops())//拖动起始距离值
            performDrag();//启动拖动操作
    }
    QPushButton::mouseMoveEvent(event);
}

void CDragButton::dragEnterEvent(QDragEnterEvent *event)
{
    CDragButton *source = qobject_cast<CDragButton *>(event->source());
    if(source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void CDragButton::dragMoveEvent(QDragMoveEvent *event)
{
    CDragButton *source = qobject_cast<CDragButton *>(event->source());
    if(source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void CDragButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);
}

void CDragButton::performDrag()
{
    emit sig_Drag();
    QMimeData *mimeData = new QMimeData();
    mimeData->setProperty(DROPDATA,m_Attrs);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
#if QT_VERSION >= 0x050000
    QPixmap p  = this->grab(this->geometry());
    drag->setPixmap(QPixmap(p));
#else
    drag->setPixmap(QPixmap::grabWidget(this,this->geometry()));
#endif
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
        sendDataFinished();
}
