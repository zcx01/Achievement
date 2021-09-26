#include "Trans.h"
#include <QMatrix4x4>
#include "Shader.h"

Trans::Trans()
{

}

void Trans::trans()
{
    QMatrix4x4 transform;
    transform.translate(0.5f,-0.5f,0.0f);
    transform.rotate(135,0.0,1.0,0.0f);

    //设置矩阵数据
    //参数1:uniform的位置值
    //参数2:矩阵的数量
    //参数3:是否进行矩阵中行和列的交换
    //参数4:真正的矩阵数据
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->Progrm(),"transform"),1,GL_FALSE,transform.constData());
}

void Trans::addVertexShader(Shader *shader)
{
    shader->AddVertexShader(":/config/Trans/vertex.glsl");
}
