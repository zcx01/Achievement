#include "Skybox.h"
#include "CTextureCude.h"
#include <QDebug>
#include "CTexture2D.h"

Skybox::Skybox()
{

}

void Skybox::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    lightingShader->Use();

    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);

    QMatrix4x4 view =camera->GetCameraView();

    QMatrix4x4 model;

    lightingShader->setMat4("model", model);
    lightingShader->setMat4("view", view);
    lightingShader->setMat4("projection", projection);

    cudeVAO->bind();
    m_cudeTexture->ActiveTexture();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    cudeVAO->release();

    glDepthFunc(GL_LEQUAL);
    m_SkyShader->Use();


    view(0,3) =0;
    view(1,3) =0;
    view(2,3) =0;
    view(3,3) =0;
    view(3,2) =0;
    view(3,1) =0;
    view(3,0) =0;


    m_SkyShader->setMat4("view",view);
    m_SkyShader->setMat4("projection",projection);


    m_SkyVAO->bind();
    m_TextureCude->ActiveTexture();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_SkyVAO->release();

    glDepthFunc(GL_LESS);

}

void Skybox::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/HighOPenGL/templatetest/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/HighOPenGL/templatetest/fragment.glsl");
    lightingShader->Link();

    m_SkyShader = new Shader;
    m_SkyShader->AddVertexShader(":/config/HighOPenGL/skybox/vertex.glsl");
    m_SkyShader->AddFragmentShader(":/config/HighOPenGL/skybox/fragment.glsl");
    m_SkyShader->Link();
}

void Skybox::initialize()
{
    glEnable(GL_DEPTH_TEST);

    initShader();

    camera = new Camera;

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    cudeVAO = new VertexArrayObject();
    cudeVAO->bind();

    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(cubeVertices,sizeof(cubeVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VBO.release();




    m_SkyVAO = new VertexArrayObject;
    m_SkyVAO->bind();

    Buffer skyVBO(Buffer::VertexBuffer);
    skyVBO.bind();
    skyVBO.allocate(skyboxVertices,sizeof(skyboxVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_cudeTexture = new CTexture2D;
    m_cudeTexture->CreateTexture(":/config/Textrue/container.jpg");

    QStringList fileNames;
    fileNames<<":/config/HighOPenGL/skybox/right.jpg"
            <<":/config/HighOPenGL/skybox/left.jpg"
           <<":/config/HighOPenGL/skybox/top.jpg"
          <<":/config/HighOPenGL/skybox/bottom.jpg"
         <<":/config/HighOPenGL/skybox/front.jpg"
        <<":/config/HighOPenGL/skybox/back.jpg";
    m_TextureCude = new CTextureCude;
    m_TextureCude->CreateTexure(fileNames,0,0);


    lightingShader->Use();
    lightingShader->setInt("texture1",0);

    m_SkyShader->Use();
    m_SkyShader->setInt("skybox",0);
}
