#include "AssimpModel.h"
#include <QImage>
#include <QDebug>
#include "Shader.h"
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>

AssimpModel::AssimpModel()
{
    m_Shader = NULL;
    isPress = false;
}

void AssimpModel::initialize()
{
    initShader();
    glEnable(GL_DEPTH_TEST);
    camera = new Camera;
    m_GlModel = new GlModel();
    QString filePath = QApplication::applicationDirPath()+"/../config/nanosuit/nanosuit.obj";
    m_GlModel->loadFile(filePath);
}


void AssimpModel::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->CalFrameTime();

    m_Shader->Use();
    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    m_Shader->setMat4("projection",projection);
    m_Shader->setMat4("view",camera->GetCameraView());
//    m_Shader->setVec3("viewPos",camera->GetPosition());

    QMatrix4x4 model;
    m_Shader->setMat4("model",model);
    m_GlModel->Draw(m_Shader);

}

void AssimpModel::initShader()
{
    if(m_Shader) return;
    m_Shader = new Shader;
    m_Shader->AddVertexShader(":/config/AssimpModel/vertex.glsl");
    m_Shader->AddFragmentShader(":/config/AssimpModel/fragment.glsl");
    m_Shader->Link();
}

void AssimpModel::keyPressEvent(QKeyEvent *event)
{
//    float cameraSpeed = 2.5 * deltaTime;

    if(event->key() == Qt::Key_W)
    {
        camera->Front();
    }
    else if (event->key() == Qt::Key_S)
    {
        camera->Behind();
    }
    //向左或向右移动，先通过叉乘创建一个单位右向量，然后把位置向量加上或减去此向量
    else if (event->key() == Qt::Key_A)
    {
        camera->Left();
    }
    else if (event->key() == Qt::Key_D)
    {
        camera->Right();
    }
}

void AssimpModel::wheelEvent(QWheelEvent *event)
{
    float aspect = camera->GetAspect() - event->angleDelta().y() / 16;
    camera->SetAspect(aspect);
}

void AssimpModel::mousePressEvent(QMouseEvent *event)
{
    isPress = true;
    lastPos = event->pos();
}

void AssimpModel::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPress) return;
    float xoffset = event->x() - lastPos.x();
    float yoffset = lastPos.y() - event->y();
    lastPos = event->pos();

    float sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera->SetCameraAngle(xoffset,yoffset);
}

void AssimpModel::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
}
