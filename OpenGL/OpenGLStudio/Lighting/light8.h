#ifndef LIGHT8_H
#define LIGHT8_H

#include "Colors.h"

class CTexture2D;
class light8 : public Colors
{
public:
    light8();

    void initialize();
    void render();
private:
    void initShader();

private:
    CTexture2D* texture;
    QList<QVector3D> cubePositions;
    QList<QVector3D> pointLightPositions;
};

#endif // LIGHT8_H
