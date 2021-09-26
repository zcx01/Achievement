#ifndef COLORS_H
#define COLORS_H

#include "openglwindow.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "Camera.h"

/**
 * @brief The Colors class
 * 继承此类仅仅用于鼠标、键盘事件和摄像机绑定
 */
class Colors : public OpenGLWindow
{
public:
    Colors();
    ~Colors();

    // OpenGLWindow interface
public:
    void initialize();
    void render();
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    virtual void renderOver();

    Shader* GetShader(const QString &fileName);

    bool CreateShader(const QString &dirPath);
protected:
    virtual void initShader();

    VertexArrayObject*      cudeVAO;
    VertexArrayObject*      lightVAO;
    Shader*                 lightingShader;
    Shader*                 lampgShader;
    Camera*                 camera;
    bool                    isPress;
    QPoint                  lastPos;        //最后的鼠标位置
    QHash<QString,Shader*>  m_Shaders;      //着色器
};

#endif // COLORS_H
