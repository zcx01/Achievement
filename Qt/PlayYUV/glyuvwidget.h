#ifndef GLYUVWIDGET_H
#define GLYUVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QOpenGLFunctions>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)

class GLYuvWidget  : public QOpenGLWidget,QOpenGLFunctions
{
    Q_OBJECT
public:
    GLYuvWidget(QWidget* parent =nullptr);
    ~GLYuvWidget();
    QWidget* setParentWidget(QWidget* parent);

public slots:
    void slotShowYuv(uchar *ptr,uint width,uint height); //显示一帧Yuv图像

protected:
    void initializeGL() ;
    void paintGL() ;

private:
    void drawYUV420p();
    void drawYUV422p();
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    GLuint textureUniformY,textureUniformU,textureUniformV,textFrame; //opengl中y、u、v分量位置
    QOpenGLTexture *textureY = nullptr,*textureU = nullptr,*textureV = nullptr;
    QOpenGLShader *vshader=nullptr,*fshader=nullptr;
    GLuint idY,idU,idV; //自己创建的纹理对象ID，创建错误返回0
    uint videoW,videoH;
    uchar *yuvPtr = nullptr;
    QWidget * widget=nullptr;
};

#endif // GLYUVWIDGET_H
