#include "CTexture2D.h"
#include <QImage>

CTexture2D::CTexture2D()
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
}

void CTexture2D::Draw(int indexSize)
{
    glDrawElements(GL_TRIANGLES,indexSize,GL_UNSIGNED_INT,0);
}

GLuint CTexture2D::CreateTexture(const QString &imageFileName)
{
    return CreateTexture(imageFileName,REPEAT);
}

GLuint CTexture2D::CreateTexture(const QString &imageFileName,EmbraceType type)
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,type);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,type);


    //-------------------------------------纹理过滤-------------------
    //参数1:指定纹理目标
    //参数2:操作类型		GL_TEXTURE_MIN_FILTER（缩小）	GL_TEXTURE_MAG_FILTER（放大）
    //参数3:过滤类型
    //GL_NEAREST					邻近过滤(默认)	选择中心点最接近纹理坐标的那个像素	会产生颗粒状的图案		更加真实
    //GL_LINEAR                     线性过滤		纹理坐标附近的纹理像素				产生更平滑的图案
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

    glBindTexture(GL_TEXTURE_2D,0);
    ids << texture;
    return texture;
}

void CTexture2D::ActiveTexture()
{
    for(int i =0; i < ids.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D,ids.at(i));
    }
}

void CTexture2D::RemoveAt(const int &index)
{
    if(ids.value(index,-1) == -1) return;
    glDeleteTextures(1,&ids[index]);
    ids.removeAt(index);
}


