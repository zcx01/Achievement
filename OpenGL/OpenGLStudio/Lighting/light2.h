#ifndef LIGHT2_H
#define LIGHT2_H

#include "Colors.h"

class light2 : public Colors
{
public:
    light2();

    void initialize();
private:
    void initShader();
};

#endif // LIGHT2_H
