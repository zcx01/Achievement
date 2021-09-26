#include "Cude.h"
#include <QVector3D>
#include "Shader.h"
Cude::Cude()
{

}

void Cude::initialize()
{
    if(!isValid()) return;

    glEnable(GL_DEPTH_TEST);

    initShader();

    float vertices[] = {
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


    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,5* sizeof(GL_FLOAT),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    //解绑VAO
    glBindVertexArray(0);

    for(int i =0; i < imageFileNames.size(); i++)
    {
        m_Textures << createTexture(imageFileNames.at(i));
    }
}

void Cude::addVertexShader(Shader *shader)
{
    shader->AddVertexShader(":/config/Coordinate/vertex.glsl");
}

void Cude::trans()
{

}


void Cude::Draw()
{
    QMatrix4x4 view;
    view.translate(0.0f,0.0f,-3.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f,this->width()/this->height(),0.1f,100.f);

    m_Shader->setMat4("view",view);
    m_Shader->setMat4("projection",projection);

    for(int i =0; i < cubePositions.size(); i++)
    {
        QMatrix4x4 model;
        model.translate(cubePositions.at(i));
        float angle = 20.0f *i;
        model.rotate(angle,1.0f,0.3f,0.5f);

        m_Shader->setMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);
    }
}
