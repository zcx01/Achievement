#include "UniformBuffer.h"
#include <QApplication>
#include <QDebug>

#define RED     "Red"
#define GREEN   "Green"
#define BLUE    "Blue"
#define YELLOW  "Yellow"

UniformBuffer::UniformBuffer()
{

}

void UniformBuffer::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    lightingShader->Use();
    uboMatrices->bind();

    //填充缓冲的特定区域
    //参数含义:缓冲目标、一个偏移量、数据的大小和数据
    glBufferSubData(uboMatrices->getType(),64,64,camera->GetCameraView().data());
    uboMatrices->release();

    cudeVAO->bind();

    GetShader(RED)->Use();
    QMatrix4x4 model;
    model.translate(-0.75,0.75,0.0);
    GetShader(RED)->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,36);

    GetShader(GREEN)->Use();
    model = QMatrix4x4();
    model.translate(0.75,0.75,0.0);
    GetShader(GREEN)->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,36);

    GetShader(YELLOW)->Use();
    model = QMatrix4x4();
    model.translate(-0.75,-0.75,0.0);
    GetShader(YELLOW)->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,36);

    GetShader(BLUE)->Use();
    model = QMatrix4x4();
    model.translate(0.75,-0.75,0.0);
    GetShader(BLUE)->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void UniformBuffer::initShader()
{
//    lightingShader = new Shader;
//    lightingShader->AddVertexShader("./config/HighOPenGL/UniformBuffer/1.vert");
//    lightingShader->AddfragmentShader("./config/HighOPenGL/UniformBuffer/2.frag");
//    qDebug()<<lightingShader->Link();

    CreateShader("./config/HighOPenGL/UniformBuffer");
}

void UniformBuffer::initialize()
{
    glEnable(GL_DEPTH_TEST);
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

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);



    for(auto iter = m_Shaders.begin(); iter != m_Shaders.end(); iter++)
    {
        iter.value()->UniformBlockBinding("Matrices",0);
    }

    uboMatrices = new Buffer (Buffer::UniformBuffer);
    uboMatrices->bind();
    uboMatrices->allocate(NULL,2*64);
    uboMatrices->release();
    uboMatrices->bindBufferRange(0,2*64);


    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    uboMatrices->bind();
    glBufferSubData(uboMatrices->getType(),0,64,projection.data());
    uboMatrices->release();
}
