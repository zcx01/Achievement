#ifndef INSTANTIATION_H
#define INSTANTIATION_H

#include "../Lighting/Colors.h"
#include "Camera.h"

class Instantiation : public Colors
{
public:
    Instantiation();
    void render();

protected:
    void initShader();
    void initialize();


private:
};

#endif // INSTANTIATION_H
