#ifndef CTEXTURECUDE_H
#define CTEXTURECUDE_H

#include <QOpenGLFunctions_3_3_Core>

class CTextureCude : protected QOpenGLFunctions_3_3_Core
{
public:
    CTextureCude();

    //创建纹理
    void CreateTexure(const QStringList &fileNames, int size, int h);

    //激活纹理
    void ActiveTexture();
protected:

private:
    GLuint       textureId;
};

#endif // CTEXTURECUDE_H
