#ifndef SKYBOX_H
#define SKYBOX_H

#include "../Lighting/Colors.h"
#include "Camera.h"

class CTextureCude;
class CTexture2D;
class VertexArrayObject;
class Skybox : public Colors
{
public:
    Skybox();
    void render();

protected:
    void initShader();
    void initialize();
private:
    CTextureCude*       m_TextureCude;
    VertexArrayObject*  m_SkyVAO;
    Shader*             m_SkyShader;
    CTexture2D*         m_cudeTexture;

};

#endif // SKYBOX_H
