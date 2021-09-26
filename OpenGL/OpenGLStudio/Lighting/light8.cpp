#include "light8.h"
#include "CTexture2D.h"

light8::light8()
{

}

void light8::initialize()
{
    glEnable(GL_DEPTH_TEST);

    initShader();

    camera = new Camera;
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
    cubePositions
            << QVector3D( 0.0f,  0.0f,  0.0f)
            << QVector3D( 2.0f,  5.0f, -15.0f)
            << QVector3D(-1.5f, -2.2f, -2.5f)
            << QVector3D(-3.8f, -2.0f, -12.3f)
            << QVector3D( 2.4f, -0.4f, -3.5f)
            << QVector3D(-1.8f,  3.0f, -8.5f)
            << QVector3D( 1.3f, -2.0f, -2.5f)
            << QVector3D( 1.5f,  2.0f, -2.5f)
            << QVector3D( 1.5f,  0.2f, -1.5f)
            << QVector3D(-1.3f,  1.0f, -1.5f)
               ;

    pointLightPositions
            << QVector3D( 0.7f,  0.2f,  2.0f)
            << QVector3D( 0.7f,  0.2f,  2.0f)
            << QVector3D(-4.0f,  2.0f, -12.0f)
            << QVector3D( 0.0f,  0.0f, -3.0f)
            ;
    cudeVAO = new VertexArrayObject;
    cudeVAO->bind();

    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(vertices,sizeof(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    lightVAO = new VertexArrayObject;
    lightVAO->bind();
    VBO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    texture = new CTexture2D;
    texture->CreateTexture(":/config/Lighting/8/container2.png");
    texture->CreateTexture(":/config/Lighting/8/container2_specular.png");
    lightingShader->Use();
    lightingShader->setInt("material.diffuse",0);
    lightingShader->setInt("material.specular",1);
}

void light8::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    lightingShader->Use();

    lightingShader->setFloat("material.shininess", 32.0f);
//    lightingShader->setVec3("dirLight.position",lightPos);


    lightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    lightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    for(int i =0; i < pointLightPositions.size(); i++)
    {
        lightingShader->setVec3(QString("pointLights[%1].position").arg(i), pointLightPositions[i]);
        lightingShader->setVec3(QString("pointLights[%1].ambient").arg(i), 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3(QString("pointLights[%1].diffuse").arg(i), 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3(QString("pointLights[%1].specular").arg(i), 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat(QString("pointLights[%1].constant").arg(i), 1.0f);
        lightingShader->setFloat(QString("pointLights[%1].linear").arg(i), 0.09);
        lightingShader->setFloat(QString("pointLights[%1].quadratic").arg(i), 0.032);
    }
    // spotLight
    lightingShader->setVec3("spotLight.position", camera->cameraPos);
    lightingShader->setVec3("spotLight.direction", camera->cameraFront);
    lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->setFloat("spotLight.constant", 1.0f);
    lightingShader->setFloat("spotLight.linear", 0.09);
    lightingShader->setFloat("spotLight.quadratic", 0.032);
    lightingShader->setFloat("spotLight.cutOff", std::cos(Camera::angleToRadian(12.5f)));
    lightingShader->setFloat("spotLight.outerCutOff", std::cos(Camera::angleToRadian(15.0f)));
    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    lightingShader->setVec3("viewPos",camera->GetPosition());

    texture->ActiveTexture();

    cudeVAO->bind();
    for(int i =0; i < cubePositions.size(); i++)
    {
        QMatrix4x4 model;
        model.translate(cubePositions.at(i));
        float angle = 20.0f *i;
        model.rotate(angle,1.0f,0.3f,0.5f);

        lightingShader->setMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);
    }

    lampgShader->Use();
    lampgShader->setMat4("projection",projection);
    lampgShader->setMat4("view",camera->GetCameraView());

    lightVAO->bind();

    for(int i =0; i < pointLightPositions.size(); i++)
    {
        QMatrix4x4 model;
        model.translate(pointLightPositions.at(i));
        model.scale(0.2f);

        lampgShader->setMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
}

void light8::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/Lighting/8/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/Lighting/8/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;
    lampgShader->AddVertexShader(":/config/Lighting/8/lightvertex.glsl");
    lampgShader->AddFragmentShader(":/config/Lighting/8/lightfragment .glsl");
    lampgShader->Link();
}

