#include "Shader.h"
#include <QFile>
#include <QDebug>
#include <QOpenGLContext>
//#include <QOpenGLShaderProgram>


Shader::Shader()
{
    m_ShaderProgrm = 0;
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
}

Shader::~Shader()
{
    for(int i =0; i < m_Shaders.size(); i++)
    {
        glDeleteShader(m_Shaders.at(i));
    }
    m_Shaders.clear();
}

bool Shader::AddVertexShader(const QString &fileName)
{
    return addShader(fileName,GL_VERTEX_SHADER);
}

bool Shader::AddFragmentShader(const QString &fileName)
{
    return addShader(fileName,GL_FRAGMENT_SHADER);
}

bool Shader::AddGeometry(const QString &fileName)
{
    return addShader(fileName,GL_GEOMETRY_SHADER);
}

void Shader::setMat4(QString name, QMatrix4x4 mat4)
{
    //设置矩阵数据
    //参数1:uniform的位置值
    //参数2:矩阵的数量
    //参数3:是否进行矩阵中行和列的交换
    //参数4:真正的矩阵数据
    glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,mat4.constData());
}

void Shader::setVec3(QString name, const QVector3D &vec3)
{
    glUniform3fv(GetUniformLocation(name), 1, reinterpret_cast<const GLfloat *>(&vec3));
}

void Shader::setVec3(QString name, const float &f1, const float &f2, const float &f3)
{
    setVec3(name,QVector3D(f1,f2,f3));
}

void Shader::setVec2(QString name, const QVector2D &vec2)
{
    glUniform2fv(GetUniformLocation(name), 1, reinterpret_cast<const GLfloat *>(&vec2));
}

void Shader::setFloat(QString name, const float &f)
{
    glUniform1fv(GetUniformLocation(name),1,&f);
}

void Shader::setInt(QString name, const int &i)
{
    glUniform1i(GetUniformLocation(name),i);
}

bool Shader::Link()
{
    //创建一个程序对象
    if(!QOpenGLContext::currentContext()) return false;

    m_ShaderProgrm = glCreateProgram();

    for(int i =0; i < m_Shaders.size(); i++)
    {
        glAttachShader(m_ShaderProgrm,m_Shaders.at(i));
    }
    //链接
    glLinkProgram(m_ShaderProgrm);

    //检查是否成功
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_ShaderProgrm,GL_LINK_STATUS,&success);

    if(!success)
    {
        glGetProgramInfoLog(m_ShaderProgrm,512,NULL,infoLog);
        qDebug()<< "link error" <<infoLog;
    }

    glUseProgram(m_ShaderProgrm);
    for(int i =0; i < m_Shaders.size(); i++)
    {
        glDeleteShader(m_Shaders.at(i));
    }
    m_Shaders.clear();
    return success;
}

void Shader::Use()
{
    if(!isValid()) return;
    glUseProgram(m_ShaderProgrm);
}

GLuint Shader::Progrm()
{
    return m_ShaderProgrm;
}

GLuint Shader::GetUniformLocation(const QString &name)
{
    int index = glGetUniformLocation(m_ShaderProgrm,name.toStdString().c_str());
    if(index == -1)
    {
        qDebug()<<"未找到"<<name;
    }
    return index;
}

//通过glUniformBlockBinding函数将Uniform缓冲链接至它
void Shader::UniformBlockBinding(const QString &name, int uniformBlockBinding)
{

    GLuint index = glGetUniformBlockIndex(m_ShaderProgrm,name.toStdString().c_str());

    //参数1:一个程序对象
    //参数2:Uniform块索引(着色器中已定义Uniform块的位置值索引),可以通过glGetUniformBlockIndex[接受一个程序对象和Uniform块的名称]获取
    glUniformBlockBinding(m_ShaderProgrm,index, uniformBlockBinding);
}

bool Shader::addShader(const QString &fileName,const GLenum &type)
{
    if(!QOpenGLContext::currentContext()) return false;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) return false;

    //创建顶点着色器
    /*
     * GL_VERTEX_SHADER:顶点着色器
     * GL_FRAGMENT_SHADER:片段着色器
     * */
    GLuint shader = glCreateShader(type);
    QByteArray byte = file.readAll();

    const char *shaderSource  = byte.constBegin();

    //把这个着色器源码附加到着色器对象上
    glShaderSource(shader,1,&shaderSource,NULL);

    //编译已存储在shader指定的着色器对象中的源代码字符串
    glCompileShader(shader);

    //检查是否成功
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        qDebug()<<"shader error" << infoLog;
    }
    m_Shaders << shader;
    return success;
}

bool Shader::isValid()
{
    return m_ShaderProgrm != 0;
}
