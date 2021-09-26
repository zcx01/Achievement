#include "Camera.h"

Camera::Camera()
{
    initData();
    CalFrameTime();
}

QMatrix4x4 Camera::GetCameraView()
{
    QMatrix4x4 view;
    //cameraPos + cameraFront 让摄像机注视着目标方向
    view.lookAt(cameraPos,cameraPos + cameraFront,cameraUp);
    return view;
}

float Camera::angleToRadian(const float &angle)
{
    return (float)(angle * 3.14159 / 180);
}

void Camera::SetCameraAngle(const float &xoffset, const float &yoffset)
{
    yaw   += xoffset;
    pitch += yoffset;

    pitch =qBound(-89.0f,pitch,89.0f);
    QVector3D front;
    front.setX(std::cos(angleToRadian(yaw)) * std::cos(angleToRadian(pitch)));
    front.setY(std::sin(angleToRadian(pitch)));
    front.setZ(std::sin(angleToRadian(yaw)) * std::cos(angleToRadian(pitch)));
    cameraFront = front.normalized();
}

void Camera::initData()
{
    cameraPos   =   QVector3D(0.0f,0.0f, 3.0f);
    cameraFront =   QVector3D(0.0f,0.0f,-1.0f);
    cameraUp    =   QVector3D(0.0f,1.0f, 0.0f);
    yaw         =    -90.0f;
    pitch       =   0;
    aspect      =   45;
    cameraSpeed =   2.5;
}

float Camera::GetAspect() const
{
    return aspect;
}

void Camera::SetAspect(float value)
{
    aspect = qBound(1.0f,value,90.0f);
}

void Camera::CalFrameTime()
{
    float current =(float)timer.elapsed() / 1000;
    timer.restart();
    deltaTime = current;

    SetCameraSpeed( 2.5 * deltaTime);
}

QVector3D Camera::GetPosition()
{
    return cameraPos;
}

float Camera::GetCameraSpeed() const
{
    return cameraSpeed;
}

void Camera::SetCameraSpeed(float value)
{
    cameraSpeed = value;
}

//向左移动，先通过叉乘创建一个单位右向量，然后把位置向量减去此向量
void Camera::Left()
{
    cameraPos -= QVector3D::crossProduct(cameraFront,cameraUp).normalized() * cameraSpeed;
}

//向右移动，先通过叉乘创建一个单位右向量，然后把位置向量加去此向量
void Camera::Right()
{
    cameraPos += QVector3D::crossProduct(cameraFront,cameraUp).normalized() * cameraSpeed;
}

//向前移动，把位置向量加上前向量
void Camera::Front()
{
    cameraPos += cameraSpeed * cameraFront;
}

//向后移动，把位置向量减去前向量
void Camera::Behind()
{
    cameraPos -= cameraSpeed * cameraFront;
}

//向上移动，把位置向量加上上向量
void Camera::Up()
{
    cameraPos += cameraSpeed * cameraUp;
}

//向下移动，把位置向量减去上向量
void Camera::Drown()
{
    cameraPos -= cameraSpeed * cameraUp;
}




