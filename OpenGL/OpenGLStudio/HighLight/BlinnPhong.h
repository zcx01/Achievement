#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "../Lighting/Colors.h"
#include "Camera.h"
#include "CTexture2D.h"

//BlinnPhong光照（使用半程向量代替镜面反射）
class BlinnPhong : public Colors
{
public:
    BlinnPhong();
    void render();

protected:
    void initShader();
    void initialize();
    void keyPressEvent(QKeyEvent *event);


private:
    CTexture2D* m_Texture;
    bool        m_Blinn;
};

#endif // BLINNPHONG_H
