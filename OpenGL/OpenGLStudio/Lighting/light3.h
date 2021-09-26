#ifndef LIGHT3_H
#define LIGHT3_H

#include "Colors.h"

class light3 : public Colors
{
public:
    light3();

    void initialize();
private:
    void initShader();
    void renderOver();
};

#endif // LIGHT3_H
