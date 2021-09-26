#include "ETexture.h"
#include <QImage>
#include <QDebug>
#include "Shader.h"
#include <QPainter>
#include <QDebug>

ETexture::ETexture()
{
    //awesomeface.png图片有错误，效果会有影响
    imageFileNames <<":/config/Textrue/container.jpg" << ":/config/Textrue/awesomeface.png";
    m_Shader = NULL;
}

void ETexture::initialize()
{
    if(!isValid()) return;

    initShader();

    unsigned int indices[] ={
        0,1,3,
        1,2,3
    };

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    GLuint VBO , EBO;
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);


    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    SetVertices();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    //解绑VAO
    glBindVertexArray(0);

    for(int i =0; i < imageFileNames.size(); i++)
    {
        m_Textures << createTexture(imageFileNames.at(i));
    }

}

void ETexture::trans()
{

}

void ETexture::SetVertices()
{
    GLfloat vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
}

void ETexture::Draw()
{
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void ETexture::startDraw()
{

}

void ETexture::render()
{
    if(!isValid()) return;
    startDraw();
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    for(int i =0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D,m_Textures.at(i));
        glUniform1i(glGetUniformLocation(m_Shader->Progrm(),QString("ourTexture%1").arg(i+1).toStdString().c_str()),i);
    }
    glBindVertexArray(VAO);
    glUniform1f(glGetUniformLocation(m_Shader->Progrm(),"op"),0.2);
    trans();
    Draw();
    glBindVertexArray(0);
}


void ETexture::initShader()
{
    if(m_Shader) return;
    m_Shader = new Shader;
    addVertexShader(m_Shader);
    m_Shader->AddFragmentShader(":/config/Textrue/fragment.glsl");
    m_Shader->Link();
}

void ETexture::addVertexShader(Shader *shader)
{
    shader->AddVertexShader(":/config/Textrue/vertex.glsl");
}

bool ETexture::isValid()
{
    return !imageFileNames.isEmpty();
}

GLuint ETexture::createTexture(const QString &imageFileName)
{
    QImage  image(imageFileName);

    image = image.convertToFormat(QImage::Format_ARGB32);

    GLuint texture;
    //-------------------------------------生成纹理------------------------
    //参数1:生成纹理的数量
    //参数2:纹理的ID
    glGenTextures(1,&texture);

    //-------------------------------------绑定纹理------------------------
    glBindTexture(GL_TEXTURE_2D,texture);

    //-------------------------------------纹理的环绕方式-------------------
    //参数1:指定纹理目标					GL_TEXTURE_2D表示2D纹理
    //参数2:设置的选项与应用的纹理轴		配置了WRAP选项，并且指定了S和T (S、T、R等价于x、y、z)
    //参数3:激活指定的纹理环绕方式       处理超出范围之外的纹理坐标
    //			方式							描述
    //		GL_REPEAT						重复纹理图像(默认)
    //		GL_MIRRORED_REPEAT				重复纹理图形，不过是镜像放置
    //		GL_CLAMP_TO_EDGE				拉伸纹理边缘
    //		GL_CLAMP_TO_BORDER				超出的坐标为用户指定的边缘颜色
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);


    //-------------------------------------纹理过滤-------------------
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //-------------------------------------生成图片纹理------------------------
    //参数1:纹理目标
    //参数2:纹理指定多级渐远纹理的级别 0 (基本基本)
    //参数3:纹理存储格式
    //参数4:纹理的宽度
    //参数5:纹理的高度
    //参数6:总是设置0
    //参数7:源图的格式  GL_BGRA(要判断大小端，此电脑是little-endian 系统)
    //参数8:数据类型
    //参数9:真正的图形数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, image.width(), image.height(), 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
    //如果没有设置纹理的级别，调用此函数为当前绑定的纹理自动生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
