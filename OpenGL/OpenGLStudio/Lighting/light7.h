#ifndef LIGHT7_H
#define LIGHT7_H

#include "Colors.h"

class CTexture2D;
class light7 : public Colors
{
public:
    light7();

    void initialize();
    void render();
private:
    void initShader();
    void renderOver();

private:
    CTexture2D* texture;
    QList<QVector3D> cubePositions;
};

#endif // LIGHT7_H
