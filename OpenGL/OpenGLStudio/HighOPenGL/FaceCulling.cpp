#include "FaceCulling.h"

FaceCulling::FaceCulling()
{

}

void FaceCulling::initialize()
{
    //启用面剔除,但注意这只对像立方体这样的封闭形状有效
    glEnable(GL_CULL_FACE);

    //改变正向面环绕顺序
    //GL_CCW	逆时针的环绕顺序
    //GL_CW     顺时针的环绕顺序
    //glFrontFace(GL_CW);

    //改变剔除的面的类型
    //GL_BACK           只剔除背向面。(默认)
    //GL_FRONT			只剔除正向面。
    //GL_FRONT_AND_BACK	剔除正向面和背向面。
    //glCullFace(GL_BACK);

    Blending::initialize();
}
