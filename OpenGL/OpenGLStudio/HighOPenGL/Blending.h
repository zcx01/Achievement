#ifndef BLENDING_H
#define BLENDING_H
#include "TemplateTest.h"

class Blending : public TemplateTest
{
public:
    Blending();

    // OpenGLWindow interface
public:
    void render();
    void initialize();
    void initShader();

protected:
    VertexArrayObject*  transparentVAO;
    CTexture2D*         grassTexture;
    QList<QVector3D>    vegetations;
};

#endif // BLENDING_H
