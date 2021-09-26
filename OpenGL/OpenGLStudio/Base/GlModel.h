#ifndef GLMODEL_H
#define GLMODEL_H
#include "Mesh.h"
//#include <vector>
#include <QList>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QOpenGLFunctions_3_3_Core>
class Mesh;
class Shader;
using namespace std;
class GlModel : public QOpenGLFunctions_3_3_Core
{
public:
    GlModel();

    void loadFile(const QString &filePath);

    void Draw(Shader *shader);

    QList<Mesh *> Meshs() const;

private:
    void processNode(aiNode *node, const aiScene *scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    //创建文件 imageFileName(文件名)
    GLuint CreateTexture(const QString &imageFileName);

    QVector3D ai3DToQ3D(const aiVector3D& vaule);
    QVector2D ai3DToQ2D(const aiVector3D &vaule);
    QList<Mesh*>        m_Meshs;
    QString             m_FileDir;
    vector<Texture>     m_Textures;//已经加载过的纹理
};

#endif // GLMODEL_H
