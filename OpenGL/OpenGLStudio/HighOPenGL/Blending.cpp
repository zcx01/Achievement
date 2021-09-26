#include "Blending.h"

Blending::Blending()
{

}

void Blending::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    QMatrix4x4 model;

    cudeVAO->bind();
    texture->ActiveTexture();
    model.translate(-1.0f, 0.0f, -1.0f);
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //第二个箱子
    model = QMatrix4x4();
    model.translate(2.0f, 0.0f, 0.0f);
    lightingShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    cudeVAO->release();

    model = QMatrix4x4();
    planeVAO->bind();
    floorTexture->ActiveTexture();
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,6);
    planeVAO->release();

    transparentVAO->bind();
    grassTexture->ActiveTexture();
    for(int i=0; i < vegetations.size();i++)
    {
        model = QMatrix4x4();
        model.translate(vegetations.at(i));
        lightingShader->setMat4("model",model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    transparentVAO->release();

}

void Blending::initialize()
{
    glEnable(GL_DEPTH_TEST);

    initShader();

    camera = new Camera;

    float cubeVertices[] = {
        // positions          // texture Coords
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };

    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    cudeVAO = new VertexArrayObject();
    cudeVAO->bind();

    Buffer VBO(Buffer::VertexBuffer);
    VBO.bind();
    VBO.allocate(&cubeVertices,sizeof(cubeVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    planeVAO = new VertexArrayObject();
    planeVAO->bind();
    Buffer planeVBO(Buffer::VertexBuffer);
    planeVBO.bind();
    planeVBO.allocate(planeVertices,sizeof(planeVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    transparentVAO = new VertexArrayObject();
    transparentVAO->bind();
    Buffer transparentVBO(Buffer::VertexBuffer);
    transparentVBO.bind();
    transparentVBO.allocate(transparentVertices,sizeof(transparentVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    texture = new CTexture2D;
    texture->CreateTexture(":/config/HighOPenGL/marble.jpg");
    floorTexture = new CTexture2D;
    floorTexture->CreateTexture(":/config/HighOPenGL/metal.png");
    grassTexture = new CTexture2D;
    grassTexture->CreateTexture(":/config/HighOPenGL/grass.png",CTexture2D::CLAMP_TO_EDGE);

    vegetations<<QVector3D(-1.5f, 0.0f, -0.48f)
               <<QVector3D( 1.5f, 0.0f, 0.51f)
               <<QVector3D( 0.0f, 0.0f, 0.7f)
               <<QVector3D(-0.3f, 0.0f, -2.3f)
               <<QVector3D(0.5f, 0.0f, -0.6f);
    lightingShader->Use();
    lightingShader->setInt("texture1",0);

}

void Blending::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/HighOPenGL/Blending/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/HighOPenGL/Blending/fragment.glsl");
    lightingShader->Link();
}
