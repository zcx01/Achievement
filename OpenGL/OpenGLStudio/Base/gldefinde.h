#ifndef GLDEFINDE_H
#define GLDEFINDE_H

#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <QString>

struct Vertex
{
    QVector3D Position; //位置向量
    QVector3D Normal;   //法向量
    QVector2D TexCoords;//纹理坐标向量
};

struct Matrix4x4{
    float m[4][4];
    Matrix4x4(const float *d){
        memcpy(m,d,sizeof(Matrix4x4));
    }
    Matrix4x4(const QMatrix4x4 &d){
         memcpy(m,d.constData(),sizeof(Matrix4x4));
    }
    Matrix4x4(){
       memset(m,0,sizeof(Matrix4x4));
    }
};

struct Texture
{
    //纹理类型
    enum TextureType
    {
        Diffuse = 0x1,    //漫反射纹理
        Specular,         //镜面反射纹理
    };

    QString     path;
    int         id;
    TextureType type;
    QString     glslStructName;

    QString getTypeString()
    {
        QString str;
        switch (type)
        {
        case Diffuse:
            str = "texture_diffuse";
            break;
        case Specular:
            str ="texture_specular";
            break;
        default:
            break;
        }
        if(!glslStructName.isEmpty())
            str = glslStructName+"."+str;
        return str;
    }
};
#endif // GLDEFINDE_H
