#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H
#include "Cude.h"
#include <QMatrix4x4>
#include <QTime>

class CameraWidget : public Cude
{
public:
    CameraWidget();

    void initialize();
    void Draw();
    void startDraw();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void CreateCamera();
    void UpdateCamera();
    void initData();

    float angleToRadian(const float &angle);

    QMatrix4x4  view;
    QVector3D   cameraPos;      //相机位置
    QVector3D   cameraFront;    //前向量-目标位置
    QVector3D   cameraUp;       //上向量
    float       deltaTime;      //每一帧处理的时间
    QTime       timer;          //开始时间，计算每一帧的时间
    QPoint      lastPos;        //最后的鼠标位置
    float       yaw;            //偏航角
    float       pitch ;         //俯仰角
    float       aspect;         //视野
    bool        isPress;
};

#endif // CAMERAWIDGET_H
