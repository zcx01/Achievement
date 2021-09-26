#include "MSAA.h"



MSAA::MSAA()
{

}

void MSAA::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,1000.0f);

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());

    QMatrix4x4 model;
    lightingShader->setMat4("model",model);
    cudeVAO->bind();
    glDrawArrays(GL_TRIANGLES,0,36);
}

void MSAA::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader("./config/HighOPenGL/MSAA/vertex.glsl");
    lightingShader->AddFragmentShader("./config/HighOPenGL/MSAA/fragment.glsl");
    lightingShader->Link();
}

void MSAA::initialize()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    initShader();
    camera = new Camera;
    float cubeVertices[] = {
        // positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    cudeVAO = new VertexArrayObject;
    cudeVAO->bind();
    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(cubeVertices,sizeof(cubeVertices));

    cudeVAO->VertexAttribPointerFloat(0,3,3,0);
}
