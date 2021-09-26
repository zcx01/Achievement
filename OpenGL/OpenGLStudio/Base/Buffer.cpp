#include "Buffer.h"

Buffer::Buffer(Type type) : m_Type(type)
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
    //生成一个对象
    glGenBuffers(1,&id);
    bind();
}

Buffer::~Buffer()
{
//------不能删除
//    destroy();
}

void Buffer::Create()
{
    if(isCreate()) return;
    glGenBuffers(1,&id);
}

bool Buffer::isCreate()
{
    return id != 0;
}

void Buffer::bind()
{
    //绑定缓冲
    /*
    GL_ARRAY_BUFFER         ：顶点缓冲对象
    GL_ELEMENT_ARRAY_BUFFER ：索引缓冲对象
    */
    glBindBuffer(m_Type,id);
}

void Buffer::allocate(const void *data, int size)
{
    //设置缓冲内存的数据
    /*
     *参数1:目标缓冲的类型
     *参数2:指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行
     *参数3:参数是我们希望发送的实际数据
     *
     *参数4:指定了我们希望显卡如何管理给定的数据。它有三种形式：
     *GL_STATIC_DRAW ：数据不会或几乎不会改变。
     *GL_DYNAMIC_DRAW：数据会被改变很多。
     *GL_STREAM_DRAW ：数据每次绘制时都会改变。
    */
    glBufferData(m_Type,size,data,GL_STATIC_DRAW);
}

void Buffer::bindBufferRange(int uniformBlockBinding, int size, int off)
{
    glBindBufferRange(m_Type,uniformBlockBinding,id,off,size);
}

int Buffer::getType() const
{
    return (int)m_Type;
}

void Buffer::release()
{
    glBindBuffer(m_Type,0);
}

void Buffer::destroy()
{
    if(!isCreate()) return;
    glDeleteBuffers(1,&id);
    id = 0;
}

GLuint Buffer::getId() const
{
    return id;
}
