#include "light7.h"
#include "CTexture2D.h"

light7::light7()
{

}

void light7::initialize()
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
            << QVector3D(-1.7f,  3.0f, -7.5f)
            << QVector3D( 1.3f, -2.0f, -2.5f)
            << QVector3D( 1.5f,  2.0f, -2.5f)
            << QVector3D( 1.5f,  0.2f, -1.5f)
            << QVector3D(-1.3f,  1.0f, -1.5f)
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
    texture->CreateTexture(":/config/Lighting/7/container2.png");
    texture->CreateTexture(":/config/Lighting/7/container2_specular.png");
    lightingShader->Use();
    lightingShader->setInt("material.diffuse",0);
    lightingShader->setInt("material.specular",1);
}

void light7::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    lightingShader->Use();

    lightingShader->setVec3("light.position",lightPos);

    //光源能够覆盖50的距离
    lightingShader->setFloat("light.constant", 1.0f);
    lightingShader->setFloat("light.linear", 0.09f);
    lightingShader->setFloat("light.quadratic", 0.032f);
    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    lightingShader->setVec3("viewPos",camera->GetPosition());

    renderOver();
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

//    lampgShader->Use();
//    lampgShader->setMat4("projection",projection);
//    lampgShader->setMat4("view",camera->GetCameraView());

//    QMatrix4x4 lampmodel;
//    lampmodel.translate(lightPos);
//    lampmodel.scale(0.2);
//    lampgShader->setMat4("model",lampmodel);

//    lightVAO->bind();
//    glDrawArrays(GL_TRIANGLES,0,36);
}

void light7::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/Lighting/7/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/Lighting/7/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;
    lampgShader->AddVertexShader(":/config/Lighting/7/lightvertex.glsl");
    lampgShader->AddFragmentShader(":/config/Lighting/7/lightfragment .glsl");
    lampgShader->Link();
}

void light7::renderOver()
{
    lightingShader->setVec3("light.ambient",  QVector3D(0.2f, 0.2f, 0.2f));
    lightingShader->setVec3("light.diffuse",  QVector3D(0.5f, 0.5f, 0.5f)); // 将光照调暗了一些以搭配场景
    lightingShader->setVec3("light.specular", QVector3D(1.0f, 1.0f, 1.0f));
    lightingShader->setVec3("light.position",  camera->cameraPos);
    lightingShader->setVec3("light.direction", camera->cameraFront);
    lightingShader->setFloat("light.cutOff",   std::cos(Camera::angleToRadian(12.5f)));
    lightingShader->setFloat("light.outerCutOff",   std::cos(Camera::angleToRadian(17.5f)));

    lightingShader->setVec3("material.specular", QVector3D(0.5f, 0.5f, 0.5f));
    lightingShader->setFloat("material.shininess", 64.0f);
    texture->ActiveTexture();
}
