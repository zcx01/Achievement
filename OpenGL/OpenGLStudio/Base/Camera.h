#ifndef CAMERA_H
#define CAMERA_H
#include <QMatrix4x4>
#include <QVector3D>
#include <QTime>

//相机
class Camera
{
public:
    Camera();

    //得到相机的矩阵
    QMatrix4x4 GetCameraView();

    static float angleToRadian(const float &angle);

    /**
     * @brief 设置相机角度
     * @param xoffset:x偏移
     * @param yoffset:y偏移
     */
    void SetCameraAngle(const float &xoffset, const float &yoffset);

    //设置相机移动的速度
    void SetCameraSpeed(float value);

    //得到移动速度
    float GetCameraSpeed() const;

    //向左移动
    void Left();

    //向右移动
    void Right();

    //向前移动
    void Front();

    //向后移动
    void Behind();

    //向上移动
    void Up();

    //向下移动
    void Drown();

    //得到视野
    float GetAspect() const;

    //设置视野
    void SetAspect(float value);

    //计算一帧需要的时间
    void CalFrameTime();

    QVector3D GetPosition();
//private:
    void initData();

    QVector3D   cameraPos;      //相机位置
    QVector3D   cameraFront;    //前向量-目标位置
    QVector3D   cameraUp;       //上向量
    QPoint      lastPos;        //最后的鼠标位置
    float       yaw;            //偏航角
    float       pitch ;         //俯仰角
    float       aspect;         //视野
    float       cameraSpeed;    //相机移动的速度
    float       deltaTime;      //每一帧处理的时间
    QTime       timer;          //开始时间，计算每一帧的时间
};

#endif // CAMERA_H
