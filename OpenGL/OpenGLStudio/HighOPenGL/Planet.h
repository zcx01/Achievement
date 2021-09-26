#ifndef PLANET_H
#define PLANET_H
/*******************************************************
    purpose     :	小行星带
*******************************************************/
#include "../Lighting/Colors.h"
#include "Camera.h"

class GlModel;

class Planet : public Colors
{
public:
    Planet();
    void render();

protected:
    void initShader();
    void initialize();


private:
    GlModel* m_Planet;
    GlModel* m_Rock;
//    QList<Matrix4x4> m_ModelMatrices;
};

#endif // PLANET_H
