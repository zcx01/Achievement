#include "Geometry.h"

#define GREEN   "Green"
Geometry::Geometry()
{

}

void Geometry::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GetShader(GREEN)->Use();
    cudeVAO->bind();
    glDrawArrays(GL_POINTS,0,4);
}

void Geometry::initShader()
{
     CreateShader("./config/HighOPenGL/Geometry");
}

void Geometry::initialize()
{
    glEnable(GL_DEPTH_TEST);
    initShader();
    camera = new Camera;
    float points[] = {
        // positions
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
    };

    cudeVAO = new VertexArrayObject;
    cudeVAO->bind();
    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(points,sizeof(points));

    cudeVAO->VertexAttribPointerFloat(0,2,5,0);
    cudeVAO->VertexAttribPointerFloat(1,3,5,2);
}
