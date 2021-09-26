#include "Planet.h"
#include "Base/GlModel.h"

const int amount = 10000;
Planet::Planet()
{
}

void Planet::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,1000.0f);

    lampgShader->Use();
    lampgShader->setMat4("projection",projection);
    lampgShader->setMat4("view",camera->GetCameraView());

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());



    QMatrix4x4 model;
    model.translate(0.0f,-3.0f,0.0f);
    model.scale(4.0f,4.0f,4.0f);

    lightingShader->setMat4("model",model);
    m_Planet->Draw(lightingShader);

    //最简单的画法
//    for(int i=0; i < m_ModelMatrices.size(); i++){
//        lightingShader->setMat4("model",m_ModelMatrices.at(i));
//        m_Rock->Draw(lightingShader);
//    }

    //优化，使用顶点属性
    lampgShader->Use();
    for(int i=0; i < m_Rock->Meshs().size();i++){
       m_Rock->Meshs().at(i)->Draw(lampgShader,amount);
    }
}

void Planet::initShader()
{
    lightingShader = new Shader; //中心天体着色器
    lightingShader->AddVertexShader("./config/HighOPenGL/Planet/vertex.glsl");
    lightingShader->AddFragmentShader("./config/HighOPenGL/Planet/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;   //小行星着色器
    lampgShader->AddVertexShader("./config/HighOPenGL/Planet/rockvertex.glsl");
    lampgShader->AddFragmentShader("./config/HighOPenGL/Planet/fragment.glsl");
    lampgShader->Link();
}

void Planet::initialize()
{
    m_Planet = new GlModel;
    m_Planet->loadFile("./config/HighOPenGL/Planet/planet/planet.obj");
    m_Rock = new GlModel;
    m_Rock->loadFile("./config/HighOPenGL/Planet/rock/rock.obj");
    glEnable(GL_DEPTH_TEST);
    initShader();
    camera = new Camera;
    camera->cameraPos =QVector3D(0.0f,0.0f,155.0f);
    qsrand(QTime(0,0,0).secsTo(QTime().currentTime()));
    float radius = 50.0f;
    float offset = 2.5f;
    static Matrix4x4 modelMatrices[amount];/**栈区的大小不会大小，放在堆区**/
    for(int i=0; i <amount;i++){
        QMatrix4x4 model;
        float angle = (float) i / (float) amount * 360.0f;
        //控制范围为[-offset,offset]
        //x和z位置变换到了一个半径为radius的圆形上
        //在半径的基础上偏移了-offset到offset。我们让y偏移的影响更小一点，让小行星带更扁平一点
        float dis = (qrand() % (int) ( 2 *offset *100)) / 100.0f - offset;
        float x = std::sin(angle) * radius + dis;
        dis = (qrand() % (int)( 2* offset *100)) / 100.0f - offset;
        float y = dis * 0.4f;
        dis = (qrand() % (int)( 2* offset *100)) / 100.0f - offset;
        float z = std::cos(angle) *radius + dis;
        model.translate(x,y,z);

        //缩放：在0.05和0.25f之间缩放
        float scale = (qrand() % 20) / 100.0f+0.05;
        model.scale(scale);

        //旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
        float rotAngle = (qrand() % 360);
        model.rotate(rotAngle,QVector3D(0.4f,0.6f,0.8f));

        modelMatrices[i] = Matrix4x4(model);
    }

    //优化【使用顶点属性】
    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    int allSize = sizeof(Matrix4x4)*amount;
    VBO.allocate(&modelMatrices[0],allSize);

    for(int i=0; i < m_Rock->Meshs().size(); i++){
        VertexArrayObject * VAO = m_Rock->Meshs().at(i)->getVAO();
        VAO->bind();

        VAO->VertexAttribPointerFloat(3,4,sizeof(Matrix4x4),0);
        VAO->VertexAttribPointerFloat(4,4,sizeof(Matrix4x4),4);
        VAO->VertexAttribPointerFloat(5,4,sizeof(Matrix4x4),2*4);
        VAO->VertexAttribPointerFloat(6,4,sizeof(Matrix4x4),3*4);

        VAO->VertexAttribDivisor(3,1);
        VAO->VertexAttribDivisor(4,1);
        VAO->VertexAttribDivisor(5,1);
        VAO->VertexAttribDivisor(6,1);

        VAO->release();
    }
    delete &(modelMatrices);

}
