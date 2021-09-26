#ifndef LIGHT5_H
#define LIGHT5_H

#include "Colors.h"

class CTexture2D;
class light5 : public Colors
{
public:
    light5();

    void initialize();
    void render();
private:
    void initShader();
    void renderOver();

private:
    CTexture2D* texture;
    QList<QVector3D> cubePositions;
};

#endif // LIGHT5_H
