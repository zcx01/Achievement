#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../Lighting/Colors.h"
#include "Camera.h"

class Geometry : public Colors
{
public:
    Geometry();
    void render();

protected:
    void initShader();
    void initialize();


private:
};

#endif // GEOMETRY_H
