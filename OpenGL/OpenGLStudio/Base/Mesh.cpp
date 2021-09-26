#include "Mesh.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArrayObject.h"

Mesh::Mesh(const vector<Vertex> &v, const vector<unsigned int> &i, const vector<Texture> &t)
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
    vertices = v;
    indices = i;
    textures = t;
    setupMesh();
}

Mesh::~Mesh()
{
    delete VAO;
    delete VBO;
    delete EBO;
}

void Mesh::Draw(Shader *shader)
{
    Draw(shader,0);
}

void Mesh::Draw(Shader *shader, const int &num)
{
    if(!shader) return;
    int diffuseNr = 1;
    int specularNr = 1;
    for(unsigned int i =0; i < textures.size(); i++)
    {
        Texture  texture = textures.at(i);
        glActiveTexture(GL_TEXTURE0 + i);
        int number=0;
        if(texture.type == Texture::Diffuse)
        {
            number = diffuseNr;
            diffuseNr++;
        }
        else if(texture.type == Texture::Specular)
        {
            number = specularNr;
            specularNr++;
        }
        shader->setInt(texture.getTypeString()+QString::number(number),i);
        glBindTexture(GL_TEXTURE_2D,texture.id);
    }
    glActiveTexture(GL_TEXTURE0);
    VAO->bind();

    if(num == 0){
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }else{
        glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0,num);
    }
    VAO->release();
}

void Mesh::setupMesh()
{
    VAO = new VertexArrayObject;

    VBO = new Buffer(Buffer::VertexBuffer);
    EBO = new Buffer(Buffer::IndexBuffer);

    VAO->bind();
    VBO->bind();

    if(vertices.size() != 0)
        VBO->allocate(&vertices[0],vertices.size() * sizeof(Vertex));

    EBO->bind();
    if(indices.size() != 0)
        EBO->allocate(&indices[0],indices.size() * sizeof(unsigned int));

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    VAO->release();
}

VertexArrayObject *Mesh::getVAO() const
{
    return VAO;
}
