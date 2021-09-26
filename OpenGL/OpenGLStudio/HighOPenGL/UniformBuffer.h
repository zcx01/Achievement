#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H

#include "../Lighting/Colors.h"
#include "Camera.h"

/**
 *任何大型的渲染程序都可能同时激活有上百个着色器程序，这时候Uniform缓冲对象的优势就会很大地体现出来了。
 * 第一，一次设置很多uniform会比一个一个设置多个uniform要快很多。
 * 第二，比起在多个着色器中修改同样的uniform，在Uniform缓冲中修改一次会更容易一些。
 * 第三，可以在着色器中使用更多的uniform
 */
class Buffer;
class UniformBuffer : public Colors
{
public:
    UniformBuffer();
    void render();

protected:
    void initShader();
    void initialize();


private:

    Buffer* uboMatrices;
};

#endif // UNIFORMBUFFER_H
