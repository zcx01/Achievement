#include "FrameTexture.h"
#include <QDebug>



FrameTexture::FrameTexture(const QString &fileName)
{
    quadFragment = fileName;
}

void FrameTexture::render()
{
    frameBuffer->bind();


    camera->CalFrameTime();

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    frameBuffer->ChangedImageStorageSize(width() * retinaScale, height() * retinaScale);


    glEnable(GL_DEPTH_TEST); // 开启深度测试
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());


    //画箱子
    QMatrix4x4 model;
    cudeVAO->bind();
    cudeTexture->ActiveTexture();
    model.translate(-1.0f, 0.0f, -1.0f);
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = QMatrix4x4();
    model.translate(2.0f, 0.0f, 0.0f);
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //画地板
    planeVAO->bind();
    floorTexture->ActiveTexture();
    model = QMatrix4x4();
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    cudeVAO->release();

    frameBuffer->release();
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置清屏为白色 (其实没必要，因为我们根本看不到后面)
    glClear(GL_COLOR_BUFFER_BIT);

    lampgShader->Use();
    quadVAO->bind();
    frameBuffer->bindTexColor2DBuffer();
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void FrameTexture::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/HighOPenGL/frametexture/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/HighOPenGL/frametexture/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;
    lampgShader->AddVertexShader(":/config/HighOPenGL/frametexture/vertexscreen.glsl");
    lampgShader->AddFragmentShader(quadFragment);
    lampgShader->Link();
}

void FrameTexture::initialize()
{
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
    float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    float quadVertices[] = { // 以标准化设备坐标填充整个屏幕的四边形的顶点属性。
                             // positions   // texCoords
                             -1.0f,  1.0f,  0.0f, 1.0f,
                             -1.0f, -1.0f,  0.0f, 0.0f,
                             1.0f, -1.0f,  1.0f, 0.0f,

                             -1.0f,  1.0f,  0.0f, 1.0f,
                             1.0f, -1.0f,  1.0f, 0.0f,
                             1.0f,  1.0f,  1.0f, 1.0f
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

    quadVAO = new VertexArrayObject;
    quadVAO->bind();

    Buffer quadVBO(Buffer::VertexBuffer);
    quadVBO.bind();
    quadVBO.allocate(quadVertices,sizeof(quadVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    floorTexture = new CTexture2D;
    floorTexture->CreateTexture(":/config/HighOPenGL/metal.png");
    cudeTexture = new CTexture2D;
    cudeTexture->CreateTexture(":/config/Textrue/container.jpg");

    lightingShader->Use();
    lightingShader->setInt("texture1",0);
    lampgShader->Use();
    lampgShader->setInt("screenTexture",0);

    frameBuffer = new FrameBuffer;
    frameBuffer->CreateTexture2D();
    frameBuffer->CreateRenderbuffers();
    frameBuffer->Check();
    //在核效果下环绕方式要设置为GL_CLAMP_TO_EDGE
    /*
     * 原因:
     * 核在对屏幕纹理的边缘进行采样的时候，由于还会对中心像素周围的8个像素进行采样，其实会取到纹理之外的像素
     * 由于环绕方式默认是GL_REPEAT，所以在没有设置的情况下取到的是屏幕另一边的像素，而另一边的像素本不应该对中心像素产生影响，
     * 这就可能会在屏幕边缘产生很奇怪的条纹。
     * 为了消除这一问题，我们可以将屏幕纹理的环绕方式都设置为GL_CLAMP_TO_EDGE。
     * 这样子在取到纹理外的像素时，就能够重复边缘的像素来更精确地估计最终的值了。
    */
    GLuint frameBufferTextureId =frameBuffer->getTexColorBufferId();
    glBindTexture(1,frameBufferTextureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(1,0);
}
