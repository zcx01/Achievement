#include "Coordinate.h"
#include "Shader.h"
#include <QMatrix4x4>

Coordinate::Coordinate()
{

}

void Coordinate::addVertexShader(Shader *shader)
{
    shader->AddVertexShader(":/config/Coordinate/vertex.glsl");
}

void Coordinate::trans()
{
    QMatrix4x4 model;
    model.rotate(-55.0f,1.0,0.0f,0.0f);

    QMatrix4x4 view;
    view.translate(0.0f,0.0f,-3.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f,this->width()/this->height(),0.1f,100.f);

    glUniformMatrix4fv(glGetUniformLocation(m_Shader->Progrm(),"model"),1,GL_FALSE,model.constData());
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->Progrm(),"view"),1,GL_FALSE,view.constData());
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->Progrm(),"projection"),1,GL_FALSE,projection.constData());
}
