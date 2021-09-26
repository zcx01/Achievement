#ifndef CUDE_H
#define CUDE_H

#include "ETexture.h"

class Cude  : public ETexture
{
public:
    Cude();

    // Texture interface
protected:
    void initialize();
    void addVertexShader(Shader *shader);
    void trans();
    void Draw();

    QList<QVector3D> cubePositions;
};

#endif // CUDE_H
