#include "GlModel.h"
#include <iostream>
#include <QFileInfo>
#include <QImage>
GlModel::GlModel()
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
}

void GlModel::loadFile(const QString &filePath)
{
    Assimp::Importer import;
    //aiProcess_Triangulate         如果模型不是（全部）由三角形组成，它需要将模型所有的图元形状变换为三角形
    //aiProcess_FlipUVs             将在处理的时候翻转y轴的纹理坐标
    //aiProcess_GenNormals          如果模型不包含法向量的话，就为每个顶点创建法线
    //aiProcess_SplitLargeMeshes    将比较大的网格分割成更小的子网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，那么它会非常有用
    //aiProcess_OptimizeMeshes      和上个选项相反，它会将多个小网格拼接为一个大的网格，减少绘制调用从而进行优化。
    const aiScene *scene = import.ReadFile(filePath.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
//    directory = path.substr(0, path.find_last_of('/'));
    QFileInfo fileInfo(filePath);
    m_FileDir = fileInfo.absolutePath();
    processNode(scene->mRootNode, scene);
}

void GlModel::Draw(Shader *shader)
{
    for(int i =0; i < m_Meshs.size(); i++)
    {
        m_Meshs[i]->Draw(shader);
    }
}

void GlModel::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshs.push_back(processMesh(mesh, scene));
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh *GlModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        vertex.Position = ai3DToQ3D(mesh->mVertices[i]);
        vertex.Normal = ai3DToQ3D(mesh->mNormals[i]);

        // 网格是否有纹理坐标？
        if(mesh->mTextureCoords[0])
        {
            vertex.TexCoords = ai3DToQ2D(mesh->mTextureCoords[0][i]);
        }
        vertices.push_back(vertex);
    }
    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // 处理材质
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return new Mesh(vertices, indices, textures);
}

vector<Texture> GlModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        QString fileName(str.C_Str());
        bool skip = false;
        for(unsigned int j = 0; j < m_Textures.size(); j++)
        {
            if(m_Textures[j].path == fileName)
            {
                textures.push_back(m_Textures[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            Texture texture;
            QString filePath = m_FileDir + "/" + fileName;
            texture.path = fileName;
            texture.id = CreateTexture(filePath);
            texture.type = (Texture::TextureType)(int)type;
            textures.push_back(texture);
        }
    }
    return textures;
}

GLuint GlModel::CreateTexture(const QString &imageFileName)
{
    QImage  image(imageFileName);

    image = image.convertToFormat(QImage::Format_ARGB32);

    GLuint texture;
    //-------------------------------------生成纹理------------------------
    //参数1:生成纹理的数量
    //参数2:纹理的ID
    glGenTextures(1,&texture);

    //-------------------------------------绑定纹理------------------------
    glBindTexture(GL_TEXTURE_2D,texture);

    //-------------------------------------纹理的环绕方式-------------------
    //参数1:指定纹理目标					GL_TEXTURE_2D表示2D纹理
    //参数2:设置的选项与应用的纹理轴		配置了WRAP选项，并且指定了S和T (S、T、R等价于x、y、z)
    //参数3:激活指定的纹理环绕方式       处理超出范围之外的纹理坐标
    //			方式							描述
    //		GL_REPEAT						重复纹理图像(默认)
    //		GL_MIRRORED_REPEAT				重复纹理图形，不过是镜像放置
    //		GL_CLAMP_TO_EDGE				拉伸纹理边缘
    //		GL_CLAMP_TO_BORDER				超出的坐标为用户指定的边缘颜色
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);


    //-------------------------------------纹理过滤-------------------
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //-------------------------------------生成图片纹理------------------------
    //参数1:纹理目标
    //参数2:纹理指定多级渐远纹理的级别 0 (基本基本)
    //参数3:纹理存储格式
    //参数4:纹理的宽度
    //参数5:纹理的高度
    //参数6:总是设置0
    //参数7:源图的格式 GL_BGRA(要判断大小端，此电脑是little-endian 系统)
    //参数8:数据类型
    //参数9:真正的图形数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, image.width(), image.height(), 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
    //如果没有设置纹理的级别，调用此函数为当前绑定的纹理自动生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

QVector3D GlModel::ai3DToQ3D(const aiVector3D& vaule)
{
    return QVector3D(vaule.x,vaule.y,vaule.z);
}

QVector2D GlModel::ai3DToQ2D(const aiVector3D& vaule)
{
    return QVector2D(vaule.x,vaule.y);
}

QList<Mesh *> GlModel::Meshs() const
{
    return m_Meshs;
}
