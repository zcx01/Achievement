#ifndef ENVIRONMENTMAPPING_H
#define ENVIRONMENTMAPPING_H

#include "../Lighting/Colors.h"
#include "Camera.h"
#include "CTextureCude.h"
#include "CTexture2D.h"

class EnvironmentMapping : public Colors
{
public:
    EnvironmentMapping(QString cudevertexFileName);
    void render();

protected:
    void initShader();
    void initialize();


private:

    CTextureCude*       m_TextureCude;
    VertexArrayObject*  m_SkyVAO;
    Shader*             m_SkyShader;
    QString             m_Cudefragment;
};

#endif // ENVIRONMENTMAPPING_H
