#include "Colors.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

Colors::Colors()
{
    isPress = false;
    cudeVAO =0;
    lightVAO =0;
    lightingShader=0;
    lampgShader=0;
    camera=0;
}

Colors::~Colors()
{
    delete cudeVAO;
    delete lightVAO;
    delete lightingShader;
    delete lampgShader;
    delete camera;
    qDeleteAll(m_Shaders.values());
    m_Shaders.clear();
}

void Colors::initialize()
{
    glEnable(GL_DEPTH_TEST);

    initShader();

    camera = new Camera;
    GLfloat vertices[] = {
        //     ---- 位置 ----
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

    cudeVAO = new VertexArrayObject();
    cudeVAO->bind();

    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(vertices,sizeof(vertices));

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);

    lightVAO = new VertexArrayObject;
    lightVAO->bind();
    VBO.bind();

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
}

void Colors::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    lightingShader->Use();

    lightingShader->setVec3("objectColor",QVector3D(1.0f, 0.5f, 0.31f));
    lightingShader->setVec3("lightColor",QVector3D( 1.0f, 1.0f, 1.0f));
    lightingShader->setVec3("lightPos",lightPos);

    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    lightingShader->setVec3("viewPos",camera->GetPosition());

    QMatrix4x4 model;
//    model.translate(1.0f,1.0f,1.0f);
//    model.rotate(30,1.0f,0.0f,1.0f);
    lightingShader->setMat4("model",model);

    renderOver();

    cudeVAO->bind();
    glDrawArrays(GL_TRIANGLES,0,36);

    lampgShader->Use();
    lampgShader->setMat4("projection",projection);
    lampgShader->setMat4("view",camera->GetCameraView());

    QMatrix4x4 lampmodel;
    lampmodel.translate(lightPos);
    lampmodel.scale(0.2);
    lampgShader->setMat4("model",lampmodel);

    lightVAO->bind();
    glDrawArrays(GL_TRIANGLES,0,36);
}

void Colors::resizeEvent(QResizeEvent *)
{
//    if(!QOpenGLContext::currentContext()) return;
//    const qreal retinaScale = devicePixelRatio();
//    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    //    render();
}

void Colors::keyPressEvent(QKeyEvent *event)
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
    else if (event->key() == Qt::Key_Up)
    {
        camera->Up();
    }
    else if(event->key() == Qt::Key_Down)
    {
        camera->Drown();
    }
}

void Colors::wheelEvent(QWheelEvent *event)
{
    float aspect = camera->GetAspect() - event->angleDelta().y() / 16;
    camera->SetAspect(aspect);
}

void Colors::mousePressEvent(QMouseEvent *event)
{
    isPress = true;
    lastPos = event->pos();
}

void Colors::mouseMoveEvent(QMouseEvent *event)
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

void Colors::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
}

void Colors::renderOver()
{

}

Shader *Colors::GetShader(const QString &fileName)
{
    return m_Shaders.value(fileName);
}

bool Colors::CreateShader(const QString &dirPath)
{
    QDir dir(dirPath);
    QFileInfoList fileInfos = dir.entryInfoList(QStringList()<<"*.vert",QDir::NoFilter,QDir::Name);
    foreach (QFileInfo fileInfo, fileInfos) {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        Shader * shader = new Shader;
        shader->AddVertexShader(QString("%1/%2.vert").arg(fileInfo.absolutePath()).arg(fileInfo.baseName()));
        shader->AddFragmentShader(QString("%1/%2.frag").arg(fileInfo.absolutePath()).arg(fileInfo.baseName()));
        shader->AddGeometry(QString("%1/%2.geom").arg(fileInfo.absolutePath()).arg(fileInfo.baseName()));
        shader->Link();
        m_Shaders.insert(fileInfo.baseName(),shader);
    }
    return !fileInfos.isEmpty();
}

void Colors::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/Lighting/1/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/Lighting/1/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;
    lampgShader->AddVertexShader(":/config/Lighting/1/vertex.glsl");
    lampgShader->AddFragmentShader(":/config/Lighting/1/lightfragment .glsl");
    lampgShader->Link();
}
