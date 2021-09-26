#include "BlinnPhong.h"
#include <QKeyEvent>


BlinnPhong::BlinnPhong()
{
    m_Blinn = true;
}

void BlinnPhong::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(0.0f, 0.0f, 0.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,1000.0f);

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    lightingShader->setVec3("viewPos",camera->GetPosition());
    lightingShader->setVec3("lightPos",lightPos);
    lightingShader->setInt("blinn",m_Blinn);

    cudeVAO->bind();
    m_Texture->ActiveTexture();
    glDrawArrays(GL_TRIANGLES,0,6);
}

void BlinnPhong::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader("./config/HighLight/BlinnPhong/vertex.glsl");
    lightingShader->AddFragmentShader("./config/HighLight/BlinnPhong/fragment.glsl");
    lightingShader->Link();
}

void BlinnPhong::initialize()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    initShader();
    camera = new Camera;
    float planeVertices[] = {
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    cudeVAO = new VertexArrayObject;
    cudeVAO->bind();
    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(planeVertices,sizeof(planeVertices));
    cudeVAO->VertexAttribPointerFloat(0,3,8,0);
    cudeVAO->VertexAttribPointerFloat(1,3,8,3);
    cudeVAO->VertexAttribPointerFloat(2,2,8,6);

    m_Texture = new CTexture2D;
    m_Texture->CreateTexture("./config/HighLight/BlinnPhong/wood.png");

    lightingShader->Use();
    lightingShader->setInt("floorTexture",0);
}

void BlinnPhong::keyPressEvent(QKeyEvent *event)
{
    Colors::keyPressEvent(event);
    if(event->key() == Qt::Key_B){
        m_Blinn = !m_Blinn;
    }
}
