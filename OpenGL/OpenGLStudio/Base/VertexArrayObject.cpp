#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
    glGenVertexArrays(1,&id);
}

VertexArrayObject::~VertexArrayObject()
{
    destroy();
}

void VertexArrayObject::bind()
{
    if(!isCreate()) return;
    glBindVertexArray(id);
}

void VertexArrayObject::Create()
{
    if(isCreate()) return;
    glGenVertexArrays(1,&id);
}

bool VertexArrayObject::isCreate()
{
    return id != 0;
}

void VertexArrayObject::release()
{
    glBindVertexArray(0);
}

void VertexArrayObject::destroy()
{
    if(!isCreate()) return;
    glDeleteVertexArrays(1,&id);
}

GLuint VertexArrayObject::getId() const
{
    return id;
}

void VertexArrayObject::VertexAttribPointerFloat(GLuint index, GLint size, GLsizei stride, const GLint offset)
{
    glEnableVertexAttribArray(index);

    //参数1:指定我们要配置的顶点属性   [因为顶点着色器源码中有<layout(location = 0)>定义了position顶点位置为0]
    //参数2:指定顶点属性的大小         [顶点属性是一个vec3，它由3个值组成，所以大小是3]
    //参数3:参数指定数据的类型
    //参数4:是否数据标准化               [如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间]
    //参数5:步长,连续的顶点属性组之间的间隔   [由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)],如果是精密排列的，也可以设置0
    //参数6:表示位置数据在缓冲中起始位置的偏移量 [由于位置数据在数组的开头，所以这里是0]
    glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,stride* sizeof(float),(void*)(offset*sizeof(float)));
}

void VertexArrayObject::VertexAttribDivisor(int index, int divisor)
{
    //该什么时候更新顶点属性的内容至新一组数据
    //参数1:需要的顶点属性的索引
    //参数2:参数是属性除数
    //      0，每次迭代时更新顶点属性
    //      1，渲染一个新实例的时候更新顶点属性
    //      n，渲染n个新实例的时候更新顶点属性
    glVertexAttribDivisor(index , divisor);
}
