#ifndef COORDINATE_H
#define COORDINATE_H

#include "ETexture.h"

class Coordinate : public ETexture
{
public:
    Coordinate();

    // Texture interface
protected:
    void addVertexShader(Shader *shader);
    void trans();
};

#endif // COORDINATE_H
