#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <QOpenGLFunctions_3_3_Core>

//帧缓冲
class FrameBuffer : protected QOpenGLFunctions_3_3_Core
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void bind();

    void Create();

    //创建一个2D图像纹理缓冲
    void CreateTexture2D();

    //创建渲染缓冲对象,能够进行深度测试（如果你需要的话还有模板测试）
    void CreateRenderbuffers();

    //深度测试和模板测试大小
    void ChangedImageStorageSize(int w,int h);

    //使用颜色附着纹理
    void bindTexColor2DBuffer();

    bool Check();

    bool isCreate();

    void release();

    void destroy();

    GLuint getId() const;

    GLuint getTexColorBufferId() const;
private:
    GLuint  id;
    GLuint  texColor2DBuffer;
    GLuint  rbo;
};

#endif // FRAMEBUFFER_H
