#ifndef ASSIMPMODEL_H
#define ASSIMPMODEL_H

#include "openglwindow.h"
#include <QImage>
#include "Camera.h"
#include "GlModel.h"

class Shader;
class AssimpModel : public OpenGLWindow
{
public:
    AssimpModel();

    void render();

protected:

    virtual void initShader();
    void initialize();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    Shader*         m_Shader;
    Camera*         camera;
    GlModel*        m_GlModel;
    bool            isPress;
    QPoint          lastPos;        //最后的鼠标位置
};

#endif // ASSIMPMODEL_H
