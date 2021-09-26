#ifndef BUFFER_H
#define BUFFER_H
#include <QOpenGLFunctions_3_3_Core>

//缓冲对象
class Buffer : protected QOpenGLFunctions_3_3_Core
{
public:
    enum Type
    {
        VertexBuffer        = GL_ARRAY_BUFFER,         // 顶点缓冲对象
        IndexBuffer         = GL_ELEMENT_ARRAY_BUFFER, // 索引缓冲对象
        UniformBuffer       = GL_UNIFORM_BUFFER,       // Uniform缓冲对象
        PixelPackBuffer     = 0x88EB, // GL_PIXEL_PACK_BUFFER
        PixelUnpackBuffer   = 0x88EC,  // GL_PIXEL_UNPACK_BUFFER
    };

    Buffer(Type type);
    ~Buffer();

    void bind();

    void allocate(const void *data, int size);

    void Create();

    bool isCreate();

    void release();

    void destroy();

    GLuint getId() const;

    int getType() const;

    //绑定Uniform缓冲对象到相同的绑定点上
    void bindBufferRange(int uniformBlockBinding,int size,int off=0);

private:
    GLuint  id;
    Type    m_Type;
};

#endif // BUFFER_H
