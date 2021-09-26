#include "CTextureCude.h"
#include <QImage>
#include <QDebug>

CTextureCude::CTextureCude()
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
    textureId = 0;
}

void CTextureCude::CreateTexure(const QStringList &fileNames, int size,int h)
{
    //-------------------------------------生成纹理------------------------
    //参数1:生成纹理的数量
    //参数2:纹理的ID
    glGenTextures(1,&textureId);


    //-------------------------------------绑定纹理------------------------
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);


    int index = 0;
    foreach (QString file, fileNames) {
        QImage image(file);
        if (image.isNull()) {
            break;
        }

        image = image.convertToFormat(QImage::Format_ARGB32);

        //qDebug() << "Image size:" << image.width() << "x" << image.height();
//        if (size <= 0)
//            size = image.width();
//        if (size != image.width() || size != image.height())
//            image = image.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Works on x86, so probably works on all little-endian systems.
        // Does it work on big-endian systems?
        //-------------------------------------生成图片纹理------------------------
        //参数1:纹理目标
        //GL_TEXTURE_CUBE_MAP_POSITIVE_X	右
        //GL_TEXTURE_CUBE_MAP_NEGATIVE_X	左
        //GL_TEXTURE_CUBE_MAP_POSITIVE_Y	上
        //GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	下
        //GL_TEXTURE_CUBE_MAP_POSITIVE_Z	后
        //GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	前
        //参数2:纹理指定多级渐远纹理的级别 0 (基本基本)
        //参数3:纹理存储格式
        //参数4:纹理的宽度
        //参数5:纹理的高度
        //参数6:总是设置0
        //参数7:源图的格式  GL_BGRA(要判断大小端，此电脑是little-endian 系统)
        //参数8:数据类型
        //参数9:真正的图形数据
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_BGRA, image.width(), image.height(), 0,
            GL_BGRA, GL_UNSIGNED_BYTE, image.bits());

        if (++index == 6)
            break;
    }

    // Clear remaining faces.
    while (index < 6) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_BGRA, size, size, 0,
            GL_BGRA, GL_UNSIGNED_BYTE, 0);
        ++index;
    }


    //-------------------------------------纹理的环绕方式-------------------
    //参数1:指定纹理目标					GL_TEXTURE_2D表示2D纹理
    //参数2:设置的选项与应用的纹理轴		配置了WRAP选项，并且指定了S和T (S、T、R等价于x、y、z)
    //参数3:激活指定的纹理环绕方式       处理超出范围之外的纹理坐标
    //			方式							描述
    //		GL_REPEAT						重复纹理图像(默认)
    //		GL_MIRRORED_REPEAT				重复纹理图形，不过是镜像放置
    //		GL_CLAMP_TO_EDGE				拉伸纹理边缘
    //		GL_CLAMP_TO_BORDER				超出的坐标为用户指定的边缘颜色
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //-------------------------------------纹理过滤-------------------
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    qDebug()<<glGetError();
}

void CTextureCude::ActiveTexture()
{
    if(textureId == 0) return;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glEnable(GL_TEXTURE_CUBE_MAP);
}
