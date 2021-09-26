#include "FrameBuffer.h"
#include <QDebug>

FrameBuffer::FrameBuffer()
{
    if(QOpenGLContext::currentContext())
    {
        initializeOpenGLFunctions();
    }
    id = 0;
    texColor2DBuffer = 0;
    rbo = 0;
    Create();
}

FrameBuffer::~FrameBuffer()
{
    destroy();
}

void FrameBuffer::bind()
{
    //绑定激活的(Active)帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER,id);
}

void FrameBuffer::Create()
{
    //创建一个帧缓冲
    glGenFramebuffers(1, &id);
}

void FrameBuffer::CreateTexture2D()
{
    if(!isCreate())
        Create();
    bind();
    // 生成纹理
    glGenTextures(1, &texColor2DBuffer);
    glBindTexture(GL_TEXTURE_2D, texColor2DBuffer);

    //设置为了屏幕大小（尽管这不是必须的）
    //给纹理的data参数传递了NULL（仅仅分配了内存而没有填充它）
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    //不关心环绕方式或多级渐远纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //核效果要设置为GL_CLAMP_TO_EDGE
    /*
     * 原因:
     * 核在对屏幕纹理的边缘进行采样的时候，由于还会对中心像素周围的8个像素进行采样，其实会取到纹理之外的像素
     * 由于环绕方式默认是GL_REPEAT，所以在没有设置的情况下取到的是屏幕另一边的像素，而另一边的像素本不应该对中心像素产生影响，
     * 这就可能会在屏幕边缘产生很奇怪的条纹。
     * 为了消除这一问题，我们可以将屏幕纹理的环绕方式都设置为GL_CLAMP_TO_EDGE。
     * 这样子在取到纹理外的像素时，就能够重复边缘的像素来更精确地估计最终的值了。
    */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    // 将它附加到当前绑定的帧缓冲对象
    //参数1:	帧缓冲的目标（绘制、读取或者两者皆有）
    //参数2:	附件类型
    //GL_COLOR_ATTACHMENT0			颜色附件(最后的0意味着我们可以附加多个颜色附件)
    //GL_DEPTH_ATTACHMENT           深度缓冲
    //GL_STENCIL_ATTACHMENT			模板缓冲
    //GL_DEPTH_STENCIL_ATTACHMENT   将深度和模板缓冲附加为一个纹理(32位数值将包含24位的深度信息和8位的模板信息)
    //参数3:  附加的纹理类型
    //GL_TEXTURE_2D					颜色格式	（和GL_COLOR_ATTACHMENT0、GL_DEPTH_STENCIL_ATTACHMENT对应）
    //GL_DEPTH_COMPONENT            深度缓冲格式（和GL_DEPTH_ATTACHMENT对应）
    //GL_STENCIL_INDEX				模板缓冲格式（和GL_STENCIL_ATTACHMENT对应）
    //参数4:	附加的纹理本身的id
    //参数5:	多级渐远纹理的级别。我们将它保留为0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColor2DBuffer, 0);
}

void FrameBuffer::CreateRenderbuffers()
{
    //创建一个渲染缓冲对象
    glGenRenderbuffers(1, &rbo);

    //绑定渲染缓冲对象
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);

    //创建一个深度和模板渲染缓冲对象
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);

    //解除绑定
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //附加这个渲染缓冲对象
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void FrameBuffer::ChangedImageStorageSize(int w, int h)
{
    if(texColor2DBuffer !=0)
    {
        bindTexColor2DBuffer();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if(rbo != 0)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
     }
}

void FrameBuffer::bindTexColor2DBuffer()
{
    glBindTexture(GL_TEXTURE_2D,texColor2DBuffer);
}

bool FrameBuffer::Check()
{
    //检测当前绑定的帧缓冲
    //返回值
    //GL_FRAMEBUFFER_COMPLETE                       完整帧
    //GL_FRAMEBUFFER_UNDEFINED						默认的帧不存在
    //GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT			没有附加至少一个缓冲
    //GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT  没有附加至少一个图像
    //GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER			没有附加至少一个颜色
    //GL_INVALID_ENUM                               帧不是可读或者可写的
    bool success = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if(!success)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
    release();//记得要解绑帧缓冲，保证我们不会不小心渲染到错误的帧缓冲上
    return success;
}

bool FrameBuffer::isCreate()
{
    return id !=0;
}

void FrameBuffer::release()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void FrameBuffer::destroy()
{
    if(isCreate())
    {
        //删除帧缓冲对象
        glDeleteFramebuffers(1,&id);
        id = 0;
    }
    if(texColor2DBuffer !=0)
    {
        glDeleteTextures(1,&texColor2DBuffer);
        texColor2DBuffer = 0;
    }
    if(rbo != 0)
    {
        glDeleteRenderbuffers(1,&rbo);
        rbo =0;
     }
}

GLuint FrameBuffer::getId() const
{
    return id;
}

GLuint FrameBuffer::getTexColorBufferId() const
{
    return texColor2DBuffer;
}
