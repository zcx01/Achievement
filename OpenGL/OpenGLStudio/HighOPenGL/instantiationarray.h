#ifndef INSTANTIATIONARRAY_H
#define INSTANTIATIONARRAY_H

#include "../Lighting/Colors.h"
#include "Camera.h"

class InstantiationArray : public Colors
{
public:
    InstantiationArray();
    void render();

protected:
    void initShader();
    void initialize();


private:
};

#endif // INSTANTIATIONARRAY_H
