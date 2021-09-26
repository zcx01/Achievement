#include "Blending2.h"
#include <QDebug>

Blending2::Blending2()
{

}

void Blending2::initShader()
{
    lightingShader = new Shader;
    lightingShader->AddVertexShader(":/config/HighOPenGL/Blending/vertex.glsl");
    lightingShader->AddFragmentShader(":/config/HighOPenGL/Blending/fragment2.glsl");
    lightingShader->Link();
}

void Blending2::initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Blending::initialize();
    grassTexture->RemoveAt(0);
    grassTexture->CreateTexture(":/config/HighOPenGL/window.png");
    lightingShader->Use();
    lightingShader->setInt("texture1",0);

    //解决最前面窗户的透明部分遮蔽了背后的窗户
    QMap<float,QVector3D> tempV3;
    for(int i=0; i< vegetations.size();i++)
    {
        tempV3.insert(camera->GetPosition().distanceToPoint(vegetations.at(i)),vegetations.at(i));
    }
    vegetations = tempV3.values();
    std::reverse(vegetations.begin(),vegetations.end());
}

