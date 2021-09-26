#ifndef MSAA_H
#define MSAA_H
/*******************************************************
    purpose     :	多重采样
*******************************************************/
#include "../Lighting/Colors.h"
#include "Camera.h"

class MSAA : public Colors
{
public:
    MSAA();
    void render();

protected:
    void initShader();
    void initialize();


private:
};

#endif // MSAA_H
