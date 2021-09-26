#ifndef LIGHT6_H
#define LIGHT6_H

#include "Colors.h"

class CTexture2D;
class light6 : public Colors
{
public:
    light6();

    void initialize();
    void render();
private:
    void initShader();
    void renderOver();

private:
    CTexture2D* texture;
    QList<QVector3D> cubePositions;
};

#endif // LIGHT6_H
