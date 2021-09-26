#ifndef TEMPLATETEST_H
#define TEMPLATETEST_H

#include "../Lighting/Colors.h"
#include "Camera.h"
#include "CTexture2D.h"

class TemplateTest : public Colors
{
public:
    TemplateTest();
    void render();

protected:
    void initShader();
    void initialize();



    VertexArrayObject*   planeVAO;
    CTexture2D*          floorTexture;
    CTexture2D*          texture;

};

#endif // TEMPLATETEST_H
