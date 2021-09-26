#ifndef LIGHT4_H
#define LIGHT4_H

#include "Colors.h"

class CTexture2D;
class light4 : public Colors
{
public:
    light4();

    void initialize();
private:
    void initShader();
    void renderOver();

private:
    CTexture2D* texture;
};

#endif // LIGHT4_H
