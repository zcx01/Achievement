#ifndef TRANS_H
#define TRANS_H
#include "ETexture.h"

class Trans : public ETexture
{
public:
    Trans();

    // OpenGLWindow interface
public:
    void trans();

    void addVertexShader(Shader *shader);
};

#endif // TRANS_H
