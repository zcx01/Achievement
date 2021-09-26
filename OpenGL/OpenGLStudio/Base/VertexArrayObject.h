#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <QOpenGLFunctions_3_3_Core>

class VertexArrayObject : protected QOpenGLFunctions_3_3_Core
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind();

    void Create();

    bool isCreate();

    void release();

    void destroy();

    GLuint getId() const;

    //index:指定我们要配置的顶点属性   [因为顶点着色器源码中有<layout(location = 0)>定义了position顶点位置为0]
    //size:指定顶点属性的大小         [顶点属性是一个vec3，它由3个值组成，所以大小是3]
    //stride:步长,连续的顶点属性组之间的间隔   [由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)],如果是精密排列的，也可以设置0
    //offset:表示位置数据在缓冲中起始位置的偏移量 [由于位置数据在数组的开头，所以这里是0]
    void VertexAttribPointerFloat(GLuint index, GLint size, GLsizei stride, const GLint offset);

    //顶点更新的方式[更新顶点属性的内容至新一组数据]
    void VertexAttribDivisor(int index, int divisor);

private:
    GLuint  id;
};

#endif // VERTEXARRAYOBJECT_H
