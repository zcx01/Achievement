#ifndef SHADER_H
#define SHADER_H
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>

//着色器
class Shader  : protected QOpenGLFunctions_3_3_Core
{
public:
    Shader();
    ~Shader();

    bool AddVertexShader(const QString &fileName);

    bool AddFragmentShader(const QString &fileName);

    bool AddGeometry(const QString &fileName);

    void setMat4(QString name, QMatrix4x4 mat4);

    void setVec3(QString name,const QVector3D &vec3);

    void setVec3(QString name,const float &f1,const float &f2,const float &f3);

    void setVec2(QString name,const QVector2D &vec2);

    void setFloat(QString name,const float &f);

    void setInt(QString name, const int &i);

    bool Link();

    void Use();

    GLuint Progrm();

    GLuint GetUniformLocation(const QString &name);

    //将着色器的Uniform块设置为绑定点0
    void UniformBlockBinding(const QString &name, int uniformBlockBinding);

private:
    bool addShader(const QString &fileName,const GLenum &type);

    bool isValid();

    QList<GLuint>   m_Shaders;
    GLuint          m_ShaderProgrm;
};

#endif // SHADER_H
