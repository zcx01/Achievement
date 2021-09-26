#ifndef CTEXTURE2D_H
#define CTEXTURE2D_H
#include <QOpenGLFunctions_3_3_Core>

//纹理
class CTexture2D : protected QOpenGLFunctions_3_3_Core
{
public:
    enum EmbraceType
    {
        REPEAT          =	GL_REPEAT           ,   //重复纹理图像(默认)
        MIRRORED_REPEAT =	GL_MIRRORED_REPEAT	,   //重复纹理图形，不过是镜像放置
        CLAMP_TO_EDGE   =	GL_CLAMP_TO_EDGE	,   //拉伸纹理边缘
        CLAMP_TO_BORDER =   GL_CLAMP_TO_BORDER	,   //超出的坐标为用户指定的边缘颜色
    };
    CTexture2D();

    //画 indexSize(索引的大小)
    void Draw(int indexSize);

    //创建文件 imageFileName(文件名)
    GLuint CreateTexture(const QString &imageFileName);

    //创建文件 imageFileName(文件名)
    GLuint CreateTexture(const QString &imageFileName,EmbraceType type);

    //激活纹理
    void ActiveTexture();

    //移除一个
    void RemoveAt(const int &index);

private:
    QList<GLuint>       ids;
};

#endif // CTEXTURE2D_H
