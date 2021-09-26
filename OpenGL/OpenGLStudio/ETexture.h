#ifndef ETEXTURE_H
#define ETEXTURE_H

#include "openglwindow.h"
#include <QImage>

class Shader;
class ETexture : public OpenGLWindow
{
public:
    ETexture();

    void render();

protected:

    void initShader();

    virtual void addVertexShader(Shader *shader);

    void initialize();

    virtual void trans();

    virtual void SetVertices();

    virtual void Draw();

    virtual void startDraw();

    bool isValid();

    GLuint createTexture(const QString &imageFileName);

    Shader*         m_Shader;
    GLuint          VAO;
    QStringList     imageFileNames;
    QList<GLuint>   m_Textures;
};

#endif // ETEXTURE_H
