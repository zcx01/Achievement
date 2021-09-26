#ifndef MESH_H
#define MESH_H

#include "vector"
#include "gldefinde.h"
#include <QOpenGLFunctions_3_3_Core>
class Shader;
class Buffer;
class VertexArrayObject;


using namespace std;
/*网格类*/
class Mesh : protected QOpenGLFunctions_3_3_Core
{
public:
    Mesh(const vector<Vertex> &v,const vector<unsigned int> &i,const vector<Texture> &t);
    ~Mesh();

    /*  网格数据  */
    vector<Vertex> vertices;/*顶点属性*/
    vector<unsigned int> indices;/*顶点索引*/
    vector<Texture> textures;/*纹理贴图*/

    void Draw(Shader *shader);
    void Draw(Shader *shader,const int &num);
    VertexArrayObject *getVAO() const;
private:
    void setupMesh();
    VertexArrayObject*  VAO;
    Buffer*             VBO;//顶点缓冲对象
    Buffer*             EBO;

};

#endif // MESH_H
