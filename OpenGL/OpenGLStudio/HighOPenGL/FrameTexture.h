#ifndef FRAMETEXTURE_H
#define FRAMETEXTURE_H

#include "../Lighting/Colors.h"
#include "Camera.h"
#include "CTexture2D.h"
#include "FrameBuffer.h"

//把所有场景的渲染到一个纹理上
class FrameTexture : public Colors
{
public:
    FrameTexture(const QString &fileName);
    void render();

protected:
    void initShader();
    void initialize();


    VertexArrayObject* planeVAO;        //地板
    VertexArrayObject* quadVAO;         //帧缓冲的四方形的范围
    CTexture2D*        floorTexture;    //地板纹理
    CTexture2D*        cudeTexture;     //箱子纹理
    FrameBuffer*       frameBuffer;     //帧缓冲
    QString            quadFragment;    //帧缓冲的四方形着色器文件名
};

#endif // FRAMETEXTURE_H
