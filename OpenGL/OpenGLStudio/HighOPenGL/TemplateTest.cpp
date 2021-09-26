#include "TemplateTest.h"



TemplateTest::TemplateTest()
{

}

void TemplateTest::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    QVector3D lightPos(1.2f, 1.0f, 2.0f);
    camera->CalFrameTime();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    lampgShader->Use();


    QMatrix4x4 projection;
    projection.perspective(camera->GetAspect(),(float)this->width()/(float)this->height(),0.1f,100.f);
    lampgShader->setMat4("projection",projection);
    lampgShader->setMat4("view",camera->GetCameraView());

    lightingShader->Use();
    lightingShader->setMat4("projection",projection);
    lightingShader->setMat4("view",camera->GetCameraView());
    QMatrix4x4 model;


    //禁用模板测试
    glStencilMask(0x00);
    //画地板
    planeVAO->bind();
    floorTexture->ActiveTexture();
    lightingShader->setMat4("model",model);
    glDrawArrays(GL_TRIANGLES,0,6);
    planeVAO->release();

    //[1]、正常绘制对象，写入模板缓冲区
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    //画箱子
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

    //[2]、现在绘制稍微缩放的对象，这次禁止写入模板缓冲区。
    //因为模板缓冲区现在填充了几个1。缓冲区中为1的部分不绘制，因此只绘制
    //对象的大小不同，使其看起来像边框。
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//不等1的片段会被丢弃
    glDisable(GL_DEPTH_TEST);//禁用深度测试
    lampgShader->Use();
    float scale = 1.1;

    cudeVAO->bind();
    texture->ActiveTexture();
    model = QMatrix4x4();
    model.translate(-1.0f, 0.0f, -1.0f);
    model.scale(scale);
    lampgShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //第二个箱子
    model = QMatrix4x4();
    model.translate(2.0f, 0.0f, 0.0f);
    model.scale(scale);
    lampgShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
}

void TemplateTest::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/HighOPenGL/templatetest/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/HighOPenGL/templatetest/fragment.glsl");
    lightingShader->Link();

    lampgShader = new Shader;//边框
    lampgShader->AddVertexShader(":/config/HighOPenGL/templatetest/vertex.glsl");
    lampgShader->AddFragmentShader(":/config/HighOPenGL/templatetest/sfragment.glsl");
    lampgShader->Link();
}

void TemplateTest::initialize()
{
    glEnable(GL_DEPTH_TEST);    //启动深度测试
    glDepthFunc(GL_LESS);       //更新深度缓冲的模式
    glEnable(GL_STENCIL_TEST);  //启用模板测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//通过的模式
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//更新缓冲的模式

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
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
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

    texture = new CTexture2D;
    texture->CreateTexture(":/config/HighOPenGL/marble.jpg");
    floorTexture = new CTexture2D;
    floorTexture->CreateTexture(":/config/HighOPenGL/metal.png");
    lightingShader->Use();
    lightingShader->setInt("texture1",0);
}
