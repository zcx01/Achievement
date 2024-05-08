#include "CameraWidget.h"
#include <QTime>
#include <QMatrix4x4>
#include "Shader.h"
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <cmath>
#include <complex>

CameraWidget::CameraWidget()
{
    initData();
    startDraw();
    timer.start();
}

void CameraWidget::initialize()
{
    Cude::initialize();
    UpdateCamera();
    //    CreateCamera();
    //   QTimer *timer = new QTimer(this);
    //   connect(timer,&QTimer::timeout,this,[=](){CreateCamera();render();});
    //   timer->start(100);
}

void CameraWidget::Draw()
{
    QMatrix4x4 projection;
    projection.perspective(aspect,this->width()/this->height(),0.1f,100.f);

    m_Shader->setMat4("view",view);
    m_Shader->setMat4("projection",projection);

    for(int i =0; i < cubePositions.size(); i++)
    {
        QMatrix4x4 model;
        model.translate(cubePositions.at(i));
        float angle = 20.0f *i;
        model.rotate(angle,1.0f,0.3f,0.5f);

        m_Shader->setMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);
    }

}

void CameraWidget::startDraw()
{
    //计算渲染上一帧需要的时间，速度 * 此时间，保证移动速度在所有的硬件上的移动速度一致
    float current =(float)timer.elapsed() / 1000;
    timer.restart();
    deltaTime = current;
}

void CameraWidget::mousePressEvent(QMouseEvent *event)
{
    isPress = true;
    lastPos = event->pos();
}

void CameraWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPress) return;
    float xoffset = event->x() - lastPos.x();
    float yoffset = lastPos.y() - event->y();
    lastPos = event->pos();

    float sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    QVector3D front;
    front.setX(std::cos(angleToRadian(yaw)) * std::cos(angleToRadian(pitch)));
    front.setY(std::sin(angleToRadian(pitch)));
    front.setZ(std::sin(angleToRadian(yaw)) * std::cos(angleToRadian(pitch)));
    cameraFront = front.normalized();

    UpdateCamera();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
}

void CameraWidget::keyPressEvent(QKeyEvent *event)
{
    //向前或向后移动，把位置向量加上或减去方向向量
    float cameraSpeed = 2.5 * deltaTime;
    if(event->key() == Qt::Key_W)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if (event->key() == Qt::Key_S)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    //向左或向右移动，先通过叉乘创建一个单位右向量，然后把位置向量加上或减去此向量
    else if (event->key() == Qt::Key_A)
    {
        cameraPos -= QVector3D::crossProduct(cameraFront,cameraUp).normalized() * cameraSpeed;
    }
    else if (event->key() == Qt::Key_D)
    {
        cameraPos += QVector3D::crossProduct(cameraFront,cameraUp).normalized() * cameraSpeed;
    }
    UpdateCamera();
    render();
}

void CameraWidget::wheelEvent(QWheelEvent *event)
{
    if(aspect >= 1.0f && aspect <=90.0f)
        aspect -= event->angleDelta().y()/16;
    if(aspect < 1.0f)
        aspect = 1.0f;
    if(aspect > 90.0f)
        aspect = 90;
}

void CameraWidget::CreateCamera()
{
    //要重置
    view = QMatrix4x4();
    QTime time = QTime::currentTime();
    float raduis = 10.0f;
    float camX = std::sin(time.msec()/100) * raduis;
    float camZ = std::cos(time.msec()/100) * raduis;
    //此函数不会重置
    view.lookAt(QVector3D(camX,0.0,camZ),QVector3D(0.0,0.0,0.0),QVector3D(0.0,1.0,0.0));
}

void CameraWidget::UpdateCamera()
{
    view = QMatrix4x4();
    //cameraPos + cameraFront 让摄像机注视着目标方向
    view.lookAt(cameraPos,cameraPos + cameraFront,cameraUp);
}

void CameraWidget::initData()
{
    cameraPos   =   QVector3D(0.0f,0.0f, 3.0f);
    cameraFront =   QVector3D(0.0f,0.0f,-1.0f);
    cameraUp    =   QVector3D(0.0f,1.0f, 0.0f);
    deltaTime   =   0;
    yaw         =    -90.0f;
    pitch       =   0;
    isPress     =   false;
    aspect      =   45;
}

float CameraWidget::angleToRadian(const float &angle)
{
    return (float)(angle * 3.14159 / 180);
}
