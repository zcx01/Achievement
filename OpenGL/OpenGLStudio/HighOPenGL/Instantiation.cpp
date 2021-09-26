#include "Instantiation.h"
#include <QVector2D>
#include <string>
#include <sstream>


Instantiation::Instantiation()
{

}

void Instantiation::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    lightingShader->Use();

    cudeVAO->bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}

void Instantiation::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader("./config/HighOPenGL/Instantiation/vertex.glsl");
    lightingShader->AddFragmentShader("./config/HighOPenGL/Instantiation/fragment.glsl");
    lightingShader->Link();
}

void Instantiation::initialize()
{
    glEnable(GL_DEPTH_TEST);
    initShader();
    camera = new Camera;
    float quadVertices[] = {
        // 位置          // 颜色
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    cudeVAO = new VertexArrayObject;
    cudeVAO->bind();
    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(quadVertices,sizeof(quadVertices));

    cudeVAO->VertexAttribPointerFloat(0,2,5,0);
    cudeVAO->VertexAttribPointerFloat(1,3,5,2);

    QVector2D translations[100];
    int index = 0;
    float offset = 0.1f;
    for(int y = -10; y < 10; y += 2)
    {
        for(int x = -10; x < 10; x += 2)
        {
            QVector2D translation;
            translation.setX((float)x / 10.0f + offset);
            translation.setY((float)y / 10.0f + offset);
            translations[index++] = translation;
        }
    }

    lightingShader->Use();
    for(int i=0; i < 100; i++){
        QString name = QString("offsets[%1]").arg(i);
        lightingShader->setVec2(name,translations[i]);
    }

}
